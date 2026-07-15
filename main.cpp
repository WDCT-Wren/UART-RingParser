#include <iostream>

class RingBuffer {
    static constexpr int arraySize = 64;
    char buffer[arraySize];
    int writeIndex = 0;
    int readIndex = 0;
    int counter = 0;

    public:
        bool push(const char input) {
            // First checks if the array is full
            if (!isFull()) {
                buffer[writeIndex] = input;
                writeIndex = (writeIndex + 1) % arraySize;
                counter++;
                return true;
            }
            return false;
        }


        bool pop(char& value) {

            if (isEmpty()) {
                return false;
            }

            value = buffer[readIndex];

            readIndex = (readIndex + 1) % arraySize;

            counter--;
            return true;
        }

        bool isFull() const {
            return counter == arraySize;
        }

        bool isEmpty() const {
            return counter == 0;
        }
} ring_buffer;

int main() {
    // TODO: properly test the wraparound mechanic of the write and read index of the ring buffer.
    return 0;
}