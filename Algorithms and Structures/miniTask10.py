def lsd_radix(arr):
    ASCII_MAX = 128
    
    assert(all(ord(c) < ASCII_MAX for c in arr))
    
    def sort_by_digit(digit):
        buffer = [0 for i in range(ASCII_MAX)] #assume there are only ascii symbs
        
        for i in range(len(arr)):
            buffer[ord(arr[i][-digit])] += 1
        
        j = 0
        sorted_arr = [0 for i in range(len(arr))]
        for i in range(1, len(buffer)):
            buffer[i] += buffer[i - 1]
    
        for i in range(len(arr) - 1, -1, -1):
            buffer[ord(arr[i][-digit])] -= 1
            sorted_arr[buffer[ord(arr[i][-digit])]] = arr[i]
        return sorted_arr
            
                
    digits = len(arr[0])
    for digit in range(1, digits + 1):
        arr = sort_by_digit(digit)
        print(arr)
        
    return arr
            


if __name__ == "__main__":
    arr = ["sldv", "fvdn", "dsvb", "cacf", 'asdg', "vhus"]
    
    arr = lsd_radix(arr)
    #print(arr)