//=============================================
//
//3DTemplate[title_Screen.h]
//Auther Matsuda Towa
//
//=============================================
#include "title_screen.h"
#include "manager.h"
#include "object.h"


//tex�p�X
const std::string CTitle_Screen::TEXTURE_NAME = "data\\TEXTURE\\title_test.png";

//=============================================
//�R���X�g���N�^
//=============================================
CTitle_Screen::CTitle_Screen(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTitle_Screen::~CTitle_Screen()
{
}

//=============================================
//������
//=============================================
HRESULT CTitle_Screen::Init()
{

	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�������g�̃T�C�Y�擾
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//�T�C�Y����
	SetSize(size);

	//���_�ݒ�
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTitle_Screen::Uninit()
{
	//�e�N���X�̏I���Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTitle_Screen::Update()
{
	//�e�N���X�̍X�V�Ă�
	CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CTitle_Screen::Draw()
{
	//�e�N���X�̕`��Ă�
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CTitle_Screen* CTitle_Screen::Create(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetTexture();
	CTitle_Screen* pTitle_Screen = new CTitle_Screen;

	//null�Ȃ�null��Ԃ�
	if (pTitle_Screen == nullptr) {return nullptr;}

	pTitle_Screen->SetPos(pos); //pos�ݒ�

	pTitle_Screen->SetType(OBJECT_TYPE_TITLE); //�^�C�v�ݒ�

	pTitle_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	pTitle_Screen->Init();

	return pTitle_Screen;
}
