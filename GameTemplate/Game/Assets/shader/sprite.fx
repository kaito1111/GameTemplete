/*!
 * @brief	スプライト用のシェーダー。
 */

cbuffer VScb : register(b0) {
	//float4x4 mWorld;	//ワールド行列。
	//float4x4 mView;	//ビュー行列。
	//float4x4 mProj;	//プロジェクション行列。

	float4x4 mWvp;		//ワールドビュープロジェクション行列。
		//float4 mulColor;
};

//Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
//sampler Sampler : register(s0);

float4 VSMain(float4 Pos: POSITION) :SV_POSITION
{
	float4 pos = mul(mWvp, Pos);
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
	return pos;
}
float4 PSMain(float4 pos : SV_POSITION) : SV_Target
{
	float4 color = float4(1.0f, 0.0f, 1.0f, 1.0f);
	color;// *= mulColor;
	return color;//colorTexture.Sample(Sampler /*,In.uv*/) * mulColor;
}