#include "timer.h"
#include "manager.h"

//�e�N�X�`���p�X
const std::string CTimer::TEXTURE_NAME = "data\\TEXTURE\\number_test.png";

//���f���ݒ�
CNumber* CTimer::m_pNumber[NUM_DIGIT] = {};

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

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//�i���o�[����
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = new CNumber();
			m_pNumber[nCnt]->Init();
		}
		//���_�ݒ�
		SetTimerVtx();
	}

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTimer::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			delete m_pNumber[nCnt];
			m_pNumber[nCnt] = nullptr;
		}
	}

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

	CNumber::SetNumVtx(GetVtxBuff(),1.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT*0.5f,0.0f),D3DXVECTOR2(30.0f,50.0f),0.1f,0.2f);

	////���_�ݒ�
	//SetTimerVtx();
}

//=============================================
//�`��
//=============================================
void CTimer::Draw()
{
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
	pTimer->m_nCurrentTime = LIMIT_TIME;
	pTimer->Init();

	return pTimer;
}

//=============================================
//�^�C�}�[�p�̒��_����
//=============================================
void CTimer::SetTimerVtx()
{

	D3DXVECTOR3 pos = GetPos();
	//�e�N�X�`�����W�ݒ�
	int a_PosTexU[NUM_DIGIT];

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//���̎��Ԃ���v�Z
		a_PosTexU[nCnt] = m_nCurrentTime / nDigit % 10;

		//����i�߂�
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;
		m_pNumber[nCnt]->SetNumVtx(GetVtxBuff(),1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), pos ,GetSize(),fMinTexU, fMaxTexU);

		//x���W�����炷
		pos.x += GetSize().x;
	}
}
