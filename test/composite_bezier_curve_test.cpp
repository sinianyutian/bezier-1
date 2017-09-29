#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>


#include <bezier/composite_bezier_curve.h>

using Eigen::Vector2d;

TEST_CASE("Bezier curve construction", "[construction]"){

    bezier::BezierCurve cubic1 = { Vector2d(1, -1), Vector2d(-1, 3), Vector2d(1, 2), Vector2d(2, 3) };
    bezier::BezierCurve cubic2 = { Vector2d(2, 3), Vector2d(-1, 3), Vector2d(4, 10), Vector2d(-1, -1) };
    bezier::BezierCurve cubic3 = { Vector2d(-1, -1), Vector2d(-1, -3), Vector2d(-2, -2), Vector2d(1, 0) };

    SECTION("invalid construction"){
        REQUIRE_THROWS_AS(bezier::CompositeBezierCurve({cubic2, cubic3, cubic1}), std::invalid_argument);
    }

    bezier::CompositeBezierCurve composite = {cubic1, cubic2, cubic3};

    SECTION("dimension"){
        REQUIRE(composite.dimension() == 2);
    }
}


TEST_CASE("Bezier curve evaluation", "[evaluation]"){
    bezier::BezierCurve cubic1 = { Vector2d(1, -1), Vector2d(-1, 3), Vector2d(1, 2), Vector2d(2, 3) };
    bezier::BezierCurve cubic2 = { Vector2d(2, 3), Vector2d(-1, 3), Vector2d(4, 10), Vector2d(-1, -1) };
    bezier::BezierCurve cubic3 = { Vector2d(-1, -1), Vector2d(-1, -3), Vector2d(-2, -2), Vector2d(1, 0) };
    bezier::CompositeBezierCurve composite = {cubic1, cubic2, cubic3};

    SECTION("test domain range"){
        REQUIRE_THROWS_AS(composite(-1), std::domain_error);
        REQUIRE_THROWS_AS(composite(2), std::domain_error);
    }

    SECTION("end points of the Bezier curves"){
        REQUIRE(composite(0) == cubic1(0));
        REQUIRE(composite(1/3.0) == cubic1(1));
        REQUIRE(composite(2/3.0) == cubic2(1));
        REQUIRE(composite(1) == cubic3(1));
    }

    SECTION("random points"){
    }

    SECTION("curve inheritance"){
        const bezier::Curve & curve = composite;
        REQUIRE(curve(0) == cubic1(0));
        REQUIRE(curve(1/3.0) == cubic1(1));
        REQUIRE(curve(2/3.0) == cubic2(1));
        REQUIRE(curve(1) == cubic3(1));
    }
}



