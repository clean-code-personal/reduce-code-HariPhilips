#include <cstdint>
#include "image.h"

namespace ImageProcessor
{
    int BrightenWholeImage(std::shared_ptr<Image> inputImage)
    {
        int attenuatedPixelCount = 0;

        auto BrightnerFun = [&attenuatedPixelCount](uint8_t pixelGrayscale) {
            uint8_t outputGrayscale = pixelGrayscale;
            if (outputGrayscale > (255 - 25)) {
                ++attenuatedPixelCount;
                outputGrayscale = 255;
            }
            else {
                outputGrayscale += 25;
            }

            return outputGrayscale;
        };

        inputImage->pixelRunner(BrightnerFun);

        return attenuatedPixelCount;
    }

    bool AddBrighteningImage(std::shared_ptr<Image> sourceImage, std::shared_ptr<Image> imageToAdd, int& attenuatedCount){
        if (imageToAdd->m_rows != sourceImage->m_rows || imageToAdd->m_columns != sourceImage->m_columns) {
            return false;
        }

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

        sourceImage->pixelRunner(BrightnerFun, imageToAdd);

        return true;
    }
}