#define CATCH_CONFIG_MAIN
#include <string>
#include "../catch.hpp"
#include "../img.hpp"
#include "../ppm.hpp"
#include "../kernel.hpp"

TEST_CASE("Test mono pixel", "[pixel]") {
    MonoPixel pixel = MonoPixel(10);
    REQUIRE(pixel == 10);
    REQUIRE(10 == pixel);
}

TEST_CASE("Test rgb pixel", "[pixel]") {
    RGBPixel pixel = RGBPixel(100, 150, 200);
    REQUIRE(pixel == 150);
    REQUIRE(150 == pixel);
    REQUIRE(pixel == "100 150 200 150");
    pixel = 15;
    REQUIRE(pixel == "10 15 20 15");
    pixel = -15;
    REQUIRE(pixel == "-10 -15 -20  -15");
    pixel = 0;
    REQUIRE(pixel == "0 0 0  0");
}

TEST_CASE("Test that pixel grid functions work", "[pixelgrid]") {
    PixelGrid<MonoPixel> pixel_grid = PixelGrid<MonoPixel>(2, 2);
    float vals_0[4] = {0};
    REQUIRE(pixel_grid == vals_0);

    float vals[4] = {0,1,2,3};
    pixel_grid = vals;
    REQUIRE(pixel_grid == vals);

    float vals_norm[4] = {0, 1./6, 2./6, 3./6};
    pixel_grid.normalise();
    printImage("pixels normed", pixel_grid);
    REQUIRE(pixel_grid == vals_norm);

    float vals_neg[4] = {0,1,2,-3};
    pixel_grid = vals_neg;
    pixel_grid.normalise();
    float vals_norm2[4] = {0, 1, 2, -3};
    pixel_grid.normalise();
    printImage("pixels normed", pixel_grid);
    REQUIRE(pixel_grid == vals_norm2);
    REQUIRE(pixel_grid.max() == 2);
    REQUIRE(pixel_grid.max_abs() == 3);
    REQUIRE(pixel_grid.min() == -3);
    REQUIRE(pixel_grid.min_abs() == 0);
    pixel_grid.autorange();
    float vals_ranged[4] = {3,4,5,0};
    printImage("RANGED", pixel_grid);
    REQUIRE(pixel_grid == vals_ranged);

}

TEST_CASE("Test loading an image from file", "[loading]") {
    PPMImage image = openImage("images/read_test.ppm");
    REQUIRE(image.magic == "P3");
    REQUIRE(image.meta  == "#Meta Info");
    REQUIRE(image[0][0] == "1 2 3  2");
    REQUIRE(image[0][1] == "4 5 6  5");
    REQUIRE(image[0][2] == "7 8 9  8");
    REQUIRE(image[1][0] == "9 8 7  8");
    REQUIRE(image[1][1] == "6 5 4  5");
    REQUIRE(image[1][2] == "3 2 1  2");
    PixelGrid<MonoPixel> mono_grid = ConvertToMonopixel(image);
    REQUIRE(image.rows == mono_grid.rows);
    REQUIRE(image.columns == mono_grid.columns);
    FOR_PIXELS_IN_GRID(image)
        REQUIRE(image[r][c].i == mono_grid[r][c].i);
    END_FOR_PIXELS
}

TEST_CASE("Test block smoothing a delta works", "[convolution]") {
    PPMImage input = openImage("images/delta.ppm");
    PixelGrid<MonoPixel> kernel = readKernel("kernels/block_smooth_2_by_2");
    PPMImage output = openImage("images/block_smoothed_delta.ppm");
    PPMImage result = input.convolve(kernel);
    REQUIRE(output.rows == result.rows);
    REQUIRE(output.columns == result.columns);
    REQUIRE(output[1][1].i == result[1][1].i);
}

TEST_CASE("test gaussian", "[kernels]") {
    float val0, val1, val2, val3;
    val0 = gauss(0, 0, 1);
    REQUIRE(val0 == 1/(2*PI));
    val1 = gauss(100, 100, 1);
    REQUIRE(val1 == 0);
    val2 = gauss(0, -1, 1);
    val3 = gauss(0.70710678, -0.70710678, 1);
    REQUIRE(val3 == val2);
}
