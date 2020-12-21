#include "stdafx.h"
#include "ForwardRender.h"

ForwardRender::ForwardRender() {

}
ForwardRender::~ForwardRender() {
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
}

void ForwardRender::Init() {
	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
}

void ForwardRender::BuckupRenderTarget() {
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11RenderTargetView* rtTbl[] = {
		m_mainRenderTarget.GetRenderTargetView()
	};
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_mainRenderTarget.GetDepthStensilView());
	if (m_mainRenderTarget.GetViewport() != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, m_mainRenderTarget.GetViewport());
	}
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
}

void ForwardRender::LoadAndDraw() {
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	ID3D11RenderTargetView* rtTbl[] = {
		m_mainRenderTarget.GetRenderTargetView()
	};
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_mainRenderTarget.GetDepthStensilView());
	if (m_mainRenderTarget.GetViewport() != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, m_mainRenderTarget.GetViewport());
	}
	//�h���h��
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(),g_camera2D.GetProjectionMatrix());
	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}