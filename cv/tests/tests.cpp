#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../img.hpp"
#include "../ppm.hpp"
#include "../kernel.hpp"

TEST_CASE("test that a new pixelgrid is filled with 0s", "[test]") {
    PixelGrid pixel_grid = PixelGrid(2, 2);
    REQUIRE(pixel_grid[0][0].r == 0);
    REQUIRE(pixel_grid[0][1].g == 0);
    REQUIRE(pixel_grid[1][0].b == 0);
    REQUIRE(pixel_grid[1][1].i == 0);
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

