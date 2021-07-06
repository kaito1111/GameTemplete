#include "LightManager.h"
#include "stdafx.h"
#include "LightBase.h"
#include "PointLight.h"
#include <algorithm>

void LightManager::Start()
{
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	
	bufferDesc.ByteWidth = sizeof(PointLight) * MAX_POINT_LIGHT;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_PointLightBuffer);

	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.ByteWidth = (((sizeof(int)) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_NumPointLightBuffer);
}

void LightManager::Update()
{
	int ligNo = 0;
	for (auto lig : PointLights) {
		if (lig->IsActive() == false) {
			//アクティブじゃない奴はスキップ。
			continue;
		}
		m_rawPointLight[ligNo] = lig->GetRawData();
		ligNo++;
	}

	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	d3dDeviceContext->UpdateSubresource(m_PointLightBuffer, 0, nullptr, &m_rawPointLight, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(4, 1, &m_PointLightBuffer);

	d3dDeviceContext->UpdateSubresource(m_NumPointLightBuffer, 0, nullptr, &ligNo, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(3, 1, &m_NumPointLightBuffer);
}

void LightManager::AddLight(LightBace * Light)
{
	if (PointLights.size() >= MAX_POINT_LIGHT) {
		return;
	}
	const std::type_info& type_info = typeid(*Light);
	if (type_info == typeid(PointLight)) {
		auto find = std::find(PointLights.begin(), PointLights.end(), Light);		
		if (find == PointLights.end()) {
			//新規登録。
			PointLights.push_back(reinterpret_cast<PointLight*>(Light));
		}
	}
}

void LightManager::RemoveLight(LightBace * Light)
{
	const std::type_info& type_info = typeid(*Light);
	if (type_info == typeid(PointLight)) {
			PointLights.erase(
			std::remove(PointLights.begin(), PointLights.end(), Light),
				PointLights.end()
		);
	}
}
