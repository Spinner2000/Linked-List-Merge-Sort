#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>
#include "LinkedList.hpp"
#define ARRAYSIZE 6
using namespace std;
void displayArray(int* ar, int begin, int end)
{
    for(int i = begin; i <= end; i++)
    {
        cout << ar[i] << " ";
    }
    cout << endl;
}
//the goal is to ensure that the array from begin1 to end2 is in order
void merge(int* ar, int begin1, int end1, int begin2, int end2)
{
    int size = end2 - begin1 + 1;
    int temp[size];
    int pos1 = begin1;
    int pos2 = begin2;
    for(int i = 0; i < size; i++)
    {
        //how do we ask if pos1 points to a legal place on the left half of the list?
        if(pos1 <= end1 && pos2 <= end2)
        {
            if(ar[pos1] < ar[pos2])
            {
                temp[i] = ar[pos1];
                pos1++;
            }
            else
            {
                temp[i] = ar[pos2];
                pos2++;
            }
        }
        else if(pos1 <= end1)
        {
            temp[i] = ar[pos1];
            pos1++;
        }
        else
        {
            temp[i] = ar[pos2];
            pos2++;
        }
    }
    
    //temp is filled up with our values in the correct order
    //we need to now transfer those value back over to ar overwriting
    //the old contents of ar with the contents of temp between begin1 and end2
    int tempPos = 0;
    for(int i = begin1; i <= end2; i++)
    {
        ar[i] = temp[tempPos];
        tempPos++;
    }
    //now ar is overwritten between begin1 and end2 with the values in order
    //and this call to merge and mergesort can end;
}
//the job of this function is to sort the list from begin to end
void mergeSort(int* ar, int begin, int end)
{
    //displayArray(ar, begin, end);
    
    //we only need to do anything in here, if the list is bigger than a 1 list
    if(begin != end)
    {
        //we DO NOT HAVE A 1 LIST!!!!!
        //so we need to divide our list in half and call mergesort on each half
        int begin1 = begin;
        int end1 = (begin + end) / 2;
        int begin2 = end1 + 1;
        int end2 = end;
        mergeSort(ar, begin1, end1);
        mergeSort(ar, begin2, end2);
        
        //now the left half is sorted and the right half is sorted
        //we need to merge them together into a single sorted portion
        //of our list from begin to end 
        merge(ar, begin1, end1, begin2, end2);
    }
    
}
int main(int argc, char** argv)
{
    srand (time(NULL));
    int ar[ARRAYSIZE];
    /*
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        ar[i] = rand() % 101;
    }
    */
    //4 2 1 6 0 3
    ar[0] = 4;
    ar[1] = 2;
    ar[2] = 1;
    ar[3] = 6;
    ar[4] = 0;
    ar[5] = 3;
    displayArray(ar, 0, ARRAYSIZE-1);
    mergeSort(ar, 0, ARRAYSIZE-1);
    displayArray(ar, 0, ARRAYSIZE-1);

    //Create Linked List
    LinkedList* ll = new LinkedList();
    ll->addFront(4);
    ll->addEnd(2);
    ll->addEnd(1);
    ll->addEnd(6);
    ll->addEnd(0);
    ll->addEnd(3);
    ll->display();
    ll->mergeSortLinkedList(1,NULL);
    ll->display();
    return 0;
}