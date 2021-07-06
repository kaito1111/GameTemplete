/*!
 * @brief	モデルシェーダー。
 */


 /////////////////////////////////////////////////////////////
 // Shader Resource View
 /////////////////////////////////////////////////////////////
 //アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
Texture2D<float4> g_shadowMap : register(t2);		//todo シャドウマップ。

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

// ポイントライト構造体を定義する
struct SPointLight {
	float3 position;	
	float3 positionInView;		//!<ビュー空間での座標。
	float4 color;
	float4 range;
};

static const int MAX_POINT_LIGHT = 1024;
//ポイントライトの数を表す定数を定義する
//static const int NUM_POINT_LIGHT = 1;
cbuffer PointLightCb :register(b3) {
	int NUM_POINT_LIGHT;
}
cbuffer PointLightCb2 : register(b4) {
	SPointLight pointsLights[MAX_POINT_LIGHT];
}

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	float3 emissionColor;	//自己発光色。
};

/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
	float4 Position : SV_Position;			//頂点座標。
	float3 Normal   : NORMAL;				//法線。
	float3 Tangent  : TANGENT;				//接ベクトル。
	float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
	float4 Position : SV_Position;			//頂点座標。
	float3 Normal   : NORMAL;				//法線。
	float2 TexCoord	: TEXCOORD0;			//UV座標。
	float3 Tangent	: TANGENT;				//接ベクトル。
	uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
	float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput {
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};

struct DirectionLight {
	float4 dligDirection[4];
	float4 dligColor[4];
};

cbuffer Slight : register(b1) {
	DirectionLight direction;
	float3 eyePos;
	float specPow;
}
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}

	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain(VSInputNmTxVcTangent In)
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	psInput.worldPos = pos;
	//ローカル座標系からワールド座標系に変換する。
	float4 worldPos = mul(mWorld, In.Position);
	//続いて、ライトビュープロジェクション空間に変換。
	psInput.posInLVP = mul(mLightView, worldPos);
	psInput.posInLVP = mul(mLightProj, psInput.posInLVP);

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin(VSInputNmTxWeights In)
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));

	//ローカル座標系からワールド座標系に変換する。
	float4 worldPos = mul(mWorld, In.Position);
	//続いて、ライトビュープロジェクション空間に変換。
	psInput.posInLVP = mul(mLightView, worldPos);
	psInput.posInLVP = mul(mLightProj, psInput.posInLVP);

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain(PSInput In) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, direction.dligDirection[i])) * direction.dligColor[i];

		float3 R = reflect(direction.dligDirection[i], In.Normal);

		float3 toEye = eyePos - In.worldPos;
		toEye = normalize(toEye);

		float t = dot(toEye, R);
		if (t < 0.0f) {
			t = 0.0f;
		}

		t = pow(t, specPow);

		lig += direction.dligColor[i].xyz*t * 2;
		lig *= 0.75f;
	}
	//ポイントライトから光によるLambert拡散反射を計算する
	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		float3  ligDir = normalize(In.worldPos - pointsLights[i].position);
		float distance = length(In.worldPos - pointsLights[i].position);
		float t = max(0.0f, dot(-ligDir, In.Normal));
		float affect = 1.0f - min(1.0f, distance / pointsLights[i].range.x);
		affect = pow(affect, pointsLights[i].range.y);
		lig += pointsLights[i].color.xyz * t * affect;
	}
	//環境光
	lig += 0.1f;
	//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
	float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
	shadowMapUV *= float2(0.5f, -0.5f);
	shadowMapUV += 0.5f;
	//シャドウマップの範囲内かどうかを判定する。
	if (shadowMapUV.x < 0.0f || shadowMapUV.y < 0.0f || shadowMapUV.x > 1.0f || shadowMapUV.y > 1.0f) {
		float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		finalColor.xyz = albedoColor.xyz * lig;
		return finalColor;
	}
	///LVP空間での深度値を計算。
	float zInLVP = In.posInLVP.z / In.posInLVP.w;
	//シャドウマップに書き込まれている深度値を取得。
	float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);


	if (zInLVP > zInShadowMap + 0.0001f) {
		//影が落ちているので、光を弱くする
		lig *= 0.5f;
	}
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	//自己発光を加算。
	finalColor.xyz += emissionColor;
	return finalColor;
}

//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}

TextureCube<float4> skyCubeMap : register(t0);	//スカイキューブマップ。

//空用のシェーダー。
float4 PSMain_SkyCube(PSInput In) : SV_Target0
{
	float4 color = skyCubeMap.Sample(Sampler, In.Normal);
	color.xyz += emissionColor;
	return color;
}