#include "LinkedList.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}

int LinkedList::removeAtIndex(int index)
{
    if(this->head)
    {
        if(index < 0 || index >= this->count)
        {
            cout << "ArrayIndexOutOfBoundException!!!!" << endl;
        }
        else
        {
            //I actuall have something to remove
            if(index == 0)
            {
                return this->removeFront();
            }
            else if(index == this->count-1)
            {
                return this->removeEnd();
            }
            else
            {
                //we are removing from somewhere in the middle
                Node* prevDude = this->head;
                Node* dude2Remove = this->head;

                //How do I get prevDude and dude2Remove set in a single loop?
                //run dude2Remove to the correct index
                for(int i = 0; i < index; i++)
                {
                    dude2Remove = dude2Remove->getNextNode();
                }

                //now make preDude point to the node right before dude2Remove
                while(prevDude->getNextNode() != dude2Remove)
                {
                    prevDude = prevDude->getNextNode();
                }

                /* Identical result as the while loop above
                //what is another way we could have written the while loop above?
                for(int i = 0; i < index-1; i++)
                {
                    prevDude = prevDude->getNextNode();
                }
                */

               //Now everything is position and we are ready to operate!!!
               prevDude->setNextNode(dude2Remove->getNextNode());
               dude2Remove->setNextNode(NULL);
               int value2Return = dude2Remove->getPayload();
               delete(dude2Remove);
               this->count--;
               return value2Return;
            }   
        }
    }
    else
    {
        cout << "Nothing to Remove from the Empty List" << endl;
    }
}

int LinkedList::addAtIndex( int value){
    Node* n=new Node(value);
    int index=this->count;


    if(this->head)
    {
        if(index < 0 || index >= this->count)
        {
            cout << "ArrayIndexOutOfBoundException!!!!" << endl;
        }
        else
        {
            if(index == 0)
            {
                addFront(value);
            }
            else if(index == this->count-1)
            {
                addEnd(value);
            }
            else{
                Node* dude2Add = this->head;
                Node* otherDude=this->head;
                for(int i = 0; i < index-1; i++)
                {
                    dude2Add = dude2Add->getNextNode();
                    otherDude=otherDude->getNextNode();
                }

                otherDude=otherDude->getNextNode();
                dude2Add->setNextNode(n);
                n->setNextNode(otherDude);



                int value2Return = n->getPayload();
                return value2Return;
            }
        }
    }
}
void LinkedList::addEnd(int value)
{
    Node* n = new Node(value);
    if(head == NULL)
    {
        //we have the empty list
        this->head = n;
        this->tail = n;
    }
    else
    {
        //we have a list with at least one element in it, and we know that tail
        //points to the end of that list.
        this->tail->setNextNode(n);
        this->tail = n;
    }
    this->count++;
}

void LinkedList::addFront(int value){
     if(this->head)
    {
        //add it to the front
        Node* n = new Node(value);
        n->setNextNode(this->head);
        this->head = n;
         this->count++;
    }
    else
    {
        //we have an empty list, so addFront and addEnd mean the same thing
        this->addEnd(value);
    }
}

int LinkedList::removeEnd()
{
    if(this->count > 0)
    {
        Node* n = this->tail;
        int value = n->getPayload();
        if(this->count == 1)
        {
            this->head = NULL;
            this->tail = NULL;
            
        }
        else
        {
            Node* currNode = this->head;
            while(currNode->getNextNode() != this->tail)
            {
                currNode = currNode->getNextNode();
            }
            this->tail = currNode;
            this->tail->setNextNode(NULL);
        }
        this->count--;
        delete(n); //if we didn't do this, we technically have a memory leak
        return value;
    }
    
}

int LinkedList::removeFront(){
     if(this->head)
    {
        Node* currFront = this->head;
        this->head = this->head->getNextNode();
        currFront->setNextNode(NULL);
        int valueToReturn = currFront->getPayload();
        delete(currFront);
        this->count--;
        return valueToReturn;
    }
}

void LinkedList::swap(int index1, int index2)
{
    int smaller = index1;
    int larger = index2;
    if(this->get(larger)->getPayload() < this->get(smaller)->getPayload())
    {
        smaller = index2;
        larger = index1;
    }
    Node* smallerNode = this->get(smaller);
    Node* largerNode = this->get(larger);
    printf("smaller: %d, larger: %d\n", smaller, larger);
    smallerNode->setNextNode(largerNode->getNextNode());
    largerNode->setPrevNode(smallerNode->getPrevNode());
    largerNode->setNextNode(smallerNode);
    smallerNode->getNextNode()->setPrevNode(smallerNode);
    smallerNode->setPrevNode(largerNode);
    if(smaller == 0)
    {
        this->head = largerNode;
    }

    if(larger == this->count-1)
    {
        this->tail = smallerNode;
    }
}

Node* LinkedList::get(int index)
{
    Node* node2Return = this->head;
    for(int i = 0; i < index; i++)
    {
        node2Return = node2Return->getNextNode();
    }
    return node2Return;
}

void LinkedList::mergeLinkedLists(int begin1, int end1, int begin2, int end2){
    int pos1=begin1;
    int pos2=begin2;
    for(int i=0;i<this->count;i++){
        if(pos1 <= end1 && pos2 <= end2)
        {
            if(this->get(pos1)->getPayload() < this->get(pos2)->getPayload())
            {
                this->swap(pos1,i);
                pos1++;
            }
            else
            {
                this->swap(pos2,i);
                pos2++;
            }
        }
         else if(pos1 <= end1)
        {
            this->swap(pos1,i);
            pos1++;
        }
        else
        {
            this->swap(pos2,i);
            pos2++;
        }
    }
}

void LinkedList::mergeSortLinkedList(int begin, int end){
    if(this->head != this->tail){
        int begin1=begin;
        int end1=(this->count/2);
        int begin2=end1+1;
        int end2=this->count;
        mergeSortLinkedList(begin1,end1);
        mergeSortLinkedList(begin2,end2);

        mergeLinkedLists(begin1, end1, begin2, end2);
    }
}


void LinkedList::display()
{
    if(this->count == 0)
    {
        cout << "the empty list" << endl;
    }
    else
    {
        Node* currNode = this->head;
        while(currNode->getNextNode() != NULL)
        {
            cout << currNode->getPayload() << " -> ";
            currNode = currNode->getNextNode();
        }
        cout << currNode->getPayload() << endl;
    }
    
}