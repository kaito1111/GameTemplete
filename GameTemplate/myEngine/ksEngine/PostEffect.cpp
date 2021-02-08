#include "stdafx.h"
#include "PostEffect.h"
#include "graphics/Bloom.h"

PostEffect::PostEffect()
{
}

PostEffect::~PostEffect()
{
}

struct SVertex {
	float position[4];		//���_���W�B
	float uv[2];			//UV���W�B���ꂪ�e�N�X�`�����W
};

void PostEffect::Init()
{
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//���_�o�b�t�@���������B
	SVertex vertex[4] = {
		//���_�P
		{
			//���W�@position[4]
			-1.0f,  -1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 1.0f
		},
		//���_�Q
		{
			//���W�@position[4]
			1.0f, -1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 1.0f
		},
		//���_�R
		{
			//���W�@position[4]
			-1.0f,  1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 0.0f
		},
		//���_�S
		{
			//���W�@position[4]
			1.0f,  1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 0.0f
		},
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(vertex);				//���_�o�b�t�@�̃T�C�Y�B���_�̃T�C�Y�~���_���ƂȂ�B
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//���_�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
	m_bloom.Init();
}

void PostEffect::ChangeMainRendertTarget()
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->OMGetRenderTargets(
		1,
		&m_PostEffectRenderTargetView,
		&m_PostEffectDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	deviceContext->RSGetViewports(&numViewport, &m_PostEffectViewports);
	ChangeRenderTarget(
		m_mainRenderTarget.GetRenderTargetView(),
		m_mainRenderTarget.GetDepthStensilView(),
		&m_PostEffectViewports
	);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	m_copyMainRtToFrameBufferSprite.Update();
}

void PostEffect::PostRender()
{
	ChangeRenderTarget(
		m_PostEffectRenderTargetView,
		m_PostEffectDepthStencilView,
		&m_PostEffectViewports
	);
	m_copyMainRtToFrameBufferSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetOrthoProjectionMatrix()
	);
	if (m_PostEffectRenderTargetView != nullptr) {
		m_PostEffectRenderTargetView->Release();
	}
	if (m_PostEffectDepthStencilView != nullptr) {
		m_PostEffectDepthStencilView->Release();
	}
}

void PostEffect::Draw()
{
	m_bloom.Draw(*this);
}

void PostEffect::DrawFullScreenQuadPrimitive(ksEngine::Shader& vsShader, ksEngine::Shader& psShader)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�v���~�e�B�u�̃g�|���W�[�Ƃ��āA�g���C�A���O���X�g���b�v��ݒ肷��B
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;
	//�P�x���o�p�̃V�F�[�_�[��ݒ肷��B
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
	);
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
	);
	deviceContext->IASetInputLayout(vsShader.GetInputLayout());

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
	deviceContext->Draw(4, 0);
}