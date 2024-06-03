#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "Windows.h"


#define n 1000


//ð������
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

//��������
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

//ѡ������
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
//����Ϊ��������
  // ��������������Ԫ�ص�ֵ
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �����黮��Ϊ�����֣������ػ��ֵ���±�
int divide(int arr[], int low, int high) {
    int middle = arr[high];  // ѡȡ���һ��Ԫ����Ϊ��׼��
    int i = low - 1;  // ��ʼ����СԪ�ص�����

    for (int j = low; j < high; j++) {
        if (arr[j] < middle) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// ����������
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = divide(arr, low, high);

        // �ֱ�Ի��ֵ������ֽ��еݹ�����
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


//����Ϊ�鲢����
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
    //�ݹ����
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
    //origin��������
    for (int i = 0; i < n; i++) {
        origin[i] = arr[i];
    }
    //�鿴��������
    //for (int i = 0; i < n; i++) {
    //   printf("%d\n ", origin[i]);
    //}
    LARGE_INTEGER frequency;
    //����ð������ʱ��
    LARGE_INTEGER bubblestart, bubbleend;
    double elapsedTime1;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&bubblestart);

    bubbleSort(n, arr);

    QueryPerformanceCounter(&bubbleend);

    elapsedTime1 = (double)(bubbleend.QuadPart - bubblestart.QuadPart) / frequency.QuadPart;

    printf("bubblesort: %lf ��\n", elapsedTime1);
    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }



    //���Բ�������ʱ��
    LARGE_INTEGER insertstart, insertend;
    double elapsedTime2;

    QueryPerformanceCounter(&insertstart);

    insertSort(n, arr);

    QueryPerformanceCounter(&insertend);

    elapsedTime2 = (double)(insertend.QuadPart - insertstart.QuadPart) / frequency.QuadPart;

    printf("insertsort: %lf ��\n", elapsedTime2);

    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }


    //����ѡ������
    LARGE_INTEGER selectstart, selectend;
    double elapsedTime3;
    //for (int i = 0; i < n; i++) {
    //    printf("%d ", arr[i]);
    //}
    QueryPerformanceCounter(&selectstart);

    selectSort(n, arr);

    QueryPerformanceCounter(&selectend);

    elapsedTime3 = (double)(selectend.QuadPart - selectstart.QuadPart) / frequency.QuadPart;

    printf("selectsort: %lf ��\n", elapsedTime3);

    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }

    //���Կ�������
    LARGE_INTEGER quickstart, quickend;
    double elapsedTime4;


    QueryPerformanceCounter(&quickstart);

    quickSort(arr, 0, n - 1);

    QueryPerformanceCounter(&quickend);

    elapsedTime4 = (double)(quickend.QuadPart - quickstart.QuadPart) / frequency.QuadPart;

    printf("quicksort:  %lf ��\n", elapsedTime4);

    for (int i = 0; i < n; i++) {
        arr[i] = origin[i];
    }
    //���Թ鲢����
    int fina[n];//fina���Ա����鲢���Ϻ������
    LARGE_INTEGER mergestart, mergeend;
    double elapsedTime5;

    QueryPerformanceCounter(&mergestart);

    mergeSort(arr, fina, 0, n - 1);

    QueryPerformanceCounter(&mergeend);

    elapsedTime5 = (double)(mergeend.QuadPart - mergestart.QuadPart) / frequency.QuadPart;

    printf("mergesort:  %lf ��\n", elapsedTime5);
    //��final����Żص�arr��
    for (int i = 0; i < n; i++) {
        arr[i] = fina[i];
    }
   // for (int i = 0; i < n; i++) {
    //   printf("%d ", arr[i]);
   // }
}