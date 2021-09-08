#include "stdafx.h"
#include "SpringCamera.h"

namespace {
	const float dampingK = 35.0f;//����

	float CalcSpringScalar(
		float positionNow,
		float positionTarget,
		float& moveSpeed)
	{
		float deltaTime = gameTime().GetFrameDeltaTime();

		float dampingRate = 0.2f;
		float distance;
		distance = positionTarget - positionNow;
		if (fabsf(distance) < FLT_EPSILON) {
			moveSpeed = 0.0f;
			return positionTarget;
		}
		//�������v�Z���Ă�
		float originalDir = distance;
		originalDir /= fabsf(distance);

		float springAccel;
		springAccel = distance;

		//�����Ă�񂾂낤
		float t = dampingK / (2.0f * dampingRate);
		float springK = t * t;
		springAccel *= springK;

		//�����x������B
		float vt = moveSpeed;
		vt *= dampingK;
		springAccel -= vt;
		springAccel *= deltaTime;
		moveSpeed += springAccel;
		float newPos = positionNow;
		float addPos = moveSpeed;
		addPos *= deltaTime;
		newPos += addPos;
		vt = positionTarget - newPos;
		if (fabsf(vt) < FLT_EPSILON) {
			//�ڕW���W�܂ňړ����������B
			newPos = positionTarget;
			moveSpeed = 0.0f;
		}
		else {
			vt /= fabsf(vt);
			if (vt * originalDir < 0.0f) {
				//�ڕW���W�𒴂����B
				newPos = positionTarget;
				moveSpeed = 0.0f;
			}
		}
		return newPos;
	}

	/*!
	* @brief	�o�l�������g�p���āA���݂̈ʒu�A�ڕW�ƂȂ�ʒu�A���x�A�����x����V�����ʒu���v�Z����B
	*/
	CVector3 CalcSpringVector(
		const CVector3& positionNow,
		const CVector3& positionTarget,
		CVector3& moveSpeed,
		float maxMoveSpeed,
		float dampingRate
	)
	{
		float deltaTime = min(1.0f / 30.0f, gameTime().GetFrameDeltaTime());
		//���݂̈ʒu�ƖڕW�̈ʒu�Ƃ̍��������߂�B
		CVector3 distance;
		distance.Subtract(positionTarget, positionNow);
		CVector3 originalDir = distance;
		originalDir.Normalize();
		CVector3 springAccel;
		springAccel = distance;

		float t = dampingK / (2.0f * dampingRate);
		float springK = t * t;
		springAccel.Scale(springK);
		//�����x������B
		CVector3 vt = moveSpeed;
		vt.Scale(dampingK);
		springAccel.Subtract(vt);

		springAccel.Scale(deltaTime);
		moveSpeed.Add(springAccel);
		if (moveSpeed.LengthSq() > maxMoveSpeed*maxMoveSpeed) {
			//�ō����x��葬���Ȃ��Ă��܂����B
			moveSpeed.Normalize();
			moveSpeed.Scale(maxMoveSpeed);
		}
		CVector3 newPos = positionNow;
		if (moveSpeed.Length() < 1.0f) {
			newPos = positionTarget;
			moveSpeed = CVector3::Zero();
		}
		else {
			CVector3 addPos = moveSpeed;
			addPos.Scale(deltaTime);
			newPos.Add(addPos);
			vt.Subtract(positionTarget, newPos);
			vt.Normalize();
			if (vt.Dot(originalDir) < 0.0f) {
				//�ڕW���W�𒴂����B
				newPos = positionTarget;
				moveSpeed = CVector3::Zero();
			}
		}
		return newPos;
	}
}
void SpringCamera::Init(
	Camera & camera, 
	float moveMaxSpeed)
{
	m_camera = &camera;
	SetTarget(m_camera->GetTarget());
	SetPosition(m_camera->GetPosition());
	m_TargetMoveSpeed = CVector3::Zero();
	m_PositionMoveSpeed = CVector3::Zero();
	m_MaxMoveSpeed = moveMaxSpeed;
}

void SpringCamera::Update()
{
	UpdateSpringCamera();
	UpdateCamera();
}

void SpringCamera::UpdateSpringCamera()
{
	if (m_camera == nullptr) {
		return;
	}
	if (m_isRefresh) {
		//���t���b�V�����K�v�Ȃ�A�J�����̍��W����C�ɖڕW���W�ɂ���B
		//�V�[���̐؂�ւ�莞�ȂǁA��C�ɃJ������ύX����K�v������Ƃ��Ɏg�p���Ă��������B
		m_camera->SetTarget(m_Target);
		m_camera->SetPosition(m_Position);
		m_isRefresh = false;
	}
	else {
		m_dampingRate = CalcSpringScalar(m_dampingRate, m_targetDampingRate, m_dampingRateVel);
		CVector3 target = CalcSpringVector(m_camera->GetTarget(), m_Target, m_TargetMoveSpeed, m_MaxMoveSpeed, m_dampingRate);
		CVector3 position = CalcSpringVector(m_camera->GetPosition(), m_Position, m_PositionMoveSpeed, m_MaxMoveSpeed, m_dampingRate);
		m_camera->SetTarget(target);
		m_camera->SetPosition(position);
	}
}
