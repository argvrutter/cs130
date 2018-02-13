/*
 * Author: Aiden Rutter
 * Lab 5 CPP, Assembly sorting
 */
#include <stdlib.h>
#include <iostream>
void c_BubbleSort(char *array, int size);
void c_SelectionSort(short *array, int size);
void c_InsertionSort(int *array, int size);
//greatest sum: double value of one element when added together
long c_GreatestSum(int *array, int size);

extern "C"
{ //Need extern "C" so the linker can see this from assembly w/o name mangling.
    void BubbleSort(char *array, int size);
    void SelectionSort(short *array, int size);
    void InsertionSort(int *array, int size);
    //greatest sum: double value of one element when added together
    long GreatestSum(int *array, int size);
}

void c_BubbleSort(char *array, int size)
{
    bool sorted = 0;
    char temp;
    while(!sorted)
    {
        sorted = 1;
        for(int i=1; i<size; i++)
        {
            if(array[i-1] > array[i])
            {
                //swap
                temp = array[i-1];
                array[i-1] = array[i];
                array[i] = temp;
                sorted = 0;
            }
        }
    }
}

void c_SelectionSort(short *array, int size)
{
    short saveElement, smallest;
    for(int step=0; step<size; step++)
    {
        smallest = step;
        //find smallest
        for(int i=step+1; i<size; i++)
        {
            if(array[i] < array[smallest])
            {
                smallest = i;
            }
        }
        if(smallest != step)
        {
            saveElement=array[step];
            array[step]=array[smallest];
            array[smallest]=saveElement;
        }
    }
}

void c_InsertionSort(int *array, int size)
{
    int currentElement, i;
    for(int step=1; step<size; step++)
    {
        currentElement = array[step];
        i= step-1;
        while(i>=0 && array[i] > currentElement)
        {
            array[i+1] = array[i];
            i-=1;
        }
        array[i+1] = currentElement;
    }
}

long c_GreatestSum(int *array, int size)
{
    //double the largest element to get the largest sum.
    long sum=0;
    c_InsertionSort(array, size);
    array[size-1] *= 2;
    for(int i=0; i<size; i++)
    {
        sum += array[i];
    }
    return sum;
}

int main()
{
    int arr[10];
    short arr2[10];
    char arr3[10];
    srand(3);
    for(int i=0; i<10; i++)
    {
        arr[i] = rand() % 100 -50;
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        std::cout << arr[i] << std::endl;
    }
    std::cout << "arr 1: insertion" << std::endl;
    InsertionSort(arr, 10);
    for(int i=0; i<10; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    std::cout << "arr 2: selection" << std::endl;
    SelectionSort(arr2, 10);
    for(int i=0; i<10; i++)
    {
        std::cout << arr2[i] << std::endl;
    }
    BubbleSort(arr3, 10);
    std::cout << "arr 3: bubble" << std::endl;
    for(int i=0; i<10; i++)
    {
        std::cout << (int)arr3[i] << std::endl;
    }
    std::cout << "c++ greatest sum" << std::endl;
    std::cout << c_GreatestSum(arr, 10) << std::endl;

    std::cout << "assembly greatest sum" << std::endl;
    std::cout << GreatestSum(arr, 10) << std::endl;
}
