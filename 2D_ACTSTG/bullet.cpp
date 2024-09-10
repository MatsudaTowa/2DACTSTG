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
const std::string CBullet::TEXTURE_NAME ="data\\TEXTURE\\slash_test.png";

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
//�`��
//=============================================
void CBullet::Draw()
{
	//�e�N���X�̕`��
	CAttack_Manager::Draw();
}

//=============================================
//�e�쐬
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type)
{
	CBullet* pBullet = nullptr;

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet = new CPanetRaring_Slash;
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet = new CPanetRaring_Slash;
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
    pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
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
//�^�C�v�擾
//=============================================
CBullet::BULLET_ALLEGIANCE CBullet::GetBulletType()
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
CElecBullet::CElecBullet(int nPriority) :CBullet(nPriority)
{
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
	return E_NOTIMPL;
}

//=============================================
//�I��
//=============================================
void CElecBullet::Uninit()
{
}

//=============================================
//�X�V
//=============================================
void CElecBullet::Update()
{
}

//=============================================
//�`��
//=============================================
void CElecBullet::Draw()
{
}
