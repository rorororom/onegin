#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "color.h"

void qSort(void *data, int left, int right, int len, int (*compare)(const void *, const void *));
int partition(void *data, int left, int right, int len, int (*compare)(const void *, const void *));
void swap(void *data, int a, int b, int size);
void print_data(void *data, int mid, int left, int right, int len, int size, int (*compare)(const void *, const void *));
void print_pointer(void *data, int mid, int left, int right, int size);

int compare_int(const void *a, const void *b);

int main()
{
    int data[] = {4, 18, 9, 0, 90, 8, 15, 88, 9, 7, 18, 1, 22};
    int len = sizeof(data) / sizeof(data[0]);
    int left = 0;
    int right = len - 1;

    qSort(data, left, right, len, compare_int);

    for (int i = 0; i < len; i++)
        printf(" %d ", data[i]);
}

void qSort(void *data, int left, int right, int len, int (*compare)(const void *, const void *))
{
    assert(data != NULL);
    assert(isfinite(left));
    assert(isfinite(right));

    if (left < right)
    {
        int mid = partition(data, left, right, len, compare);

        qSort(data, left, mid, len, compare);
        qSort(data, mid + 1, right, len, compare);
    }
}

int partition(void *data, int left, int right, int len, int (*compare)(const void *, const void *))
{
    assert(data != NULL);
    assert(isfinite(left));
    assert(isfinite(right));

    int size = sizeof(int); // Размер элемента данных (в данном случае int)
    int mid = (left + right) / 2;
    void *sup_element = (char *)data + mid * size;

    while (1)
    {
        while (compare(data + left * size, sup_element) < 0)
        {
            print_pointer(data, mid, left, right, size);

            left++;

            print_pointer(data, mid, left, right, size);
            print_data(data, mid, left, right, len, size, compare);
        }

        while (compare(data + right * size, sup_element) > 0)
        {
            print_pointer(data, mid, left, right, size);

            right--;

            print_pointer(data, mid, left, right, size);
            print_data(data, mid, left, right, len, size, compare);
        }

        if (left >= right)
        {
            return right;
        }

        print_pointer(data, mid, left, right, size);
        print_data(data, mid, left, right, len, size, compare);

        swap(data, left, right, size);

        print_pointer(data, mid, left, right, size);
        print_data(data, mid, left, right, len, size, compare);

        left++;
        right--;
    }

    return right;
}

void swap(void *data, int a, int b, int size)
{
    assert(data != NULL);
    assert(isfinite(a));
    assert(isfinite(b));

    char temp[size];
    memcpy(temp, (char *)data + a * size, size);
    memcpy((char *)data + a * size, (char *)data + b * size, size);
    memcpy((char *)data + b * size, temp, size);
}

void print_data(void *data, int mid, int left, int right, int len, int size, int (*compare)(const void *, const void *))
{
    assert(data != NULL);
    assert(isfinite(left));
    assert(isfinite(right));
    assert(isfinite(mid));

    for (int i = 0; i < len; i++)
    {
        if (i == mid)
            printf(" %d ", *(int *)((char *)data + i * size));
        else if (i == left)
            printf(COLOR_RED(" %d "), *(int *)((char *)data + i * size));
        else if (i == right)
            printf(COLOR_RED(" %d "), *(int *)((char *)data + i * size));
        else if (i < mid)
            printf(COLOR_YELLOW(" %d "), *(int *)((char *)data + i * size));
        else
            printf(COLOR_BLUE(" %d "), *(int *)((char *)data + i * size));
    }

    printf("\n");
}

void print_pointer(void *data, int mid, int left, int right, int size)
{
    assert(data != NULL);
    assert(isfinite(left));
    assert(isfinite(right));
    assert(isfinite(mid));

    printf("\n");
    printf("левый указатель на номере %d, значение - %d\n", left, *(int    *) ((char *)data + left * size));
    printf("опорный элемент на номере %d, значение - %d\n", mid, *(int *)((char *)data + mid * size));
    printf("правый указатель на номере %d, значение - %d\n", right, *(int *)((char *)data + right * size));
    printf("\n");
}

int compare_int(const void *a, const void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
        return 1;
}


