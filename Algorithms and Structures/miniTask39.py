def isMatch(self, s: str, p: str) -> bool:
    i = 0 # s iter
    j = 0 # p iter
    last_match = 0
    char_encountered = -1 # for iteration if "*" is encountered
    while i < len(s):
        if j < len(p) and (s[i] == p[j] or p[j] == '?'):
            i += 1
            j += 1
        elif j < len(p) and p[j] == '*':
            last_match = i
            char_encountered = j
            j += 1
        elif char_encountered != -1:
            j = char_encountered + 1
            i = last_match + 1
            last_match += 1
        else:
            return False
    while j < len(p) and p[j] == '*': # if s is empty and p is like ("******")
        j += 1
    return j == len(p)