#pragma once
#include "graphics/SkinModel.h"
namespace ksEngine {
	class SkinModelRender : public IGameObject
	{
	public:
		SkinModelRender();
		~SkinModelRender();

		//Assets/modelData/はいらない
		void Init(const wchar_t* filePath, EnFbxUpAxis Up = EnFbxUpAxis::enFbxUpAxisZ);
		void SetPosition(const CVector3& pos) {
			m_Pos = pos;
		}
		void SetRotation(const CQuaternion& rot) {
			m_Rot = rot;
		}
		void SetScale(const CVector3& scale) {
			m_Scale = scale;
		}
		SkinModel& GetModel() {
			return m_SkinModel;
		}
		 void SetDraw(bool isDraw) {
			 m_IsDraw = isDraw;
		 }

		 void SetRenderMode(int rm) {
			 m_RenderMode = rm;
		 }		
		 //	モデルマテリアルの検索。
		 //param[in]	findEffect		マテリアルを見つけた時に呼ばれるコールバック関数
		 void FindMaterial(std::function<void(ModelEffect*)> findMaterial) const
		 {
			 m_SkinModel.FindMaterial(findMaterial);
		 }
		 void SetAmbientColor(float color)
		 {
			 m_SkinModel.SetAmbientColor(color);
		 }
		 void SetPostRender(bool isRender) {
			 m_IsPostrender = isRender;
		 }
		 void SetShadowRecive(bool IsShadowRecive) {
			 m_SkinModel.SetShadowRecive(IsShadowRecive);
		 }
	private:
		void Update()override;
		void Draw()override;
		void PostRender()override;
	private:
		SkinModel m_SkinModel;
		CVector3 m_Pos = CVector3::Zero();
		CQuaternion m_Rot = CQuaternion::Identity();
		CVector3 m_Scale = CVector3::One();
		bool m_IsDraw = true;
		int m_RenderMode = 0;
		bool m_IsPostrender = false;
	};
}