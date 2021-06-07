#pragma once

#include "Skeleton.h"
#include "graphics/RenderTarget.h"
class Shader;
class ModelEffect;

/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
enum EnRenderMode {
	enNormalDraw,
	enSilhouetteDraw,
	enShadowDraw
};
/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
	static const int m_NumDirection = 4;
	struct DirectionLight {
		CVector4 Direction[m_NumDirection];
		CVector4 Color[m_NumDirection];
	};
	struct Light {
		DirectionLight dir;
		CVector3 eyePos;
		float pow;
	};
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	SkinModel();
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );
	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};

	const void SetRenderMode(int rm) {
		m_renderMode = rm;
	}

	void QueryMaterials(std::function<void(ModelEffect*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<ModelEffect*>(material));
		});
	}
	typedef std::function<void(std::unique_ptr<DirectX::ModelMeshPart>&)>		OnFindMesh;
	void FindMesh(OnFindMesh findMesh) const
	{
		if (m_modelDx != nullptr) {
			for (auto& modelMeshs : m_modelDx->meshes) {
				for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
					findMesh(mesh);
				}
			}
		}
	}
	void FindMaterial(std::function<void(ModelEffect*)> findMaterial) const
	{
		FindMesh([&](auto& mesh) {
			ModelEffect* effect = reinterpret_cast<ModelEffect*>(mesh->effect.get());
			findMaterial(effect);
		});
	}
	// ���Ȕ����F��ݒ�B
	void SetEmissionColor(CVector3 color)
	{
		m_emissionColor = color;
	}
private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	
	void InitShader();

	void InitDirectionLight();

	void InitSilhouettoDepthStepsilState();

private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CVector3 emissionColor;	//!<���Ȕ����F�B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	ksEngine::Shader m_vsShader;
	ksEngine::Shader m_psShader;
	ID3D11Buffer* m_light = nullptr;
	Light m_dirLight;

	ksEngine::Shader m_psSilhouette;
	int m_renderMode = 0;
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//�V���G�b�g�`��p�̃f�v�X�X�e���V���X�e�[�g�B

	RenderTarget m_renderTarget;
	CVector3 m_emissionColor = CVector3::Zero();				//���Ȕ����J���[�B
};

