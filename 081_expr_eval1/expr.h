#include <cstdlib>
#include <iostream>
#include <sstream>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression
{
 private:
  long num;  //if input is a single number

 public:
  NumExpression() { num = 0; }
  NumExpression(long a) : num(a) {}

  virtual std::string toString() const {
    std::stringstream in;
    in << num;
    std::string out = in.str();
    in.clear();
    return out;
  }
  virtual ~NumExpression() {}  //why virtual
};
class PlusExpression : public NumExpression
{
 private:
  std::string plsexp;

 public:
  //evaluating its right hand side, and then adding the two results together
  //  to get its answer

  PlusExpression(Expression * lhs, Expression * rhs) {
    char op = '+';
    std::stringstream instant;
    instant << '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
    plsexp = instant.str();
  }
  virtual std::string toString() const { return plsexp; }
};
