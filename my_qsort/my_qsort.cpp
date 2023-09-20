#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "color.h"

void qSort (int data[], int left, int right, int len);
int partition (int data[], int left, int right, int len );
void swap (int data[], int a, int b);
void print_data (int data[], int mid, int left, int right, int len);
void print_pointer (int data[], int mid, int left, int right);

int main ()
{
    int data[] = {4, 18, 9, 0, 90, 8, 15, 88, 9, 7, 18, 1, 22};
    int len = sizeof (data) / sizeof (data[0]);
    int left = 0;
    int right = len - 1;

    qSort (data, left, right, len);

    for (int i = 0; i < len; i++)
        printf (" %d ", data[i]);
}

void qSort (int data[], int left, int right, int len)
{
    assert (data != NULL);
    assert (isfinite (left));
    assert (isfinite (right));

    if (left < right)
    {
        int mid = partition(data, left, right, len);

        qSort(data, left, mid, len);
        qSort(data, mid + 1, right, len);
    }
}

int partition(int data[], int left, int right, int len)
{
    assert (data != NULL);
    assert (isfinite (left));
    assert (isfinite (right));

    int mid = (left + right) / 2;
    int sup_element = data[mid];

    while (1)
    {
        while (data[left] < sup_element)
        {
            print_pointer (data, mid, left, right);

            left++;

            print_pointer (data, mid, left, right);
            print_data (data, mid, left, right, len);
        }

        while (data[right] > sup_element)
        {
            print_pointer (data, mid, left, right);

            right--;

            print_pointer (data, mid, left, right);
            print_data (data, mid, left, right, len);
        }

        if (left >= right)
        {
            return right;
        }

        print_pointer (data, mid, left, right);
        print_data (data, mid, left, right, len);

        swap(data, left, right);

        print_pointer (data, mid, left, right);
        print_data (data, mid, left, right, len);

        left++;
        right--;
    }

    return right;
}


void swap (int data[], int a, int b)
{
    assert (data != NULL);
    assert (isfinite (a));
    assert (isfinite (b));

    int temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void print_data (int data[], int mid, int left, int right, int len)
{
    assert (data != NULL);
    assert (isfinite (left));
    assert (isfinite (right));
    assert (isfinite (mid));

    for (int i = 0; i < len; i++)
    {
        if (i == mid) printf (" %d ", data[i]);
        else if (i == left) printf (COLOR_RED (" %d "), data[i]);
        else if (i == right) printf (COLOR_RED (" %d "), data[i]);
        else if (i < mid) printf (COLOR_YELLOW (" %d "), data[i]);
        else printf (COLOR_BLUE (" %d "), data[i]);
    }

    printf ("\n");
}

void print_pointer (int data[], int mid, int left, int right)
{
    assert (data != NULL);
    assert (isfinite (left));
    assert (isfinite (right));
    assert (isfinite (mid));

    printf ("\n");
    printf ("левый указатель на номере %d, значание - %d\n", left, data[left]);
    printf ("опорный элемент на номере %d, значание - %d\n", mid, data[mid]);
    printf ("правый указатель на номере %d, значание - %d\n", right, data[right]);
    printf ("\n");
}

