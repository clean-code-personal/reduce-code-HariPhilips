#include "CppUnitTest.h"
#include "../brightener.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ImageProcessor;

namespace brighteningtest
{
    TEST_CLASS(BrighteningTest)
    {
    public:

        TEST_METHOD(BrightensWholeImage)
        {
            auto image = CreateImage({ 45, 55, 65, 254 });

            int attenuatedCount = 0;
            BrightenWholeImage(image, attenuatedCount);

            Assert::AreEqual(1, attenuatedCount);
            Assert::AreEqual(90, int(image->m_pixels[2]));
        }

        TEST_METHOD(BrightensWithAnotherImage)
        {
            auto image = CreateImage({ 45, 55, 65, 75 });

            // Test by brightening only the right part
            auto brighteningImage = std::make_shared<Image>(2, 2);
            brighteningImage->m_pixels[0] = 0; brighteningImage->m_pixels[1] = 25;
            brighteningImage->m_pixels[2] = 0; brighteningImage->m_pixels[3] = 25;

            int attenuatedCount = 0;
            bool succeeded = AddBrighteningImage(image, brighteningImage, attenuatedCount);
            Assert::IsTrue(succeeded);
            Assert::AreEqual(45, int(image->m_pixels[0])); // left-side pixel is unchanged
            Assert::AreEqual(80, int(image->m_pixels[1])); // right-side pixel is brightened
            Assert::AreEqual(0, attenuatedCount);
        }

        std::shared_ptr<Image> CreateImage(std::vector<int> pixelValues)
        {
            auto image = std::make_shared<Image>(2, 2);

            for (auto i = 0; i < pixelValues.size(); i++)
            {
                image->m_pixels[i] = pixelValues[i];
            }

            return image;
        }
    };
}
