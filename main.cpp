#include <iostream>

class RingBuffer {
    static constexpr int arraySize = 64;
    char buffer[arraySize];
    int writeIndex = 0;
    int readIndex = 0;
    int counter = 0;

    public:
        /**
         * Method that pushes a byte into the ring buffer
         * @param input byte to be inputted in the buffer
         * @return a boolean to confirm the success/failure of the push
         */
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

        /**
         * method to pop or read the head in the ring buffer.
         *
         * @param the initial value passed by reference to be edited to reflect the current head of the index
         * @return a boolean to confirm the success/failure of the method call as well as the reference of value being
         * edited.
         */
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
    
    return 0;
}