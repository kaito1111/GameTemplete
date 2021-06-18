#pragma once
#include <string>
#include <Windows.h>
namespace ksEngine {
	class Sky final : public IGameObject
	{
	public:

		Sky();

		~Sky();

		//�폜����
		void OnDestroy()override;

		// �J�n�����B
		bool Start()override;

		// ��̑傫����ݒ�B
		void SetScale(float scale)
		{
			m_scale = { scale, scale, scale };
			m_isDirty = true;
		}

		// ��̑傫����ݒ�(�x�N�g����)		
		void SetScale(CVector3 scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}

		// ���Ȕ����J���[��ݒ�B
		void SetEmissionColor(CVector3 emissionColor)
		{
			m_emissionColor = emissionColor;
			m_isDirty = true;
		}

		// ��̈ʒu�����߂�B
		void SetPosition(CVector3 pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		// �X�V�����B
		void Update() override;

		// ��̃L���[�u�}�b�v�̃t�@�C���p�X��ݒ�B
		void SetSkyCubeMapFilePath(const wchar_t* filepath)
		{
			if (m_IsStart == true) {
				MessageBox(
					NULL,
					TEXT("SkyCubeMap�̃��[�h���������Ă��邽��"),
					TEXT("SkyCubeMap�̃��[�h���������Ă��邽�߃L���[�u�}�b�v�̍����ւ��͂ł��܂���BSetSkyCubeMapFilePath�֐��̃R�����g���Q�Ƃ��āA�K�؂ȃ^�C�~���O�Ŗ{�֐��𗘗p���Ă��������B"),
					MB_ICONWARNING);
			}
			m_skyCubeMapFilePath = filepath;
		}

		// ��̃��f���̃t�@�C���p�X��ݒ�B
		void SetSkyModelFilePath(const wchar_t* filePath)
		{
			if (m_IsStart == true) {
				MessageBox(
					NULL,
					TEXT("��̃��f���̃��[�h���������Ă��邽��"),
					TEXT("��̃��f���̃��[�h���������Ă��邽�ߋ�̃��f���̍����ւ��͂ł��܂���BSetSkyModelFilePath�֐��̃R�����g���Q�Ƃ��āA�K�؂ȃ^�C�~���O�Ŗ{�֐��𗘗p���Ă��������B"),
					MB_ICONWARNING);
			}
			m_skyModelFilePath = filePath;
		}

	private:
		SkinModelRender* m_skinModelRender = nullptr;							//���f���`��̃Q�[���I�u�W�F�N�g�B
		ID3D11ShaderResourceView* m_srv = nullptr;								//�X�J�C�L���[�u�}�b�v��SRV
		Shader m_psSkyShader;													//��p�̃V�F�[�_�[�B
		CVector3 m_scale = CVector3::One();										//��̊g�嗦�B
		CVector3 m_position = CVector3::Zero();									//���W�B
		CVector3 m_emissionColor = CVector3::Zero();							//���Ȕ����J���[�B
		bool m_isDirty = false;													//�_�[�e�B�t���O�B
		std::wstring m_skyCubeMapFilePath = L"Assets/sprite/SkySample.dds";		//��̃L���[�u�}�b�v�̃t�@�C���p�X�B
		std::wstring m_skyModelFilePath = L"sky.cmo";							//���cmo�t�@�C���̃t�@�C���p�X�B
		bool m_isCubemap = true;												//�L���[�u�}�b�v�H
	};
}