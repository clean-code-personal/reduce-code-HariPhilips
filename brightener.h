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


    void BrightenWholeImage(std::shared_ptr<Image> inputImage, int& attenuatedCount) {
        if (!inputImage->isSizeValid()) {
            throw PixelProcessingException("Invalid image size.");
        }

        auto BrightnerFun = [&attenuatedCount](uint8_t pixelGrayscale, int) {
            uint8_t outputGrayscale = pixelGrayscale;
            if (outputGrayscale > (255 - 25)) {
                ++attenuatedCount;
                outputGrayscale = 255;
            }
            else {
                outputGrayscale += 25;
            }

            return outputGrayscale;
        };

        inputImage->pixelRunner(BrightnerFun);

    }

    void AddBrighteningImage(std::shared_ptr<Image> inputImage, const std::shared_ptr<Image>& imageToAdd, int& attenuatedCount) {
        if (imageToAdd->m_rows != inputImage->m_rows || imageToAdd->m_columns != inputImage->m_columns) {
            throw PixelProcessingException("Image dimensions mismatch.");
        }

        auto BrightnerFun = [&attenuatedCount, &imageToAdd](uint8_t pixelGrayscale, int index) {
            uint8_t outputGrayscale = pixelGrayscale;
            uint8_t pixelGrayscaleToAdd = imageToAdd->m_pixels[index];
            if (outputGrayscale + pixelGrayscaleToAdd > 255) {
                ++attenuatedCount;
                outputGrayscale = 255;
            }
            else {
                outputGrayscale += pixelGrayscaleToAdd;
            }

            return outputGrayscale;
        };

        inputImage->pixelRunner(BrightnerFun);

    }
}