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
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
			//�G�̏����ʒu��ݒ�
			CVector3 SpownPos = funclevel.position;
			enemy->SetSpownPos(SpownPos);
			//�G�̏�����]�ʂ�ݒ�
			enemy->SetRotation(funclevel.rotation);
			//���X�g�ɐς�
			m_EnemyList.push_back(enemy);
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
