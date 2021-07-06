#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "graphics/Shader.h"
#include "graphics/SkinModelEffect.h"

SkinModel::SkinModel()
{
}

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//�萔�o�b�t�@������B
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//�T���v���X�e�[�g������B
		m_samplerState->Release();
	}
	if (m_light != nullptr) {
		m_light->Release();
	}
	if (m_silhouettoDepthStepsilState != nullptr) {
		m_silhouettoDepthStepsilState->Release();
	}
}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	InitSkeleton(filePath);

	//�萔�o�b�t�@�̍쐬�B
	InitConstantBuffer();

	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	InitShader();

	InitDirectionLight();

	InitPointLight();

	InitSilhouettoDepthStepsilState();
	
	//SkinModelDataManager���g�p����CMO�t�@�C���̃��[�h�B
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	//cmo�t�@�C���̊g���q��tks�ɕύX����B
	std::wstring skeletonFilePath = filePath;
	//�����񂩂�.cmo�t�@�C���n�܂�ꏊ�������B
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmo�t�@�C����.tks�ɒu��������B
	skeletonFilePath.replace(pos, 4, L".tks");
	//tks�t�@�C�������[�h����B
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//�X�P���g�����ǂݍ��݂Ɏ��s�����B
		//�A�j���[�V�������Ȃ����f���́A�X�P���g�����s�v�Ȃ̂�
		//�ǂݍ��݂Ɏ��s���邱�Ƃ͂���̂ŁA���O�o�͂����ɂ��Ă����B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tks�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitShader()
{
	m_vsShader.Load("Assets/shader/model.fx","VSMain", ksEngine::Shader::EnType::VS);
	m_psShader.Load("Assets/shader/model.fx", "PSMain", ksEngine::Shader::EnType::PS);

	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", ksEngine::Shader::EnType::PS);
}

void SkinModel::InitSilhouettoDepthStepsilState()
{
	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}

void SkinModel::InitPointLight()
{
	for (auto& pt : m_pointLight) {
		pt.position.x = 00.0;
		pt.position.y = 20.0f;
		pt.position.z = 00.0f;
		pt.range = 300.0f;
		pt.color.x = 1.0f;
		pt.color.y = 1.0f;
		pt.color.z = 1.0f;
	}
}

