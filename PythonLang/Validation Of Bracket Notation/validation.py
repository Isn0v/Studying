def get_open_type(symbol):
    match symbol:
        case '[' | '{' | '(':
            return 1
        case ']' | '}' | ')':
            return 0
    return -1


def match_bracket(symbol1, symbol2):
    match symbol1:
        case '{':
            if symbol2 == '}':
                return 1
        case '[':
            if symbol2 == ']':
                return 1
        case '(':
            if symbol2 == ')':
                return 1
    return 0


_in = list(input())[::-1]
stack_of_brackets = []
bracket_indexes = []

pos = 0

while _in:
    symbol = _in.pop()
    if get_open_type(symbol) == -1:
        pos += 1
        continue

    pos += 1
    if not get_open_type(symbol):
        if len(stack_of_brackets) == 0 or not match_bracket(stack_of_brackets[-1], symbol):
            print(pos)
            break
        else:
            stack_of_brackets.pop()
            bracket_indexes.pop()
    else:
        stack_of_brackets.append(symbol)
        bracket_indexes.append(pos)
else:
    if len(stack_of_brackets) > 0:
        print(bracket_indexes[0])
    else:
        print("Success")
