#pragma once
#include <Vector2.h>
#include <math.h>
#include <assert.h>

struct Matrix2x2 {
	float m[2][2];
};

struct Matrix3x3 {
	float m[3][3];
};

Vector2 Add(Vector2 a, Vector2 b);
Vector2 Multiply(Vector2 vector1, Vector2 vector2);
Matrix2x2 Transpose(Matrix2x2 matrix);
Matrix3x3 Transpose(Matrix3x3 matrix);
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);
Matrix2x2 Inverse(Matrix2x2 matrix);
Matrix3x3 Inverse(Matrix3x3 matrix);
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
Matrix3x3 MakeTranslateMatrix(Vector2 translate);
Matrix2x2 MakeScaleMatrix2x2(Vector2 scale);
Matrix3x3 MakeScaleMatrix3x3(Vector2 scale);
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
Matrix2x2 MakeRotateMatrix2x2(float theta);
Matrix3x3 MakeRotateMatrix3x3(float theta);
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);
float Length(const float& v);
float Length(const Vector2& v);