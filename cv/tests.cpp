//
// Created by seneda on 05/06/16.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "img.hpp"

TEST_CASE("test that a new pixelgrid is filled with 0s", "[test]") {
    PixelGrid pixel_grid = PixelGrid(2, 2);
    REQUIRE(pixel_grid[0][0].r == 0);
    REQUIRE(pixel_grid[0][1].g == 0);
    REQUIRE(pixel_grid[1][0].b == 0);
    REQUIRE(pixel_grid[1][1].i == 0);
}
