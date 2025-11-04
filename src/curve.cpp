#include "curve.h"

Curve::Curve(const std::initializer_list<Vector<2>> points) {
    points_.reserve(points.size());

    for (const auto& element : points) {
        points_.push_back(element);
    }
}

float Curve::evaluate(const double t) const {
    std::vector<Vector<2>> result = points_;
    while (result.size() > 1) {
        std::vector<Vector<2>> thePoints(result.size() - 1);
        for (int i = 0; i < result.size() - 1; i++) {
            thePoints.at(i) = lerpPoint(result[i], result[i + 1], t);
        }

        result = thePoints;
    }

    return result[0][1];
}

Curve Curve::linear = {{0, 0}, {1, 1}};

Curve Curve::sineIn = {{0, 0}, {0.47, 0}, {0.745, 0.715}, {1, 1}};

Curve Curve::sineOut = {{0, 0}, {0.39, 0.575}, {0.565, 1}, {1, 1}};
Curve Curve::sineInOut = {{0, 0}, {0.445, 0.05}, {0.55, 0.95}, {1, 1}};
Curve Curve::circIn = {{0, 0}, {0.6, 0}, {0.8, 0.2}, {1, 1}};

Curve Curve::circOut = {{0, 0}, {0.2, 0.8}, {0.4, 1}, {1, 1}};
Curve Curve::circInOut = {{0, 0}, {0.785, 0.135}, {0.15, 0.865}, {1, 1}};
Curve Curve::cubicIn = {{0, 0}, {0.55, 0}, {0.675, 0.19}, {1, 1}};

Curve Curve::cubicOut = {{0, 0}, {0.215, 0.61}, {0.355, 1}, {1, 1}};
Curve Curve::cubicInOut = {{0, 0}, {0.645, 0.045}, {0.355, 0.955}, {1, 1}};
Curve Curve::quartIn = {{0, 0}, {0.895, 0}, {0.755, 0.035}, {1, 1}};

Curve Curve::quartOut = {{0, 0}, {0.23, 0.945}, {0.275, 1}, {1, 1}};
Curve Curve::quartInOut = {{0, 0}, {0.77, 0}, {0.175, 1}, {1, 1}};
Curve Curve::expoIn = {{0, 0}, {0.95, 0.05}, {0.795, 0.035}, {1, 1}};

Curve Curve::expoOut = {{0, 0}, {0.19, 0.91}, {0.22, 0.985}, {1, 1}};
Curve Curve::expoInOut = {{0, 0}, {0.87, 0}, {0.13, 1}, {1, 1}};
Curve Curve::backIn = {{0, 0}, {0.6, -0.28}, {0.735, 0.045}, {1, 1}};

Curve Curve::backOut = {{0, 0}, {0.175, 0.885}, {0.32, 1.28}, {1, 1}};
Curve Curve::backInOut = {{0, 0}, {0.68, -0.55}, {0.265, 1.55}, {1, 1}};
Curve Curve::elasticIn = {{0, 0}, {0.42, -0.6}, {0.58, 1.6}, {1, 1}};

Curve Curve::elasticOut = {{0, 0}, {0.42, -0.6}, {0.58, 1.6}, {1, 1}};
Curve Curve::elasticInOut = {{0, 0}, {0.42, -0.6}, {0.58, 1.6}, {1, 1}};
Curve Curve::bounceIn = {{0, 0}, {0.28, 0.84}, {0.42, 0.99}, {0, 1}};

Curve Curve::bounceOut = {{0, 0}, {0.01, 0}, {0.58, 0.42}, {1, 1}};
Curve Curve::bounceInOut = {{0, 0}, {0.42, 0}, {0.58, 1}, {1, 1}};
Curve Curve::smoothStep = {{0, 0}, {0.5, 0}, {0.5, 1}, {1, 1}};

Curve Curve::smootherStep = {{0, 0}, {0.445, 0}, {0.555, 1}, {1, 1}};

Vector<2> Curve::lerpPoint(const Vector<2>& start, const Vector<2>& end, const float t) {
    return start + (end - start) * t;
}
