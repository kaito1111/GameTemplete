#include "stdafx.h"
#include "Sprite.h"
#include <Windows.h>
namespace ksEngine {
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CVector4 mulColor;
	};
	void Sprite::Init(const wchar_t* fileName/*, float w, float h*/)
	{
		CreateVertexBuffer();
		//CreateIndexBuffer();
		CreateConstantBuffer();
		InitShader();
		CreateFromDDSTextureFromFile(fileName);
		IsCreated = true;
	}
	void Sprite::Update()
	{
		if (!IsCreated) {
			return;
		}
		m_deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		SetVertexBuffer();
		SetWorld();
		m_deviceContext->IASetInputLayout(m_vs.GetInputLayout());
	}
	void Sprite::Draw(const CMatrix & viewMatrix, const CMatrix & projMatrix)
	{
		if (m_TextureSRV == nullptr) {
			MessageBox(
				NULL,
				TEXT("テクスチャなし"),
				TEXT("スプライト"),
				MB_ICONWARNING);
			return;
		}
		SetWVP(viewMatrix, projMatrix);
		ConstantBuffer();
		m_deviceContext->PSSetShaderResources(0, 1, &m_TextureSRV);
		SetShader();

		UINT strid = sizeof(SSimpleVertex);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &strid, &offset);
		//m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//m_deviceContext->DrawIndexed(5, 0, 0);


		m_deviceContext->Draw(
			4,
			0
		);

	}
	void Sprite::CreateVertexBuffer()
	{
		// 頂点バッファの初期化。
		//頂点バッファのソースデータ。
		SSimpleVertex vertices[] =
		{
			{CVector4(0.5, 0.5f, 0.5f, 1.0f),CVector2(1.0,0.0f)},
			{CVector4(-0.5f, 0.5f, 0.5f, 1.0f),CVector2(0.0f,0.0f)},
			{CVector4(0.5f, -0.5f, 0.5f, 1.0f),CVector2(1.0f,1.0f)},
			{CVector4(-0.5, -0.5f, 0.5f, 1.0f),CVector2(0.0f,1.0f)},
			//{CVector4(-0.5f, 0.5f, 0.5f, 1.0f),CVector2(0.0f,0.0f)},
		};

		//頂点バッファの定義データを作成する。
		D3D11_BUFFER_DESC desc = { 0 };	//0クリア。
		desc.Usage = D3D11_USAGE_DEFAULT;
		int a = sizeof(vertices);
		desc.ByteWidth = a;	  //バッファの大きさ。
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//どのバッファにバインドするかを指定する。
		desc.CPUAccessFlags = 0;	//CPUからアクセスするか決める。0ならしない。
		//頂点バッファのソースデータを指定する。
		D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0で初期化。
		InitData.pSysMem = vertices;
		//頂点バッファをVRAM上に作成する。
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &InitData, &m_vertexBuffer);
	}
	//void Sprite::CreateIndexBuffer()
	//{
	//	D3D11_BUFFER_DESC bd = { 0 };
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	//	bd.StructureByteStride = 2;
	//	bd.ByteWidth = 2 * 5;
	//	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//	bd.CPUAccessFlags = 0;
	//	D3D11_SUBRESOURCE_DATA InitData = { 0 };
	//	short indices[] = { 0,1,2,3,4 };
	//	InitData.pSysMem = indices;
	//	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
	//}
	void Sprite::CreateConstantBuffer()
	{
		//定数バッファの定義データを作成する。
		D3D11_BUFFER_DESC desc = { 0 };	//0クリア。
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(SVSConstantBuffer);		//バッファの大きさ。
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//どのバッファにバインドするかを指定する。
										 //定数バッファの場合、ここが頂点バッファと変わる・。
		desc.CPUAccessFlags = 0;
		//定数バッファをVRAM上に作成する。
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, nullptr, &m_constantBuffer);

	}
	void Sprite::InitShader()
	{
		//頂点シェーダーをロード。
		//第一引数はロードするシェーダーソースファイルのファイルパス。
		//第二引数はエントリーポイントとなる関数の名前。 
		//第三引数はロードしたシェーダーのタイプ。ここは頂点シェーダー。
		m_vs.Load(
			"Assets/shader/sprite.fx",
			"VSMain",
			Shader::EnType::VS
		);
		//ピクセルシェーダーをロード。
		m_ps.Load(
			"Assets/shader/sprite.fx",
			"PSMain",
			Shader::EnType::PS
		);
	}
	void Sprite::CreateFromDDSTextureFromFile(const wchar_t* fileName)
	{
		HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), fileName, 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &m_TextureSRV);
		if (FAILED(hr)) {
			MessageBox(
				NULL,
				TEXT("FilePathがおかしいです。\nFilePathが間違えていないか確認してください"),
				TEXT("Sprite"),
				MB_ICONWARNING
			);
		}
	}
	void Sprite::SetVertexBuffer()
	{
		unsigned int stride = sizeof(SSimpleVertex);
		unsigned int offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	void Sprite::SetWorld()
	{
		CMatrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(m_position);
		mRot.MakeRotationFromQuaternion(m_rotation);
		mScale.MakeScaling(m_scale);
		m_world.Mul(mScale, mRot);
		m_world.Mul(mTrans, m_world);
	}

	void Sprite::SetWVP(const CMatrix & viewMatrix, const CMatrix & projMatrix)
	{
		//ワールド・ビュー・プロジェクション行列を更新する。
		SVSConstantBuffer cb;

		//まずはワールド行列。今回は単位行列にしとく。
		//続いてビュー行列。
		cb.mWorld.Mul(m_world, viewMatrix);
		//最後にプロジェクション行列。
		cb.mWorld.Mul(cb.mWorld, projMatrix);

		cb.mulColor = CVector4::White();
		//VRAM上の定数バッファの内容を更新。
		m_deviceContext->UpdateSubresource(m_constantBuffer, 0, NULL, &cb, 0, 0);
	}
	void Sprite::ConstantBuffer()
	{
		//頂点シェーダーで使用する定数バッファを設定。
		m_deviceContext->VSSetConstantBuffers(
			0,					//定数バッファをバインドするスロット番号(後述)
			1,					//設定するバッファの数。
			&m_constantBuffer	    //設定する定数バッファ配列。
		);

		//ピクセルシェーダーで使用する定数バッファを設定。
		m_deviceContext->PSSetConstantBuffers(
			0,					//定数バッファをバインドするスロット番号(後述)
			1,					//設定するバッファの数。
			&m_constantBuffer	    //設定する定数バッファ配列。
		);
	}
	void Sprite::SetShader()
	{
		m_deviceContext->VSSetShader(
			(ID3D11VertexShader*)m_vs.GetBody(),
			NULL,
			0);
		m_deviceContext->PSSetShader(
			(ID3D11PixelShader*)m_ps.GetBody(),
			NULL,
			0);
	}


}