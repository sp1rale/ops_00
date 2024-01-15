#include <iostream>

using namespace std;

template <typename T, size_t MaxSize>
class Queue {
private:
    T elements[MaxSize];
    size_t front;
    size_t rear;

public:
    Queue() : front(0), rear(0) {}

    bool IsEmpty() const {
        return front == rear;
    }

    bool IsFull() const {
        return (rear + 1) % MaxSize == front;
    }

    void Enqueue(const T& value) {
        if (IsFull()) {
        cerr << "Queue is full. Unable to enqueue.\n";
            return;
        }
        elements[rear] = value;
        rear = (rear + 1) % MaxSize;
    }

    void Dequeue() {
        if (IsEmpty()) {
        cerr << "Queue is empty. Unable to dequeue.\n";
            return;
        }
        front = (front + 1) % MaxSize;
    }

    void Show() const {
        cout << "Queue elements: ";
        size_t current = front;
        while (current != rear) {
         cout << elements[current] << " ";
            current = (current + 1) % MaxSize;
        }
        cout << "\n";
    }
};

int main() {
    Queue<int, 5> intQueue;

    intQueue.Enqueue(1);
    intQueue.Enqueue(2);
    intQueue.Enqueue(3);
    intQueue.Show();

    intQueue.Dequeue();
    intQueue.Show();

    intQueue.Enqueue(4);
    intQueue.Enqueue(5);
    intQueue.Enqueue(6); 
    intQueue.Show();

    return 0;
}