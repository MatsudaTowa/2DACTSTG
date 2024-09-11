//=============================================
//
//3DTemplate[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "effect.h"
#include "enemy.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;
const std::string CBullet::PANETRARING_TEXTURE_NAME ="data\\TEXTURE\\slash_test.png";
const std::string CBullet::ELEC_TEXTURE_NAME ="data\\TEXTURE\\elekball.png";

//=============================================
//�R���X�g���N�^
//=============================================
CBullet::CBullet(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//������
//=============================================
HRESULT CBullet::Init()
{
	//�e�N���X�̏�����
	CAttack_Manager::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBullet::Uninit()
{
	//�e�N���X�̏I��
	CAttack_Manager::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBullet::Update()
{

	//�e�N���X�̍X�V
	CAttack_Manager::Update();
	
	//�g�p���Ă���Ƃ�
	OnActive();

}

//=============================================  
//�`��
//=============================================
void CBullet::Draw()
{
	//�e�N���X�̕`��
	CAttack_Manager::Draw();
}

//=============================================
//�g�p����Ă鎞�̏���
//=============================================
void CBullet::OnActive()
{
	//�̗͎擾
	int nLife = GetLife();

	if (nLife > 0)
	{//���C�t������Ώ������s
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		//���W���X�V
		SetPos(pos);
		//���_���W
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//�����蔻��`�F�b�N�ϐ�
		bool bHitCheck = false;

		//���܂��Ă邩�̃`�F�b�N�ϐ�
		bool bHitUnder = false;

		bHitUnder = HitGround();

		switch (m_Allegiance)
		{
		case BULLET_ALLEGIANCE_PLAYER:
			bHitCheck = HitEnemy();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		case BULLET_ALLEGIANCE_ENEMY:
			bHitCheck = HitPlayer();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		default:
			assert(false);
			break;
		}

		//�����蔻��`�F�b�N
		bHitCheck = HitBlock();

		if (bHitCheck == true)
		{//�������Ă���
			Uninit();
		}
	}
	else
	{
		//�I��
		Uninit();
	}
}

//=============================================
//�e�쐬
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size
,int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type)
{
	CBullet* pBullet = nullptr;

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet = new CPanetRaring_Slash;
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet = new CElecBullet;
		break;

	default:
		break;
	}

	if (pBullet == nullptr) {return nullptr;}

	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos�ݒ�
	pBullet->SetSize(size); //�T�C�Y�ݒ�
	pBullet->SetRot(rot);
	pBullet->m_move = move; //�ړ��ʑ��
	pBullet->SetLife(nLife); //�������
	pBullet->SetDamage(nDamage); //�З͑��

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&PANETRARING_TEXTURE_NAME)));
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&ELEC_TEXTURE_NAME)));
		break;

	default:
		break;
	}
	pBullet->m_Allegiance = Allegiance; //�e�̐ݒ�
	pBullet->SetType(OBJECT_TYPE_BULLET); //�^�C�v�ݒ�
	pBullet->Init();

	return pBullet;
}

//=============================================
//�ړ��ʎ擾
//=============================================
D3DXVECTOR3 CBullet::GetMove()
{
	return m_move;
}

//=============================================
//�G���������擾
//=============================================
CBullet::BULLET_ALLEGIANCE CBullet::GetBulletAllegiance()
{
	return m_Allegiance;
}

//=============================================
//�R���X�g���N�^
//=============================================
CPanetRaring_Slash::CPanetRaring_Slash(int nPriority):CBullet(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CPanetRaring_Slash::~CPanetRaring_Slash()
{
}

//=============================================
//������
//=============================================
HRESULT CPanetRaring_Slash::Init()
{
	//�e�N���X�̏�����
	CBullet::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CPanetRaring_Slash::Uninit()
{
	//�e�N���X�̏I��
	CBullet::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPanetRaring_Slash::Update()
{
	//�e�N���X�̍X�V
	CBullet::Update();

	//�̗͎擾
	int nLife = GetLife();

	if (nLife > 0)
	{//���C�t������Ώ������s

		//���܂��Ă邩�̃`�F�b�N�ϐ�
		bool bHitUnder = false;

		bHitUnder = HitGround();
	}
}

//=============================================
//�`��
//=============================================
void CPanetRaring_Slash::Draw()
{
	//�e�N���X�̕`��
	CBullet::Draw();
}


//=============================================
//�R���X�g���N�^
//=============================================
CElecBullet::CElecBullet(int nPriority) :CBullet(nPriority),m_Electype(CElecBullet::ELECTYPE::TYPE_NONE)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�^�C�v������
}

//=============================================
//�f�X�g���N�^
//=============================================
CElecBullet::~CElecBullet()
{
}

//=============================================
//������
//=============================================
HRESULT CElecBullet::Init()
{
	//�e�N���X�̏�����
	CBullet::Init();

	//�X�^���o�C��Ԃ�
	m_Electype = CElecBullet::ELECTYPE::TYPE_STAND_BY;

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CElecBullet::Uninit()
{
	//�e�N���X�̏I��
	CBullet::Uninit();
}

//=============================================
//�X�V
//=============================================
void CElecBullet::Update()
{
	if (m_Electype == CElecBullet::ELECTYPE::TYPE_MOVE)
	{
		SetMove(D3DXVECTOR3(-3.0f,0.0f,0.0f));
		//�e�N���X�̍X�V
		CBullet::Update();
	}
	else if (m_Electype == CElecBullet::ELECTYPE::TYPE_STAND_BY)
	{
		//�g�p���Ă���Ƃ�
		OnActive();
	}
}

//=============================================
//�`��
//=============================================
void CElecBullet::Draw()
{
	//�e�N���X�̕`��
	CBullet::Draw();
}

//=============================================
//����
//=============================================
CElecBullet* CElecBullet::ElecCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance, BULLET_TYPE type)
{
	CElecBullet* pBullet = new CElecBullet;

	if (pBullet == nullptr) { return nullptr; }

	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos�ݒ�
	pBullet->SetSize(size); //�T�C�Y�ݒ�
	pBullet->SetRot(rot);
	pBullet->SetLife(nLife); //�������
	pBullet->SetDamage(nDamage); //�З͑��

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&PANETRARING_TEXTURE_NAME)));
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&ELEC_TEXTURE_NAME)));
		break;

	default:
		break;
	}
	pBullet->SetBulletAllegiance(Allegiance); //�e�̐ݒ�
	pBullet->SetType(OBJECT_TYPE_BULLET); //�^�C�v�ݒ�
	pBullet->Init();

	return pBullet;
}

void CElecBullet::SetElecType(ELECTYPE type)
{
	m_Electype = type;
}
