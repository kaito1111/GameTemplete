#pragma once
#include <string>
#include <Windows.h>
namespace ksEngine {
	class Sky final : public IGameObject
	{
	public:

		Sky();

		~Sky();

		//削除処理
		void OnDestroy()override;

		// 開始処理。
		bool Start()override;

		// 空の大きさを設定。
		void SetScale(float scale)
		{
			m_scale = { scale, scale, scale };
			m_isDirty = true;
		}

		// 空の大きさを設定(ベクトル版)		
		void SetScale(CVector3 scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}

		// 自己発光カラーを設定。
		void SetEmissionColor(CVector3 emissionColor)
		{
			m_emissionColor = emissionColor;
			m_isDirty = true;
		}

		// 空の位置を決める。
		void SetPosition(CVector3 pos)
		{
			m_position = pos;
			m_isDirty = true;
		}

		// 更新処理。
		void Update() override;

		// 空のキューブマップのファイルパスを設定。
		void SetSkyCubeMapFilePath(const wchar_t* filepath)
		{
			if (m_IsStart == true) {
				MessageBox(
					NULL,
					TEXT("SkyCubeMapのロードが完了しているため"),
					TEXT("SkyCubeMapのロードが完了しているためキューブマップの差し替えはできません。SetSkyCubeMapFilePath関数のコメントを参照して、適切なタイミングで本関数を利用してください。"),
					MB_ICONWARNING);
			}
			m_skyCubeMapFilePath = filepath;
		}

		// 空のモデルのファイルパスを設定。
		void SetSkyModelFilePath(const wchar_t* filePath)
		{
			if (m_IsStart == true) {
				MessageBox(
					NULL,
					TEXT("空のモデルのロードが完了しているため"),
					TEXT("空のモデルのロードが完了しているため空のモデルの差し替えはできません。SetSkyModelFilePath関数のコメントを参照して、適切なタイミングで本関数を利用してください。"),
					MB_ICONWARNING);
			}
			m_skyModelFilePath = filePath;
		}

	private:
		SkinModelRender* m_skinModelRender = nullptr;							//モデル描画のゲームオブジェクト。
		ID3D11ShaderResourceView* m_srv = nullptr;								//スカイキューブマップのSRV
		Shader m_psSkyShader;													//空用のシェーダー。
		CVector3 m_scale = CVector3::One();										//空の拡大率。
		CVector3 m_position = CVector3::Zero();									//座標。
		CVector3 m_emissionColor = CVector3::Zero();							//自己発光カラー。
		bool m_isDirty = false;													//ダーティフラグ。
		std::wstring m_skyCubeMapFilePath = L"Assets/sprite/SkySample.dds";		//空のキューブマップのファイルパス。
		std::wstring m_skyModelFilePath = L"sky.cmo";							//空のcmoファイルのファイルパス。
		bool m_isCubemap = true;												//キューブマップ？
	};
}