#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

typedef CircleShape ElementType;
static int a = 0;

class Balls : CircleShape
{
public:
    
    class Node 
    {
    public:

        //------ Node DATA MEMBERS
        ElementType data;
        Node* next;
        Node* prev;
        int index;
        
        //------ Node OPERATIONS
        //-- Default constrctor: initializes next member to Node()
        Node()
            : next(0), prev(0)
        {}
        //-- Explicit-value constructor:  initializes data member to dataValue
        //--                             and next member to 0
        Node(int index)
            : next(0), prev(0)
        {}

        Node(ElementType dataValue, int index)
            : data(dataValue), next(0), prev(0), index(index)
        {}

        //Color getFillColor()
        //{
        //    return CircleShape::getFillColor();
        //}

        //Vector2f getPosition()
        //{
        //    return CircleShape::getPosition();
        //}

        //void move(Vector2f velocity)
        //{
        //    CircleShape::move(velocity);
        //}

        //FloatRect getGlobalBounds()
        //{
        //    return CircleShape::getGlobalBounds();
        //}

        //void draw(RenderWindow& w)
        //{
        //    w.draw((CircleShape)*this);
        //}

    }; //--- end of Node class

    typedef Node* NodePointer;

    //-- Definition of the class constructor
    Balls()
        : first(0), mySize(0)
    {}

     //-- Definition of the destructor
    ~Balls() 
    {
        NodePointer prevptr = first,
             ptr;

            while (prevptr != 0)
            {
                ptr = prevptr->next;
                delete prevptr;
                prevptr = ptr;
            }
    }
    
    // Definition of empty()
    bool empty()
    {
        return mySize == 0;
    }

    //-- Definition of insert()
    void insert(ElementType dataVal, int index)
    {
        if (index < 0 || index > mySize)
        {
            cerr << "can't insert at " << index << endl;
            return;
        }

        NodePointer newPtr = new Node(dataVal, index),
            predPtr = first, nextptr;
        if (index == 0)
        {
            if (empty())
            {
                newPtr->next = first;
                first = newPtr;
                mySize++;
                int i = 0;
                NodePointer delptr = first;
                while (delptr != 0) {
                    delptr->index = i++;
                    delptr = delptr->next;
                }
                return;
            }
            else {
                newPtr->next = first;
                first->prev = newPtr;
                first = newPtr;
                mySize++;
                int i = 0;
                NodePointer delptr = first;
                while (delptr != 0) {
                    delptr->index = i++;
                    delptr = delptr->next;
                }
                newPtr->data.setPosition(predPtr->data.getPosition().x + 80.f, predPtr->data.getPosition().y);
                return;
            }
        }
        else {
            if (index == mySize)
            {
                while (predPtr->next != 0)
                    predPtr = predPtr->next;
                predPtr->next = newPtr;
                newPtr->prev = predPtr;
                newPtr->data.setPosition(predPtr->data.getPosition().x + 80.f, predPtr->data.getPosition().y);
                mySize++;
                int i = 0;
                NodePointer delptr = first;
                while (delptr != 0) {
                    delptr->index = i++;
                    delptr = delptr->next;
                }
                return;
            }
            for (int i = 1; i < index; i++)
                predPtr = predPtr->next;
            nextptr = predPtr->next;
            if (nextptr != 0)nextptr->prev = newPtr;
            newPtr->next = nextptr;
            newPtr->prev = predPtr;
            predPtr->next = newPtr;
            //            newPtr->data.setPosition(predPtr->data.getPosition().x + 80.f, predPtr->data.getPosition().y);
            //            predPtr=predPtr->next;
            //            for(newPtr=first;newPtr->next!=0;newPtr=newPtr->next);
            //            while (nextptr->next != 0 && newPtr->data.getPosition().x < 1020)
            //            {
            //                nextptr->data.move(predPtr->data.getPosition().x + 80.f, nextptr->data.getPosition().y);
            //                nextptr = nextptr->next;
            //                predPtr = predPtr->next;
            //            }
            predPtr = first;
            newPtr = first->next;
            for (nextptr = first; nextptr->next != 0; nextptr = nextptr->next);
            while (nextptr->data.getPosition().x < 1300 && newPtr->next != 0)
            {
                newPtr->data.setPosition(predPtr->data.getPosition().x + 80.f, newPtr->data.getPosition().y);
                predPtr = predPtr->next;
                newPtr = newPtr->next;
            }
        }
        int i = 0;
        NodePointer delptr = first;
        while (delptr != 0) {
            delptr->index = i++;
            delptr = delptr->next;
        }
        mySize++;
        //        nextptr = first;
        //        for (; nextptr->next != 0; nextptr = nextptr->next);
        //        predPtr = nextptr->prev;
        //        while (predPtr->prev!=0)
        //        {
        //            predPtr->data.setPosition(nextptr->data.getPosition().x - 80.f, predPtr->data.getPosition().y);
        //            predPtr = predPtr->prev;
        //            nextptr = nextptr->prev;
        //        }
    }

