#pragma once
#include "graphics/2D/Sprite.h"

namespace ksEngine {
	class SpriteRender :public IGameObject
	{
	public:
		SpriteRender() {};
		~SpriteRender() {};

		void Init(const wchar_t* fileName, bool is3DDraw = false);
		void Update()override;
		void Draw()override;
		void PostRender()override;

		void SetPosition(const CVector3& pos) {
			m_Pos = pos;
		}
		void SetRotation(const CQuaternion& rot) {
			m_Rot = rot;
		}
		void SetScale(const CVector3& scale) {
			m_Scale = scale;
		}
	private:
		ksEngine::Sprite m_sprite;
		CVector3 m_Pos = CVector3::Zero();
		CQuaternion m_Rot = CQuaternion::Identity();
		CVector3 m_Scale = CVector3::One();
		bool m_Is3DDraw = false;
	};
}