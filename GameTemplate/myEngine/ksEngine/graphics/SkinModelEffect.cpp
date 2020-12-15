#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	////通常描画。
	//deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
	//deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTexture);

	switch (m_RenderMode) {
	case enNormalDraw:
		//通常描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTexture);
		break;
	case enSilhouetteDraw:
		//シルエット描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//デプスステンシルステートを切り替える。
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	case enShadowDraw:
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
	}
	//deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);

}