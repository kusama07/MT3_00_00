#include <Novice.h>
#include "MyMath.h"

const char kWindowTitle[] = "GC1A_03_クサマリョウト_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 rotate{ 1.0f,1.0f,1.0f };
	Vector3 translate{ 1.0f,1.0f,1.0f };
	Vector3 kLocalVertices[3]{
		{0.0f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f}
	};

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

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

		Vector3 v1{ 1.2f,-3.9f,2.5f };
		Vector3 v2{ 2.8f,0.4f,-1.3f };
		Vector3 cross = Cross(v1, v2);
		VectorScreenPrintf(0, 0, cross, "Cross");

		// 前後
		if (keys[DIK_W]) {
			translate.y += 1.0f;
		} else if (keys[DIK_S]) {
			translate.y -= 1.0f;
		}
		// 左右
		if (keys[DIK_A]) {
			translate.x -= 1.0f;
		} else if (keys[DIK_D]) {
			translate.x += 1.0f;
		}
		// Y軸回転
		if (keys[DIK_Q]) {
			rotate.y += 1.0f;
		} else if (keys[DIK_E]) {
			rotate.y -= 1.0f;
		}

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth) , float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y), 
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y),
			RED,kFillModeSolid
		);

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
