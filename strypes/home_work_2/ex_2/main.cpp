#include <assert.h>
#include <iostream>
#include <limits>

// [[https://stackoverflow.com/questions/4915462/how-should-i-do-floating-point-comparison]]
template <typename T>
inline bool nearly_equal(T a, T b,
                         T epsilon = std::numeric_limits<T>::epsilon() * 128,
                         T abs_th = std::numeric_limits<T>::min()) {
  assert(std::numeric_limits<T>::epsilon() <= epsilon);
  assert(epsilon < T(1));

  if (a == b)
    return true;

  auto diff = std::abs(a - b);
  auto norm =
      std::min((std::abs(a) + std::abs(b)), std::numeric_limits<T>::max());
  return diff < std::max(abs_th, epsilon * norm);
}

template <typename T>
inline bool nearly_equal_2(T a, T b,
                           T epsilon = std::numeric_limits<T>::epsilon() * 128,
                           T abs_th = std::numeric_limits<T>::min()) {
  assert(std::numeric_limits<T>::epsilon() <= epsilon);
  assert(epsilon < T(1));

  if (a == b)
    return true;

  auto diff = std::abs(a - b);
  auto norm = std::min(std::abs(a + b), std::numeric_limits<T>::max());
  return diff < std::max(abs_th, epsilon * norm);
}

template <typename T>
inline bool
nearly_equal_3(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 128) {
  T absA = std::abs(a);
  T absB = std::abs(b);
  T diff = std::abs(a - b);

  if (a == b) {
    return true;
  } else if (a == T(0) || b == T(0) || diff < std::numeric_limits<T>::min()) {
    return diff < (epsilon * std::numeric_limits<T>::min());
  } else {
    return diff / (absA + absB) < epsilon;
  }
}

template <typename T>
inline bool
absolute_epsilon_equal(T a, T b,
                       T epsilon = std::numeric_limits<T>::epsilon() * 128) {
  T absA = std::abs(a);
  T absB = std::abs(b);
  T diff = std::abs(a - b);

  return diff < (epsilon * std::numeric_limits<T>::min());
}

template <typename T>
inline bool
relative_distance_equal(T a, T b,
                        T epsilon = std::numeric_limits<T>::epsilon() * 128) {
  T absA = std::abs(a);
  T absB = std::abs(b);
  T diff = std::abs(a - b);

  return diff / (absA + absB) < epsilon;
}

template <typename T> bool AlmostEqual2sComplement(T A, T B, int maxUlps) {
  assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
  int aInt = *(int *)&A;
  if (aInt < 0)
    aInt = 0x80000000 - aInt;
  int bInt = *(int *)&B;
  if (bInt < 0)
    bInt = 0x80000000 - bInt;
  int intDiff = std::abs(aInt - bInt);
  if (intDiff <= maxUlps)
    return true;
  return false;
}

// Data

// Data arrays for float
constexpr float float_data_X[] = {
    1.0f,                               // X0
    1.0f / 3.0f,                        // X1
    1.0f,                               // X2
    4.9303807e-32f,                     // X3
    4.930381e-32f,                      // Y31
    std::numeric_limits<float>::max(),  // X4
    -std::numeric_limits<float>::max(), // X5
};

// Data arrays for float
constexpr float float_data_Y[] = {
    1.0f,                                   // Y0
    1.0f / 3,                               // Y1
    1.0f * (1.0f / 3.0f),                   // Y2
    4.9309825e-32f,                         // Y32
    4.930381e-32f,                          // Y31
    std::numeric_limits<float>::infinity(), // Y4
    -std::numeric_limits<float>::infinity() // Y5
};

// Data arrays for double
constexpr double double_data_X[] = {
    1.0f,                               // X0
    1.0f / 3.0f,                        // X1
    1.0f,                               // X2
    4.9303807e-32f,                     // X3
    4.930381e-32f,                      // Y31
    std::numeric_limits<float>::max(),  // X4
    -std::numeric_limits<float>::max(), // X5
};

// Data arrays for float
constexpr double double_data_Y[] = {
    1.0f,                                   // Y0
    1.0f / 3,                               // Y1
    1.0f * (1.0f / 3.0f),                   // Y2
    4.9309825e-32f,                         // Y32
    4.9309825e-32f,                         // Y32
    std::numeric_limits<float>::infinity(), // Y4
    -std::numeric_limits<float>::infinity() // Y5
};

constexpr bool expected_results[] = {
    true,  // equal
    true,  // equal
    true,  // equal
    false, // not equal
    false, // not equal
    false, // not equal
};

constexpr double epsilon_values_double[] = {
    std::numeric_limits<double>::epsilon() * 128,
    std::numeric_limits<double>::epsilon() * 256,
    std::numeric_limits<double>::epsilon() * 512};

constexpr float epsilon_values_float[] = {
    std::numeric_limits<float>::epsilon() * 128,
    std::numeric_limits<float>::epsilon() * 256,
    std::numeric_limits<float>::epsilon() * 512};

template <typename T>
void test_approaches(const T *data, size_t data_size, const T *epsilon_values,
                     size_t epsilon_size, const bool *expected_results,
                     int maxUlps = 4) {
  std::cout << "Testing for type: " << typeid(T).name() << std::endl;
  size_t result_index = 0;
  for (size_t i = 0; i < data_size; i += 2) {
    T a = data[i];
    T b = data[i + 1];

    for (size_t j = 0; j < epsilon_size; ++j) {
      T epsilon = epsilon_values[j];
      // Test nearly_equal
      bool result = nearly_equal(a, b, epsilon);
      std::cout << std::boolalpha << "nearly_equal with epsilon " << epsilon
                << ": "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;

      // Test nearly_equal_2
      result = nearly_equal_2(a, b, epsilon);
      std::cout << "nearly_equal_2 with epsilon " << epsilon << ": "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;

      // Test nearly_equal_3
      result = nearly_equal_3(a, b, epsilon);
      std::cout << "nearly_equal_3 with epsilon " << epsilon << ": "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;

      // Test absolute_epsilon_equal
      result = absolute_epsilon_equal(a, b, epsilon);
      std::cout << "absolute_epsilon_equal with epsilon " << epsilon << ": "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;

      // Test relative_distance_equal
      result = relative_distance_equal(a, b, epsilon);
      std::cout << "relative_distance_equal with epsilon " << epsilon << ": "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;

      // Test AlmostEqual2sComplement
      result = AlmostEqual2sComplement(a, b, maxUlps);
      std::cout << "AlmostEqual2sComplement with epsilon " << epsilon << ": "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;

      std::cout << std::endl;
      ++result_index;

      // Test with ==
      result = (a == b);
      std::cout << "== operator: "
                << (result == expected_results[result_index] ? "Test succeeded"
                                                             : "Test failed")
                << std::endl;
    }
  }
}

int main() {
  // Call test_approaches for floats
  test_approaches(float_data_X, sizeof(float_data_X) / sizeof(float_data_X[0]),
                  epsilon_values_float,
                  sizeof(epsilon_values_double) /
                      sizeof(epsilon_values_double[0]),
                  expected_results);

  // Call test_approaches for doubles
  test_approaches(
      double_data_X, sizeof(double_data_X) / sizeof(double_data_X[0]),
      epsilon_values_double,
      sizeof(epsilon_values_double) / sizeof(epsilon_values_double[0]),
      expected_results);

  return 0;
}
