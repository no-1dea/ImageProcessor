#pragma once

#include <cstdint>
#include <fstream>

void WriteByte(std::ofstream &output, uint8_t byte);

void WriteInt(std::ofstream &output, uint32_t value);

uint8_t ReadByte(std::ifstream &input);

uint32_t ReadInt(std::ifstream &input);

void CopyNBytes(std::ifstream &input, std::ofstream &output, size_t n);

void SkipNBytes(std::ifstream &input, size_t n);
