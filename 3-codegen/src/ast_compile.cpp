#include "ast.hpp"

#include <string>
#include <regex>

static int makeNameUnq=0;

static std::string makeName(std::string base)
{
  return "_"+base+"_"+std::to_string(makeNameUnq++);
}

void CompileRec(
  std::string destReg,    // The name of the register to put the result in
  TreePtr program
){
  std::regex reNum("^-?[0-9]+$");
  std::regex reId("^[a-z][a-z0-9]*$");

  if( regex_match( program->type, reNum ) ){
    std::cout<<"const "<<destReg<<" "<<program->type<<std::endl;

  }else if( regex_match( program->type, reId ) ){
    std::string zero = makeName("zero");
    std::cout<<"const "<<zero<<" 0"<<std::endl;
    std::cout<<"add "<<destReg<<" "<<program->type<<" "<<zero<<std::endl;

  }else if(program->type=="Param"){
    std::cout<<"param "<<destReg<<" "<<program->value<<std::endl;

  }else if(program->type=="Seq"){
    for(unsigned i=0; i<program->branches.size(); i++){
      CompileRec(destReg, program->branches[i]);
    }
    // TODO : handle the others
  }else if(program->type=="Assign"){
    CompileRec(program->value,program->branches.at(0));
  }else if(program->type=="Add"){
    if( regex_match( (program->branches.at(0))->type, reNum)){
      std::cout<<"const "<<(program->branches.at(0))->type<<" "<<(program->branches.at(0))->type<<std::endl;
    }else if( regex_match( (program->branches.at(1))->type, reNum )){
      std::cout<<"const "<<(program->branches.at(1))->type<<" "<<(program->branches.at(1))->type<<std::endl;
    }
      std::cout<<"add "<<destReg<<" "<<(program->branches.at(0))->type<<" "<<(program->branches.at(1))->type<<std::endl;
  }else if(program->type=="Output"){
    std::cout<<"output " <<(program->branches.at(0))->type<<std::endl;
    CompileRec(destReg,program->branches.at(0));
  }else if(program->type=="Input"){
    std::cout<<"input "<<destReg<<std::endl;
  //  CompileRec(destReg,program->branches.at(0));
  }else if(program->type=="LessThan"){
    if( regex_match( (program->branches.at(0))->type, reNum)){
      std::cout<<"const "<<(program->branches.at(0))->type<<" "<<(program->branches.at(0))->type<<std::endl;
    }else if( regex_match( (program->branches.at(1))->type, reNum )){
      std::cout<<"const "<<(program->branches.at(1))->type<<" "<<(program->branches.at(1))->type<<std::endl;
    }
    std::cout<<"lt "<<destReg<<" "<<(program->branches.at(0))->type<<" "<<(program->branches.at(1))->type<<std::endl;
    //CompileRec((program->branches.at(0))->type,program->branches.at(0));
  }else if(program->type=="Sub"){
    if( regex_match( (program->branches.at(0))->type, reNum)){
      std::cout<<"const "<<(program->branches.at(0))->type<<" "<<(program->branches.at(0))->type<<std::endl;
    }else if( regex_match( (program->branches.at(1))->type, reNum )){
      std::cout<<"const "<<(program->branches.at(1))->type<<" "<<(program->branches.at(1))->type<<std::endl;
    }
    std::cout<<"sub "<<destReg<<" "<<(program->branches.at(0))->type<<" "<<(program->branches.at(1))->type<<std::endl;
  }else if(program->type=="If"){
    std::string ifelse = makeName("else");
    std::string jump = makeName("jump");
    std::string zero = makeName("zero");
    std::cout << "const " << zero << " 0"<< std::endl;
    CompileRec((program->branches.at(0))->type,program->branches.at(0));
    std::cout << "beq " << (program->branches.at(0))->type << " " << zero << " " << ifelse <<std::endl;
    CompileRec(destReg,program->branches.at(1));
    std::cout<<"beq " << zero << " " << zero << " " << jump <<std::endl;
    std::cout << ":" << ifelse << std::endl;
    CompileRec(destReg,program->branches.at(2));
    std::cout << ":" << jump << std::endl;

  }else if(program->type=="While"){
    std::string labeltop = makeName("top");
    std::string labelbottom = makeName("bottom");
    std::string zero = makeName("zero");
    std::cout << ":" << labeltop << std::endl;
    std::cout << "const " << zero << " 0"<< std::endl;
    std::cout << "beq " << (program->branches.at(0))->type << " " << zero << " " << labelbottom <<std::endl;
    CompileRec((program->branches.at(0))->type,program->branches.at(1));
    std::cout<<"beq " << zero << " " << zero << " " << labeltop <<std::endl;
    std::cout<<":"<<labelbottom<<std::endl;
    CompileRec(destReg,program->branches.at(0));
  }else{
    throw std::runtime_error("Unknown construct '"+program->type+"'");
  }
}

void Compile(
    TreePtr program
){
    // Create a register to hold the final result
    std::string res=makeName("res");

    // Compile the whole thing
    CompileRec(res, program);

    // Put the result out
    std::cout<<"halt "<<res<<"\n";
}
