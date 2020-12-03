#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "graphics/Shader.h"
#include "graphics/SkinModelEffect.h"

SkinModel::SkinModel()
{
}

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}
	if (m_light != nullptr) {
		m_light->Release();
	}
	if (m_albedoTexture != nullptr) {
		m_albedoTexture->Release();
	}
	if (m_silhouettoDepthStepsilState != nullptr) {
		m_silhouettoDepthStepsilState->Release();
	}
}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

	InitShader();

	InitDirectionLight();

	InitSilhouettoDepthStepsilState();
	
	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitShader()
{
	m_vsShader.Load("Assets/shader/model.fx","VSMain", ksEngine::Shader::EnType::VS);
	m_psShader.Load("Assets/shader/model.fx", "PSMain", ksEngine::Shader::EnType::PS);

	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", ksEngine::Shader::EnType::PS);
}

void SkinModel::InitSilhouettoDepthStepsilState()
{
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //ZバッファにZ値を描き込まない。
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z値が大きければフレームバッファに描き込む。

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}

void SkinModel::InitDirectionLight()
{
	m_dirLight.dir.Direction[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.dir.Color[0] = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_dirLight.dir.Direction[1] = { 0.0f, -1.0f, 0.0f, 0.0f };
	m_dirLight.dir.Color[1] = { 0.0f, 1.0f, 0.0f, 1.0f };

	m_dirLight.dir.Direction[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	m_dirLight.dir.Color[2] = { 1.0f, 0.0f, 1.0f, 1.0f };

	m_dirLight.dir.Direction[3] = { 1.0f, 0.0f, -1.0f, 0.0f };
	m_dirLight.dir.Color[3] = { 1.0f, 1.0f, 0.0f, 1.0f };
	m_dirLight.eyePos = g_camera3D.GetPosition();
	m_dirLight.pow = 5.0f;
}

void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	bufferDesc.ByteWidth = sizeof(Light);				//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_light);
}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	m_dirLight.eyePos = g_camera3D.GetPosition();
	d3dDeviceContext->UpdateSubresource(m_light, 0, nullptr, &m_dirLight, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_light);

	//定数バッファの内容を更新。
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();

	//d3dDeviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
	//switch (m_renderMode) {
	//case 0:
	//	//通常描画。
	//	d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
	//	d3dDeviceContext->PSSetShaderResources(0, 1, &m_albedoTexture);
	//	break;
	//case 1:
	//	//シルエット描画。
	//	d3dDeviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
	//	//デプスステンシルステートを切り替える。
	//	d3dDeviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
	//	break;
	//}


	m_renderTarget.OffScreenRendering();

	QueryMaterials([&](ModelEffect* material) {
		//差し替え前のテクスチャをスタックに退避。
		material->PushAlbedoTexture();
		//テクスチャを差し替える。
		material->SetAlbedoTexture(m_renderTarget.GetRTSRV());
	});

	//描画。                                                                           
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);

	m_renderTarget.OnScreenRendering();

	//背景のテクスチャを元に戻す。
	QueryMaterials([&](ModelEffect* material) {
		//差し替え前のテクスチャをスタックから復帰。
		material->PopAlbedoTexture();
	});

	//描画。                                                                           
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}