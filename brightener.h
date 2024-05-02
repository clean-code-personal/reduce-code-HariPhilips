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


    void ExecutePixelRunner(std::shared_ptr<Image> inputImage, int& attenuatedCount, const std::shared_ptr<Image>& imageToAdd = nullptr )
    {
        auto BrightnerFun = [&attenuatedCount](uint8_t pixelGrayscale, uint8_t pixelGrayscaleToAdd) {
            uint8_t outputGrayscale = pixelGrayscale;
            if (outputGrayscale + pixelGrayscaleToAdd > 255) {
                ++attenuatedCount;
                outputGrayscale = 255;
            }
            else {
                outputGrayscale += pixelGrayscaleToAdd;
            }

            return outputGrayscale;
        };

        if (imageToAdd)
            inputImage->pixelRunner(BrightnerFun, imageToAdd);
        else
            inputImage->pixelRunner(BrightnerFun);
    }

    void BrightenWholeImage(std::shared_ptr<Image> inputImage, int& attenuatedCount) {
        if (!inputImage->isSizeValid()) {
            throw PixelProcessingException("Invalid image size.");
        }

        ExecutePixelRunner(inputImage, attenuatedCount);
    }

    void AddBrighteningImage(std::shared_ptr<Image> inputImage, const std::shared_ptr<Image>& imageToAdd, int& attenuatedCount) {
        if (imageToAdd->m_rows != inputImage->m_rows || imageToAdd->m_columns != inputImage->m_columns) {
            throw PixelProcessingException("Image dimensions mismatch.");
        }

        ExecutePixelRunner(inputImage, attenuatedCount, imageToAdd);
    }
}