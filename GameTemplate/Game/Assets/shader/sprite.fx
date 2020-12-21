/*!
 * @brief	スプライト用のシェーダー。
 */

cbuffer cb : register(b0) {
	//float4x4 mWorld;	//ワールド行列。
	//float4x4 mView;	//ビュー行列。
	//float4x4 mProj;	//プロジェクション行列。

	float4x4 mWvp;		//ワールドビュープロジェクション行列。
	float4 mulColor;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
sampler Sampler : register(s0);

PSInput VSMain(PSInput Input)
{
	PSInput In;
	In.pos = mul(mWvp, Input.pos);
	In.uv = Input.uv;
	//PSInput psIn;
	//psIn.pos = mul(mvp, In.pos);
	//psIn.pos = In.pos;
	//psIn.uv = In.uv;
	////ワールド行列をモデルの頂点座標に乗算する。
	//float4 pos = mul(mWorld, Pos);
	////ビュー行列を乗算。
	//pos = mul(mView, pos);
	////プロジェクション行列を乗算して、
	////スクリーンの正規化座標系(-1.0～1.0の座標系)に変換する。
	//pos = mul(mProj, pos);
	//座標変換が終わった。
	return In;
}
float4 PSMain(PSInput In) : SV_Target0
{
	//float4 color /*= float4(1.0f, 0.0f, 1.0f, 1.0f)*/;
	//color = mulColor;
	return colorTexture.Sample(Sampler ,In.uv) * mulColor;
}