    //-- Definition of erase()
    void erase(int index)
    {
        if (index < 0 || index >= mySize)
        {
            cerr << "can't delete at " << index << endl;
            return;
        }
        mySize--;

        NodePointer ptr,
            predPtr = first, nextPtr;
        if (index == 0)
        {
            ptr = first;
            first = ptr->next;
            delete ptr;
            if (!empty()) {
                first->prev = 0;
            }
        }
        else
        {
            for (int i = 1; i < index; i++)
                predPtr = predPtr->next;
            ptr = predPtr->next;
            nextPtr = ptr->next;
            if (predPtr != 0)predPtr->next = nextPtr;
            if (nextPtr != 0)nextPtr->prev = predPtr;
            delete ptr;
        }
        if (empty()) return;
        int i = 0;
        NodePointer delptr = first;
        while (delptr != 0) {
            delptr->index = i++;
            delptr = delptr->next;
        }
        ptr = first->next;
        predPtr = first;
        for (delptr = first; delptr->next != 0; delptr = delptr->next);
        while (ptr != 0 && delptr->data.getPosition().x < 1020)
        {
            ptr->data.setPosition(predPtr->data.getPosition().x - 80.f, ptr->data.getPosition().y);
            ptr = ptr->next;
            predPtr = predPtr->next;
        }
    }

