#include "binary_io.h"
#include "picture.h"

namespace {
size_t CalculatePadding(size_t width) {
    for (size_t padding = 0; padding < 4; ++padding) {
        if ((width * 3 + padding) % 4 == 0) {
            return padding;
        }
    }
    return 0;
}

Color ReadPixel(std::ifstream& input) {
    Color pixel;
    pixel.blue = ReadByte(input);
    pixel.green = ReadByte(input);
    pixel.red = ReadByte(input);
    return pixel;
}

void ReadMatrixOfPixels(std::ifstream& input, std::vector<std::vector<Color>>& data, size_t width, size_t height) {
    size_t padding = CalculatePadding(width);
    for (size_t y = height; y >= 1; --y) {
        for (size_t x = 0; x < width; ++x) {
            data[y - 1][x] = ReadPixel(input);
        }
        SkipNBytes(input, padding);
    }
}

void WritePixel(std::ofstream& output, const Color& pixel) {
    WriteByte(output, pixel.blue);
    WriteByte(output, pixel.green);
    WriteByte(output, pixel.red);
}

void WritePadding(std::ofstream& output, size_t padding) {
    for (size_t i = 0; i < padding; ++i) {
        WriteByte(output, 0);
    }
}

void WriteBMPHeader(std::ofstream& output, size_t width, size_t height) {
    WriteByte(output, 66);
    WriteByte(output, 77);
    int size_of_file = 54 + width * height * 3 + CalculatePadding(width) * width;
    for (const auto& four_bytes : {size_of_file, 0, 54}) {
        WriteInt(output, four_bytes);
    }
}

void WriteDIBHeader(std::ofstream& output, size_t width, size_t height) {
    WriteInt(output, 40);
    WriteInt(output, width);
    WriteInt(output, height);
    for (const auto& byte : {1, 0, 24, 0}) {
        WriteByte(output, byte);
    }

    for (const auto& four_bytes : {0, 16, 2835, 2835, 0, 0}) {
        WriteInt(output, four_bytes);
    }
}

void WriteMatrixOfPixels(std::ofstream& output, const std::vector<std::vector<Color>>& data, size_t width,
                         size_t height) {
    size_t padding = CalculatePadding(width);
    for (size_t y = height; y >= 1; --y) {
        for (size_t x = 0; x < width; ++x) {
            WritePixel(output, data[y - 1][x]);
        }
        WritePadding(output, padding);
    }
}
}  // namespace

Picture::Picture() = default;

Picture::Picture(std::ifstream& input) {
    size_t bytes_before_size = 18;
    size_t bytes_before_matrix = 28;
    SkipNBytes(input, bytes_before_size);
    width_ = ReadInt(input);
    height_ = ReadInt(input);
    SkipNBytes(input, bytes_before_matrix);

    data_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
    ReadMatrixOfPixels(input, data_, width_, height_);
}

size_t Picture::GetWidth() const {
    return width_;
}

size_t Picture::GetHeight() const {
    return height_;
}

std::vector<std::vector<Color>> Picture::GetCopyOfPixelMatrix() const {
    return data_;
}

Color& Picture::GetPixel(size_t row, size_t column) {
    return data_[row][column];
}

void Picture::ChangeWidth(size_t new_width) {
    width_ = new_width;
}

void Picture::ChangeHeight(size_t new_height) {
    height_ = new_height;
}

void Picture::Save(std::ofstream& output) {
    WriteBMPHeader(output, width_, height_);
    WriteDIBHeader(output, width_, height_);
    WriteMatrixOfPixels(output, data_, width_, height_);
}
