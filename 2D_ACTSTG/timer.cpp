#include "timer.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CTimer::TEXTURE_NAME = "data\\TEXTURE\\number_test.png";

//=============================================
//�R���X�g���N�^
//=============================================
CTimer::CTimer(int nPriority):CObject2D(nPriority), m_nFrameCnt(0),m_nCurrentTime(0)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�t���[���J�E���g�ƍ��̎��Ԃ�������
}

//=============================================
//�f�X�g���N�^
//=============================================
CTimer::~CTimer()
{
}

//=============================================
//������
//=============================================
HRESULT CTimer::Init()
{
	//�e�N���X�̏�����
	CObject2D::Init();

	//�e�N�X�`�����W�ݒ�
	SetTexPos(D3DXVECTOR2(0.1f, 1.0f));

	//���_�ݒ�
	SetTimerVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTimer::Uninit()
{
	//�e�N���X�̏I��
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CTimer::Update()
{
	//�e�N���X�̍X�V
	CObject2D::Update();

	m_nFrameCnt++;

	if (m_nFrameCnt >= 60)
	{
		m_nCurrentTime++;
		m_nFrameCnt = 0;
	}



	//���_�ݒ�
	SetTimerVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}

//=============================================
//�`��
//=============================================
void CTimer::Draw()
{
	//�e�N���X�̕`��
	CObject2D::Draw();
}

//=============================================
//����
//=============================================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTimer*pTimer = new CTimer();

	//null�Ȃ�null��Ԃ�
	if(pTimer == nullptr) {return nullptr;}

	CTexture* pTexture = CManager::GetTexture();

	pTimer->SetPos(pos); //pos���
	pTimer->SetSize(size); //size���
	pTimer->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pTimer->SetType(OBJECT_TYPE_TIMER); //�^�C�v�ݒ�
	pTimer->Init();

	return pTimer;
}

//=============================================
//�^�C�}�[�p�̒��_����
//=============================================
void CTimer::SetTimerVtx(float rhw, D3DCOLOR col)
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
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - GetSize().x
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


	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];
	int One = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		a_PosTexU[nCnt] = m_nCurrentTime / One % 10;
		One *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		float fDigit0, fDigit1;
		fDigit0 = a_PosTexU[nCnt] * 0.1f;
		fDigit1 = fDigit0 + 0.1f;
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fDigit0, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fDigit1, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fDigit0, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fDigit1, 1.0f);
	}

	//�A�����b�N
	GetVtxBuff()->Unlock();
}
