#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) { 
int _reg_1 = std::atol(argv[0]);
int _reg_2 = std::atol(argv[1]);
int _reg_3 = std::atol(argv[2]);
int _res_0;
if (_reg_1 != 0){
_res_0=_reg_2;
}else{
_res_0=_reg_3;
}
return _res_0;
}
