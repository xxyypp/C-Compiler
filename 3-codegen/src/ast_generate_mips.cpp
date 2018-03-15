#include "ast.hpp"

#include <string>
#include <regex>
#include <fstream>
#include <cstdlib>

static int makeNameUnq=0;
static std::string makeName(std::string base)
{
  return "_"+base+"_"+std::to_string(makeNameUnq++);
}

void generate_m(
  std::string destReg,    // The name of the register to put the result in
  TreePtr program
){
  std::ofstream output;
  output.open("output.cpp", std::ios_base::app);
  std::regex reNum("^-?[0-9]+$");
  std::regex reId("^[a-z][a-z0-9]*$");

  if( regex_match( program->type, reNum ) ){
    output<<"int "<<destReg<<"="<<program->type<<";"<<std::endl;

  }else if( regex_match( program->type, reId ) ){
    std::string zero = makeName("zero");
    output<<"int "<<zero<<"= 0 ;"<<std::endl;
    output<<"int "<<destReg<<"="<<program->type<<"; "<<std::endl;

  }else if(program->type=="Param"){
    output<< "int "<<destReg << " = "<<"std::atol(argv["<<program->value<<"]);"<<std::endl;

  }else if(program->type=="Seq"){
    for(unsigned i=0; i<program->branches.size(); i++){
      generate_m(destReg, program->branches[i]);
    }
    // TODO : handle the others
  }else if(program->type=="Assign"){
    generate_m(program->value,program->branches.at(0));
  }else if(program->type=="Add"){
      std::string reg1 = makeName("reg");
      std::string reg2 = makeName("reg");
      generate_m(reg1,program->branches.at(0));
      generate_m(reg2,program->branches.at(1));
      output<<"int "<<destReg<<"="<<reg1<<"+"<<reg2<<";"<<std::endl;
  }else if(program->type=="Output"){
    output<<"std::cin << " <<(program->branches.at(0))->type<<";" << std::endl;
    generate_m(destReg,program->branches.at(0));
  }else if(program->type=="Input"){
    output<<"std::cin << "<<destReg << ";" <<std::endl;
  //  generate_m(destReg,program->branches.at(0));
  }else if(program->type=="LessThan"){
    std::string reg1 = makeName("reg");
    std::string reg2 = makeName("reg");
    generate_m(reg1,program->branches.at(0));
    generate_m(reg2,program->branches.at(1));
    //std::cout<<"lt "<<destReg<<" "<<(program->branches.at(0))->type<<" "<<(program->branches.at(1))->type<<std::endl;
    /*output << "if (_reg_1 < _reg_2){ \n";
    output << " return 1; \n";
    output << "}else{ \n";
    output << " return 0; \n";
    output << "}";*/
    output << "int _res_0;" << "\n";
    output <<  destReg << "=" << reg1 << " < "<< reg2 << ";" << "\n";
    //generate_m((program->branches.at(0))->type,program->branches.at(0));
  }else if(program->type=="Sub"){
    std::string reg1 = makeName("reg");
    std::string reg2 = makeName("reg");
    generate_m(reg1,program->branches.at(0));
    generate_m(reg2,program->branches.at(1));
    output<<"int "<<destReg<<"="<<reg1<<"-"<<reg2<<";"<<std::endl;
  }else if(program->type=="If"){
  /*  std::string ifelse = makeName("else");
    std::string jump = makeName("jump");
    std::string zero = makeName("zero");
    std::cout << "const " << zero << " 0"<< std::endl;
    generate_m((program->branches.at(0))->type,program->branches.at(0));
    std::cout << "beq " << (program->branches.at(0))->type << " " << zero << " " << ifelse <<std::endl;
    generate_m(destReg,program->branches.at(1));
    std::cout<<"beq " << zero << " " << zero << " " << jump <<std::endl;
    std::cout << ":" << ifelse << std::endl;
    generate_m(destReg,program->branches.at(2));
    std::cout << ":" << jump << std::endl;
    */
    std::string reg1 = makeName("reg");
    generate_m(reg1,program->branches.at(0));
    std::string reg2 = makeName("reg");
    generate_m(reg2,program->branches.at(1));
    std::string reg3 = makeName("reg");
    generate_m(reg3,program->branches.at(2));
    output <<"int "<<destReg << ";" << "\n";
    output << "if (_reg_1 != 0){" << "\n";
    output <<destReg<<"="<<reg2 << ";"<<std::endl;
    output << "}else{" << "\n";
    output <<destReg<<"="<<reg3 << ";"<<std::endl;
    output << "}" << std::endl;

  }else if(program->type=="While"){
    std::string labeltop = makeName("top");
    std::string labelbottom = makeName("bottom");
    std::string zero = makeName("zero");
    std::cout << ":" << labeltop << std::endl;
    std::cout << "const " << zero << " 0"<< std::endl;
    std::cout << "beq " << (program->branches.at(0))->type << " " << zero << " " << labelbottom <<std::endl;
    generate_m((program->branches.at(0))->type,program->branches.at(1));
    std::cout<<"beq " << zero << " " << zero << " " << labeltop <<std::endl;
    std::cout<<":"<<labelbottom<<std::endl;
    generate_m(destReg,program->branches.at(0));
  }else{
    throw std::runtime_error("Unknown construct '"+program->type+"'");
  }
}

void Compile(
    TreePtr program
){
    // Create a register to hold the final result
    std::string res=makeName("res");
    std::ofstream output;
    output.open("output.cpp");
    output << "#include <iostream>" << "\n";
    output << "#include <cstdlib>" << "\n";
    output << std::endl;
    output << "int main(int argc, char *argv[]) { \n";
    output.close();
    // Compile the whole thing
    generate_m(res, program);
    output.open("output.cpp",std::ios_base::app);
    output<<"return " << res <<";"<<"\n";
    output << "}\n";
}
