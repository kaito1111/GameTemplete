#pragma once
class Fade;
class Game;
/// <summary>
/// �Q�[�����ŏ�����n�߂�N���X
/// </summary>
class GameStart :	public IGameObject
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
	bool Start()override final;
	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override final;

private: 
	Fade* m_fade = nullptr;	//�t�F�[�h�̃|�C���^
	Game* m_Game = nullptr;	//�Q�[���̃|�C���^
};

