//=============================================
//
//�X�L�b�vUI[skip_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "skip_UI.h"
#include "manager.h"
#include "object.h"

//tex�p�X
const std::string CSkip_UI::BUTTON_A_TEXTURE_NAME = "data\\TEXTURE\\skip_A.png";
const std::string CSkip_UI::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\skip_enter.png";

//=============================================
//�R���X�g���N�^
//=============================================
CSkip_UI::CSkip_UI(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CSkip_UI::~CSkip_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CSkip_UI::Init()
{

	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CSkip_UI::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CSkip_UI::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CSkip_UI::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CSkip_UI* CSkip_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();
	CSkip_UI* pSkip_UI = new CSkip_UI;

	//null�Ȃ�null��Ԃ�
	if (pSkip_UI == nullptr) { return nullptr; }

	pSkip_UI->SetPos(pos); //pos�ݒ�

	pSkip_UI->SetSize(size); //size�ݒ�

	pSkip_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));

	pSkip_UI->SetType(OBJECT_TYPE_TUTORIAL); //�^�C�v�ݒ�

	pSkip_UI->Init();

	return pSkip_UI;
}
