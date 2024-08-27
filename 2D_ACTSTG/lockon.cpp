//=============================================
//
//�Ə�[lockon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "lockon.h"
#include "manager.h"

//tex�p�X
const std::string CLockOn::TEXTURE_NAME = "data\\TEXTURE\\lockon.png";

//=============================================
//�R���X�g���N�^
//=============================================
CLockOn::CLockOn(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CLockOn::~CLockOn()
{
}

//=============================================
//������
//=============================================
HRESULT CLockOn::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CLockOn::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CLockOn::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();
}

//=============================================
//�`��
//=============================================
void CLockOn::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//����
//=============================================
CLockOn* CLockOn::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CLockOn* pLockOn = new CLockOn;

	// null�Ȃ�null��Ԃ�
	if (pLockOn == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	pLockOn->SetPos(pos); //pos�ݒ�

	pLockOn->SetSize(size); //�T�C�Y�ݒ�

	pLockOn->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���̐ݒ�

	pLockOn->m_col = col; //�J���[�̐ݒ�

	pLockOn->SetType(OBJECT_TYPE_LOCKON); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pLockOn->Init(); //�G�t�F�N�g�̏���������

	return pLockOn;
}
