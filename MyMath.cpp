#include "MyMath.h"

Vector2 Add(Vector2 a, Vector2 b)
{
	Vector2 result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;

	return result;
};

Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 result = {};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {

			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
}

float Length(const float& v)
{
	float result;
	result = sqrtf(v * v);

	return result;
}

float Length(const Vector2& v)
{
	float result;
	result = sqrtf(v.x * v.x + v.y * v.y);

	return result;
}

Vector2 Multiply(Vector2 vector1, Vector2 vector2)
{
	Vector2 result;

	result.x = vector1.x * vector2.x;
	result.y = vector1.y * vector2.y;

	return result;
}

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix)
{
	Vector2 result = {};

	result = { (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]), (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) };

	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	Matrix3x3 result = {};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}

	return result;
}

Matrix2x2 Transpose(Matrix2x2 matrix) {
	Matrix2x2 result;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}

	return result;
};

Matrix3x3 Transpose(Matrix3x3 matrix) {
	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}

	return result;
};

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 ans;

	ans.m[0][0] = 2.0f / (right - left);
	ans.m[0][1] = 0.0f;
	ans.m[0][2] = 0.0f;

	ans.m[1][0] = 0.0f;
	ans.m[1][1] = 2.0f / (top - bottom);
	ans.m[1][2] = 0.0f;

	ans.m[2][0] = (left + right) / (left - right);
	ans.m[2][1] = (top + bottom) / (bottom - top);
	ans.m[2][2] = 1.0f;

	return ans;
};

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 ans;

	ans.m[0][0] = width / 2.0f;
	ans.m[0][1] = 0.0f;
	ans.m[0][2] = 0.0f;

	ans.m[1][0] = 0.0f;
	ans.m[1][1] = -(height / 2.0f);
	ans.m[1][2] = 0.0f;

	ans.m[2][0] = left + (width / 2.0f);
	ans.m[2][1] = top + (height / 2.0f);
	ans.m[2][2] = 1.0f;

	return ans;
};

Matrix3x3 MakeRotateMatrix3x3(float theta) {

	Matrix3x3 result = {};

	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[0][2] = 0.0f;

	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[1][2] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;

	return result;
};

Matrix2x2 Inverse(Matrix2x2 matrix) {

	float im = (matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[0][1] * matrix.m[1][0]);

	return Matrix2x2{
		(1 / im) * matrix.m[1][1],(1 / im) * -(matrix.m[0][1]),
		(1 / im) * -(matrix.m[1][0]),(1 / im) * matrix.m[0][0]
	};
};

Matrix3x3 Inverse(Matrix3x3 matrix) {

	float im = (
		(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) +
		(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +
		(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
		(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -
		(matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) -
		(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));

	return Matrix3x3{
		(1 / im) * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]),
		(1 / im) * -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]),
		(1 / im) * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]),

		(1 / im) * -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]),
		(1 / im) * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]),
		(1 / im) * -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]),

		(1 / im) * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]),
		(1 / im) * -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]),
		(1 / im) * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]),
	};

}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;
	return result;
}

Matrix2x2 MakeScaleMatrix2x2(Vector2 scale) {
	Matrix2x2 result = {};

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;

	return result;
};

Matrix3x3 MakeScaleMatrix3x3(Vector2 scale) {
	Matrix3x3 result = {};

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;

	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	Matrix3x3 result;

	result = Multiply(MakeScaleMatrix3x3(scale), MakeRotateMatrix3x3(rotate));
	
	result = Multiply(result, MakeTranslateMatrix(translate));

	return result;
}

Matrix2x2 MakeRotateMatrix2x2(float theta)
{
	Matrix2x2 result = {};

	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);

	return result;
};