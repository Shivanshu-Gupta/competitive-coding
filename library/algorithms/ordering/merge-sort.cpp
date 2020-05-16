//
// Created by Shivanshu Gupta on 01/02/20.
//
#include "bits/stdc++.h"

using namespace std;

void merge(int arr[], int f, int m,
           int l) {    //f,m,l are indice of the first and last element of first half and last element of second half
    int size1 = m - f + 1;
    int size2 = l - m;
    int i = f, j = f, k = f;
    int *b = new int[size1];
    for (; j <= m; j++)        //j becomes m+1 at the end of loop which is the index of first element of second half
        b[j] = arr[j];
    for (; i <= m && j <= l;) {
        if (b[i] < arr[j])
            arr[k++] = b[i++];
        else if (b[i] > arr[j])
            arr[k++] = arr[j++];
        else {
            arr[k++] = b[i++];
            j++;
        }
    }
    for (; j <= l;)
        arr[k++] = arr[j++];
    for (; i <= m;)
        arr[k++] = b[i++];
}

void merge_sort(int *arr, int f, int l) {
    int mid;
    if (f < l) {
        mid = (f + l) / 2;
        merge_sort(arr, f, mid);
        merge_sort(arr, mid + 1, l);
        merge(arr, f, mid, l);
    }
}

int main() {
    int size;
    //scanf_s("%d", &size);
    cin >> size;
    int *vec = new int[size];
    for (int i = 0; i < size; i++) {
        //scanf_s("%d", vec[i]);
        cin >> vec[i];
    }
    merge_sort(vec, 0, size - 1);
    for (int i = 0; i < size; i++)
        cout << vec[i];
    //printf("%d", vec[i]);

}


