#pragma once
#include <cstdint>
#include <iostream>
#include <functional>

const int PixelBrightenerFactor = 25;

class Image {
public:
    using PixelProcessCallback = std::function < uint8_t(uint8_t, uint8_t)>;

    Image(uint16_t rows, uint16_t columns) : m_rows(rows), m_columns(columns) {
        m_pixels = new uint8_t[m_rows * m_columns];
    }

    ~Image() {
        std::cout << "freeing pixel memory.\n";
        delete[] m_pixels;
    }

    bool isSizeValid() {
        return m_rows <= 1024 && m_columns <= 1024;
    }

    void pixelRunner(PixelProcessCallback pixelProcessor) {
        for (int x = 0; x < m_rows; x++) {
            for (int y = 0; y < m_columns; y++) {
                int pixelIndex = x * m_columns + y;
                m_pixels[pixelIndex] = pixelProcessor(m_pixels[pixelIndex], PixelBrightenerFactor);
            }
        }
    }

    void pixelRunner(PixelProcessCallback pixelProcessor, std::shared_ptr<Image> imageToAdd) {
        for (int x = 0; x < m_rows; x++) {
            for (int y = 0; y < m_columns; y++) {
                int pixelIndex = x * m_columns + y;
                if (imageToAdd) {
                    m_pixels[pixelIndex] = pixelProcessor(m_pixels[pixelIndex], imageToAdd->m_pixels[pixelIndex]);
                }
            }
        }
    }

    const uint16_t m_rows;
    const uint16_t m_columns;
    uint8_t* m_pixels; // max 1k x 1k image
};
