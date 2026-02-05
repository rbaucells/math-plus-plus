#pragma once
#include <vector>
#include "../src/old/helper.h"
#include "../src/old/vector.h"

template<scalar T = float>
class Curve {
public:
    Curve() = default;

    Curve(std::initializer_list<Vector<2, T>> intitializerList) {
        points.reserve(intitializerList.size());

        for (const auto& element : intitializerList) {
            points.push_back(element);
        }
    }

    [[nodiscard]] T evaluate(T t) const {
        std::vector<Vector<2>> result = points;

        while (result.size() > 1) {
            std::vector<Vector<2>> thePoints(result.size() - 1);

            for (int i = 0; i < result.size() - 1; i++) {
                thePoints.at(i) = lerpPoint(result[i], result[i + 1], t);
            }

            result = thePoints;
        }

        return result[0][1];
    }

    std::vector<Vector<2>> points;

private:
    static Vector<2> lerpPoint(const Vector<2, T>& start, const Vector<2, T>& end, T t)  {
        return start + (end - start) * t;
    }
};

namespace Curves {
    inline Curve<float> linear = {{0, 0}, {1, 1}};

    inline Curve<float> sineIn = {{0, 0}, {0.47, 0}, {0.745, 0.715}, {1, 1}};
    inline Curve<float> sineOut = {{0, 0}, {0.39, 0.575}, {0.565, 1}, {1, 1}};
    inline Curve<float> sineInOut = {{0, 0}, {0.445, 0.05}, {0.55, 0.95}, {1, 1}};

    inline Curve<float> circIn = {{0, 0}, {0.6, 0}, {0.8, 0.2}, {1, 1}};
    inline Curve<float> circOut = {{0, 0}, {0.2, 0.8}, {0.4, 1}, {1, 1}};
    inline Curve<float> circInOut = {{0, 0}, {0.785, 0.135}, {0.15, 0.865}, {1, 1}};

    inline Curve<float> cubicIn = {{0, 0}, {0.55, 0}, {0.675, 0.19}, {1, 1}};
    inline Curve<float> cubicOut = {{0, 0}, {0.215, 0.61}, {0.355, 1}, {1, 1}};
    inline Curve<float> cubicInOut = {{0, 0}, {0.645, 0.045}, {0.355, 0.955}, {1, 1}};

    inline Curve<float> quartIn = {{0, 0}, {0.895, 0}, {0.755, 0.035}, {1, 1}};
    inline Curve<float> quartOut = {{0, 0}, {0.23, 0.945}, {0.275, 1}, {1, 1}};
    inline Curve<float> quartInOut = {{0, 0}, {0.77, 0}, {0.175, 1}, {1, 1}};

    inline Curve<float> expoIn = {{0, 0}, {0.95, 0.05}, {0.795, 0.035}, {1, 1}};
    inline Curve<float> expoOut = {{0, 0}, {0.19, 0.91}, {0.22, 0.985}, {1, 1}};
    inline Curve<float> expoInOut = {{0, 0}, {0.87, 0}, {0.13, 1}, {1, 1}};

    inline Curve<float> backIn = {{0, 0}, {0.6, -0.28}, {0.735, 0.045}, {1, 1}};
    inline Curve<float> backOut = {{0, 0}, {0.175, 0.885}, {0.32, 1.28}, {1, 1}};
    inline Curve<float> backInOut = {{0, 0}, {0.68, -0.55}, {0.265, 1.55}, {1, 1}};

    inline Curve<float> elasticIn = {{0, 0}, {0.42, -0.6}, {0.58, 1.6}, {1, 1}};
    inline Curve<float> elasticOut = {{0, 0}, {0.42, -0.6}, {0.58, 1.6}, {1, 1}};
    inline Curve<float> elasticInOut = {{0, 0}, {0.42, -0.6}, {0.58, 1.6}, {1, 1}};

    inline Curve<float> bounceIn = {{0, 0}, {0.28, 0.84}, {0.42, 0.99}, {0, 1}};
    inline Curve<float> bounceOut = {{0, 0}, {0.01, 0}, {0.58, 0.42}, {1, 1}};
    inline Curve<float> bounceInOut = {{0, 0}, {0.42, 0}, {0.58, 1}, {1, 1}};

    inline Curve<float> smoothStep = {{0, 0}, {0.5, 0}, {0.5, 1}, {1, 1}};
    inline Curve<float> smootherStep = {{0, 0}, {0.445, 0}, {0.555, 1}, {1, 1}};
}
