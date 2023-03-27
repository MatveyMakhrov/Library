#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

TEST_CASE("[rational] - Rational ctor") {
    SUBCASE("implementation") {
        CHECK(Rational() == Rational(0, 1));
        CHECK(Rational(3) == Rational(3, 1));
        CHECK(Rational(-3) == Rational(-3, 1));
        CHECK(Rational(10, 6) == Rational(5, 3));
        CHECK(Rational(-10, 6) == Rational(-5, 3));
        CHECK(Rational(10, -6) == Rational(-5, 3));
        CHECK(Rational(-10, -6) == Rational(5, 3));
    }
    SUBCASE("algebra operations") {
        CHECK(Rational(25, 4) * Rational(4, 1) == Rational(25, 1));
        CHECK(Rational(10, 6) + Rational(2, 1) == Rational(11, 3));
        CHECK(Rational(4, -3) - Rational(2, 1) == Rational(-10, 3));
        CHECK(Rational(2, -8) / Rational(2, 3) == Rational(-3, 8));
    }
    SUBCASE("comparsion") {
        CHECK(Rational(25, 1) > Rational(36, 6));
        CHECK(Rational(100, -100) < Rational(2, 1));
    }
    SUBCASE("errors") {
        CHECK_THROWS(Rational(1, 0));
        CHECK_THROWS(Rational(4, -3) / Rational(0, 1));
    }
}