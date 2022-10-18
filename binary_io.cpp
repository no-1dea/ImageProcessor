#include "binary_io.h"

void WriteByte(std::ofstream& output, uint8_t byte) {
    output.write(reinterpret_cast<char*>(&byte), 1);
}

void WriteInt(std::ofstream& output, uint32_t value) {
    for (size_t i = 0; i < 4; ++i) {
        WriteByte(output, (value >> i * 8) & 0xFF);
    }
}

uint8_t ReadByte(std::ifstream& input) {
    uint8_t byte;
    input.read(reinterpret_cast<char*>(&byte), 1);
    return byte;
}

uint32_t ReadInt(std::ifstream& input) {
    uint32_t result = 0;
    for (size_t i = 0; i < 4; ++i) {
        result += (ReadByte(input) << i * 8);
    }
    return result;
}

void CopyNBytes(std::ifstream& input, std::ofstream& output, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        WriteByte(output, ReadByte(input));
    }
}

void SkipNBytes(std::ifstream& input, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        ReadByte(input);
    }
}
