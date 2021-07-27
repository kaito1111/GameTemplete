#pragma once

class Effect : public ksEngine::IGameObject
{
public:
	Effect(){}
	~Effect(){
		Release();
	}
	/// <summary>
	/// 解放
	/// </summary>
	void Release();
	/// <summary>
	/// エフェクトを再生
	/// </summary>
	/// <param name="filePath">再生するエフェクトのファイルパス</param>
	void Play(const wchar_t* filePath);
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3& pos) {
		m_Position = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot) {
		m_Rotarion = rot;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const CVector3& scale) {
		m_Scale = scale;
	}
	/// <summary>
	/// エフェクトが再生中か判定
	/// </summary>
	/// <returns></returns>
	bool IsPlay()const;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

private:
	Effekseer::Effect*  m_effect = nullptr;
	Effekseer::Handle   m_handle = -1;
	CVector3			m_Position = CVector3::Zero();			//座標
	CQuaternion			m_Rotarion = CQuaternion::Identity();	//回転
	CVector3			m_Scale = CVector3::One();				//拡大率
};

