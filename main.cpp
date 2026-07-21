#include <iostream>
#include <cstring>

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
         * @param value the initial value passed by reference to be edited to reflect the current head of the index
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

class CommandParser {
    static constexpr int cmdSize = 64;
    char cmd[cmdSize];
    int index = 0;
    // 2. Command accumulator: separate fixed char array, pop() bytes off ring buffer into it until '\n' hit = one complete command.
    // No std::string/dynamic alloc. Needs own counter (like ring buffer's).
    public:
        void process(RingBuffer& ring_buffer) {
            char value;

            while (ring_buffer.pop(value)) {
                if (index >= (cmdSize - 1)) {
                    std::cout << "Command Overload! inputted command is larger than 64 bytes!" << std::endl;
                    index = 0;
                }
                if (value == '\n') {
                    cmd[index] = '\0';

                    // Currently cout since dispatching and tokenizing is in phase 3.
                    std::cout << "Command received: " << cmd << std::endl;
                    compare();

                    // Reset accumulator after each complete command
                    index = 0;
                    continue;
                }
                cmd[index++] = value;
            }
        }

    // 4. Compare accumulated command against known strings ("LED ON", "LED OFF", "TEMP?") - find the right C-string comparison tool (not ==)
        void compare() {
            const char* commands[] = {"LED ON", "LED OFF", "TEMP?"};

            for (int i = 0; i < 3; i++) {
                if (std::strcmp(cmd, commands[i]) == 0) {
                    // cout the matched command (no state changes yet - that's phase 3)
                    std::cout << "Command found!: " << commands[i] << std::endl;
                    break;
                }
            }
        }
} command_parser;

int main() {
    char* command = "LED ON\nTEMP?\nLED OFF\n";

    for (int i = 0;i < strlen(command); i++) {
        ring_buffer.push(command[i]);
    }
    command_parser.process(ring_buffer);

    return 0;
}