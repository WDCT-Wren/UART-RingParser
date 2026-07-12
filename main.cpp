#include <iostream>

struct RingBuffer {
    char array[64];
    int writeIndex = 0;
    int readIndex = 0;

    //TODO: when pushing it should take into consideration if they're overwriting an index.
    void push(char input) {
        if (writeIndex == 64) {
            writeIndex = 0;
        }//does not check if the index is already occupied.
        array[writeIndex] = input;
        writeIndex++;
    }


    char pop() {
        if (readIndex == 64) {
            readIndex = 0;
        }
        const char output = array[readIndex];
        array[readIndex] = 0;
        readIndex++;
        return output;
    }

    bool isFull() {

    }
} ring_buffer;

void writeArray() {
    for (int i = 0; i < 64; i++) {
        std::cout << ring_buffer.array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    char input = 'a';
    for (int i = 0; i < 64; i++) {
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