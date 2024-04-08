#include <string>

class Expression {
public:
  virtual ~Expression() = default;
  virtual Expression *diff(const std::string &variable) const = 0;
};

class Binary : public Expression {
protected:
  Expression *left;
  Expression *right;

public:
  Binary(Expression *l, Expression *r) : left(l), right(r) {}
};

class Unary : public Expression {
protected:
  Expression *expression;

public:
  Unary(Expression *expr) : expression(expr) {}
};

class Add : public Binary {
public:
  Add(Expression *l, Expression *r) : Binary(l, r) {}
  Expression *diff(const std::string &variable) const override;
};

class Sub : public Binary {
public:
  Sub(Expression *l, Expression *r) : Binary(l, r) {}
  Expression *diff(const std::string &variable) const override;
};

class Mult : public Binary {
public:
  Mult(Expression *l, Expression *r) : Binary(l, r) {}
  Expression *diff(const std::string &variable) const override;
};

class Div : public Binary {
public:
  Div(Expression *l, Expression *r) : Binary(l, r) {}
  Expression *diff(const std::string &variable) const override;
};

class Exponent : public Binary {
public:
  Exponent(Expression *base, Expression *exponent) : Binary(base, exponent) {}
  Expression *diff(const std::string &variable) const override;
};

class Var : public Expression {
private:
  std::string name;

public:
  Var(const std::string &n) : name(n) {}
  Expression *diff(const std::string &variable) const override;
  std::string getName() const { return name; }
};

class Val : public Expression {
private:
  double value;

public:
  Val(double val) : value(val) {}
  Expression *diff(const std::string &variable) const override;
  double getValue() const { return value; }
};
