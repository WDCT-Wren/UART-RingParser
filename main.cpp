#include <iostream>

struct RingBuffer {
    char array[64];
    int writeIndex = 0;
    int readIndex = 0;

    void push(const char input) {
        if (writeIndex == 64) writeIndex = 0;
        std::cout << writeIndex << std::endl;

        // First checks if the index being written on is already occupied.
        if (array[writeIndex] != 0) {
            // placeholder consequence for trying to overwrite an already-occupied index
            std::cout << "index already filled!" << std::endl;
        }
        else {
            array[writeIndex] = input;
        }
        writeIndex++;
    }


    char pop() {
        if (readIndex == 64) {
            readIndex = 0;
        }
        const char output = array[readIndex];
        array[readIndex] = '\0';
        readIndex++;
        return output;
    }

    bool isFull() {

    }

    bool isEmpty() {

    }
} ring_buffer;

void writeArray() {
    for (int i = 0; i < 65; i++) {
        if (ring_buffer.array[i] == 0) std::cout << "0" << " ";
        std::cout << ring_buffer.array[i];
    }
    std::cout << std::endl;
}

int main() {
    char input = 'a';
    for (int i = 0; i < 65; i++) {
        ring_buffer.push(input);
        input++;
    }

    std::cout << ring_buffer.writeIndex << std::endl;
    writeArray();

    for (int i = 0; i < 64; i++) {
        std:: cout << ring_buffer.pop() << " ";
        input++;
    }
    std:: cout << std::endl;
    writeArray();

    return 0;
}