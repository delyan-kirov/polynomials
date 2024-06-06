#ifdef unix
#if 0
  /bin/cc -lstdc++ test.cpp && ./a.out && rm ./a.out && exit;
#endif
#endif

#include "Array.h"
#include "Matrix.h"
#include "Text.cpp"
#include <iostream>
#include <optional>

// ex 1: Merging Sorted Arrays
static void
testMergeSortedArrays()
{
  std::cout << "\n--- ex 1: Merge Sorted Arrays ---\n\n";

  Array<int> arr1(3);
  arr1.set(0, 1);
  arr1.set(1, 3);
  arr1.set(2, 5);

  Array<int> arr2(4);
  arr2.set(0, 2);
  arr2.set(1, 4);
  arr2.set(2, 6);
  arr2.set(3, 11);

  Array<int> mergedArray = mergeSortedArrays(arr1, arr2);

  std::cout << "First Array:\n";
  arr1.print();
  std::cout << '\n';
  std::cout << "Second Array:\n";
  arr2.print();
  std::cout << '\n';

  std::cout << "Merged Array:\n";
  mergedArray.print();

  arr1.destroy();
  arr2.destroy();
  mergedArray.destroy();
}

// ex 2: Finding the Majority Element
static void
testFindMajorityElement()
{
  std::cout << "\n--- ex 2: Find Majority Element ---\n\n";
  {
    std::cout << "Example 1\n";
    Array<int> arr(7);
    arr.set(0, 1);
    arr.set(1, 2);
    arr.set(2, 3);
    arr.set(3, 1);
    arr.set(4, 1);
    arr.set(5, 1);
    arr.set(6, 4);

    std::optional<int> majorityElement = findMajorityElement(arr);

    std::cout << "Array:\n";
    arr.print();
    std::cout << '\n';

    if (majorityElement) {
      std::cout << "The majority element is: " << *majorityElement << std::endl;
    } else {
      std::cout << "There is no majority element." << std::endl;
    }

    arr.destroy();
  }
  std::cout << "\nExample 2\n";
  {
    Array<int> arr(7);
    arr.set(0, 1);
    arr.set(1, 2);
    arr.set(2, 3);
    arr.set(3, 4);
    arr.set(4, 5);
    arr.set(5, 6);
    arr.set(6, 7);

    std::optional<int> majorityElement = findMajorityElement(arr);

    std::cout << "Array:\n";
    arr.print();
    std::cout << '\n';

    if (majorityElement) {
      std::cout << "The majority element is: " << *majorityElement << std::endl;
    } else {
      std::cout << "There is no majority element." << std::endl;
    }

    arr.destroy();
  }
}

// ex 3: Checking for Anagrams
// Text.h
size_t
strlen(const char* str);
bool
areAnagrams(const char* str1, const char* str2);

static void
testCheckAnagrams()
{
  std::cout << "\n--- ex 3: Check Anagrams ---\n\n";

  // test positive
  {
    const char* str1 = "listen";
    const char* str2 = "silent";

    if (areAnagrams(str1, str2)) {
      std::cout << "\"" << str1 << "\" and \"" << str2 << "\" are anagrams.\n";
    } else {
      std::cout << "\"" << str1 << "\" and \"" << str2
                << "\" are not anagrams.\n";
    }
  }

  // test negative
  {
    const char* str3 = "abc";
    const char* str4 = "xyz";

    if (areAnagrams(str3, str4)) {
      std::cout << "\"" << str3 << "\" and \"" << str4 << "\" are anagrams.\n";
    } else {
      std::cout << "\"" << str3 << "\" and \"" << str4
                << "\" are not anagrams.\n";
    }
  }
}

// ex 4: Rotating a Matrix
static void
testRotateMatrix()
{
  std::cout << "\n--- ex 4: Rotate Matrix ---\n\n";

  std::cout << "Example 1\n";
  {
    Matrix<int> mat(3, 3);
    mat.set(0, 0, 1);
    mat.set(0, 1, 2);
    mat.set(0, 2, 3);
    mat.set(1, 0, 4);
    mat.set(1, 1, 5);
    mat.set(1, 2, 6);
    mat.set(2, 0, 7);
    mat.set(2, 1, 8);
    mat.set(2, 2, 9);

    std::cout << "Original Matrix:\n";
    mat.print();

    rotate90DegInPlace(mat);

    std::cout << "Rotated Matrix:\n";
    mat.print();

    mat.destroy();
  }
  std::cout << "\nExample 2\n";
  {
    Matrix<int> mat(2, 2);
    mat.set(0, 0, 1);
    mat.set(0, 1, 2);
    mat.set(1, 0, 3);
    mat.set(1, 1, 4);

    std::cout << "Original Matrix:\n";
    mat.print();

    rotate90DegInPlace(mat);

    std::cout << "Rotated Matrix:\n";
    mat.print();

    mat.destroy();
  }
}

// ex 5: Multiplying Matrices
static void
testMultiplyMatrices()
{
  std::cout << "\n--- ex 5: Multiply Matrices ---\n\n";

  std::cout << "Example 1:\n";
  {
    Matrix<int> mat1(2, 2);
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 2);
    mat1.set(1, 0, 3);
    mat1.set(1, 1, 4);

    Matrix<int> mat2(2, 2);
    mat2.set(0, 0, 5);
    mat2.set(0, 1, 6);
    mat2.set(1, 0, 7);
    mat2.set(1, 1, 8);

    Matrix<int> result = multiply(mat1, mat2);

    std::cout << "Matrix 1:\n";
    mat1.print();

    std::cout << "Matrix 2:\n";
    mat2.print();

    std::cout << "Result Matrix:\n";
    result.print();

    mat1.destroy();
    mat2.destroy();
    result.destroy();
  }
  std::cout << "\nExample 2:\n";
  {
    Matrix<int> mat1(2, 2);
    mat1.set(0, 0, 1);
    mat1.set(0, 1, 0);
    mat1.set(1, 0, 0);
    mat1.set(1, 1, 1);

    Matrix<int> mat2(2, 2);
    mat2.set(0, 0, 1);
    mat2.set(0, 1, 1);
    mat2.set(1, 0, 1);
    mat2.set(1, 1, 1);

    Matrix<int> result = multiply(mat1, mat2);

    std::cout << "Matrix 1:\n";
    mat1.print();

    std::cout << "Matrix 2:\n";
    mat2.print();

    std::cout << "Result Matrix:\n";
    result.print();

    mat1.destroy();
    mat2.destroy();
    result.destroy();
  }
}

int
main()
{
  testMergeSortedArrays();
  testFindMajorityElement();
  testCheckAnagrams();
  testRotateMatrix();
  testMultiplyMatrices();
  return 0;
}
