#include "stdafx.h"
#include "GaussianBlur.h"

GaussianBlur::GaussianBlur()
{
}

GaussianBlur::~GaussianBlur()
{
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
}

void GaussianBlur::Init(ID3D11ShaderResourceView * srcTextureSRV, float blurIntensity)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);

	//�\�[�X�e�N�X�`����SRV���R�s�[
	m_SrcTextureSRV = srcTextureSRV;
	//UpdateWeight�֐��Ŏg�p����̂ŁA�u���[�̋����������o�ϐ��ɋL�����Ă���
	m_BlurIntensity = blurIntensity;

	//�擾�e�N�X�`������A�e�N�X�`�������擾����B
	D3D11_TEXTURE2D_DESC texDesc;
	{
		//�\�[�X�e�N�X�`���̏����擾�B
		ID3D11Texture2D* tex;
		//�܂��ASRV�Ɋ֘A�t������Ă���e�N�X�`�����擾����B
		srcTextureSRV->GetResource((ID3D11Resource**)&tex);
		tex->GetDesc(&texDesc);
		//�e�N�X�`�������擾�ł����̂Ńe�N�X�`���̎Q�ƃJ�E���^�����낷�B
		tex->Release();
	}
	//�\�[�X�e�N�X�`���̕��ƍ������L�����Ă����B
	m_srcTextureHight = texDesc.Height;
	m_srcTextureWidth = texDesc.Width;

	//X�u���[�p�̃����_�[�^�[�Q�b�g���쐬
	m_renderTarget[enRenderTarget_XBlur].Create(
		texDesc.Width / 2,//���̉𑜓x�𔼕��ɂ���B
		texDesc.Height,
		texDesc.Format
	);

	//Y�u���[�p�̃����_�����O�^�[�Q�b�g���쐬�B
	m_renderTarget[enRenderTarget_YBlur].Create(
		texDesc.Width / 2,//���̉𑜓x�𔼕��ɂ���B
		texDesc.Height / 2,//�c�̉𑜓x�𔼕��ɂ���B
		texDesc.Format
	);

	//�V�F�[�_�[�����[�h�B
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", ksEngine::Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", ksEngine::Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", ksEngine::Shader::EnType::PS);
	//VRCM��ɒ萔�o�b�t�@���쐬�B
	m_blurCbGPU.Create(nullptr, sizeof(SBlurParam));

	//�쐬�ς�
	m_IsCreate = true;
}

void GaussianBlur::UpdateWeights()
{
	//�K�E�X�t�B���^�̏d�݂��X�V����B
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_BlurIntensity);
		total += 2.0f*m_blurParam.weights[i];
	}
	//�d�݂̍��v�Ŋe�d�݂����Z���āA���K������B
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}

void GaussianBlur::Execute(PostEffect & postEffect)
{
	if (m_IsCreate == false) {
		//�������Y��
		return;
	}
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	UpdateWeights();

	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	auto d3d11CbGpu = m_blurCbGPU.GetD3D11Buffer();
	deviceContext->UpdateSubresource(
		d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
	deviceContext->PSSetConstantBuffers(
		0, 1, &d3d11CbGpu);

	{
		ChangeRenderTarget(
			m_renderTarget[enRenderTarget_XBlur].GetRenderTargetView(),
			m_renderTarget[enRenderTarget_XBlur].GetDepthStensilView(),
			m_renderTarget[enRenderTarget_XBlur].GetViewport());
		deviceContext->VSSetShaderResources(0, 1, &m_SrcTextureSRV);
		deviceContext->PSSetShaderResources(0, 1, &m_SrcTextureSRV);

		postEffect.DrawFullScreenQuadPrimitive(m_vsXBlur, m_psBlur);
	}

	{

		ChangeRenderTarget(
			m_renderTarget[enRenderTarget_YBlur].GetRenderTargetView(),
			m_renderTarget[enRenderTarget_YBlur].GetDepthStensilView(),
			m_renderTarget[enRenderTarget_YBlur].GetViewport());
		auto srcTextrueSrv = m_renderTarget[enRenderTarget_XBlur].GetRenderTargetSRV();
		deviceContext->VSSetShaderResources(0, 1, &srcTextrueSrv);
		deviceContext->PSSetShaderResources(0, 1, &srcTextrueSrv);

		postEffect.DrawFullScreenQuadPrimitive(m_vsYBlur, m_psBlur);
	}
}
