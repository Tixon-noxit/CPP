//
// Created by Тихон Чабусов on 20.06.2024.
//

#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

// Test fixture for S21Matrix
class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        // You can initialize matrices here if needed
    }

    void TearDown() override {
        // Code here will be called immediately after each test
    }
};

// Test for the default constructor
TEST(MatrixTest, DefaultConstructor) {
S21Matrix m;
EXPECT_EQ(m.getRows(), 3);
EXPECT_EQ(m.getCols(), 3);
}

// Test for the parameterized constructor
TEST(MatrixTest, ParameterizedConstructor) {
S21Matrix m(2, 2);
EXPECT_EQ(m.getRows(), 2);
EXPECT_EQ(m.getCols(), 2);
}

// Test for the copy constructor
TEST(MatrixTest, CopyConstructor) {
S21Matrix m1(2, 2);
m1(0, 0) = 1.0;
S21Matrix m2(m1);
EXPECT_EQ(m2.getRows(), 2);
EXPECT_EQ(m2.getCols(), 2);
EXPECT_EQ(m2(0, 0), 1.0);
}

// Test for the move constructor
TEST(MatrixTest, MoveConstructor) {
S21Matrix m1(2, 2);
m1(0, 0) = 1.0;
S21Matrix m2(std::move(m1));
EXPECT_EQ(m2.getRows(), 2);
EXPECT_EQ(m2.getCols(), 2);
EXPECT_EQ(m2(0, 0), 1.0);
EXPECT_EQ(m1.getRows(), 0);
EXPECT_EQ(m1.getCols(), 0);
}

// Test for the assignment operator
TEST(MatrixTest, AssignmentOperator) {
S21Matrix m1(2, 2);
m1(0, 0) = 1.0;
S21Matrix m2 = m1;
EXPECT_EQ(m2.getRows(), 2);
EXPECT_EQ(m2.getCols(), 2);
EXPECT_EQ(m2(0, 0), 1.0);
}

// Test for the addition operator
TEST(MatrixTest, AdditionOperator) {
S21Matrix m1(2, 2);
S21Matrix m2(2, 2);
m1(0, 0) = 1.0;
m2(0, 0) = 2.0;
S21Matrix m3 = m1 + m2;
EXPECT_EQ(m3(0, 0), 3.0);
}

// Test for the subtraction operator
TEST(MatrixTest, SubtractionOperator) {
S21Matrix m1(2, 2);
S21Matrix m2(2, 2);
m1(0, 0) = 3.0;
m2(0, 0) = 2.0;
S21Matrix m3 = m1 - m2;
EXPECT_EQ(m3(0, 0), 1.0);
}

// Test for the multiplication by number operator
TEST(MatrixTest, MultiplicationByNumberOperator) {
S21Matrix m1(2, 2);
m1(0, 0) = 2.0;
S21Matrix m2 = m1 * 3.0;
EXPECT_EQ(m2(0, 0), 6.0);
}

// Test for the multiplication by matrix operator
TEST(MatrixTest, MultiplicationByMatrixOperator) {
S21Matrix m1(2, 3);
S21Matrix m2(3, 2);
m1(0, 0) = 1.0;
m2(0, 0) = 2.0;
S21Matrix m3 = m1 * m2;
EXPECT_EQ(m3(0, 0), 2.0);
}

// Test for the equality operator
TEST(MatrixTest, EqualityOperator) {
S21Matrix m1(2, 2);
S21Matrix m2(2, 2);
m1(0, 0) = 1.0;
m2(0, 0) = 1.0;
EXPECT_TRUE(m1 == m2);
}

// Test for the transpose method
TEST(MatrixTest, Transpose) {
S21Matrix m1(2, 3);
m1(0, 1) = 1.0;
S21Matrix m2 = m1.Transpose();
EXPECT_EQ(m2(1, 0), 1.0);
}

// Test for setting rows
TEST(MatrixTest, SetRows) {
S21Matrix m(2, 2);
m.setRows(3);
EXPECT_EQ(m.getRows(), 3);
EXPECT_EQ(m.getCols(), 2);
}

