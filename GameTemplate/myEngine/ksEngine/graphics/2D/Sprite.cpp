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
				TEXT("�e�N�X�`���Ȃ�"),
				TEXT("�X�v���C�g"),
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
		// ���_�o�b�t�@�̏������B
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
		SSimpleVertex vertices[] =
		{
			{CVector4(0.5, 0.5f, 0.5f, 1.0f),CVector2(1.0,0.0f)},
			{CVector4(-0.5f, 0.5f, 0.5f, 1.0f),CVector2(0.0f,0.0f)},
			{CVector4(0.5f, -0.5f, 0.5f, 1.0f),CVector2(1.0f,1.0f)},
			{CVector4(-0.5, -0.5f, 0.5f, 1.0f),CVector2(0.0f,1.0f)},
			//{CVector4(-0.5f, 0.5f, 0.5f, 1.0f),CVector2(0.0f,0.0f)},
		};

		//���_�o�b�t�@�̒�`�f�[�^���쐬����B
		D3D11_BUFFER_DESC desc = { 0 };	//0�N���A�B
		desc.Usage = D3D11_USAGE_DEFAULT;
		int a = sizeof(vertices);
		desc.ByteWidth = a;	  //�o�b�t�@�̑傫���B
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//�ǂ̃o�b�t�@�Ƀo�C���h���邩���w�肷��B
		desc.CPUAccessFlags = 0;	//CPU����A�N�Z�X���邩���߂�B0�Ȃ炵�Ȃ��B
		//���_�o�b�t�@�̃\�[�X�f�[�^���w�肷��B
		D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0�ŏ������B
		InitData.pSysMem = vertices;
		//���_�o�b�t�@��VRAM��ɍ쐬����B
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


}