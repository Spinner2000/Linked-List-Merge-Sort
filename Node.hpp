class Node
{
    private:
        int payload;
        Node* nextNode;
        Node* prevNode;
    
    public:
        Node(int payload);
        void setPrevNode(Node* n);
        void setNextNode(Node* n);
        Node* getNextNode();
        Node* getPrevNode();
        int getPayload();
};