    //Definition of destroy function
    void destroy(ElementType data, int index) {
        NodePointer prevptr, newptr, nextptr;
        newptr = first;
        if (index == 0) //check if index is 0 
        {
            if (data.getFillColor() == first->data.getFillColor()) //if data of the first element is the same of the one to be inserted 
            {
                while (data.getFillColor() == first->data.getFillColor()) // the first and the next elements of the same data are destroyed
                {
                    erase(0);
                    if (first == 0) {
                        break;
                    }
                }
                return;
            }
            /*else {
                insert(data, 0);
                return;
            }*/
        }

        if (index == mySize) //check if index is my size
        {
           /* insert(data, mySize);*/
            while (newptr->index != index) {
                newptr = newptr->next;
            }
            prevptr = newptr->prev;
            if (prevptr->data.getFillColor() == data.getFillColor()) //if data of the last element is the same of the one to be inserted
            {
                while (prevptr->data.getFillColor() == data.getFillColor()) // the last and all the previous elements of the same data are destroyed
                {
                    erase(prevptr->index);
                    prevptr = newptr->prev;
                    if (prevptr == 0)break;
                }
                erase(newptr->index);
                return;
            }
            else {
                return;
            }
        }
        /*insert(data, index);*/
        while (newptr->index != index) //newptr points at the node inserted
        {
            newptr = newptr->next;
            if (newptr == 0) break;
        }

        prevptr = newptr->prev;
        nextptr = newptr->next;
        if (newptr->data.getFillColor() != nextptr->data.getFillColor() && newptr->data.getFillColor() != prevptr->data.getFillColor())
        {
            return;//return directly after inserting if node strikes 2 nodes of different data  
        }
        else {
            while (prevptr->data.getFillColor() == newptr->data.getFillColor()) //erase all previous nodes that are of the same data
            {
                erase(prevptr->index);
                prevptr = newptr->prev;
                if (prevptr == 0) 
                {
                    prevptr = newptr;
                    break;
                }
            }
            while (nextptr->data.getFillColor() == newptr->data.getFillColor()) //erase all next nodes that are of the same data
            {
                erase(nextptr->index);
                nextptr = newptr->next;
                if (nextptr == 0) 
                {
                    nextptr = newptr;
                    break;
                }
            }
        }

        ElementType tempprev = prevptr->data;
        ElementType tempnext = nextptr->data;
        while (tempprev.getFillColor() == tempnext.getFillColor()) //balls collision after destroying balls at the inserted location
        {
            if (mySize == 3) //check whether all nodes are going to be destroyed 
            {
                if (first->data.getFillColor() == first->next->next->data.getFillColor()) {
                    erase(0);
                    erase(0);
                    erase(0);
                    return;
                }
            }
            if (prevptr != 0) 
            {
                erase(prevptr->index);
                prevptr = newptr->prev;
            }
            if (nextptr != 0) 
            {
                erase(nextptr->index);
                nextptr = newptr->next;
            }
            if (prevptr != 0) 
            {
                if (prevptr->prev != 0) 
                {
                    while (prevptr->data.getFillColor() == prevptr->prev->data.getFillColor())
                    {
                        erase(prevptr->index);
                        prevptr = newptr->prev;
                        if (prevptr->prev == 0) 
                        {
                            erase(0);
                            break;
                        }
                    }
                }
            }
            if (nextptr != 0) 
            {
                if (nextptr->next != 0) 
                {
                    while (nextptr->data.getFillColor() == nextptr->next->data.getFillColor())
                    {
                        erase(nextptr->index);
                        nextptr = newptr->next;
                        if (nextptr->next == 0) 
                        {
                            erase(mySize - 1);
                            break;
                        }
                    }
                }
            }
            if (prevptr != 0) 
            {
                if (tempprev.getFillColor() == prevptr->data.getFillColor())
                {
                    erase(prevptr->index);
                    prevptr = newptr->prev;
                }
            }
            if (nextptr != 0) 
            {
                if (tempnext.getFillColor() == nextptr->data.getFillColor())
                {
                    erase(nextptr->index);
                    nextptr = newptr->next;
                }
            }
            if (prevptr == 0 || nextptr == 0) break;
            tempprev = prevptr->data;
            tempnext = nextptr->data;
        }
        erase(newptr->index);
        if (first == 0) 
        {
            cout << "Good game" << endl;
        }
    };

    int getIndex(Node *p)
    {
        return p->index;
    }


    Color getFillColor(int index)
    {
        NodePointer ptr= first;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        return ptr->data.getFillColor();
    }

    Vector2f getPosition(int index)
    {
        NodePointer ptr = first;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        return ptr->data.getPosition();
    }

    void move(Vector2f velocity , int index)
    {
        NodePointer ptr = first;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        ptr->data.move(velocity);;
    }

    FloatRect getGlobalBounds(int index)
    {
        NodePointer ptr = first;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        return ptr->data.getGlobalBounds();
    }

    void draw(RenderWindow& w , int index)
    {
        NodePointer ptr = first;
        for (int i = 0; i<index; i++)
            ptr = ptr->next;

       w.draw((CircleShape)ptr->data);
    }

    int getIndex(FloatRect loc)
    {
        NodePointer ptr = first;
        while (ptr != 0)
        {
            if (ptr->data.getGlobalBounds().intersects(loc))
                return ptr->index;
            ptr = ptr->next;
        }
        return -1;
    }

private:
    //data members
    NodePointer first;
    int mySize;
};