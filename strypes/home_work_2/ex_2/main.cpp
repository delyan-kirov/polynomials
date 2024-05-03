#include <assert.h>
#include <cfloat>
#include <iostream>
#include <limits>

inline bool nearly_equal_1(float a, float b, float epsilon = 128 * FLT_EPSILON,
                           float abs_th = FLT_MIN) {
  assert(std::numeric_limits<float>::epsilon() <= epsilon);
  assert(epsilon < 1.f);

  if (a == b)
    return true;

  auto diff = std::abs(a - b);
  auto norm =
      std::min((std::abs(a) + std::abs(b)), std::numeric_limits<float>::max());
  return diff < std::max(abs_th, epsilon * norm);
}

inline bool nearly_equal_2(float a, float b, float epsilon = 128 * FLT_EPSILON,
                           float abs_th = FLT_MIN) {
  assert(std::numeric_limits<float>::epsilon() <= epsilon);
  assert(epsilon < 1.f);

  if (a == b)
    return true;

  auto diff = std::abs(a - b);
  auto norm = std::min(std::abs(a + b), std::numeric_limits<float>::max());
  return diff < std::max(abs_th, epsilon * norm);
}

inline bool nearly_equal_3(float a, float b,
                           float epsilon = 128 * FLT_EPSILON) {
  float absA = std::abs(a);
  float absB = std::abs(b);
  float diff = std::abs(a - b);

  if (a == b) {
    return true;
  } else if (a == 0 || b == 0 || diff < std::numeric_limits<float>::min()) {
    return diff < (epsilon * std::numeric_limits<float>::min());
  } else {
    return diff / (absA + absB) < epsilon;
  }
}

inline bool absolute_epsilon_equal(float a, float b,
                                   float epsilon = 128 * FLT_EPSILON) {
  float absA = std::abs(a);
  float absB = std::abs(b);
  float diff = std::abs(a - b);

  return diff < (epsilon * std::numeric_limits<float>::min());
}

inline bool relative_equal(float a, float b,
                           float epsilon = 128 * FLT_EPSILON) {
  float absA = std::abs(a);
  float absB = std::abs(b);
  float diff = std::abs(a - b);

  return diff / (absA + absB) < epsilon;
}

constexpr float X0 = 1.0;
constexpr float Y0 = 1.0;
constexpr float X1 = 1.0 / 3.0;
constexpr float Y1 = 1.0 / 3;
constexpr float X2 = 1.0;
constexpr float Y2 = 1.0 * (1 / 3);

int main() {
  std::cout << "Hello" << " " << "world" << "!" << std::endl;
  return 0;
}
