#include "stdafx.h"
#include "Sprite.h"
#include <Windows.h>
namespace ksEngine {
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CVector4 mulColor;
	};
	void Sprite::Init(const wchar_t* fileName, float w, float h)
	{
		//共通の初期化処理を呼び出す。
		InitCommon(w, h);
		CreateFromDDSTextureFromFile(fileName);
		IsCreated = true;
	}
	void Sprite::Init(ID3D11ShaderResourceView * srv, float w, float h)
	{
		//共通の初期化処理を呼び出す。
		InitCommon(w, h);
		m_TextureSRV = srv;
		m_TextureSRV->AddRef();	//参照カウンタを増やす。
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
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		//半透明合成のブレンドステートを設定する。
		m_deviceContext->OMSetBlendState(
			m_translucentBlendState, //設定するブレンディングステート
			blendFactor, //ブレンディングファクター。気にしなくてよい
			0xffffffff //サンプリングマスク。気にしなくてよい。
		);
		SetWVP(viewMatrix, projMatrix);
		ConstantBuffer();
		m_deviceContext->PSSetShaderResources(0, 1, &m_TextureSRV);
		//サンプラステートを設定。
		//m_deviceContext->PSSetSamplers(0, 1, &m_samplerState);
		m_deviceContext->IASetInputLayout(m_vs.GetInputLayout());
		SetShader();


		UINT strid = sizeof(SSimpleVertex);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &strid, &offset);
		m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, offset);
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		auto* RS = g_graphicsEngine->GetRS();
		m_deviceContext->RSSetState(RS);
		//m_deviceContext->DrawIndexed(6, 0, 0);

		m_deviceContext->Draw(
			4,
			0
		);

	}

	void Sprite::InitCommon(float w, float h)
	{
		CreateVertexBuffer(w, h);
		CreateIndexBuffer();
		CreateConstantBuffer();
		InitSamplerState();
		InitShader();
		InitTranslucentBlendState();
	}

	void Sprite::CreateVertexBuffer(float w, float h)
	{
		// 頂点バッファの初期化。
		//頂点バッファのソースデータ。
		m_Size.x = w;
		m_Size.y = h;
		float halfW = w * 0.5f;
		float halfH = h * 0.5f;
		SSimpleVertex vertices[] =
		{
			{CVector4(halfW, halfH, 0.5f, 1.0f),CVector2(1.0,0.0f)},
			{CVector4(-halfW, halfH, 0.5f, 1.0f),CVector2(0.0f,0.0f)},
			{CVector4(halfW, -halfH, 0.5f, 1.0f),CVector2(1.0f,1.0f)},
			{CVector4(-halfW, -halfH, 0.5f, 1.0f),CVector2(0.0f,1.0f)},
			//{CVector4(-0.5f, 0.5f, 0.5f, 1.0f),CVector2(0.0f,0.0f)},
		};

		//頂点バッファの定義データを作成する。
		D3D11_BUFFER_DESC desc = { 0 };	//0クリア。
		desc.Usage = D3D11_USAGE_DEFAULT;
		int verticesSize = sizeof(vertices);
		desc.ByteWidth = verticesSize;	  //バッファの大きさ。
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//どのバッファにバインドするかを指定する。
		desc.CPUAccessFlags = 0;	//CPUからアクセスするか決める。0ならしない。
		//頂点バッファのソースデータを指定する。
		D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0で初期化。
		InitData.pSysMem = vertices;
		//頂点バッファをVRAM上に作成する。
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &InitData, &m_vertexBuffer);
	}
	void Sprite::CreateIndexBuffer()
	{
		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		short index[6] = {
			0,1,2,		//三角形一つ目
			2,1,3, 		//三角形二つ目
		};
		InitData.pSysMem = index;

		D3D11_BUFFER_DESC bd = { 0 };
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.StructureByteStride = sizeof(short);
		bd.ByteWidth = sizeof(index);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
	}

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
	void Sprite::InitTranslucentBlendState()
	{
		//例のごとく、作成するブレンドステートの情報を設定する。
		CD3D11_DEFAULT defaultSettings;
		//デフォルトセッティングで初期化する。
		CD3D11_BLEND_DESC blendDesc(defaultSettings);
		//αブレンディングを有効にする。
		blendDesc.RenderTarget[0].BlendEnable = true;
		//ソースカラーのブレンディング方法を指定している。
		//ソースカラーとはピクセルシェーダ―からの出力を指している。
		//この指定では、ソースカラーをSRC(rgba)とすると、
		//最終的なソースカラーは下記のように計算される。
		//最終的なソースカラー = SRC.rgb × SRC.a・・・・・・ ①
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		//ディスティネーションカラーのブレンディング方法を指定している。
		//ディスティネーションカラーとは、
		//すでに描き込まれているレンダリングターゲットのカラーを指している。
		//この指定では、ディスティネーションカラーをDEST(rgba)、
		//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
		//下記のように計算される。
		//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・②
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
		//この指定だと、①＋②のカラーが書き込まれる。
		//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
		//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
		//となる。
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//この設定で、ブレンドステートを作成すると
		//半透明合成を行えるブレンドステートが作成できる。
		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
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
		//ピボットを考慮に入れた平行移動行列を作成。
		//ピボットは真ん中が0.0, 0.0、左上が-1.0f, -1.0、右下が1.0、1.0になるようにする。
		CVector2 localPivot = m_pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//画像のハーフサイズを求める。
		CVector2 halfSize = m_Size;
		halfSize.x *= 0.5f;
		halfSize.y *= 0.5f;
		CMatrix mPivotTrans;

		mPivotTrans.MakeTranslation(
			{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
		);
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
		m_alpha += g_pad[0].GetLStickXF()*0.1f;
		cb.mulColor.w = m_alpha;
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

	void Sprite::InitSamplerState()
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	}

}