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

class CommandParser {
    // TODO: Phase 2 - Command Parser
    // 1. Fake byte source: hardcoded string "LED ON\nTEMP?\nLED OFF\n", push() into ring buffer one byte at a time (simulates UART)
    // 2. Command accumulator: separate fixed char array, pop() bytes off ring buffer into it until '\n' hit = one complete command. No std::string/dynamic alloc. Needs own counter (like ring buffer's).
    // 3. Reset accumulator after each complete command (array contents vs counter - same lesson as ring buffer)
    // 4. Compare accumulated command against known strings ("LED ON", "LED OFF", "TEMP?") - find the right C-string comparison tool (not ==)
    // 5. cout the matched command (no state changes yet - that's phase 3)
    // Checkpoint: feed full 3-command string, confirm all 3 match correctly in order, no leftover bytes bleeding between commands
    // Decide: interleave push/pop in one loop, or two separate passes? (think: which matches real UART behavior)
} command_parser;

int main() {
    return 0;
}