// Test for setting columns
TEST(MatrixTest, SetCols) {
S21Matrix m(2, 2);
m.setCols(3);
EXPECT_EQ(m.getRows(), 2);
EXPECT_EQ(m.getCols(), 3);
}

// Test case: Inverse of a 2x2 matrix
TEST(MatrixInverseTest, InverseOf2x2) {
S21Matrix A(2, 2);
A(0, 0) = 1; A(0, 1) = 2;
A(1, 0) = 3; A(1, 1) = 4;

S21Matrix A_inv = A.InverseMatrix();

// Expected inverse of A: [-2, 1]
//                        [ 1.5, -0.5]
ASSERT_DOUBLE_EQ(A_inv(0, 0), -2);
ASSERT_DOUBLE_EQ(A_inv(0, 1), 1);
ASSERT_DOUBLE_EQ(A_inv(1, 0), 1.5);
ASSERT_DOUBLE_EQ(A_inv(1, 1), -0.5);
}

// Test case: Inverse of a 3x3 matrix
TEST(MatrixInverseTest, InverseOf3x3) {
S21Matrix B(3, 3);
B(0, 0) = 1; B(0, 1) = 2; B(0, 2) = 3;
B(1, 0) = 0; B(1, 1) = 1; B(1, 2) = 4;
B(2, 0) = 5; B(2, 1) = 6; B(2, 2) = 0;

S21Matrix B_inv = B.InverseMatrix();

// Expected inverse of B:
// [ -24, 18, 5]
// [  20, -15, -4]
// [  -5,  4, 1]
ASSERT_DOUBLE_EQ(B_inv(0, 0), -24);
ASSERT_DOUBLE_EQ(B_inv(0, 1), 18);
ASSERT_DOUBLE_EQ(B_inv(0, 2), 5);
ASSERT_DOUBLE_EQ(B_inv(1, 0), 20);
ASSERT_DOUBLE_EQ(B_inv(1, 1), -15);
ASSERT_DOUBLE_EQ(B_inv(1, 2), -4);
ASSERT_DOUBLE_EQ(B_inv(2, 0), -5);
ASSERT_DOUBLE_EQ(B_inv(2, 1), 4);
ASSERT_DOUBLE_EQ(B_inv(2, 2), 1);
}

// Test case: Inverse of a singular matrix (should throw exception)
TEST(MatrixInverseTest, SingularMatrix) {
S21Matrix C(3, 3);
C(0, 0) = 1; C(0, 1) = 0; C(0, 2) = 0;
C(1, 0) = 0; C(1, 1) = 0; C(1, 2) = 0;
C(2, 0) = 0; C(2, 1) = 0; C(2, 2) = 0;

try {
S21Matrix C_inv = C.InverseMatrix();
FAIL() << "Expected std::invalid_argument";
} catch (const std::invalid_argument& e) {
EXPECT_STREQ(e.what(), "Matrix is singular and cannot be inverted");
} catch (...) {
FAIL() << "Expected std::invalid_argument";
}
}

// Test case: Inverse of a non-square matrix (should throw exception)
TEST(MatrixInverseTest, NonSquareMatrix) {
S21Matrix D(2, 3); // 2x3 matrix

try {
S21Matrix D_inv = D.InverseMatrix();
FAIL() << "Expected std::invalid_argument";
} catch (const std::invalid_argument& e) {
EXPECT_STREQ(e.what(), "Matrix must be square to calculate inverse");
} catch (...) {
FAIL() << "Expected std::invalid_argument";
}
}

// Test case: Subtracting matrices of the same size
TEST(MatrixSubtractionTest, SubtractSameSizeMatrices) {
S21Matrix A(3, 3);
A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
A(2, 0) = 7; A(2, 1) = 8; A(2, 2) = 9;

S21Matrix B(3, 3);
B(0, 0) = 9; B(0, 1) = 8; B(0, 2) = 7;
B(1, 0) = 6; B(1, 1) = 5; B(1, 2) = 4;
B(2, 0) = 3; B(2, 1) = 2; B(2, 2) = 1;

A -= B;

// Expected result: A - B = [[-8, -6, -4],
//                           [-2, 0, 2],
//                           [4, 6, 8]]
ASSERT_DOUBLE_EQ(A(0, 0), -8);
ASSERT_DOUBLE_EQ(A(0, 1), -6);
ASSERT_DOUBLE_EQ(A(0, 2), -4);
ASSERT_DOUBLE_EQ(A(1, 0), -2);
ASSERT_DOUBLE_EQ(A(1, 1), 0);
ASSERT_DOUBLE_EQ(A(1, 2), 2);
ASSERT_DOUBLE_EQ(A(2, 0), 4);
ASSERT_DOUBLE_EQ(A(2, 1), 6);
ASSERT_DOUBLE_EQ(A(2, 2), 8);
}

