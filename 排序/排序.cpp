#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "Windows.h"


#define n 1000


//冒泡排序
double bubbleSort(int number, int arr[]) {
    for (int i = 0; i < number; ++i) {
        for (int j = 0; j < number - i - 1; ++j) {
            if (arr[j] >= arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 0;
}

//插入排序
double insertSort(int number, int arr[]) {
    for (int i = 1; i < number; ++i) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
            else {
                break;
            }
        }
    }
    return 0;
}

//选择排序
double selectSort(int number, int arr[]) {
    for (int i = 0; i < number - 1; i++) {
        for (int j = i + 1; j < number; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 0;
}
//以下为快速排序
  // 交换数组中两个元素的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 将数组划分为两部分，并返回划分点的下标
int divide(int arr[], int low, int high) {
    int middle = arr[high];  // 选取最后一个元素作为基准点
    int i = low - 1;  // 初始化较小元素的索引

    for (int j = low; j < high; j++) {
        if (arr[j] < middle) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 快速排序函数
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = divide(arr, low, high);

        // 分别对划分的两部分进行递归排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


//以下为归并排序
void merge(int* arr1, int* arr2, int* result, int length1, int length2) {
    int point1 = 0;
    int point2 = 0;
    int resultPoint = 0;
    while (!(point1 == length1 && point2 == length2)) {
        if (point1 == length1) {
            result[resultPoint] = arr2[point2];
            point2++, resultPoint++;
            continue;
        }
        if (point2 == length2) {
            result[resultPoint] = arr1[point1];
            point1++, resultPoint++;
            continue;
        }
        if (arr1[point1] < arr2[point2]) {
            result[resultPoint] = arr1[point1];
            point1++, resultPoint++;
        }
        else {
            result[resultPoint] = arr2[point2];
            point2++, resultPoint++;
        }
    }
}

void mergeSort(int* arr, int* re, int startIndex, int endIndex) {
    //递归分组
    if (startIndex == endIndex) {
        re[0] = arr[startIndex];
        return;
    }
    int middle = (startIndex + endIndex) / 2;
    int* in1 = (int*)malloc((middle - startIndex + 1) * sizeof(int));
    mergeSort(arr, in1, startIndex, middle);
    int* in2 = (int*)malloc((endIndex - middle) * sizeof(int));
    mergeSort(arr, in2, middle + 1, endIndex);
    merge(in1, in2, re, middle - startIndex + 1, endIndex - middle);
}


int main() {
    int arr[n];
    int origin[n];
    srand((unsigned int)(time(NULL)));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
    //origin保存乱码
    for (int i = 0; i < n; i++) {
        origin[i] = arr[i];
    }
    //查看具体数组
    //for (int i = 0; i < n; i++) {
    //   printf("%d\n ", origin[i]);
    //}
    LARGE_INTEGER frequency;
    //测试冒泡排序时间
    LARGE_INTEGER bubblestart, bubbleend;
    double elapsedTime1;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&bubblestart);

    bubbleSort(n, arr);

    QueryPerformanceCounter(&bubbleend);

    elapsedTime1 = (double)(bubbleend.QuadPart - bubblestart.QuadPart) / frequency.QuadPart;

    printf("bubblesort: %lf 秒\n", elapsedTime1);
    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }



    //测试插入排序时间
    LARGE_INTEGER insertstart, insertend;
    double elapsedTime2;

    QueryPerformanceCounter(&insertstart);

    insertSort(n, arr);

    QueryPerformanceCounter(&insertend);

    elapsedTime2 = (double)(insertend.QuadPart - insertstart.QuadPart) / frequency.QuadPart;

    printf("insertsort: %lf 秒\n", elapsedTime2);

    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }


    //测试选择排序
    LARGE_INTEGER selectstart, selectend;
    double elapsedTime3;
    //for (int i = 0; i < n; i++) {
    //    printf("%d ", arr[i]);
    //}
    QueryPerformanceCounter(&selectstart);

    selectSort(n, arr);

    QueryPerformanceCounter(&selectend);

    elapsedTime3 = (double)(selectend.QuadPart - selectstart.QuadPart) / frequency.QuadPart;

    printf("selectsort: %lf 秒\n", elapsedTime3);

    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }

    //测试快速排序
    LARGE_INTEGER quickstart, quickend;
    double elapsedTime4;


    QueryPerformanceCounter(&quickstart);

    quickSort(arr, 0, n - 1);

    QueryPerformanceCounter(&quickend);

    elapsedTime4 = (double)(quickend.QuadPart - quickstart.QuadPart) / frequency.QuadPart;

    printf("quicksort:  %lf 秒\n", elapsedTime4);

    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }
    //测试归并排序
    int fina[n];//fina用以保留归并整合后的数组
    LARGE_INTEGER mergestart, mergeend;
    double elapsedTime5;

    QueryPerformanceCounter(&mergestart);

    mergeSort(arr, fina, 0, n - 1);

    QueryPerformanceCounter(&mergeend);

    elapsedTime5 = (double)(mergeend.QuadPart - mergestart.QuadPart) / frequency.QuadPart;

    printf("mergesort:  %lf 秒\n", elapsedTime5);
    //将final数组放回到arr中
    for (int i = 0; i < n; i++) {
        arr[i] = fina[i];
    }
   // for (int i = 0; i < n; i++) {
    //   printf("%d ", arr[i]);
   // }
}