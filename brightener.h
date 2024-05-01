#include <cstdint>
#include "image.h"

namespace ImageProcessor
{

    void ExecutePixelRunner(std::shared_ptr<Image> inputImage, const std::shared_ptr<Image>& imageToAdd, int& attenuatedCount)
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

        inputImage->pixelRunner(BrightnerFun, imageToAdd);
    }

    bool BrightenWholeImage(std::shared_ptr<Image> inputImage, int& attenuatedCount, std::shared_ptr<Image> imageToAdd = nullptr) {
        if (!inputImage->isSizeValid()) {
            return false;
        }

        ExecutePixelRunner(inputImage, imageToAdd, attenuatedCount);

        return true;
    }

    bool AddBrighteningImage(std::shared_ptr<Image> inputImage, const std::shared_ptr<Image>& imageToAdd, int& attenuatedCount) {
        if (imageToAdd->m_rows != inputImage->m_rows || imageToAdd->m_columns != inputImage->m_columns) {
            return false;
        }

        ExecutePixelRunner(inputImage, imageToAdd, attenuatedCount);

        return true;
    }
}