#pragma once
class Fade;
/// <summary>
/// �Q�[�����P�����蒼���N���X
/// ���񂾂Ƃ��ɌĂ΂��
/// </summary>
class ReSetGame final : public IGameObject
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
	Fade* m_Fade = nullptr;		//�t�F�[�h�̃|�C���^
};

