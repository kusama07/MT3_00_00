#include <Novice.h>
#include "MyMath.h"
#include <imgui.h>

const char kWindowTitle[] = "GC1A_03_クサマリョウト_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraTranslate{ 0.0f,1.0f, -6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Sphere sphere = { { 0.0f, 0.0f, 0.0f }, 0.7f };
	Vector3 gridCenter = { 0.0f, -0.4f, 1.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, {0.0f,0.0f,0.0f}, sphere.center);
		Matrix4x4 worldMatrix1 = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { -0.2f,0.0f,0.0f }, gridCenter);

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 worldViewProjectionMatrix1 = Multiply(worldMatrix1, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth) , float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices;
		Vector3 ndcVertex = Transform(sphere.center, worldViewProjectionMatrix);
		screenVertices = Transform(ndcVertex, viewportMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix1, viewportMatrix);
		DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

		ImGui::Begin("window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("sphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("sphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
