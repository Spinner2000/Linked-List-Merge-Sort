#include "Node.hpp"

class LinkedList
{
    private:
        Node* head;
        Node* tail;
        int count;
        Node* get(int index);
        void swap(int index1, int index2);

    public:
        LinkedList();
        void mergeLinkedLists(int begin1, int end1, int begin2, int end2);
        void display();
        void addEnd(int value);
        void addFront(int value);
        void mergeSortLinkedList(int begin, int end);
        int removeEnd();
        int removeFront();
        int removeAtIndex(int index);
        int addAtIndex( int value);
};