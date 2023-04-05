#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cctype>

std::map<std::string, int> priority_map = {
        {"(", 1}, {")", 1},
        {"!", 2}, {"-", 2}, {"~", 2},
        {"*", 3}, {"/", 3}, {"%", 3},
        {"+", 4}, {"-", 4},
        {"<<", 5}, {">>", 5},
        {"<", 6}, {"<=", 6}, {">", 6}, {">=", 6},
        {"==", 7}, {"!=", 7},
        {"&", 8},
        {"^", 9}, //XOR
        {"|", 10},
        {"&&", 11},
        {"||", 12}
};

std::string sorting_operators(std::stack<std::string>& operator_tokens, std::string cur_operator){
    std::string ret_op = "";

    if (operator_tokens.empty()){
        operator_tokens.push(cur_operator);
    } else {
        int cur_priority = priority_map[cur_operator];
        if (cur_priority == 0){
            throw std::string("No such operator: ") + cur_operator;
        }

        int latest_priority = priority_map[operator_tokens.top()];
        if (latest_priority == 0){
            throw std::string("No such operator: ") + operator_tokens.top();
        }

        //need some improvements about left associations
        if (latest_priority < cur_priority){
            ret_op = operator_tokens.top();
            operator_tokens.pop();

            operator_tokens.push(cur_operator);
        } else if (cur_operator == ")"){
            while (operator_tokens.top() != "("){
                if (operator_tokens.empty()){
                    throw std::string("Invalid formula: open bracket missed");
                }

                ret_op += operator_tokens.top();
                operator_tokens.pop();
            }
        } else {
            operator_tokens.push(cur_operator);
        }
    }

    return ret_op;
}

int main() {
    std::cout << "Formula: ";
    std::string formula;
    std::cin >> formula;

    //need cleaning
    auto operator_tokens = new std::stack<std::string>();
    std::string polska_string = "";
    std::string cur_operator = "";

    for(std::size_t i = 0; i < formula.size(); i++){
        if (std::isdigit(formula[i])){
            polska_string += formula[i];
        } else {
            // need adding some features to support unary operations
            cur_operator += formula[i];
            if (std::isdigit(formula[i + 1])){
                cur_operator = sorting_operators(*operator_tokens, cur_operator);
                if(cur_operator != ""){
                    polska_string += cur_operator;
                }
            }
        }
    }

    while (!operator_tokens->empty()){
        polska_string += operator_tokens->top();
        operator_tokens->pop();
    }

    delete operator_tokens;
    std::cout << polska_string;
}