// Test case: Subtracting matrices of different sizes (should throw exception)
TEST(MatrixSubtractionTest, SubtractDifferentSizeMatrices) {
S21Matrix C(2, 3); // 2x3 matrix
S21Matrix D(3, 2); // 3x2 matrix

try {
C -= D;
FAIL() << "Expected std::invalid_argument";
} catch (const std::invalid_argument& e) {
EXPECT_STREQ(e.what(), "Matrices dimensions must match for subtraction");
} catch (...) {
FAIL() << "Expected std::invalid_argument";
}
}

// Test case: Subtracting matrices where dimensions match but are different content
TEST(MatrixSubtractionTest, SubtractMatricesWithSameSizeDifferentContent) {
S21Matrix E(2, 2);
E(0, 0) = 1; E(0, 1) = 2;
E(1, 0) = 3; E(1, 1) = 4;

S21Matrix F(2, 2);
F(0, 0) = 4; F(0, 1) = 3;
F(1, 0) = 2; F(1, 1) = 1;

E -= F;

// Expected result: E - F = [[-3, -1],
//                           [1, 3]]
ASSERT_DOUBLE_EQ(E(0, 0), -3);
ASSERT_DOUBLE_EQ(E(0, 1), -1);
ASSERT_DOUBLE_EQ(E(1, 0), 1);
ASSERT_DOUBLE_EQ(E(1, 1), 3);
}

// Test case: Subtracting a matrix from itself (should result in zero matrix)
TEST(MatrixSubtractionTest, SubtractMatrixFromItself) {
S21Matrix G(3, 3);
G(0, 0) = 1; G(0, 1) = 2; G(0, 2) = 3;
G(1, 0) = 4; G(1, 1) = 5; G(1, 2) = 6;
G(2, 0) = 7; G(2, 1) = 8; G(2, 2) = 9;

S21Matrix original_G = G;
G -= original_G;

// Expected result: G - G = [[0, 0, 0],
//                           [0, 0, 0],
//                           [0, 0, 0]]
ASSERT_DOUBLE_EQ(G(0, 0), 0);
ASSERT_DOUBLE_EQ(G(0, 1), 0);
ASSERT_DOUBLE_EQ(G(0, 2), 0);
ASSERT_DOUBLE_EQ(G(1, 0), 0);
ASSERT_DOUBLE_EQ(G(1, 1), 0);
ASSERT_DOUBLE_EQ(G(1, 2), 0);
ASSERT_DOUBLE_EQ(G(2, 0), 0);
ASSERT_DOUBLE_EQ(G(2, 1), 0);
ASSERT_DOUBLE_EQ(G(2, 2), 0);
}

// Test case: Subtracting a larger matrix from a smaller matrix (should throw exception)
TEST(MatrixSubtractionTest, SubtractLargerMatrixFromSmallerMatrix) {
S21Matrix H(3, 3);
H(0, 0) = 1; H(0, 1) = 2; H(0, 2) = 3;
H(1, 0) = 4; H(1, 1) = 5; H(1, 2) = 6;
H(2, 0) = 7; H(2, 1) = 8; H(2, 2) = 9;

S21Matrix I(2, 2);
I(0, 0) = 1; I(0, 1) = 2;
I(1, 0) = 3; I(1, 1) = 4;

try {
H -= I;
FAIL() << "Expected std::invalid_argument";
} catch (const std::invalid_argument& e) {
EXPECT_STREQ(e.what(), "Matrices dimensions must match for subtraction");
} catch (...) {
FAIL() << "Expected std::invalid_argument";
}
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
