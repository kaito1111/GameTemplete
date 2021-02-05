#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	void Create(UINT w,UINT h, DXGI_FORMAT format);
	void SaveRenderTarget();
	void BackUpRenderTarget();

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̃N���A�B
	/// </summary>
	/// <param name="clearColor">�N���A�J���[</param>
	void ClearRenderTarget(float* clearColor);

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�r���[���擾�B
	/// </summary>
	/// <returns>�����_�����O�^�[�Q�b�g�r���[</returns>
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}

	/// <summary>
	/// �f�v�X�X�e���V���r���[���擾�B
	/// </summary>
	/// <returns>�f�v�X�X�e���V���r���[</returns>
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}

	/// <summary>
	/// �����_�����O�^�[�Q�b�g��SRV���擾�B
	/// </summary>
	/// <returns>�����_�����O�^�[�Q�b�g��SRV</returns>
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	/// <summary>
	/// �r���[�|�[�g�̎擾�B
	/// </summary>
	/// <returns>�r���[�|�[�g</returns>
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
	float GetWidth() {
		return m_width;
	}
	float GetHeight() {
		return m_height;
	}
private:
	ID3D11RenderTargetView*		m_oldRenderTargetView;
	ID3D11DepthStencilView*		m_oldDepthStencilView;
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//!<�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<�����_�[�^�[�Q�b�g�r���[�B
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<�����_�����O�^�[�Q�b�g��SRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<�f�v�X�X�e���V���r���[�B
	D3D11_VIEWPORT				m_viewport;							//!<�r���[�|�[�g�B
	float m_width = 0;
	float m_height = 0;
};

