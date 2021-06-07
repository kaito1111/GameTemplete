#include "stdafx.h"
#include "Sky.h"
#include "graphics/SkinModelEffect.h"

ksEngine::Sky::Sky()
{
}

ksEngine::Sky::~Sky()
{
}

void ksEngine::Sky::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}

bool ksEngine::Sky::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init(m_skyModelFilePath.c_str());
	m_skyCube.CreateFromDDSTextureFromFile(m_skyCubeMapFilePath.c_str());
	//参照カウンタを上げておかないと、解放済みのテクスチャにアクセスしちゃう。
	m_skyCube.AddRef();
	m_psSkyShader.Load("shader/model.fx", "PSMain_SkyCube", Shader::EnType::PS);
	//マテリアルにクエリをかけて、シェーダーとテクスチャを差し替えるぜ。
	m_skinModelRender->FindMaterial([&](ModelEffect* mat) {
		mat->SetRender3DModelPSShader(m_psSkyShader);
		mat->SetDiffuseTexture(m_skyCube.GetBody());
	});
	//初回は必ず更新を行う。
	m_isDirty = true;
	return true;
}

void ksEngine::Sky::Update()
{
	if (m_isDirty == true) {
		//更新の必要あり。
		m_skinModelRender->SetScale(m_scale);
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetEmissionColor(m_emissionColor);
		m_isDirty = false;
	}
}
