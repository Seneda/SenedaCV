#define CATCH_CONFIG_MAIN
#include <string>
#include "../catch.hpp"
#include "../img.hpp"
#include "../ppm.hpp"
#include "../kernel.hpp"

TEST_CASE("Test pixel struct", "[pixel]") {
    RGBPixel pixel = RGBPixel(100, 150, 200);
    REQUIRE(pixel == 150);
    REQUIRE(pixel == "100 150 200 150"_rgb);
    pixel = 15;
    REQUIRE(pixel == "10 15 20 15"_rgb);
    pixel = -15;
    REQUIRE(pixel == "-10 -15 -20  -15"_rgb);
    pixel = 0;
    REQUIRE(pixel == "0 0 0  0"_rgb);
}

TEST_CASE("test that a new pixelgrid is filled with 0s", "[test]") {
    PixelGrid pixel_grid = PixelGrid(2, 2);
    REQUIRE(pixel_grid[1][1] == "0 0 0 0"_rgb);
}

TEST_CASE("Test loading an image from file", "[loading]") {
    PPMImage image = openImage("images/read_test.ppm");
    REQUIRE(image.magic == "P3");
    REQUIRE(image.meta  == "#Meta Info");
    REQUIRE(image[0][0] == "1 2 3  2"_rgb);
    REQUIRE(image[0][1] == "4 5 6  5"_rgb);
    REQUIRE(image[0][2] == "7 8 9  8"_rgb);
    REQUIRE(image[1][0] == "9 8 7  8"_rgb);
    REQUIRE(image[1][1] == "6 5 4  5"_rgb);
    REQUIRE(image[1][2] == "3 2 1  2"_rgb);
}

TEST_CASE("Test block smoothing a delta works", "[convolution]") {
    PPMImage input = openImage("images/delta.ppm");
    PixelGrid kernel = readKernel("kernels/block_smooth_2_by_2");
    PPMImage output = openImage("images/block_smoothed_delta.ppm");
    PPMImage result = input.convolve(kernel);
    REQUIRE(output.rows == result.rows);
    REQUIRE(output.columns == result.columns);
    REQUIRE(output[1][1].i == result[1][1].i);
}

