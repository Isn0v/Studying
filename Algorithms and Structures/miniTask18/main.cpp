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

std::string sorting_operators(std::stack<std::string>& operator_tokens, const std::string& cur_operator, std::string& polska_string){
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

                polska_string += operator_tokens.top() + " ";
                operator_tokens.pop();
            }
            operator_tokens.pop();
        } else {
            operator_tokens.push(cur_operator);
        }
    }

    return ret_op;
}

bool is_operator(const std::string& cur_operator){
    if (priority_map[cur_operator] == 0){
        return false;
    } else {
        return true;
    }
}

int main() {

    std::cout << "Formula: ";
    std::string formula;
    std::cin >> formula;

    //need cleaning
    auto operator_tokens = new std::stack<std::string>();
    std::string polska_string = "";
    std::string cur_operator = "";
    std::string cur_digit = "";

    for(std::size_t i = 0; i < formula.size() - 1; i++){
        if (formula[i] == ' '){
            continue;
        }

        if (std::isdigit(formula[i])){
            cur_digit += formula[i];
        } else {
            // need adding some features to support unary operations
            polska_string += cur_digit + " ";
            cur_digit = "";

            cur_operator += formula[i];
            if (!std::isdigit(formula[i + 1])){

                if (is_operator(cur_operator) && !is_operator(cur_operator + formula[i + 1])){
                    cur_operator = sorting_operators(*operator_tokens, cur_operator, polska_string);
                }
            } else {
                if (is_operator(cur_operator)){
                    cur_operator = sorting_operators(*operator_tokens, cur_operator, polska_string);
                }

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