void SkinModel::InitDirectionLight()
{
	m_dirLight.dir.Direction[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.dir.Color[0] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//����𑾗z���Ƃ���
	m_dirLight.dir.Direction[1] = { -1.0f, -1.0f, -1.0f, 0.0f };
	m_dirLight.dir.Direction[1].Normalize();
	m_dirLight.dir.Color[1] = { 1.2f, 1.2f, 1.2f, 1.0f };

	m_dirLight.dir.Direction[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	m_dirLight.dir.Color[2] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_dirLight.dir.Direction[3] = { 1.0f, 1.0f, -1.0f, 0.0f };
	m_dirLight.dir.Direction[3].Normalize();
	m_dirLight.dir.Color[3] = { 0.2f, 0.2f, 0.2f, 1.0f };
	m_dirLight.eyePos = g_camera3D.GetPosition();
	m_dirLight.pow = 5.0f;
}

void SkinModel::InitConstantBuffer()
{
	//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
	int bufferSize = sizeof(SVSConstantBuffer);
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	//�쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	bufferDesc.ByteWidth = (((sizeof(Light)) / 16) + 1) * 16;				//SDirectionLight��16byte�̔{���ɂȂ��Ă���̂ŁA�؂�グ�͂��Ȃ��B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_light); 

	bufferDesc.ByteWidth = (((sizeof(PointLight)) / 16) + 1) * 16;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_PointLightBuffer);
}
void SkinModel::InitSamplerState()
{
	//�e�N�X�`���̃T���v�����O���@���w�肷�邽�߂̃T���v���X�e�[�g���쐬�B
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//���s�ړ��s����쐬����B
	transMatrix.MakeTranslation( position );
	//��]�s����쐬����B
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//�g��s����쐬����B
	scaleMatrix.MakeScaling(scale);
	//���[���h�s����쐬����B
	//�g��~��]�~���s�ړ��̏��Ԃŏ�Z����悤�ɁI
	//���Ԃ��ԈႦ���猋�ʂ��ς���B
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//�X�P���g���̍X�V�B
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	m_dirLight.eyePos = g_camera3D.GetPosition();
	d3dDeviceContext->UpdateSubresource(m_light, 0, nullptr, &m_dirLight, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_light);

	d3dDeviceContext->UpdateSubresource(m_PointLightBuffer, 0, nullptr, &m_pointLight, 0, 0);
	d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_PointLightBuffer);


	//�萔�o�b�t�@�̓��e���X�V�B
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	vsCb.mLightProj = g_graphicsEngine->GetShadowMap()->GetLightProjMatrix();
	vsCb.mLightView = g_graphicsEngine->GetShadowMap()->GetLightViewMatrox();
	vsCb.emissionColor = m_emissionColor;
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//�萔�o�b�t�@��GPU�ɓ]���B
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	//�T���v���X�e�[�g��ݒ�B
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//�{�[���s���GPU�ɓ]���B
	m_skeleton.SendBoneMatrixArrayToGPU();

	switch (m_renderMode)
	{
		//�ʏ�`��
	case enNormalDraw:
		//�ʏ�`��
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
			//�ʏ�`��
			modelMaterial->SetRenderMode(enNormalDraw);
		});

		//�`��B                                                                           
		m_modelDx->Draw(
			d3dDeviceContext,
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix
		);
		break;
		//�V���G�b�g�`�恨�ʏ�`��
	case enSilhouetteDraw:

		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
			//�V���G�b�g�`��
			modelMaterial->SetRenderMode(enSilhouetteDraw);
		});

		//�`��B                                                                           
		m_modelDx->Draw(
			d3dDeviceContext,
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix
		);
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
			//�ʏ�`��ɐ؂�ւ�
			modelMaterial->SetRenderMode(enNormalDraw);
		});

		//�`��B                                                                           
		m_modelDx->Draw(
			d3dDeviceContext,
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix
		);
		break;
	case enShadowDraw:
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
			//�V���h�E�`��
			modelMaterial->SetRenderMode(enShadowDraw);
		});
		//�`��B                                                                           
		m_modelDx->Draw(
			d3dDeviceContext,
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix
		);
		////�ʏ�`��
		//m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		//	auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
		//	//�ʏ�`��
		//	modelMaterial->SetRenderMode(enNormalDraw);
		//});

		////�`��B                                                                           
		//m_modelDx->Draw(
		//	d3dDeviceContext,
		//	state,
		//	m_worldMatrix,
		//	viewMatrix,
		//	projMatrix
		//);
	default:
		break;
	}
	//m_renderTarget.OffScreenRendering();

	//m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
	//	auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
	//	//�����ւ��O�̃e�N�X�`�����X�^�b�N�ɑޔ��B
	//	modelMaterial->PushAlbedoTexture();
	//	//�e�N�X�`���������ւ���B
	//	//modelMaterial->SetAlbedoTexture(m_renderTarget.GetRTSRV());
	//	//�V���G�b�g�`��ɐ؂�ւ�
	//	modelMaterial->SetRenderMode(1);
	//});
	////QueryMaterials([&](ModelEffect* material) {
	////	//�����ւ��O�̃e�N�X�`�����X�^�b�N�ɑޔ��B
	////	material->PushAlbedoTexture();
	////	//�e�N�X�`���������ւ���B
	////	material->SetAlbedoTexture(m_renderTarget.GetRTSRV());
	////});

	////�`��B                                                                           
	//m_modelDx->Draw(
	//	d3dDeviceContext,
	//	state,
	//	m_worldMatrix,
	//	viewMatrix,
	//	projMatrix
	//);

	////m_renderTarget.OnScreenRendering();

	//////�w�i�̃e�N�X�`�������ɖ߂��B
	//m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
	//	auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
	//	//�����ւ��O�̃e�N�X�`�����X�^�b�N���畜�A�B
	//	modelMaterial->PopAlbedoTexture();
	//	//�ʏ�`��ɖ߂�
	//	modelMaterial->SetRenderMode(0);
	//});

	////�`��B                                                                           
	//m_modelDx->Draw(
	//	d3dDeviceContext,
	//	state,
	//	m_worldMatrix,
	//	viewMatrix,
	//	projMatrix
	//);
}