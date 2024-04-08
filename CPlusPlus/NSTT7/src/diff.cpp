#include "diff.h"
#include <stdexcept>

Expression *Var::diff(const std::string &variable) const {
  if (variable == name) {
    return new Val(1);
  } else {
    return new Val(0);
  }
}

Expression *Exponent::diff(const std::string &variable) const {
  // The derivative of an exponent is given by the power rule (simplified
  // version) For simplicity, we're assuming the exponent is a constant A full
  // implementation would handle the general case with the chain rule
  if (dynamic_cast<Var *>(right) != nullptr) {
    // d(u^y)/dx = u^y * d(y*ln(u))/dx = u^y * ln(u) * dy/dx
    throw std::runtime_error("Chain rule not implemented yet");
  } else if (Var *v = dynamic_cast<Var *>(left);
             v && v->getName() == variable) {
    // d(u^n)/dx = n * u^(n-1) * du/dx
    Expression *n_minus_one = new Sub(right, new Val(1));
    return new Mult(new Mult(right, new Exponent(left, n_minus_one)),
                    left->diff(variable));
  } else {
    // Exponent is a constant, base is not just the variable
    return new Val(0);
  }
}

Expression *Div::diff(const std::string &variable) const {
  return new Div(new Sub(new Mult(left->diff(variable), right),
                         new Mult(left, right->diff(variable))),
                 new Mult(right, right));
}

Expression *Mult::diff(const std::string &variable) const {
  return new Add(new Mult(left->diff(variable), right),
                 new Mult(left, right->diff(variable)));
}

Expression *Sub::diff(const std::string &variable) const {
  return new Sub(left->diff(variable), right->diff(variable));
}

Expression *Add::diff(const std::string &variable) const {
  return new Add(left->diff(variable), right->diff(variable));
}

Expression *Val::diff(const std::string &variable) const { return new Val(0); }
