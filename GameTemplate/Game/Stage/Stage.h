#pragma once
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
class PhysicsStageObject;
class Player;
class SceneChangeLocation;
class ReturnLocatoin;
class Candle;
class Torch;
/// <summary>
/// �X�e�[�W�̃N���X
/// </summary>
class Stage final :public IGameObject
{
public:
	/// <summary>
	/// �C���X�^���X���j������鎞�ɌĂ΂��֐��B
	/// </summary>
	/// <remarks>
	/// �{�G���W���Ŏ������Ă���A�Q�[���I�u�W�F�N�g���폜����
	/// DeleteGO�֐��́A�����ɃC���X�^���X���폜����킯�ł͂Ȃ��A
	/// 1�t���[���x��ăC���X�^���X���폜�����B
	/// ���̂��߁A�f�X�g���N�^�̌Ăяo�����ADeleteGO�̌Ăяo������1�t���[���x��邱�ƂƂȂ�B
	/// DeleteGO���Ă΂ꂽ�^�C�~���O�ŁA�s�������I��������OnDestroy()�ɋL�q����B
	/// </remarks>
	void OnDestroy()override final;

	/// <summary>
	/// �X�e�[�W��ǂݍ��ފ֐�
	/// ���̊֐��ł����X�e�[�W�����Ȃ�
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void Load(const wchar_t* filePath);
	/// <summary>
	/// �X�e�[�W�œǂݍ��񂾃v���C���[�̏����ʒu��Ԃ��@
	/// </summary>
	/// <returns>�v���C���[�̏����ʒu</returns>
	const CVector3 GetPlayerPos()const {
		return m_SpownPlayerPosition;
	}
	/// <summary>
	/// �X�e�[�W�œǂݍ��񂾃v���C���[�̉�]�ʂ�Ԃ�
	/// </summary>
	/// <returns>�v���C���[�̉�]��</returns>
	const CQuaternion GetPlayerRotation() const{
		return m_PlayerSpawnRot;
	}
	/// <summary>
	/// �^�C�g���V�[�����Ƀv���C���[�̂���ʒu
	/// </summary>
	/// <returns>�v���C���[�̈ʒu</returns>
	const CVector3 GetTitlePos() const{
		return m_TitlePos;
	}
	/// <summary>
	/// �^�C�g���V�[���̃J�����̈ʒu
	/// </summary>
	/// <returns></returns>
	const CVector3 GetTitleCameraPos() const{
		return m_TitleCameraPos;
	}
	/// <summary>
	/// �^�C�g���V�[���̃J�����̒����_
	/// </summary>
	const CVector3 GetTitleCameraTarget()const {
		return m_TitleCameraTarget;
	}
private:
	std::vector< PhysicsStageObject*> m_PSOList;			//�ÓI�����I�u�W�F�N�g�B�̃|�C���^���X�g				
	Level m_level;											//�X�e�[�W��ǂݍ��ރ��x��
	wchar_t m_LevelFilePath[256] = {};						//���x���œǂݍ��ނƂ��Ɏg���t�@�C���p�X
	CVector3 m_SpownPlayerPosition = CVector3::Zero();		//�v���C���[�̏����ʒu
	CQuaternion m_PlayerSpawnRot = CQuaternion::Identity();	//�v���C���[�̏�����]��
	Sky* m_sky = nullptr;									//��̃L���[�u�}�b�v
	CVector3 m_TitlePos = CVector3::Zero();					//�v���C���[���^�C�g���ɂ���Ƃ��̈ʒu
	CVector3 m_TitleCameraPos = CVector3::Zero();			//�^�C�g���V�[���̃J�����̈ʒu
	CVector3 m_TitleCameraTarget = CVector3::Zero();		//�^�C�g���V�[���̃J�����̒����_
	std::vector<SceneChangeLocation*> m_SCLoc;				//���̃V�[���̈ړ�����N���X�̃��X�g
	std::vector<ReturnLocatoin*> m_RCLoc;					//�O�̃V�[���ɖ߂�N���X�̃��X�g
	std::vector<Candle*> m_Can;								//�L�����h���̃��X�g
	std::vector<Torch*> m_Torch;							//�����̃��X�g
};

