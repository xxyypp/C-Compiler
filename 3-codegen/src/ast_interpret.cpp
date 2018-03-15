#include "ast.hpp"

#include <regex>

int32_t Interpret(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program
){
    std::regex reNum("^-?[0-9]+$");//decimal number
    std::regex reId("^[a-z][a-z0-9]*$");//variable
                                        //input
                                        //output [x]
                                        //lessthan [ a b ]
                                        //add [ a b] - * /
                                        //assign
                                        //seq
                                        //if
                                        //while
    if( regex_match(program->type, reNum) ){
        return std::atol(program->type.c_str());
    }
    else if( regex_match(program->type, reId) ){ // TODO : Check for things matching reId

        return (context.bindings[program->type]);

    }else if(program->type=="Param"){
        unsigned index=atol(program->value.c_str());
        auto value=context.params.at(index);
        return value;

    }else if(program->type=="Output"){
        int32_t val=Interpret(context, program->branches.at(0));
        std::cout<<val<<std::endl;
        return val;

        // TODO: Handle other constructs
    }else if(program->type=="Input"){
        int32_t val;
        std::cin >> val;
        return val;
    }else if(program->type=="LessThan"){
        int32_t v1 = Interpret(context,program->branches.at(0));
        int32_t v2 = Interpret(context,program->branches.at(1));
        if(v1 < v2){
          return 1;
        }else{
          return 0;
        }
    }else if(program->type=="Add"){
        int32_t v1 = Interpret(context,program->branches.at(0));
        int32_t v2 = Interpret(context,program->branches.at(1));
        return v1+v2;
    }else if(program->type=="Sub"){
        int32_t v1 = Interpret(context,program->branches.at(0));
        int32_t v2 = Interpret(context,program->branches.at(1));
        return v1-v2;
    }else if(program->type=="Assign"){
        auto it = context.bindings.find(program->value);
        if(it != context.bindings.end()){
          context.bindings[program->type] = std::atol(program->value.c_str());
        }
        int32_t val=Interpret(context, program->branches.at(0));
        context.bindings[program->value] = val;
        //std::cout << "input test: " << val << std::endl;
        return val;

    }else if(program->type=="Seq"){
        int32_t temp;
        for(unsigned int i=0; i<program->branches.size(); i++){
              temp = Interpret(context, program->branches[i]);
        }
        return temp;
    }else if(program->type=="If"){
      /*
      if condition->type matches regex for number
      root->branch[0]->type == "0"
      root = root->branch[2]
      if type != 0
      root
      branch at 0 != 0 return left

      */
        int32_t v1 = Interpret(context,program->branches.at(0));
        if (v1 != 0){
          int32_t v2 = Interpret(context,program->branches.at(1));
          return v2;
        }else{
          int32_t v3 = Interpret(context,program->branches.at(2));
          return v3;
        }
    }else if(program->type=="While"){
        int32_t v1 = Interpret(context,program->branches.at(0));
        while (v1 != 0){
          v1 = Interpret(context,program->branches.at(1));
        }
        return 0;
    }else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}
