/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */

cbuffer cb : register(b0) {
	//float4x4 mWorld;	//���[���h�s��B
	//float4x4 mView;	//�r���[�s��B
	//float4x4 mProj;	//�v���W�F�N�V�����s��B

	float4x4 mWvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float4 mulColor;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
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
	////���[���h�s������f���̒��_���W�ɏ�Z����B
	//float4 pos = mul(mWorld, Pos);
	////�r���[�s�����Z�B
	//pos = mul(mView, pos);
	////�v���W�F�N�V�����s�����Z���āA
	////�X�N���[���̐��K�����W�n(-1.0�`1.0�̍��W�n)�ɕϊ�����B
	//pos = mul(mProj, pos);
	//���W�ϊ����I������B
	return In;
}
float4 PSMain(PSInput In) : SV_Target0
{
	//float4 color /*= float4(1.0f, 0.0f, 1.0f, 1.0f)*/;
	//color = mulColor;
	return colorTexture.Sample(Sampler ,In.uv) * mulColor;
}