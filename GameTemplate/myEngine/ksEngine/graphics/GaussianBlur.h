#pragma once
#include "graphics/GPUBuffer/ConstantBufferGPU.h"
#include "Shader.h"
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();

	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="srcTexture">�u���[��������e�N�X�`����SRV</param>
	/// <param name="blurIntensity">�u���[�̋����B�l���傫���قǋ����u���[��������B</param>
	void Init(ID3D11ShaderResourceView* srcTextureSRV, float blurIntensity);
	/// <summary>
	/// �u���[�̎��s
	/// </summary>
	/// <param name="postEffect">
	/// �|�X�g�G�t�F�N�g�̃C���X�^���X�B
	/// �S��ʕ`��̋@�\���g�����������ł��B�B�B
	/// </param>
	/// <remarks>
	/// Init�֐����Ăяo������Ŏ��s����悤�ɂ��Ă��������B
	/// </remarks>
	void Execute(PostEffect& postEffect);

	ID3D11ShaderResourceView* GetResultTextureSRV() {
		return m_renderTarget[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
private:
	/// <summary>
	/// �u���[�̏d�݂̍X�V�B
	/// </summary>
	void UpdateWeights();
private:
	static const int NUM_WEIGHTS = 8;	//�J�E�X�t�B���^�̏d�݂̐��B
	/// <summary>
	/// �u���[�p�̃p�����[�^�o�b�t�@�B
	/// </summary>
	/// <remarks>
	/// �����ύX������AAssets/shader/GaussianBlur.fx��CBBlur�̒��g���ύX����悤�ɁB
	/// </remarks>
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};
	ID3D11ShaderResourceView* m_SrcTextureSRV = nullptr;//�\�[�X�e�N�X�`����SRV
	float m_BlurIntensity = 25.0f;						//�u���[�̋����B�u���[�̃E�F�C�g�̌v�Z�Ŏg�p����܂��B
	bool m_IsCreate = false;
	unsigned int m_srcTextureWidth = 0;
	unsigned int m_srcTextureHight = 0;
	ksEngine::Shader m_vsXBlur;
	ksEngine::Shader m_vsYBlur;
	ksEngine::Shader m_psBlur;
	SBlurParam m_blurParam;
	ID3D11SamplerState* m_samplerState=nullptr;
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�B
	/// </summary>
	enum EnRenderTarget {
		enRenderTarget_XBlur,		//X�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_YBlur,		//Y�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_Num,			//�����_�����O�^�[�Q�b�g�̖����B
	};
	RenderTarget m_renderTarget[enRenderTarget_Num];		//�����_�����O�^�[�Q�b�g�B
	ConstantBufferGPU m_blurCbGPU;
};