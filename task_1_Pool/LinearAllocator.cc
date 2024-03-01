#include <cstddef> // for size_t
#include <iostream> // for debugging

class LinearAllocator {
private:
    struct Buffer {
        Buffer* next;
        size_t size;
        char* data;
    };

    Buffer* head;
    size_t bufferSize;
    size_t remainingSize;
    char* currentPtr;

public:
    LinearAllocator(size_t bufferSize) : head(nullptr), bufferSize(bufferSize), remainingSize(0), currentPtr(nullptr) {
        createBuffer();
    }

    ~LinearAllocator() {
        while (head != nullptr) {
            Buffer* temp = head;
            head = head->next;
            delete[] temp->data;
            delete temp;
        }
    }

    void* allocate(size_t size) {
        if (size > remainingSize) {
            createBuffer();
        }

        void* ptr = currentPtr;
        currentPtr += size;
        remainingSize -= size;
        return ptr;
    }

    void reset() {
        head = nullptr;
        createBuffer();
    }

private:
    void createBuffer() {
        Buffer* newBuffer = new Buffer;
        newBuffer->size = bufferSize;
        newBuffer->data = new char[bufferSize];
        newBuffer->next = nullptr;

        if (head == nullptr) {
            head = newBuffer;
        } else {
            Buffer* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newBuffer;
        }

        currentPtr = newBuffer->data;
        remainingSize = bufferSize;
    }
};

int main() {
    LinearAllocator allocator(1024);

    // Example usage
    int* intPtr = static_cast<int*>(allocator.allocate(sizeof(int)));
    *intPtr = 42;

    char* charPtr = static_cast<char*>(allocator.allocate(sizeof(char)));
    *charPtr = 'A';

    std::cout << *intPtr << std::endl; // Output: 42
    std::cout << *charPtr << std::endl; // Output: A

    allocator.reset();

    return 0;
}
