#include "LightManager.h"
#include "stdafx.h"
#include "LightBase.h"
#include "PointLight.h"
#include <algorithm>
#include"Light/DirectionLight.h"

void LightManager::Start()
{
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	
	bufferDesc.ByteWidth = sizeof(PointLight) * MAX_POINT_LIGHT;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_PointLightBuffer);

	bufferDesc.ByteWidth = (((sizeof(int)) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_NumPointLightBuffer);

	bufferDesc.ByteWidth = sizeof(DirectionLight)*MAX_DIRECRION_LIGHT;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_DirectionLightsBuffer);

	bufferDesc.ByteWidth = (((sizeof(int)) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_NumDirectionLightBuffer);
}

void LightManager::Update()
{
	int ligNo = 0;
	for (auto lig : PointLights) {
		if (lig->IsActive() == false) {
			//�A�N�e�B�u����Ȃ��z�̓X�L�b�v�B
			continue;
		}
		m_rawPointLight[ligNo] = lig->GetRawData();
		ligNo++;
	}

	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	d3dDeviceContext->UpdateSubresource(m_PointLightBuffer, 0, nullptr, &m_rawPointLight, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_PointLightBuffer);

	d3dDeviceContext->UpdateSubresource(m_NumPointLightBuffer, 0, nullptr, &ligNo, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_NumPointLightBuffer);

	ligNo = 0;
	for (auto lig : DirectionLights) {
		if (lig->IsActive() == false) {
			//�A�N�e�B�u����Ȃ��z�̓X�L�b�v�B
			continue;
		}
		m_rawDirectionLight[ligNo] = lig->GetRawData();
		ligNo++;
	}
	d3dDeviceContext->UpdateSubresource(m_DirectionLightsBuffer, 0, nullptr, &m_rawDirectionLight, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(4, 1, &m_DirectionLightsBuffer);

	d3dDeviceContext->UpdateSubresource(m_NumDirectionLightBuffer, 0, nullptr, &ligNo, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(3, 1, &m_NumDirectionLightBuffer);
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
			//�V�K�o�^�B
			PointLights.push_back(reinterpret_cast<PointLight*>(Light));
		}
	}
	else if (type_info == typeid(DirectionLight)) {
		auto find = std::find(DirectionLights.begin(), DirectionLights.end(), Light);
		if (find == DirectionLights.end()) {
			//�V�K�o�^�B
			DirectionLights.push_back(reinterpret_cast<DirectionLight*>(Light));
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
	else if (type_info == typeid(DirectionLight)) {
		DirectionLights.erase(
			std::remove(DirectionLights.begin(), DirectionLights.end(), Light),
			DirectionLights.end()
		);
	}
}
