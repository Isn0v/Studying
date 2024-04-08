#include <string>


// Base class for all expressions
class Expression {
public:
    virtual ~Expression() = default;
    virtual Expression* diff(const std::string& variable) const = 0;
};

// Derived class for binary operations
class Binary : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    Binary(Expression* l, Expression* r) : left(l), right(r) {}
    // Implementation of `diff` will depend on the specific binary operation
};

// Derived class for unary operations
class Unary : public Expression {
protected:
    Expression* expression;
public:
    Unary(Expression* expr) : expression(expr) {}
    // Implementation of `diff` will depend on the specific unary operation
};

// Derived class for addition
class Add : public Binary {
public:
    Add(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(const std::string& variable) const override;
};

// Derived class for subtraction
class Sub : public Binary {
public:
    Sub(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(const std::string& variable) const override;
};

// Derived class for multiplication
class Mult : public Binary {
public:
    Mult(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(const std::string& variable) const override;
};

// Derived class for division
class Div : public Binary {
public:
    Div(Expression* l, Expression* r) : Binary(l, r) {}
    Expression* diff(const std::string& variable) const override;
};

// Derived class for exponentiation
class Exponent : public Binary {
public:
    Exponent(Expression* base, Expression* exponent) : Binary(base, exponent) {}
    Expression* diff(const std::string& variable) const override;
};

// Derived class for variables
class Var : public Expression {
private:
    std::string name;
public:
    Var(const std::string& n) : name(n) {}
    Expression* diff(const std::string& variable) const override;
    std::string getName() const { return name; }
};

// Derived class for constants
class Val : public Expression {
private:
    double value;
public:
    Val(double val) : value(val) {}
    Expression* diff(const std::string& variable) const override;
    double getValue() const { return value; }
};

// Implementations should go here or in a corresponding .cpp file.