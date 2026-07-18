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

        void printBuffer() {
            for (int i = 0; i < arraySize; i++) {
                std::cout << buffer[i] << " ";
            }
            std::cout << std::endl;
        }
} ring_buffer;

int main() {
    int constexpr bufferSize = 64;

    char data[bufferSize] = {
        'i', '1', 'j', '5', '2', 'M', '*', 'w', 'Q', 'p', '^', '$', '@', '4', '_', '8',
        '%', 'k', '3', '&', 'G', '!', '9', '7', 'x', 'V', 'z', 'D', '_', 'h', 'L', '=',
        '0', '{', 'a', 'T', '[', 'u', 'Y', 'm', '|', '~', 'y', '9', '!', 'c', '2', 'b',
        '4', 'L', '+', 'X', '6', 'P', '~', 'R', '9', '_', 'z', '4', '#', 'Q', '2', 'g'
    };

    char reciever[bufferSize] = {
        'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'
    };

    // push 64 bytes filling the system
    for (int i = 0; i < bufferSize; i++) {
        ring_buffer.push(data[i]);
    }
    std::cout << ring_buffer.isFull() << std::endl;

    // pop 32 bytes
    for (int i = 0; i < 32; i++) {
        ring_buffer.pop(reciever[i]);
    }

    //display the popped 32 bytes
    for (int i = 0; i < bufferSize; i++) {
        std::cout << reciever[i] << " ";
    }
    std::cout << std::endl;

    // push another 32 to wrap the tail around
    for (int i = 0; i < 32; i++) {
        ring_buffer.push(data[i]);
    }
    std::cout << ring_buffer.isFull() << std::endl;

    // then pop the whole buffer.
    std::cout << "popped buffer: " << std::endl;
    for (int i = 0; i < bufferSize; i++) {
        ring_buffer.pop(reciever[i]);
    }

    for (int i = 0; i < bufferSize; i++) {
        std::cout << reciever[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "real buffer: " << std::endl;
    ring_buffer.printBuffer();

    /*
     * TODO: trace the expected pop sequence by hand.
     */
    return 0;
}