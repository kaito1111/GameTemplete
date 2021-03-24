#include "pch.h"
#include "EnemySpawner.h"
#include "Archer/Archer.h"
#include "Archer/Arrow.h"

bool EnemySpawner::Start()
{
	//Game�N���X���玝���Ă����t�@�C���p�X�����[�h
	m_Level.Init(m_filePath, [&](LevelObjectData funclevel)->bool {
		//�G�l�~�[�̖��O������������
		if (wcscmp(funclevel.name, L"keleton") == 0) {
			//�G�̃C���X�^���X���쐬
			Arrow* arrow = NewGO<Arrow>(0, "archer");
			//�G�̏����ʒu��ݒ�
			CVector3 SpownPos = funclevel.position;
			arrow->Init(SpownPos, funclevel.rotation);
			//archer->SetSpownPosition(SpownPos);
			////�G�̏�����]�ʂ�ݒ�
			//archer->SetRotation(funclevel.rotation);
			//���X�g�ɐς�
			//m_EnemyList.push_back(enemy);
			CVector3 Pos = CVector3::Zero();
			Pos.x += 100.0f;
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
			//�G�̏����ʒu��ݒ�
			/*CVector3 */SpownPos = funclevel.position + Pos;
			enemy->SetSpownPos(SpownPos);
			//�G�̏�����]�ʂ�ݒ�
			enemy->SetRotation(funclevel.rotation);
			return true;
		}
	});
	return true;
}
void EnemySpawner::OnDestroy()
{
	//�G�̃C���X�^���X���폜
	DeleteGOs("enemy");
}
