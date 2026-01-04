#include <vector>
#include <stdexcept>

template <typename T> class RingBuffer {
private:
    int head;
    int tail;
    std::vector<T> buffer;
    int capacity;
public:
    RingBuffer(int fixed_size) {
        if (fixed_size > 0) 
        {buffer = std::vector<T>(fixed_size);
        head = tail = -1;
        capacity = fixed_size;}
        else {
            throw std::invalid_argument("size must be > 0");
        }
    }
    
    bool isFull(){
        return (tail+1)%capacity == head;
    }
    bool isEmpty(){
        return head == -1;
    }

    bool push(const T& value){
   
        if (isFull())
            // buffer is full 
            return false;
        else if (isEmpty())
           { // buffer is empty
                head = head +1;}
        tail = (tail+1)%capacity;
        buffer[tail]=value;
        return true;
        
    }


    bool pop(T& out){
        if (isEmpty())
            return false;
        out =buffer[head];
        if (head == tail)
        {
            // only one element in buffer
            head =-1;
            tail=-1;
        }
        else {
            head = (head+1)%capacity;
        }
        return true;

    }


    


};
