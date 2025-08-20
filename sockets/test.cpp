#include <iostream>
#include <cstring>

int main() {
    uint32_t val = 10;
    uint32_t sum = 0x12345678;
    uint8_t data[16];
    uint32_t file_size = 16;
    uint32_t ChecksumLength = 4;

    uint32_t offset = val;
    if (offset > (file_size - ChecksumLength)) {
        std::cout << "cannot insert checksum at " << offset << " for input size" << file_size << std::endl;
        return 1;
    }

    uint8_t* sumBytesPtr = reinterpret_cast<uint8_t*>(&sum);


    std::memcpy(&data[offset], sumBytesPtr, ChecksumLength);

    for (int i = 0; i < file_size; i++) {
        std::cout << std::hex << (int)data[i] << " ";
    }

    return 0;
}