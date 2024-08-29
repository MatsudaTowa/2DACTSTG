#include "button_UI.h"
#include "manager.h"

//tex�p�X
const std::string CButton_UI::TEXTURE_NAME_PAD_Y = "data\\TEXTURE\\acquisition_y.png";
const std::string CButton_UI::TEXTURE_NAME_KEYBOARD_F = "data\\TEXTURE\\acquisition_F.png";

//=============================================
//�R���X�g���N�^
//=============================================
CButton_UI::CButton_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CButton_UI::~CButton_UI()
{
}

//=============================================
//������
//=============================================
HRESULT CButton_UI::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,0.8f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CButton_UI::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CButton_UI::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();

	ChangeSize();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
}

//=============================================
//�`��
//=============================================
void CButton_UI::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//�T�C�Y�ύX
//=============================================
void CButton_UI::ChangeSize()
{
}

//=============================================
//����
//=============================================
CButton_UI* CButton_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTON_TYPE type)
{
	CButton_UI* pButton_UI = new CButton_UI;

	// null�Ȃ�null��Ԃ�
	if (pButton_UI == nullptr) { return nullptr; }

	//�e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	pButton_UI->SetPos(pos); //pos�ݒ�

	pButton_UI->SetSize(size); //�T�C�Y�ݒ�

	switch (type)
	{
	case CButton_UI::BUTTON_TYPE::BUTTON_TYPE_PAD_Y:
		pButton_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_PAD_Y))); //�e�N�X�`���̐ݒ�	
		break;
	case CButton_UI::BUTTON_TYPE::BUTTON_TYPE_KEYBOARD_F:
		pButton_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_KEYBOARD_F))); //�e�N�X�`���̐ݒ�	
		break;
	default:
		break;
	}

	pButton_UI->SetType(OBJECT_TYPE_BUTTON_UI); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pButton_UI->Init(); //�G�t�F�N�g�̏���������

	return pButton_UI;
}
