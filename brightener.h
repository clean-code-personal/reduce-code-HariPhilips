#include <cstdint>
#include "image.h"
#include <stdexcept>

namespace ImageProcessor
{

    // Define a custom exception for pixel processing errors
    class PixelProcessingException : public std::exception {
    public:
        explicit PixelProcessingException(const char* message) : m_message(message) {}

        const char* what() const noexcept override {
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };

    uint8_t BrightenPixel(int pixelGrayscale, int& attenuatedCount) {
        if (pixelGrayscale > 255) {
            ++attenuatedCount;
            return 255;
        }
        return pixelGrayscale;
    }

    void BrightenWholeImage(std::shared_ptr<Image> inputImage, int& attenuatedCount) {
        if (!inputImage->isSizeValid()) {
            throw PixelProcessingException("Invalid image size.");
        }

        auto brightnerFun = [&attenuatedCount](uint8_t pixelGrayscale, int) {
            uint8_t pixelGrayscaleToAdd = 25;
            return BrightenPixel(pixelGrayscale + pixelGrayscaleToAdd, attenuatedCount);
        };

        inputImage->pixelRunner(brightnerFun);
    }

    void AddBrighteningImage(std::shared_ptr<Image> inputImage, const std::shared_ptr<Image>& imageToAdd, int& attenuatedCount) {
        if (imageToAdd->m_rows != inputImage->m_rows || imageToAdd->m_columns != inputImage->m_columns) {
            throw PixelProcessingException("Image dimensions mismatch.");
        }

        auto brightnerFun = [&attenuatedCount, imageToAdd](uint8_t pixelGrayscale, int index) {
            uint8_t pixelGrayscaleToAdd = imageToAdd->m_pixels[index];
            return BrightenPixel(pixelGrayscale + pixelGrayscaleToAdd, attenuatedCount);
        };

        inputImage->pixelRunner(brightnerFun);
    }
}