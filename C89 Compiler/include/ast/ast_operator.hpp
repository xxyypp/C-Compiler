#ifndef ast_operator_hpp
#define ast_operator_hpp

#include <string>
#include <iostream>

class Operator
    : public Program
{
private:
    const Program *left;
    const Program *right;
protected:
    Operator(const Program *_left, const Program *_right)
        : left(_left),right(_right)
    {}

public:
    virtual const char *getOp() const = 0;

    const Program *getLeft() const {
      return left;
    }

    const Program *getRight() const{
      return right;
    }

    virtual void print() const override
    {
      //std::cout << "addiu ";
      //left->print();
      //right->print();
    }

    virtual void printdeclare(Top *pt) const override{
      std::string in = "lbl";
      std::string str1 = pt->makeName(in);
      getLeft()->printdeclare(pt);
      std::cout << "sw $t1, " << pt->GetIndex() << "($sp)" << '\n';
      // std::cout << "#---------------------------" << '\n';
      // std::cout << "#op is:" << getOp() << '\n';
      // std::cout << "#---------------------------" << '\n';
      pt->Opmap.insert(std::pair<std::string, int>(str1,pt->GetIndex()));
      pt->IncrementIndex();

      std::string str2 = pt->makeName(in);
      getRight()->printdeclare(pt);
      std::cout << "sw $t1, " << pt->GetIndex() << "($sp)" << '\n';
      pt->Opmap.insert(std::pair<std::string, int>(str2,pt->GetIndex()));
      pt->IncrementIndex();

      std::string op = getOp();
      if(op == "+"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "add $t1, $t0, $t1" << '\n';
      }else if(op == "-"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "sub $t1, $t0, $t1" << '\n';
      }else if(op == "*"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "mult $t1, $t0" << '\n';
        std::cout << "mflo $t1" << '\n';
      }else if(op == "/"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "div $t0, $t1" << '\n';
        std::cout << "mflo $t1" << '\n';
      }else if(op == "%"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "div $t0, $t1" << '\n';
        std::cout << "mfhi $t1" << '\n';
      }else if(op == "=="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "xor $t1, $t0, $t1" << '\n';
        std::cout << "sltu $t1, $t1, 1" << '\n';
      }else if(op == "!="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "xor $t1, $t0, $t1" << '\n';
        std::cout << "sltu $t1, $t0, $t1" << '\n';
      }else if(op == "|"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "or $t1, $t0, $t1" << '\n';
      }else if(op == "^"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "xor $t1, $t0, $t1" << '\n';
      }else if(op == "&"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "and $t1, $t0, $t1" << '\n';
      }else if(op == "<"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t0, $t1" << '\n';
      }else if(op == ">"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t1, $t0" << '\n';
      }else if(op == "<="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t0, $t1" << '\n';
        std::cout << "xori $t1, $t1, 1" << '\n';
      }else if(op == ">="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t1, $t0" << '\n';
        std::cout << "xori $t1, $t1, 1" << '\n';
      }else if(op == ">>"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slav $t1, $t0, $t1" << '\n';
      }else if(op == "<<"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "sllv $t1, $t0, $t1" << '\n';
      }
    }

    virtual void ReturnPrint(Top *pt) const override{
      std::string in = "lbl";
      std::string str1 = pt->makeName(in);
      getLeft()->printdeclare(pt);
      std::cout << "sw $t1, " << pt->GetIndex() << "($sp)" << '\n';
      pt->Opmap.insert(std::pair<std::string, int>(str1,pt->GetIndex()));
      pt->IncrementIndex();

      std::string str2 = pt->makeName(in);
      getRight()->printdeclare(pt);
      std::cout << "sw $t1, " << pt->GetIndex() << "($sp)" << '\n';
      pt->Opmap.insert(std::pair<std::string, int>(str2,pt->GetIndex()));
      pt->IncrementIndex();

      std::string op = getOp();
      if(op == "+"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "add $t1, $t0, $t1" << '\n';
      }else if(op == "-"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "sub $t1, $t0, $t1" << '\n';
      }else if(op == "*"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "mult $t1, $t0" << '\n';
        std::cout << "mflo $t1" << '\n';
      }else if(op == "/"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "div $t0, $t1" << '\n';
        std::cout << "mflo $t1" << '\n';
      }else if(op == "%"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "div $t0, $t1" << '\n';
        std::cout << "mfhi $t1" << '\n';
      }else if(op == "=="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "xor $t1, $t0, $t1" << '\n';
        std::cout << "sltu $t1, $t1, 1" << '\n';
      }else if(op == "!="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "xor $t1, $t0, $t1" << '\n';
        std::cout << "sltu $t1, $t0, $t1" << '\n';
      }else if(op == "|"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "or $t1, $t0, $t1" << '\n';
      }else if(op == "^"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "xor $t1, $t0, $t1" << '\n';
      }else if(op == "&"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "and $t1, $t0, $t1" << '\n';
      }else if(op == "<"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t0, $t1" << '\n';
      }else if(op == ">"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t1, $t0" << '\n';
      }else if(op == "<="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t0, $t1" << '\n';
        std::cout << "xori $t1, $t1, 1" << '\n';
      }else if(op == ">="){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slt $t1, $t1, $t0" << '\n';
        std::cout << "xori $t1, $t1, 1" << '\n';
      }else if(op == ">>"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "slav $t1, $t0, $t1" << '\n';
      }else if(op == "<<"){
        std::cout << "lw $t0, " << pt->Opmap[str1] <<"($sp)" << '\n';
        std::cout << "lw $t1, " << pt->Opmap[str2] <<"($sp)" << '\n';
        std::cout << "sllv $t1, $t0, $t1" << '\n';
      }
      std::cout << "sw $t1, " << pt->GetIndex() << "($sp)" << '\n';
      std::cout << "lw $2, " << pt->GetIndex() << "($sp)" << '\n';
    }

    virtual void printcode(Top *pt) const override{}

    ~Operator(){
      delete left;
      delete right;
    }
};

