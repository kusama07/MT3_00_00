#pragma once
#include <Vector2.h>
#include <Vector3.h>
#include <cmath>
#include <assert.h>

struct Matrix2x2 {
	float m[2][2];
};

struct Matrix3x3 {
	float m[3][3];
};

struct Matrix4x4 {
	float m[4][4];
};

Vector2 Add(const Vector2& v1, const Vector2& v2);
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

// 00_01
Vector3 Add(const Vector3 &v1, const Vector3 &v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label);

// 00_02
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();
void MatrixScreenPrintf(int x, int y, Matrix4x4& matrix, const char* label);

// 00_03
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 00_04
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);