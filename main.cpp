/*
 * Emmanuel Adebayo
 * 2/23/21
 * main.cpp
 * priority quueue with linked list
 */
#include <iostream>
#include <string>

using namespace std;

template <class TBD>
class dynamicPriorityQueue {
private:
    struct Node {
        TBD name, address, city, state, zip, postalClass;
        Node* next;

        Node(TBD name, TBD address, TBD city, TBD state, TBD zip, TBD postalClass){
            this->name = name;
            this->address = address;
            this->city = city;
            this->state = state;
            this->zip = zip;
            this->postalClass = postalClass;
            next = NULL;
        }
    };

    Node* head;
    Node* tail;
    int count;
    int capacity;

public:
    //capacity of zero means unlimited
    dynamicPriorityQueue(int capacity = 0){
        if (capacity < 0){
            throw invalid_argument("capacity cannot be less than zero");
        }
        head = NULL;
        tail = NULL;
        count = 0;
        this->capacity = capacity;
    }

    //copy constructor
    dynamicPriorityQueue(const dynamicPriorityQueue& other){
        cout <<"copy constructor called" <<endl;
        purgeQueue();
        head = NULL;
        tail = NULL;
        count = other.count;
        capacity = other.capacity;

        if (other.head != NULL){
            Node* otherPtr = other.head;
            Node* last = new Node (otherPtr->item);
            head = last;
            tail = last;

            while (otherPtr->next != NULL) {
                otherPtr = otherPtr->next;
                Node* temp = new Node(otherPtr->item);
                tail->next = temp;
                tail = tail->next;
            }
        }
    }

    dynamicPriorityQueue& operator=(const dynamicPriorityQueue& other){
        cout <<"Assignmengt operator called" <<endl;
        return *this;
    }
    ~dynamicPriorityQueue(){
        purgeQueue();
    }
    int getSize(){
        return count;
    }
    int getCapacity(){
        return capacity;
    }
    bool empty(){
        return (head == NULL);
    }
    bool full(){
        return (count == capacity);
    }
    TBD getHead(){
        if (head == NULL){
            throw underflow_error("Queue is empty!!!");
        }
        return head->item;
    }
    TBD getTail(){
        if (tail == NULL){
            throw underflow_error("queue is empty!!!");
        }
        return tail->item;
    }
    void push(TBD name, TBD adress, TBD city, TBD state, TBD zip, TBD postClass){

        enum PostalClass {
            Priority_Mail_Express = 1,
            Priority_Mail,
            First_Class_Mail,
            Periodicals,
            USPS_Marketing_Mail,
            Package_Services,
            USPS_Retail_Ground
        };

        //check postal class

        if (postClass == "Priority_Mail_Express"){
            PostalClass postalClass = Priority_Mail_Express;
            postClass = postalClass;
        }
        else if (postClass == "Priority_Mail"){
            PostalClass postalClass = Priority_Mail;
            postClass = postalClass;
        }
        else if (postClass == "First_Class_Mail"){
            PostalClass postalClass = First_Class_Mail;
            postClass = postalClass;
        }
        else if (postClass == "Periodicals"){
            PostalClass postalClass = Periodicals;
            postClass = postalClass;
        }
        else if (postClass == "USPS_Marketing_Mail"){
            PostalClass postalClass = USPS_Marketing_Mail;
            postClass = postalClass;
        }
        else if (postClass == "Package_Services"){
            PostalClass postalClass = Package_Services;
            postClass = postalClass;
        }
        else if (postClass == "USPS_Retail_Ground"){
            PostalClass postalClass = USPS_Retail_Ground;
            postClass = postalClass;
        } else{
            cout<<"not in category"<<endl;
            throw invalid_argument("nnot in category");
        }


        //use capacity of zero to indicate unlimited
        if (capacity != 0 && count == capacity){
            throw overflow_error("queue is at capacity!!!");
        }
        //insert at the head;

        if (head == NULL || head->postalClass > postClass ){
            cout <<"adding " <<name << " to the start of queue" <<endl;
            Node* temp = new Node(name, adress, city, state, zip, postClass);
            temp->next = head;
            head = temp;
            tail = temp;

        } else{

            Node* current = head;
            Node* temp = new Node(name, adress, city, state, zip, postClass);

            //iterate until we reach end of list

            while (current->next != NULL) {

                if (postClass < current->next->postalClass) {
                    temp->next = current->next;
                    current->next = temp;
                    break;
                }


                current = current->next;
            }


            //if we reached end of list we add at the end
            if (current->next == NULL) {
                cout << "Adding " << name << " to end of list!!!" << endl;
                current->next = temp;
            }

        }
        count++;
    }

    void pop(){
        if (head == NULL){
            throw underflow_error("queue is empty!!!");
        }
        cout <<"deleting "<<head->item <<"from queue" <<endl;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
    }

    void printQueue(){
        Node* current = head;

        //iterate until we reach end of list
        while (current != NULL){
            cout << current->name <<endl;
            cout << current->address <<endl;
            cout << current->city <<endl;
            cout << current->state <<endl;
            cout << current->zip <<endl;
            cout << current->postalClass <<endl;
            current = current->next;
        }
    }
    void purgeQueue(){
        Node* current = head;
        Node* temp;

        //iterate until we reach end of list
        while (current != NULL){
            temp = current;
            current = current->next;

            cout <<"deleting " <<temp->name <<endl;
            delete temp;
        }
        count = 0;
        head = NULL;
        tail = NULL;
    }



};

int main() {

                            /*
                             *
                             *
                             * Priority_Mail_Express = 1,
                                Priority_Mail,
                                First_Class_Mail,
                                Periodicals,
                                USPS_Marketing_Mail,
                                Package_Services,
                                USPS_Retail_Ground
                             * */



    dynamicPriorityQueue<string> myQueue;

    myQueue.push("jason", "2017 foyt drive", "chicago", "ohare", "2233", "USPS_Retail_Ground");
    myQueue.push("segun", "2333 cou act", "bamidele", "vegas", "6637", "Package_Services");
    myQueue.push("ojo", "1245 eps way", "texas", "aboot", "8337", "USPS_Marketing_Mail");
    myQueue.push("lanre", "6234 lakeview drive", "ekitu", "onodo", "hhgh", "Periodicals");
    myQueue.push("reagan", "white foyt drive", "washigton", "indiana", "0001", "Priority_Mail_Express");
    myQueue.push("dancdr", "idk sum drive", "terrehaute", "indiana", "7878", "First_Class_Mail");
    myQueue.push("dimmy", "last foyt drive", "indianapolis", "indiana", "46224", "Priority_Mail");




    //shallow copy
/*
    dynamicPriorityQueue<string> anotherQueue;
    anotherQueue = myQueue;
*/
    cout<<"info out"<<endl;
    cout<<endl;
    myQueue.printQueue();

    cout<<endl;
   //cout<<"printing another queue"<<endl;
    //anotherQueue.printQueue();


    return 0;
}