class AddOperator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "+";
  }
public:
    AddOperator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}

    virtual void print() const override
    {
      // std::cout << "addiu ";
      // left->print();
      // right->print();
    }

    virtual void printcode(Top *pt){}

    ~AddOperator(){}
};

class SubOperator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "-";
  }
public:
    SubOperator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}

    virtual void print() const override
    {}

    virtual void printcode(Top *pt){}

    ~SubOperator(){}
};
class MultOperator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "*";
  }
public:
    MultOperator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}

    virtual void print() const override
    {
      // std::cout << "addiu ";
      // left->print();
      // right->print();
    }

    virtual void printcode(Top *pt){}

    ~MultOperator(){}
};
class DividOperator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "/";
  }
public:
    DividOperator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}

    virtual void print() const override
    {
      // std::cout << "addiu ";
      // left->print();
      // right->print();
    }

    virtual void printcode(Top *pt){}

    ~DividOperator(){}
};
class ModOperator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "%";
  }
public:
    ModOperator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}

    virtual void print() const override
    {
      // std::cout << "addiu ";
      // left->print();
      // right->print();
    }

    virtual void printcode(Top *pt){}

    ~ModOperator(){}
};

class EQ_Operator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "==";
  }
public:
    EQ_Operator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~EQ_Operator(){}
};

class NE_OPerator
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "==";
  }
public:
    NE_OPerator(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~NE_OPerator(){}
};

class OR
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "|";
  }
public:
    OR(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~OR(){}
};

class XOR
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "^";
  }
public:
    XOR(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~XOR(){}
};

class AND
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "&";
  }
public:
    AND(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~AND(){}
};

class LESS
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "<";
  }
public:
    LESS(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~LESS(){}
};
class GREATER
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return ">";
  }
public:
    GREATER(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~GREATER(){}
};

class LE
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "<=";
  }
public:
    LE(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~LE(){}
};
class GE
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return ">=";
  }
public:
    GE(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~GE(){}
};
class LEFT
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return "<<";
  }
public:
    LEFT(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~LEFT(){}
};
class RIGHT
    : public Operator
{
protected:
  virtual const char *getOp() const override{
    return ">>";
  }
public:
    RIGHT(const Program *_left, const Program *_right)
        : Operator(_left, _right)
    {}
    virtual void print() const override
    {}
    virtual void printcode(Top *pt){}

    ~RIGHT(){}
};


#endif
