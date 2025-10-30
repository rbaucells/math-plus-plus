#pragma once
#include <vector>

#include "vector.h"

class Curve {
public:
    Curve() = default;
    Curve(const Curve& other);
    Curve(std::initializer_list<Vector<2>> points);

    [[nodiscard]] float evaluate(double t) const;

    void addPoint(const Vector<2>& point);
    std::vector<Vector<2>> getPoints();

    // static curves
    static Curve linear;

    static Curve sineIn;
    static Curve sineOut;
    static Curve sineInOut;

    static Curve circIn;
    static Curve circOut;
    static Curve circInOut;

    static Curve cubicIn;
    static Curve cubicOut;
    static Curve cubicInOut;

    static Curve quartIn;
    static Curve quartOut;
    static Curve quartInOut;

    static Curve expoIn;
    static Curve expoOut;
    static Curve expoInOut;

    static Curve backIn;
    static Curve backOut;
    static Curve backInOut;

    static Curve elasticIn;
    static Curve elasticOut;
    static Curve elasticInOut;

    static Curve bounceIn;
    static Curve bounceOut;
    static Curve bounceInOut;

    static Curve smoothStep;
    static Curve smootherStep;

private:
    std::vector<Vector<2>> points_;

    static Vector<2> lerpPoint(const Vector<2>& start, const Vector<2>& end, float t);
};
