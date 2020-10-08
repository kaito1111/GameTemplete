#include "pch.h"
#include "system/system.h"
#include "Player.h"
#include "Player2.h"
#include "Stage.h"
#include "level/Level.h"
#include "graphics/Shader.h"
struct SSimpleVertex {
	CVector4 pos;
};
struct SVSConstantBuffer {
	CMatrix mWorld;
	//CVector4 mulColor;
};
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	CGameObjectManager()->Init();

	// ���_�o�b�t�@�̏������B
	//���_�o�b�t�@�̃\�[�X�f�[�^�B
	SSimpleVertex vertices[] =
	{
		CVector4(1.77778f, 1.0f, 0.5f, 1.0f),
		CVector4(1.77778f, -1.0f, 0.5f, 1.0f),
		CVector4(-1.77778f, -1.0f, 0.5f, 1.0f),
		CVector4(-1.77778f, 1.0f, 0.5f, 1.0f),
		CVector4(1.77778f, 1.0f, 0.5f, 1.0f),
	};

	//���_�o�b�t�@�̒�`�f�[�^���쐬����B
	D3D11_BUFFER_DESC desc = { 0 };	//0�N���A�B
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(vertices);	  //�o�b�t�@�̑傫���B
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//�ǂ̃o�b�t�@�Ƀo�C���h���邩���w�肷��B
	desc.CPUAccessFlags = 0;	//CPU����A�N�Z�X���邩���߂�B0�Ȃ炵�Ȃ��B
	//���_�o�b�t�@�̃\�[�X�f�[�^���w�肷��B
	D3D11_SUBRESOURCE_DATA InitData = { 0 };	//0�ŏ������B
	InitData.pSysMem = vertices;
	ID3D11Buffer* vertexBuffer;
	//���_�o�b�t�@��VRAM��ɍ쐬����B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc,&InitData, &vertexBuffer);

	
	//�萔�o�b�t�@�̒�`�f�[�^���쐬����B
	D3D11_BUFFER_DESC desc2 = { 0 };	//0�N���A�B
	desc2.Usage = D3D11_USAGE_DEFAULT;
	desc2.ByteWidth = sizeof(SVSConstantBuffer);		//�o�b�t�@�̑傫���B
	desc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//�ǂ̃o�b�t�@�Ƀo�C���h���邩���w�肷��B
									 //�萔�o�b�t�@�̏ꍇ�A���������_�o�b�t�@�ƕς��E�B
	desc2.CPUAccessFlags = 0;
	ID3D11Buffer* constantBuffer;
	//�萔�o�b�t�@��VRAM��ɍ쐬����B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc2, nullptr, &constantBuffer);

	//���_�V�F�[�_�[�����[�h�B
	//�������̓��[�h����V�F�[�_�[�\�[�X�t�@�C���̃t�@�C���p�X�B
	//�������̓G���g���[�|�C���g�ƂȂ�֐��̖��O�B 
	//��O�����̓��[�h�����V�F�[�_�[�̃^�C�v�B�����͒��_�V�F�[�_�[�B
	Shader vsShader;
	vsShader.Load(
		"Assets/shader/sprite.fx",
		"VSMain",
		Shader::EnType::VS
	);
	Shader psShader;
	//�s�N�Z���V�F�[�_�[�����[�h�B
	psShader.Load(
		"Assets/shader/sprite.fx",
		"PSMain",
		Shader::EnType::PS
	);
	//IGameObjectPtr hoge = NewGO< PlayerHoge>(0);
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		CGameObjectManager()->ExcuteMain();
		CGameObjectManager()->ExcuteGame();

		auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		
		//static CVector4 mulColor = { 0.0f,0.0f,1.0f,1.0f };//m_mulColor�̓��e��ύX�B
		//static CVector4 mulColor = CVector4::White();
		//if (g_pad[0].IsPress(enButtonA)) {
		//	//A�{�^���������ꂽ
		//	mulColor.x += 0.05f;
		//	//X = max(X, 0.0f);	//x�̒l��0.0��菬�����Ȃ�Ȃ��悤�ɁB
		//}
		//if (g_pad[0].IsPress(enButtonB)) {
		//	//B�{�^���������ꂽ�B
		//	mulColor.x -= 0.05f;
		//	//X = min(X, 1.0f);	//x�̒l��1.0���傫���Ȃ�Ȃ��悤�ɁB
		//}

		//deviceContext->UpdateSubresource(
		//	constantBuffer,
		//	0,
		//	NULL,
		//	&mulColor,
		//	0,
		//	0
		//);
		//deviceContext->PSSetConstantBuffers(
		//	0,
		//	1,
		//	&constantBuffer
		//);

		unsigned int stride = sizeof(SSimpleVertex);
		unsigned int offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		deviceContext->VSSetShader(
			(ID3D11VertexShader*)vsShader.GetBody(),
			NULL,
			0
		);
		deviceContext->PSSetShader(
			(ID3D11PixelShader*)psShader.GetBody(),
			NULL,
			0
		);
		deviceContext->IASetInputLayout(vsShader.GetInputLayout());

		//���[���h�E�r���[�E�v���W�F�N�V�����s����X�V����B
		SVSConstantBuffer cb;
		//�܂��̓��[���h�s��B����͒P�ʍs��ɂ��Ƃ��B
		cb.mWorld = CMatrix::Identity();
		//cb.mulColor = CVector4::White();
		CVector3 trans = { 0.0f,0.0f,0.0f };
		CMatrix mTrans=CMatrix::Identity();
		mTrans.MakeTranslation(trans);
		//�����ăr���[�s��B
		CMatrix mView;
		mView.MakeLookAt(
			{ 0.0f, 0.0f, 1.5f },		//���_
			{ 0.0f, 0.0f, 0.0f },	//�����_
			{ 0.0f, 1.0f, 0.0f }		//�����
		);
		//�Ō�Ƀv���W�F�N�V�����s��B
		CMatrix mProj;
		mProj.MakeProjectionMatrix(
			CMath::PI * 0.5f,					//��p
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��
			0.1f,								//�ߕ��ʂ܂ł̋���
			1000.0f								//�����ʂ܂ł̋����B
		);
		CMatrix mWvp = CMatrix::Identity();
		cb.mWorld.Mul(cb.mWorld,mTrans);
		cb.mWorld.Mul(mView, cb.mWorld);
		cb.mWorld.Mul(mProj, cb.mWorld);

		//cb.mulColor.x = mulColor.x;

		//VRAM��̒萔�o�b�t�@�̓��e���X�V�B
		deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &cb, 0, 0);

		//���_�V�F�[�_�[�Ŏg�p����萔�o�b�t�@��ݒ�B
		deviceContext->VSSetConstantBuffers(
			0,					//�萔�o�b�t�@���o�C���h����X���b�g�ԍ�(��q)
			1,					//�ݒ肷��o�b�t�@�̐��B
			&constantBuffer	    //�ݒ肷��萔�o�b�t�@�z��B
		);

		////���_�V�F�[�_�[�Ŏg�p����萔�o�b�t�@��ݒ�B
		//deviceContext->PSSetConstantBuffers(
		//	0,					//�萔�o�b�t�@���o�C���h����X���b�g�ԍ�(��q)
		//	1,					//�ݒ肷��o�b�t�@�̐��B
		//	&constantBuffer	    //�ݒ肷��萔�o�b�t�@�z��B
		//);
		deviceContext->Draw(
			5,
			0
		);
		//�J�����̍X�V�B
		g_camera3D.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}