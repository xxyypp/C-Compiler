#include "ast.hpp"

#include <regex>
#include <cstdlib>
#include <fstream>
#include <string>

extern int flagadd = 0;
extern int flagsub = 0;
extern int flagother = 0;

int32_t const_f(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr &program
){
    //flagadd = false;
    //bool flatsub = false;
    std::regex reNum("^-?[0-9]+$");//decimal number
    std::regex reId("^[a-z][a-z0-9]*$");//variable

    if( regex_match(program->type, reNum) ){
        return std::atol(program->type.c_str());
    }else if( regex_match(program->type, reId) ){ // TODO : Check for things matching reId

        return (context.bindings[program->type]);

    }else if(program->type=="Add"){
        int32_t v1 = const_f(context,program->branches.at(0));
        int32_t v2 = const_f(context,program->branches.at(1));

        if((regex_match(((program->branches.at(0))->type),reNum))&&(regex_match(((program->branches.at(1))->type),reNum))){
          int32_t res = v1 + v2;
          program->type = std::to_string(res);
          program->branches.clear();
          flagadd = 1;
          //std::cout << "changed in add" << '\n';

          return 1; //branches changed
        }
        flagadd = 0;
        return v1+v2; //branches not changed
    }else if(program->type=="Sub"){
      int32_t v1 = const_f(context,program->branches.at(0));
      int32_t v2 = const_f(context,program->branches.at(1));

      if((regex_match(((program->branches.at(0))->type),reNum))&&(regex_match(((program->branches.at(1))->type),reNum))){
        int32_t res = v1 - v2;
        program->type = std::to_string(res);
        program->branches.clear();
        flagsub = 1;

        return 1; //branches changed
      }
      flagsub = 0;
      return v1-v2; //branches not changed

    }else if(program->type=="Param"){
        unsigned index=atol(program->value.c_str());
        auto value=context.params.at(index);
        return value;

    }else if(program->type=="Output"){
        int32_t val=const_f(context, program->branches.at(0));
        std::cout<<val<<std::endl;
        return val;

        // TODO: Handle other constructs
    }else if(program->type=="Input"){
        int32_t val;
        std::cin >> val;
        return val;
    }else if(program->type=="LessThan"){
        int32_t v1 = const_f(context,program->branches.at(0));
        int32_t v2 = const_f(context,program->branches.at(1));
        if(v1 < v2){
          return 1;
        }else{
          return 0;
        }
    }else if(program->type=="Assign"){
        auto it = context.bindings.find(program->value);
        if(it != context.bindings.end()){
          context.bindings[program->type] = std::atol(program->value.c_str());
        }
        int32_t val=const_f(context, program->branches.at(0));
        context.bindings[program->value] = val;
        //std::cout << "input test: " << val << std::endl;
        return val;

    }else if(program->type=="Seq"){
        int32_t temp;
        for(unsigned int i=0; i<program->branches.size(); i++){
              temp = const_f(context, program->branches[i]);
        }
        return temp;
    }else if(program->type=="If"){
        int32_t v1 = const_f(context,program->branches.at(0));
        if (v1 != 0){
          int32_t v2 = const_f(context,program->branches.at(1));
          return v2;
        }else{
          int32_t v3 = const_f(context,program->branches.at(2));
          return v3;
        }
    }else if(program->type=="While"){
        int32_t v1 = const_f(context,program->branches.at(0));
        while (v1 != 0){
          v1 = const_f(context,program->branches.at(1));
        }
        return 0;
    }else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }/*else{
        int32_t ret =0;

        for(auto it = program->branches.begin(); it != program->branches.end();it++){
          if (const_f(context,*it)&&(flagadd == 1 ||flagsub == 1)){
            std::cout << "changed in auto" << '\n';
            return 1;
          }
          return 0;
        }

        //throw std::runtime_error("Unknown construct '"+program->type+"'");
    }*/
}

int main(int argc, char *argv[])
{
    if(argc<2){
        fprintf(stderr, "Usage : interpreter sourceCode [ arg0 [ arg1 [ ... ] ] ]\n");
        fprintf(stderr, "Missing sourceCode.\n");
        exit(1);
    }


    std::ifstream code(argv[1]);

    InterpretContext context;
    for(int i=2; i<argc; i++){
        context.params.push_back(atol(argv[i]));
    }

    TreePtr src=Parse(code);
    //PrettyPrint(std::cerr, src);
    //std::cout << "" << '\n';
    int32_t tmp =  const_f(context, src);
    PrettyPrint(std::cerr, src);
    if (flagadd == 1 || flagsub == 1 || flagother == 1){
      //std::cout<<"changed \n";
      return 0;
    }else{
      //std::cout << "not changed" << '\n';
      return 1; //assume tree not changed
    }
}
