#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"
Bloom::Bloom()
{
}

Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr) {
		m_disableBlendState->Release();
	}
	//if (m_blurParamCB != nullptr) {
	//	m_blurParamCB->Release();
	//}
	//if (m_samplerState != nullptr) {
	//	m_samplerState->Release();
	//}
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}

void Bloom::Init()
{
	InitRenderTarget();

	InitShader();

	InitAlphaBlendState();

	//InitConstantBuffer();

	InitSamplerState();

	//�P�x�e�N�X�`�����ڂ������߂̃K�E�V�A���u���[������������B
	ID3D11ShaderResourceView* srcBlurTexture = m_luminanceRT.GetRenderTargetSRV();
	for (int i = 0; i < NUM_DOWN_SAMPLE; i++) {
		m_gaussianBlur[i].Init(srcBlurTexture, 25.0f);
		//���̃K�E�X�u���[�Ŏg�p����\�[�X�e�N�X�`����ݒ肷��B
		srcBlurTexture = m_gaussianBlur[i].GetResultTextureSRV();
	}
}

void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();

	device->CreateBlendState(&blendDesc, &m_disableBlendState);

	//�ŏI�����p�̃u�����h�X�e�[�g���쐬����B
	//�ŏI�����͉��Z�����B
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}

//void Bloom::InitConstantBuffer()
//{
//	D3D11_BUFFER_DESC desc;
//
//	ZeroMemory(&desc, sizeof(desc));
//	desc.Usage = D3D11_USAGE_DEFAULT;
//	desc.ByteWidth = (((sizeof(SBlurParam) - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
//	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	desc.CPUAccessFlags = 0;
//	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_blurParamCB);
//}

void Bloom::InitShader()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", ksEngine::Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", ksEngine::Shader::EnType::PS);
	//m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", ksEngine::Shader::EnType::VS);
	//m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", ksEngine::Shader::EnType::VS);
	//m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", ksEngine::Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", ksEngine::Shader::EnType::PS);
}

void Bloom::InitRenderTarget()
{
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	////�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
	////���u���[�p�B
	//m_downSamplingRT[0].Create(
	//	FRAME_BUFFER_W * 0.5f,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);
	////�c�u���[�p�B
	//m_downSamplingRT[1].Create(
	//	FRAME_BUFFER_W * 0.5f,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
	//	FRAME_BUFFER_H * 0.5f,	//�c�̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);

}

void Bloom::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void Bloom::Draw(PostEffect & postEffect)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//�܂��͋P�x�𒊏o����B
	{
		//���u�����h�𖳌��ɂ���B
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		ChangeRenderTarget(
			m_luminanceRT.GetRenderTargetView(),
			m_luminanceRT.GetDepthStensilView(), 
			m_luminanceRT.GetViewport()
		);
		//�����_�����O�^�[�Q�b�g�̃N���A�B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_luminanceRT.ClearRenderTarget(clearColor);

		//�V�[�����e�N�X�`���Ƃ���B
		auto mainRTTexSRV = postEffect.GetMainRenderTarget()->GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(m_vs, m_psLuminance);
	}

	for (int i = 0; i < NUM_DOWN_SAMPLE; i++) {
		m_gaussianBlur[i].Execute(postEffect);
	}
	
	//�Ō�ɂڂ������G�����Z�����Ń��C�������_�����O�^�[�Q�b�g�ɍ������ďI���B
	{
		auto MainrenderTarget = postEffect.GetMainRenderTarget();
		ChangeRenderTarget(
			MainrenderTarget->GetRenderTargetView(),
			MainrenderTarget->GetDepthStensilView(),
			MainrenderTarget->GetViewport(),
			false
		);

		for (int registerNo = 0; registerNo < NUM_DOWN_SAMPLE; registerNo++) {
			auto srv = m_gaussianBlur[registerNo].GetResultTextureSRV();
			deviceContext->PSSetShaderResources(registerNo, 1, &srv);
		}

		//���Z�����p�̃u�����f�B���O�X�e�[�g��ݒ肷��B
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(m_vs, m_psFinal);

		//�u�����f�B���O�X�e�[�g��߂��B
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	}
}