#include <iostream>
#include "brightener.h"

using namespace ImageProcessor;

int main() {
    auto image = std::make_shared<Image>(512, 512);
    std::cout << "Brightening a 512 x 512 image\n";

    int attenuatedCount = 0;
    BrightenWholeImage(image, attenuatedCount);
    std::cout << "Attenuated " << attenuatedCount << " pixels\n";
}
