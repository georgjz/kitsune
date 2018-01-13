#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define cimg_use_png
#include <CImg.h>

#include "InputParser.hpp"

// used as switch mostly
enum class BitFormats { _2bpp, _4bpp };

// little helper function
uint16_t getPixelColor(const int x, const int y, const cimg_library::CImg<uint8_t> &inputImage)
{
    uint16_t pixelR = inputImage(x, y, 0);
    uint16_t pixelG = inputImage(x, y, 1);
    uint16_t pixelB = inputImage(x, y, 2);
    uint16_t pixel = ((pixelB & 0xf8) << 7) |
                     ((pixelG & 0xf8) << 2) |
                      (pixelR >> 3);
    pixel &= 0x7fff; // set MSB to zero
    return pixel;
}
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    // parse arguments
    std::vector <std::string> tokens;
    for(auto i = 1; i < argc; ++i)
    {
        tokens.push_back(std::string(argv[i]));
    }

    // get input file name
    std::string imageFileName { getCmdOption(tokens, "-f") };
    if(imageFileName == "")
    {
        std::cout << "No input file found, please specify input with -f" << std::endl;
        return -1;
    }
    std::cout << imageFileName << std::endl;

    // get bit format
    std::string bitFormatArg { getCmdOption(tokens, "-b") };
    if(bitFormatArg == "")
    {
        std::cout << "No bit format found, please specify bit format with -b" << std::endl;
        return -1;
    }
    BitFormats bitFormat;
    if(bitFormatArg == "2bpp")
    {
        bitFormat = BitFormats::_2bpp;
    }
    else if(bitFormatArg == "4bpp")
    {
        bitFormat = BitFormats::_4bpp;
    }
    else
    {
            std::cout << "No legal bit format found, use 2bpp oder 4bpp with -b" << std::endl;
            return -1;
    }

    // get output file name
    std::string outputName { getCmdOption(tokens, "-o") };
    if(outputName == "")
    {
        std::cout << "Please specify output file name with -o" << std::endl;
        return -1;
    }

    // open the image and perform resolution check
    cimg_library::CImg<uint8_t> inputImage(imageFileName.c_str());
    if(!inputImage.width() % 8 || !inputImage.height() % 8)
    {
        std::cout << "Image size and width must be multiple of 8" << std::endl;
        return -1;
    }
    const uint8_t imageWidth  {static_cast<uint8_t>(inputImage.width())};
    const uint8_t imageHeight {static_cast<uint8_t>(inputImage.height())};

    // convert colors to BGR555, count colors and select background color
    std::vector<uint16_t> colorPalette;

    for(auto y = 0; y < imageHeight; ++y)
    {
        for(auto x = 0; x < imageWidth; ++x)
        {
            uint16_t pixelColor { getPixelColor(x, y, inputImage) };
            auto itr = std::find(colorPalette.begin(), colorPalette.end(), pixelColor);
            if(itr == colorPalette.end())
            {
                colorPalette.push_back(pixelColor);
                //std::cout << std::hex << pixelColor << std::endl;
            }
        }
    }
    const auto colorCount = colorPalette.size();

    // TODO: check for max color count according to bit format

    // std::cout << "number of colors: " << colorPalette.size() << std::endl;
    // show resized image (zoom 4x)
    cimg_library::CImg<uint8_t> resizedImage (inputImage.get_resize(4*imageWidth, 4*imageHeight));

    cimg_library::CImgDisplay main_disp(resizedImage,"Click to choose background color");
    uint16_t backgroundColor {0};
    while (!main_disp.is_closed())
    {
        main_disp.wait();
        if(main_disp.button() && main_disp.mouse_y()>=0)
        {
            backgroundColor = getPixelColor(main_disp.mouse_x(), main_disp.mouse_y(), resizedImage);
            main_disp.close();
        }
    }

    std::cout << "Chosen BG color: " << std::hex << backgroundColor << std::endl;
    // find backgroundColor in palette and swap to first place
    auto itr = std::find(colorPalette.begin(), colorPalette.end(), backgroundColor);
    auto tempColor = *colorPalette.begin();
    *colorPalette.begin() = backgroundColor;
    *itr = tempColor;

    // create palette output file
    std::ofstream paletteFile;
    paletteFile.open(outputName+".pal", std::ios::binary | std::ios::out);
    paletteFile.seekp(0);

    for(uint16_t color : colorPalette)
    {
        std::cout << std::hex << color << std::endl;
        uint8_t lowerByte   = color & 0x00ff;
        uint8_t higherByte  = color >> 8;
        paletteFile << lowerByte;
        paletteFile << higherByte;
    }

    // fill rest of palette with black
    for(auto i = 2*colorCount; i < 32; ++i)
    {
        uint8_t zero {0};
        paletteFile << zero;
    }

    paletteFile.close();

    // create colorIndexMap
    std::vector<std::vector<uint8_t> > colorIndexMap(imageWidth, std::vector<uint8_t>(imageHeight, 0));
    for(auto y = 0; y < imageHeight; ++y)
    {
        for(auto x = 0; x < imageWidth; ++x)
        {
            // get pixel and find color index
            uint16_t testPixel = getPixelColor(x, y, inputImage);
            uint8_t pos = std::find(colorPalette.begin(), colorPalette.end(), testPixel) - colorPalette.begin();
            // TODO: error check
            colorIndexMap[x][y] = pos;
        }
    }

    // create bitplanes output file
    std::ofstream bitplanesFile;
    bitplanesFile.open(outputName+".bin", std::ios::binary | std::ios::out);
    bitplanesFile.seekp(0);

    // TODO: modulize in function
    // bitplanes that will hold data
	uint8_t bitplane0{0}, bitplane1{0}, bitplane2{0}, bitplane3{0};
    uint8_t yTilesCount{static_cast<uint8_t>(imageWidth >> 3)},
            xTilesCount{static_cast<uint8_t>(imageHeight >> 3)};
    uint16_t tilesCount{static_cast<uint16_t>(xTilesCount * yTilesCount)};
    uint8_t xTile{0}, yTile{0};

    for(auto tile = 0; tile < tilesCount; ++tile)
    {
        for(auto y = 0; y < 8; ++y)
        {
            for(auto x = 0; x < 8; ++x)
            {
                uint8_t bit = 0;
                uint8_t index = colorIndexMap[8*xTile + x][8*yTile + y];
                bit = index & 1;
                bitplane0 |= (bit << (7 - x));

                index >>= 1;
                bit = index & 1;
                bitplane1 |= (bit << (7 - x));

                index >>= 1;
                bit = index & 1;
                bitplane2 |= (bit << (7 - x));

                index >>= 1;
                bit = index & 1;
                bitplane3 |= (bit << (7 - x));
            } // x loop
            // write bitplane line to output file
            bitplanesFile.seekp(32*tile + 2*y);
            bitplanesFile << bitplane0;
            bitplanesFile.seekp(32*tile + 2*y + 1);
            bitplanesFile << bitplane1;
            bitplanesFile.seekp(32*tile + (2*y + 16));
            bitplanesFile << bitplane2;
            bitplanesFile.seekp(32*tile + (2*y + 16) + 1);
            bitplanesFile << bitplane3;

            // reset bitplanes
            bitplane0 &= 0;
            bitplane1 &= 0;
            bitplane2 &= 0;
            bitplane3 &= 0;
        } // y loop
        ++xTile;
        if(xTile >= xTilesCount)
        {
            xTile = 0;              // reset counter
            ++yTile;
            if(yTile >= yTilesCount) break;
        }
    } // tile loop

    // everything is fine.
    return 0;
}
