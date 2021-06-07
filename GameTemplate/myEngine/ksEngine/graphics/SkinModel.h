#pragma once

#include "Skeleton.h"
#include "graphics/RenderTarget.h"
class Shader;
class ModelEffect;

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
enum EnRenderMode {
	enNormalDraw,
	enSilhouetteDraw,
	enShadowDraw
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
	static const int m_NumDirection = 4;
	struct DirectionLight {
		CVector4 Direction[m_NumDirection];
		CVector4 Color[m_NumDirection];
	};
	struct Light {
		DirectionLight dir;
		CVector3 eyePos;
		float pow;
	};
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	SkinModel();
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};

	const void SetRenderMode(int rm) {
		m_renderMode = rm;
	}

	void QueryMaterials(std::function<void(ModelEffect*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<ModelEffect*>(material));
		});
	}
	typedef std::function<void(std::unique_ptr<DirectX::ModelMeshPart>&)>		OnFindMesh;
	void FindMesh(OnFindMesh findMesh) const
	{
		if (m_modelDx != nullptr) {
			for (auto& modelMeshs : m_modelDx->meshes) {
				for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
					findMesh(mesh);
				}
			}
		}
	}
	void FindMaterial(std::function<void(ModelEffect*)> findMaterial) const
	{
		FindMesh([&](auto& mesh) {
			ModelEffect* effect = reinterpret_cast<ModelEffect*>(mesh->effect.get());
			findMaterial(effect);
		});
	}
	// 自己発光色を設定。
	void SetEmissionColor(CVector3 color)
	{
		m_emissionColor = color;
	}
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	
	void InitShader();

	void InitDirectionLight();

	void InitSilhouettoDepthStepsilState();

private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ライトビュー行列。
		CVector3 emissionColor;	//!<自己発光色。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	ksEngine::Shader m_vsShader;
	ksEngine::Shader m_psShader;
	ID3D11Buffer* m_light = nullptr;
	Light m_dirLight;

	ksEngine::Shader m_psSilhouette;
	int m_renderMode = 0;
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//シルエット描画用のデプスステンシルステート。

	RenderTarget m_renderTarget;
	CVector3 m_emissionColor = CVector3::Zero();				//自己発光カラー。
};

