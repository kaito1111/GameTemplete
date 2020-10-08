#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"
#include "graphics/Shader.h"
struct SSimpleVertex {
	CVector4 pos;
};
struct SVSConstantBuffer {
	CMatrix mWorld;
	//CVector4 mulColor;
};
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	CGameObjectManager()->Init();

	// 頂点バッファの初期化。
	//頂点バッファのソースデータ。
	SSimpleVertex vertices[] =
	{
		CVector4(1.77778f, 1.0f, 0.5f, 1.0f),
		CVector4(1.77778f, -1.0f, 0.5f, 1.0f),
		CVector4(-1.77778f, -1.0f, 0.5f, 1.0f),
		CVector4(-1.77778f, 1.0f, 0.5f, 1.0f),
		CVector4(1.77778f, 1.0f, 0.5f, 1.0f),
	};

	//頂点バッファの定義データを作成する。
	D3D11_BUFFER_DESC desc = { 0 };	//0クリア。
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(vertices);	  //バッファの大きさ。
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//どのバッファにバインドするかを指定する。
	desc.CPUAccessFlags = 0;	//CPUからアクセスするか決める。0ならしない。
	//頂点バッファのソースデータを指定する。
	D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0で初期化。
	InitData.pSysMem = vertices;
	ID3D11Buffer* vertexBuffer;
	//頂点バッファをVRAM上に作成する。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc,&InitData, &vertexBuffer);

	
	//定数バッファの定義データを作成する。
	D3D11_BUFFER_DESC desc2 = { 0 };	//0クリア。
	desc2.Usage = D3D11_USAGE_DEFAULT;
	desc2.ByteWidth = sizeof(SVSConstantBuffer);		//バッファの大きさ。
	desc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//どのバッファにバインドするかを指定する。
									 //定数バッファの場合、ここが頂点バッファと変わる・。
	desc2.CPUAccessFlags = 0;
	ID3D11Buffer* constantBuffer;
	//定数バッファをVRAM上に作成する。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc2, nullptr, &constantBuffer);

	//頂点シェーダーをロード。
	//第一引数はロードするシェーダーソースファイルのファイルパス。
	//第二引数はエントリーポイントとなる関数の名前。 
	//第三引数はロードしたシェーダーのタイプ。ここは頂点シェーダー。
	Shader vsShader;
	vsShader.Load(
		"Assets/shader/sprite.fx",
		"VSMain",
		Shader::EnType::VS
	);
	Shader psShader;
	//ピクセルシェーダーをロード。
	psShader.Load(
		"Assets/shader/sprite.fx",
		"PSMain",
		Shader::EnType::PS
	);
	//IGameObjectPtr hoge = NewGO< PlayerHoge>(0);
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		CGameObjectManager()->ExcuteMain();
		CGameObjectManager()->ExcuteGame();

		auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		
		//static CVector4 mulColor = { 0.0f,0.0f,1.0f,1.0f };//m_mulColorの内容を変更。
		//static CVector4 mulColor = CVector4::White();
		//if (g_pad[0].IsPress(enButtonA)) {
		//	//Aボタンが押された
		//	mulColor.x += 0.05f;
		//	//X = max(X, 0.0f);	//xの値が0.0より小さくならないように。
		//}
		//if (g_pad[0].IsPress(enButtonB)) {
		//	//Bボタンが押された。
		//	mulColor.x -= 0.05f;
		//	//X = min(X, 1.0f);	//xの値が1.0より大きくならないように。
		//}

		//deviceContext->UpdateSubresource(
		//	constantBuffer,
		//	0,
		//	NULL,
		//	&mulColor,
		//	0,
		//	0
		//);
		//deviceContext->PSSetConstantBuffers(
		//	0,
		//	1,
		//	&constantBuffer
		//);

		unsigned int stride = sizeof(SSimpleVertex);
		unsigned int offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		deviceContext->VSSetShader(
			(ID3D11VertexShader*)vsShader.GetBody(),
			NULL,
			0
		);
		deviceContext->PSSetShader(
			(ID3D11PixelShader*)psShader.GetBody(),
			NULL,
			0
		);
		deviceContext->IASetInputLayout(vsShader.GetInputLayout());

		//ワールド・ビュー・プロジェクション行列を更新する。
		SVSConstantBuffer cb;
		//まずはワールド行列。今回は単位行列にしとく。
		cb.mWorld = CMatrix::Identity();
		//cb.mulColor = CVector4::White();
		CVector3 trans = { 0.0f,0.0f,0.0f };
		CMatrix mTrans=CMatrix::Identity();
		mTrans.MakeTranslation(trans);
		//続いてビュー行列。
		CMatrix mView;
		mView.MakeLookAt(
			{ 0.0f, 0.0f, 1.5f },		//視点
			{ 0.0f, 0.0f, 0.0f },	//注視点
			{ 0.0f, 1.0f, 0.0f }		//上方向
		);
		//最後にプロジェクション行列。
		CMatrix mProj;
		mProj.MakeProjectionMatrix(
			CMath::PI * 0.5f,					//画角
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比
			0.1f,								//近平面までの距離
			1000.0f								//遠平面までの距離。
		);
		CMatrix mWvp = CMatrix::Identity();
		cb.mWorld.Mul(cb.mWorld,mTrans);
		cb.mWorld.Mul(mView, cb.mWorld);
		cb.mWorld.Mul(mProj, cb.mWorld);

		//cb.mulColor.x = mulColor.x;

		//VRAM上の定数バッファの内容を更新。
		deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);

		//頂点シェーダーで使用する定数バッファを設定。
		deviceContext->VSSetConstantBuffers(
			0,					//定数バッファをバインドするスロット番号(後述)
			1,					//設定するバッファの数。
			&constantBuffer	    //設定する定数バッファ配列。
		);

		////頂点シェーダーで使用する定数バッファを設定。
		//deviceContext->PSSetConstantBuffers(
		//	0,					//定数バッファをバインドするスロット番号(後述)
		//	1,					//設定するバッファの数。
		//	&constantBuffer	    //設定する定数バッファ配列。
		//);
		deviceContext->Draw(
			5,
			0
		);
		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}