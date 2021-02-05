struct VSInput {
	float4 Pos : SV_Position;
	float2 uv:TEXCOORDO;
};

struct PS_BlurInput {
	float4 pos : SV_POSITION;
	float4 tex0 : TEXCOORDO0;
	float4 tex1 : TEXCOORDO1;
	float4 tex2 : TEXCOORDO2;
	float4 tex3 : TEXCOORDO3;
	float4 tex4 : TEXCOORDO4;
	float4 tex5 : TEXCOORDO5;
	float4 tex6 : TEXCOORDO6;
	float4 tex7 : TEXCOORDO7;
};

Texture2D<float4> srcTexture : register(t0);
sampler Sampler : register(s0);

cbuffer CBBlur : register(b0) {
	float4 weight[2];
}

PS_BlurInput VSXBlur(VSInput In)
{
	float2 texSize;
	float level;
	srcTexture.GetDimensions(0, texSize.x, texSize.y, level);

	PS_BlurInput Out;
	Out.pos = In.Pos;
	float2 tex = In.uv;

	Out.tex0.xy = tex + float2(1.0 / texSize.x, 0.0f);
	Out.tex0.zw = tex - float2(1.0 / texSize.x, 0.0f);

	Out.tex1.xy = tex + float2(3.0 / texSize.x, 0.0f); 
	Out.tex1.zw = tex - float2(3.0 / texSize.x, 0.0f);

	Out.tex2.xy = tex + float2(5.0 / texSize.x, 0.0f);
	Out.tex2.zw = tex - float2(5.0 / texSize.x, 0.0f);

	Out.tex3.xy = tex + float2(7.0 / texSize.x, 0.0f);
	Out.tex3.zw = tex - float2(7.0 / texSize.x, 0.0f);

	Out.tex4.xy = tex + float2(9.0 / texSize.x, 0.0f);
	Out.tex4.zw = tex - float2(9.0 / texSize.x, 0.0f);

	Out.tex5.xy = tex + float2(11.0 / texSize.x, 0.0f);
	Out.tex5.zw = tex - float2(11.0 / texSize.x, 0.0f);

	Out.tex6.xy = tex + float2(13.0 / texSize.x, 0.0f);
	Out.tex6.zw = tex - float2(13.0 / texSize.x, 0.0f);

	Out.tex7.xy = tex + float2(15.0 / texSize.x, 0.0f);
	Out.tex7.zw = tex - float2(15.0 / texSize.x, 0.0f);

	return Out;
}

PS_BlurInput VSYBlur(VSInput In) {

	float2 texSize;
	float level;
	srcTexture.GetDimensions(0, texSize.x, texSize.y, level);

	PS_BlurInput Out;
	Out.pos = In.Pos;
	float2 tex = In.uv;

	Out.tex0.xy = tex + float2(0.f,1.0 / texSize.y);
	Out.tex0.zw = tex - float2(0.0f,1.0 / texSize.y);

	Out.tex1.xy = tex + float2(0.0f,3.0 / texSize.y);
	Out.tex1.zw = tex - float2(0.0f,3.0 / texSize.y);

	Out.tex2.xy = tex + float2(0.0f,5.0 / texSize.y);
	Out.tex2.zw = tex - float2(0.0f,5.0 / texSize.y);

	Out.tex3.xy = tex + float2(0.0f,7.0 / texSize.y);
	Out.tex3.zw = tex - float2(0.0f,7.0 / texSize.y);

	Out.tex4.xy = tex + float2(0.0f,9.0 / texSize.y);
	Out.tex4.zw = tex - float2(0.0f,9.0 / texSize.y);

	Out.tex5.xy = tex + float2(0.0f,11.0 / texSize.y);
	Out.tex5.zw = tex - float2(0.0f, 11.0 / texSize.y);

	Out.tex6.xy = tex + float2(0.0f, 13.0 / texSize.y);
	Out.tex6.zw = tex - float2(0.0f, 13.0 / texSize.y);

	Out.tex7.xy = tex + float2(0.0f, 15.0 / texSize.y);
	Out.tex7.zw = tex - float2(0.0f, 15.0 / texSize.y);

	return Out;
}

float4 PSBlur(PS_BlurInput In):SV_Target0
{
	float4 Color;
	Color = weight[0].x*(srcTexture.Sample(Sampler, In.tex0.xy)
		+ srcTexture.Sample(Sampler, In.tex0.zw));
	Color +=weight[0].y*(srcTexture.Sample(Sampler,In.tex1.xy)
		+ srcTexture.Sample(Sampler, In.tex1.zw));
	Color += weight[0].z*(srcTexture.Sample(Sampler, In.tex2.xy)
		+ srcTexture.Sample(Sampler, In.tex2.zw));
	Color += weight[0].w*(srcTexture.Sample(Sampler, In.tex3.xy)
		+ srcTexture.Sample(Sampler, In.tex3.zw));	
	Color += weight[1].x*(srcTexture.Sample(Sampler, In.tex4.xy)
		+ srcTexture.Sample(Sampler, In.tex4.zw));
	Color += weight[1].y*(srcTexture.Sample(Sampler, In.tex5.xy)
		+ srcTexture.Sample(Sampler, In.tex5.zw));
	Color += weight[1].z*(srcTexture.Sample(Sampler, In.tex6.xy)
		+ srcTexture.Sample(Sampler, In.tex6.zw));
	Color += weight[1].w*(srcTexture.Sample(Sampler, In.tex7.xy)
		+ srcTexture.Sample(Sampler, In.tex7.zw));

	return float4(Color.xyz, 1.0f);
}