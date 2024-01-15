#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct QueueNode {
        T value;
        int priority;

        QueueNode(const T& val, int prio) : value(val), priority(prio) {}

        bool operator<(const QueueNode& other) const {
            return priority < other.priority;
        }
    };

    priority_queue<QueueNode> elements;
    const size_t max_size;

public:
    PriorityQueue(size_t max_size) : max_size(max_size) {}

    bool IsEmpty() const {
        return elements.empty();
    }

    bool IsFull() const {
        return elements.size() == max_size;
    }
 
    void InsertWithPriority(const T& value, int priority) {
        if (IsFull()) {
            cerr << "Queue is full. Unable to insert with priority.\n";
            return;
        }
        elements.push(QueueNode(value, priority));
    }

    void PullHighestPriorityElement() {
        if (IsEmpty()) {
            cerr << "Queue is empty. Unable to pull highest priority element.\n";
            return;
        }
        elements.pop();
    }

   
    const T& Peek() const {
        if (IsEmpty()) {
           cerr << "Queue is empty. Unable to peek.\n";
            static T default_value;
            return default_value;
        }
        return elements.top().value;
    }

    void Show() const {
        cout << "Priority Queue elements:\n";
        priority_queue<QueueNode> copy = elements; 
        while (!copy.empty()) {
        cout << "Value: " << copy.top().value << ", Priority: " << copy.top().priority << "\n";
            copy.pop();
        }
        cout << "\n";
    }
};

int main() {
    PriorityQueue<int> intPriorityQueue(5);

    intPriorityQueue.InsertWithPriority(1, 3);
    intPriorityQueue.InsertWithPriority(2, 1);
    intPriorityQueue.InsertWithPriority(3, 2);
    intPriorityQueue.Show();

    intPriorityQueue.PullHighestPriorityElement();
    intPriorityQueue.Show();

    cout << "Peek: " << intPriorityQueue.Peek() << "\n";

    return 0;
}
