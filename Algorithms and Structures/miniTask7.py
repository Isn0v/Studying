#алгоритм из лекции не получилось реализовать
#поэтому обратился за помощью в интернет
#не обессудьте (может из лекции потом попробую или у вас спрощу по деталям реализации)
def merge(arr, start, mid, end):
    start2 = mid + 1
 
    if (arr[mid] <= arr[start2]):
        return
 
    while (start <= mid and start2 <= end):
 
        if (arr[start] <= arr[start2]):
            start += 1
        else:
            value = arr[start2]
            index = start2

            while (index != start):
                arr[index] = arr[index - 1]
                index -= 1
 
            arr[start] = value
 
            start += 1
            mid += 1
            start2 += 1
 
 
def sort(arr, left, right):
    if (left < right):
 
        mid = left + (right - left) // 2
 
        sort(arr, left, mid)
        sort(arr, mid + 1, right)
 
        merge(arr, left, mid, right)

if __name__ == "__main__":
    arr = [45, 6, 24, 654, 32, 756]
    sort(arr, 0, len(arr) - 1)
    print(arr)
 