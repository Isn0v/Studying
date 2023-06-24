#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cctype>

using namespace std;

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

bool is_operator(const string& elem){
    if (priority_map[elem] == 0){
        return false;
    } else {
        return true;
    }
}

bool is_digit(string str){
    return isdigit(str[0]);
}

//1 - part of number
//2 - part of operator
//3 - anything else
int get_symbol_type(const char token){
    if (isdigit(token)){
        return 1;
    } else if (is_operator(to_string(token))){
        return 2;
    } else {
        return 3;
    }
}

vector<string> parse_expression_to_list(string& expression){
    vector<string> parsed{};

    string lexema(1, expression[0]);

    for(int i = 1; i < expression.size(); i++){
        int token_type = get_symbol_type(expression[i]);

        if (token_type == 1 && token_type == get_symbol_type(lexema[lexema.size() - 1]) ||
        token_type == 2 && token_type == get_symbol_type(lexema[lexema.size() - 1]) && is_operator(lexema + to_string(expression[i]))){
            lexema.push_back(expression[i]);

        } else {
            parsed.push_back(lexema);
            lexema = string(1, expression[i]);
        }
    }
    parsed.push_back(lexema);
    return parsed;
}

int main() {

    cout << "Formula: ";
    string formula;
    cin >> formula;

    auto parsed = parse_expression_to_list(formula);

    stack<string> operator_stack{};
    vector<string> polska_list{};

    for (auto elem: parsed){
        if (is_digit(elem)){
            polska_list.push_back(elem);
        } else if (is_operator(elem)){
            if (operator_stack.empty()){
                operator_stack.push(elem);
            } else {
                int cur_priority = priority_map[elem];
                int latest_priority = priority_map[operator_stack.top()];

                if (latest_priority < cur_priority && latest_priority != 1){
                    polska_list.push_back(operator_stack.top());
                    operator_stack.pop();

                    operator_stack.push(elem);
                } else if (elem == ")"){
                    while (operator_stack.top() != "("){

                        polska_list.push_back(operator_stack.top());
                        operator_stack.pop();
                    }
                    operator_stack.pop();
                } else {
                    operator_stack.push(elem);
                }
            }
        }
    }

    while(!operator_stack.empty()){
        polska_list.push_back(operator_stack.top());
        operator_stack.pop();
    }

    cout << "Polska_list:\n";
    for (auto elem: polska_list){
        cout << elem << ' ';
    }
}
