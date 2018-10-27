#include <cstdlib>
#include <iostream>
#include <sstream>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;  //abstract method
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
  virtual long evaluate() const { return num; }
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
  virtual long evaluate() const { return lhsplus->evaluate() + rhsplus->evaluate(); }
  virtual ~PlusExpression() {
    delete lhsplus;
    delete rhsplus;
  }
};
class MinusExpression : public NumExpression
{
 private:
  std::string plsexp;
  Expression * lhsmi;
  Expression * rhsmi;

 public:
  //evaluating its right hand side, and then adding the two results together
  //  to get its answer

  MinusExpression(Expression * lhs, Expression * rhs) {
    lhsmi = lhs;
    rhsmi = rhs;
    char op = '-';
    std::stringstream instant;
    instant << '(' + lhsmi->toString() + ' ' + op + ' ' + rhsmi->toString() + ')';
    plsexp = instant.str();
  }

  virtual std::string toString() const { return plsexp; }
  virtual long evaluate() const { return lhsmi->evaluate() - rhsmi->evaluate(); }
  virtual ~MinusExpression() {
    delete lhsmi;
    delete rhsmi;
  }
};
class DivExpression : public NumExpression
{
 private:
  std::string plsexp;
  Expression * lhsdiv;
  Expression * rhsdiv;

 public:
  //evaluating its right hand side, and then adding the two results together
  //  to get its answer

  DivExpression(Expression * lhs, Expression * rhs) {
    lhsdiv = lhs;
    rhsdiv = rhs;
    char op = '/';
    std::stringstream instant;
    instant << '(' + lhsdiv->toString() + ' ' + op + ' ' + rhsdiv->toString() + ')';
    plsexp = instant.str();
  }

  virtual std::string toString() const { return plsexp; }
  virtual long evaluate() const { return lhsdiv->evaluate() / rhsdiv->evaluate(); }
  virtual ~DivExpression() {
    delete lhsdiv;
    delete rhsdiv;
  }
};
class TimesExpression : public NumExpression
{
 private:
  std::string plsexp;
  Expression * lhstim;
  Expression * rhstim;

 public:
  //evaluating its right hand side, and then adding the two results together
  //  to get its answer

  TimesExpression(Expression * lhs, Expression * rhs) {
    lhstim = lhs;
    rhstim = rhs;
    char op = '*';
    std::stringstream instant;
    instant << '(' + lhstim->toString() + ' ' + op + ' ' + rhstim->toString() + ')';
    plsexp = instant.str();
  }

  virtual std::string toString() const { return plsexp; }
  virtual long evaluate() const { return lhstim->evaluate() * rhstim->evaluate(); }
  virtual ~TimesExpression() {
    delete lhstim;
    delete rhstim;
  }
};
