#include <cstdlib>
#include <iostream>
#include <sstream>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression
{
 private:
  long num;  //if input is a single number

 public:
  NumExpression() {}
  NumExpression(long a) : num(a) {}

  virtual std::string toString() const {
    std::stringstream in;
    in << num;
    std::string out = in.str();
    in.clear();
    return out;
  }
  virtual ~NumExpression() {}  //virtual
};
class PlusExpression : public NumExpression
{
 private:
  std::string plsexp;
  Expression * lhsplus;
  Expression * rhsplus;

 public:
  //evaluating its right hand side, and then adding the two results together
  //  to get its answer

  PlusExpression(Expression * lhs, Expression * rhs) {
    lhsplus = lhs;
    rhsplus = rhs;
    char op = '+';
    std::stringstream instant;
    instant << '(' + lhsplus->toString() + ' ' + op + ' ' + rhsplus->toString() + ')';
    plsexp = instant.str();
  }
  virtual std::string toString() const { return plsexp; }
  virtual ~PlusExpression() {
    delete lhsplus;
    delete rhsplus;
  }
};
