#include <iostream>

template<typename T>
bool isEven(T number) {
    return number % 2 == 0;
}

template <typename Checker, typename None = void>
bool isMatch(Checker checker, int& index) {
    return false;
}

template<typename Checker, typename FirstArg, typename... Args>
bool isMatch(Checker checker, int& index, FirstArg firstArg, Args... args) {
    // return checker(*firstArg) ? true : isMatch(checker, index + 1, args...);
    if (checker(*firstArg)) {
        return true;
    } else {
        index++;
        return isMatch(checker, index, args...);
    }
}

template<typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker checker, Args... args){
    int index = 0;
    return isMatch(checker, index, args...) ? index : -1;
}





int main() {
    int numbers[] = {5, 6, 7, 8, 10};
    int index = getIndexOfFirstMatch(isEven<int>, numbers);
    if (index == -1) {
        std::cout << "No even number found" << std::endl;
    } else {
        std::cout << "The first even number is at index " << index << std::endl;
    }
    return 0;
}


