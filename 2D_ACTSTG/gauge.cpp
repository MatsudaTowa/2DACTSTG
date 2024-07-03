//=============================================
//
//�Q�[�W�Ǘ�[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "gauge.h"
#include "manager.h"

//�Q�[�W�̍ő�l
const float CGauge::MAX_GAUGE_WIDE = 370.0f;

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
	SetGaugeVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

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

	if (GetSize().x <= MAX_GAUGE_WIDE)
	{//�ő�l�ȉ��Ȃ���Z
		AddGauge();
	}

	//���_�ݒ�
	SetGaugeVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
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
//�Q�[�W��������
//=============================================
void CGauge::AddGauge()
{
	//�������g�̃T�C�Y�擾
   D3DXVECTOR2 size = GetSize();

   size.x += 10.0f;

   //�T�C�Y���
   SetSize(size);
}

//=============================================
//�Q�[�W��������
//=============================================
void CGauge::SubGauge()
{

}

//=============================================
//�Q�[�W�̒��_����
//=============================================
void CGauge::SetGaugeVtx(float rhw, D3DCOLOR col)
{
    CRenderer* pRender = CManager::GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

    if (GetVtxBuff() == nullptr)
    {
        pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetVtxBuff(), NULL);
    }
    VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾

	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y + GetSize().y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	GetVtxBuff()->Unlock();
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
