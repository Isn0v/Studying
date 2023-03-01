
#достаточно посчитать количество инверсий
#поэтому использую алгоритм из прошлой задачи
def sort(arr, start, mid, end):
    start2 = mid + 1
    count = 0
    if arr[mid] <= arr[start2]:
        return 0

    while start <= mid and start2 <= end:

        if arr[start] <= arr[start2]:
            start += 1
        else:
            value = arr[start2]
            index = start2

            while index != start:
                arr[index] = arr[index - 1]
                index -= 1

            arr[start] = value

            start += 1
            mid += 1
            start2 += 1
            count += (mid - start + 1)
    return count


def merge(arr, left, right):
    count1 = count2 = count3 = 0
    if left < right:
        m = left + (right - left) // 2

        count1 = merge(arr, left, m)
        count2 = merge(arr, m + 1, right)

        count3 = sort(arr, left, m, right)
    return count1 + count2 + count3


def simple_solution(arr):

    for i in range(len(arr)):
        if i - arr[i] > 1 or i - arr[i] < -1:
            return False
        
    return True