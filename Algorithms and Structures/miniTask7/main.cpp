void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

int merge(int* arr1, int len1, int* arr2, int len2, int* buf){
    int i = 0, j = 0, k = 0;
    int inv = 0;
    while (i < len1 && j < len2){
        if (arr1[i] <= arr2[j]){
            swap(buf[k], arr1[i]);
            i++;
        } else {
            swap(buf[k], arr2[j]);
            j++;
            inv += len1 - i;
        }
        k++;
    }

    while (i < len1) {
        swap(buf[k], arr1[i]);
        k++;
        i++;
    }
    while (j < len2) {
        swap(buf[k], arr2[j]);
        k++;
        j++;
    }
    return inv;
}

int merge_sort_impl(int* arr, int len, int* buf){
    if (len == 1){
        return 0;
    }

    int mid = len / 2;

    int inv = merge_sort_impl(arr, mid, buf);
    inv += merge_sort_impl(arr + mid, len - mid, buf);
    inv += merge(arr, mid, arr + mid, len - mid, buf);

    for (int i = 0; i < len; i++){
        swap(arr[i], buf[i]);
    }
    return inv;
}


void merge_sort_inplace(int* arr, int len){
    int unsorted = (len + 1) / 2;
    merge_sort_impl(arr + unsorted, len - unsorted, arr);

    while (unsorted != 1){
        int unsort_mid = unsorted / 2;
        merge_sort_impl(arr, unsort_mid, arr + unsort_mid);
        merge(arr, unsort_mid, arr + unsorted, len - unsorted, arr + unsorted - unsort_mid);

        unsorted -= unsort_mid;
    }

    int i = 0;
    while (arr[i] > arr[i + 1] && i + 1 < len){
        swap(arr[i + 1], arr[i]);
        i++;
    };
}


int merge_sort(int* arr, int len){
    int* buf = new int[len];

    int inv = merge_sort_impl(arr, len, buf);
    delete[] buf;
    return inv;

}
