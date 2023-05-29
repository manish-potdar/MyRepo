//write a program to implement parallel merge sort using openmp

// Path: HPC/ass4.cpp
#include <iostream>
#include <omp.h>
#include <vector>
#include <algorithm>

using namespace std;

void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1, n2 = r - m;
    vector<int> left(n1), right(n2);
    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }
    while(i < n1)
    {
        arr[k++] = left[i++];
    }
    while(j < n2)
    {
        arr[k++] = right[j++];
    }
}

void merge_sort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = (l + r)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort(arr, l, m);
                printf ("id = %d, \n", omp_get_thread_num());
            }
            #pragma omp section
            {
                merge_sort(arr, m + 1, r);
                printf ("id = %d, \n", omp_get_thread_num());
            }
        }
        merge(arr, l, m, r);
    }
}

int main()
{
    int n;
    cout << "Enter no. of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    merge_sort(arr, 0, n - 1);
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
