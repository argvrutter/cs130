/*
 * Author: Aiden Rutter
 * Lab 5 CPP, Assembly sort
 */
#include <iostream>
void c_BubbleSort(char *array, int size);
void c_SelectionSort(short *array, int size);
void c_InsertionSort(int *array, int size);
long c_GreatestSum(int *array, int size);

extern "C"
{ //Need extern "C" so the linker can see this from assembly w/o name mangling.
    void BubbleSort(char *array, int size);
    void SelectionSort(short *array, int size);
    void InsertionSort(int *array, int size);
    long GreatestSum(int *array, int size);
}

void c_BubbleSort(char *array, int size)
{
    bool sorted = 0;
    std::string temp;
    while(!sorted)
    {
        sorted = 1;
        for(int i=1; i<size; i++)
        {
            if(array[i-1] > array[i])
            {
                //swap function?
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

}

void c_InsertionSort(int *array, int size)
{

}

long c_GreatestSum(int *array, int size)
{

}
