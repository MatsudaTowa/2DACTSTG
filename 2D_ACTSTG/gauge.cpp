//=============================================
//
//�Q�[�W�Ǘ�[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "gauge.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CGauge::CGauge(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CGauge::~CGauge()
{
}

//=============================================
//������
//=============================================
HRESULT CGauge::Init()
{
    //�e�N���X�̏��������Ă�
    CObject2D::Init();

    //���_�ݒ�
    SetVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

    return S_OK;
}

//=============================================
//�I��
//=============================================
void CGauge::Uninit()
{
    //�e�N���X�̏I���Ă�
    CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CGauge::Update()
{
    //�e�N���X�̍X�V�Ă�
    CObject2D::Update();
}

//=============================================
//�`��
//=============================================
void CGauge::Draw()
{
    //�e�N���X�̕`��Ă�
    CObject2D::Draw();
}

//=============================================
//����
//=============================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CTexture* pTexture = CManager::GetTexture();
    CGauge* pGauge = new CGauge;

    // null�Ȃ�null��Ԃ�
    if (pGauge == nullptr) { return nullptr; }

    pGauge->SetPos(pos); //pos�ݒ�

    pGauge->SetSize(size); //size�ݒ�

    pGauge->SetType(OBJECT_TYPE_GAUGE); //�^�C�v�ݒ�

    //pGauge->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

    pGauge->Init();
}
