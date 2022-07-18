#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Reset test", "[reset_reverb]" )
{
    // ensure that an input signal generates an identical output signal
    // after calling reset.
    REQUIRE( false ); // TODO
}

TEST_CASE( "NaN test", "[test_nans]" )
{
    // ensure plug doesn't output nans
    REQUIRE( false ); // TODO
}

TEST_CASE( "Clipping test", "[test_clipping]" )
{
    // ensure the plugin does not clip at reasonable levels
    REQUIRE( false ); // TODO
}

TEST_CASE( "Channel test", "[test_channels]" )
{
    // ensure that the plugin can pass audio as expected in
    // MIMO, SISO, and MISO configs
    REQUIRE( false ); // TODO
}
