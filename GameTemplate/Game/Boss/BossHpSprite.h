#pragma once

/// <summary>
/// �{�X��HP�̃X�v���C�g�N���X
/// </summary>
class BossHpSprite final :public IGameObject
{
public:
	/// <summary>
	/// �C���X�^���X�����������ƁA��x�����Ă΂��J�n����
	/// </summary>
	/// <remarks>
	/// Unity��Start()�֐��̎d�l�ɏ����B
	/// </remarks>
	/// <returns>
	/// true���A���Ă�����A�����������B
	/// �����t���[���ɂ킽���ď��������������ꍇ�́A
	/// �����������܂�false��Ԃ��B
	/// </returns>
	bool Start()override;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;
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
	void OnDestroy()override;
	/// <summary>
	/// HP���Z�b�g�B
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHp(float hp) 
	{
		m_Hp = hp;
	}
private:
	SpriteRender* m_TopHpSprite = nullptr;			// ��ʏ㕔��HP�o�[�B
	SpriteRender* m_UnderHpSprite = nullptr;		
	CVector3 m_Pos = { -653.0f,-490.0f ,0.0f};
	float m_Hp = 0.0f;
	float m_MaxHp = 0.0f;
	float m_AppearanceHpScale = 0.0f;
	CVector3 m_HpScale = CVector3::One();
	SpriteRender* m_HpTopTranslucentSprite = nullptr;
	bool m_HpInit = false;
	float m_TranslucentScale = 0.0f;		//�������X�v���C�g�̃X�P�[��
	float m_HoldTime = 1.0f;				//Hp�X�P�[�����L�[�v����X�P�[��
	CVector3 m_TranslunceSpriteScale = CVector3::One();
};

