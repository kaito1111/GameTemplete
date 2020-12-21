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
		//���ʂ̏������������Ăяo���B
		InitCommon(w, h);
		CreateFromDDSTextureFromFile(fileName);
		IsCreated = true;
	}
	void Sprite::Init(ID3D11ShaderResourceView * srv, float w, float h)
	{
		//���ʂ̏������������Ăяo���B
		InitCommon(w, h);
		m_TextureSRV = srv;
		m_TextureSRV->AddRef();	//�Q�ƃJ�E���^�𑝂₷�B
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
				TEXT("�e�N�X�`���Ȃ�"),
				TEXT("�X�v���C�g"),
				MB_ICONWARNING);
			return;
		}
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		//�����������̃u�����h�X�e�[�g��ݒ肷��B
		m_deviceContext->OMSetBlendState(
			m_translucentBlendState, //�ݒ肷��u�����f�B���O�X�e�[�g
			blendFactor, //�u�����f�B���O�t�@�N�^�[�B�C�ɂ��Ȃ��Ă悢
			0xffffffff //�T���v�����O�}�X�N�B�C�ɂ��Ȃ��Ă悢�B
		);
		SetWVP(viewMatrix, projMatrix);
		ConstantBuffer();
		m_deviceContext->PSSetShaderResources(0, 1, &m_TextureSRV);
		//�T���v���X�e�[�g��ݒ�B
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
		// ���_�o�b�t�@�̏������B
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
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

		//���_�o�b�t�@�̒�`�f�[�^���쐬����B
		D3D11_BUFFER_DESC desc = { 0 };	//0�N���A�B
		desc.Usage = D3D11_USAGE_DEFAULT;
		int verticesSize = sizeof(vertices);
		desc.ByteWidth = verticesSize;	  //�o�b�t�@�̑傫���B
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//�ǂ̃o�b�t�@�Ƀo�C���h���邩���w�肷��B
		desc.CPUAccessFlags = 0;	//CPU����A�N�Z�X���邩���߂�B0�Ȃ炵�Ȃ��B
		//���_�o�b�t�@�̃\�[�X�f�[�^���w�肷��B
		D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0�ŏ������B
		InitData.pSysMem = vertices;
		//���_�o�b�t�@��VRAM��ɍ쐬����B
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &InitData, &m_vertexBuffer);
	}
	void Sprite::CreateIndexBuffer()
	{
		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		short index[6] = {
			0,1,2,		//�O�p�`���
			2,1,3, 		//�O�p�`���
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
		//�萔�o�b�t�@�̒�`�f�[�^���쐬����B
		D3D11_BUFFER_DESC desc = { 0 };	//0�N���A�B
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(SVSConstantBuffer);		//�o�b�t�@�̑傫���B
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�ǂ̃o�b�t�@�Ƀo�C���h���邩���w�肷��B
										 //�萔�o�b�t�@�̏ꍇ�A���������_�o�b�t�@�ƕς��E�B
		desc.CPUAccessFlags = 0;
		//�萔�o�b�t�@��VRAM��ɍ쐬����B
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, nullptr, &m_constantBuffer);

	}
	void Sprite::InitTranslucentBlendState()
	{
		//��̂��Ƃ��A�쐬����u�����h�X�e�[�g�̏���ݒ肷��B
		CD3D11_DEFAULT defaultSettings;
		//�f�t�H���g�Z�b�e�B���O�ŏ���������B
		CD3D11_BLEND_DESC blendDesc(defaultSettings);
		//���u�����f�B���O��L���ɂ���B
		blendDesc.RenderTarget[0].BlendEnable = true;
		//�\�[�X�J���[�̃u�����f�B���O���@���w�肵�Ă���B
		//�\�[�X�J���[�Ƃ̓s�N�Z���V�F�[�_�\����̏o�͂��w���Ă���B
		//���̎w��ł́A�\�[�X�J���[��SRC(rgba)�Ƃ���ƁA
		//�ŏI�I�ȃ\�[�X�J���[�͉��L�̂悤�Ɍv�Z�����B
		//�ŏI�I�ȃ\�[�X�J���[ = SRC.rgb �~ SRC.a�E�E�E�E�E�E �@
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		//�f�B�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@���w�肵�Ă���B
		//�f�B�X�e�B�l�[�V�����J���[�Ƃ́A
		//���łɕ`�����܂�Ă��郌���_�����O�^�[�Q�b�g�̃J���[���w���Ă���B
		//���̎w��ł́A�f�B�X�e�B�l�[�V�����J���[��DEST(rgba)�A
		//�\�[�X�J���[��SRC(RGBA)�Ƃ���ƁA�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[��
		//���L�̂悤�Ɍv�Z�����B
		//�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[ = DEST.rgb �~ (1.0f - SRC.a)�E�E�E�E�E�A
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		//�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[�̌v�Z���@���w�肵�Ă���B
		//���̎w�肾�ƁA�@�{�A�̃J���[���������܂��B
		//�܂�A�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[��
		//SRC.rgb �~ SRC.a + DEST.rgb �~ (1.0f - SRC.a)
		//�ƂȂ�B
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//���̐ݒ�ŁA�u�����h�X�e�[�g���쐬�����
		//�������������s����u�����h�X�e�[�g���쐬�ł���B
		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
	}
	void Sprite::InitShader()
	{
		//���_�V�F�[�_�[�����[�h�B
		//�������̓��[�h����V�F�[�_�[�\�[�X�t�@�C���̃t�@�C���p�X�B
		//�������̓G���g���[�|�C���g�ƂȂ�֐��̖��O�B 
		//��O�����̓��[�h�����V�F�[�_�[�̃^�C�v�B�����͒��_�V�F�[�_�[�B
		m_vs.Load(
			"Assets/shader/sprite.fx",
			"VSMain",
			Shader::EnType::VS
		);
		//�s�N�Z���V�F�[�_�[�����[�h�B
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
				TEXT("FilePath�����������ł��B\nFilePath���ԈႦ�Ă��Ȃ����m�F���Ă�������"),
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
		//�s�{�b�g���l���ɓ��ꂽ���s�ړ��s����쐬�B
		//�s�{�b�g�͐^�񒆂�0.0, 0.0�A���オ-1.0f, -1.0�A�E����1.0�A1.0�ɂȂ�悤�ɂ���B
		CVector2 localPivot = m_pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//�摜�̃n�[�t�T�C�Y�����߂�B
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
		//���[���h�E�r���[�E�v���W�F�N�V�����s����X�V����B
		SVSConstantBuffer cb;

		//�܂��̓��[���h�s��B����͒P�ʍs��ɂ��Ƃ��B
		//�����ăr���[�s��B
		cb.mWorld.Mul(m_world, viewMatrix);
		//�Ō�Ƀv���W�F�N�V�����s��B
		cb.mWorld.Mul(cb.mWorld, projMatrix);

		cb.mulColor = CVector4::White();
		m_alpha += g_pad[0].GetLStickXF()*0.1f;
		cb.mulColor.w = m_alpha;
		//VRAM��̒萔�o�b�t�@�̓��e���X�V�B
		m_deviceContext->UpdateSubresource(m_constantBuffer, 0, NULL, &cb, 0, 0);
	}
	void Sprite::ConstantBuffer()
	{
		//���_�V�F�[�_�[�Ŏg�p����萔�o�b�t�@��ݒ�B
		m_deviceContext->VSSetConstantBuffers(
			0,					//�萔�o�b�t�@���o�C���h����X���b�g�ԍ�(��q)
			1,					//�ݒ肷��o�b�t�@�̐��B
			&m_constantBuffer	    //�ݒ肷��萔�o�b�t�@�z��B
		);

		//�s�N�Z���V�F�[�_�[�Ŏg�p����萔�o�b�t�@��ݒ�B
		m_deviceContext->PSSetConstantBuffers(
			0,					//�萔�o�b�t�@���o�C���h����X���b�g�ԍ�(��q)
			1,					//�ݒ肷��o�b�t�@�̐��B
			&m_constantBuffer	    //�ݒ肷��萔�o�b�t�@�z��B
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