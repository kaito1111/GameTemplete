#pragma once
#include "graphics/2D/SampleSprite.h"
namespace ksEngine {
	class SpriteRender :public IGameObject
	{
	public:
		SpriteRender() {};
		~SpriteRender() {};

		void Init(const wchar_t* fileName, float w = FRAME_BUFFER_W, float h = FRAME_BUFFER_H, bool is3DDraw = false);
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

		//サイズの設定
		void SetSize(const CVector2 size) {
			m_Size = size;
		}

		//サイズの設定
		//xとyは同じ大きさになるよ
		void SetSize(float size) {
			m_Size = { size,size };
		}

		//サイズの設定
		//横と縦の場所に気を付けて
		void SetSize(float wide, float hight) {
			m_Size = { wide,hight };
		}

		void SetAlpha(float alpha) {
			m_alpha = alpha;
		}

		void SetPivot(float x,float y) {
			m_pivot = { x,y };
		}
		//基点左上が{1,0},右下が{0,1}
		void SetPivot(CVector2 pivot) {
			m_pivot = pivot;
		}
		void SetIsFaceCamera(bool isFaceCamera) {
			m_sprite.SetIsFaceCamera(isFaceCamera);
		}
		static CVector2 Center()
		{
			return CVector2(0.5f,0.5f);
		}
		static float YCenter() {
			return 0.5f;
		}
		static float XCenter() {
			return 0.5f;
		}
		static float Left() {
			return 1.0f;
		}
		static float Right() {
			return 0.0f;
		}
		static float Up(){
			return 0.0f;
		}
		static float Down() {
			return 1.0f;
		}
	private:
		Sprite m_sprite;
		CVector3 m_Pos = CVector3::Zero();
		CQuaternion m_Rot = CQuaternion::Identity();
		CVector3 m_Scale = CVector3::One();
		bool m_Is3DDraw = false;
		CVector2 m_Size = { 1280.0f,720.0f };
		float m_alpha = 1.0f;
		CVector2 m_pivot = { 0.5f,0.5f };
	};
}