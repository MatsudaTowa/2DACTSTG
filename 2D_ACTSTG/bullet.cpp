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
{//�C�j�V�����C�U�[�Ń��C�t�ƃ_���[�W������
	
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
		switch (m_type)
		{
		case BULLET_TYPE_PLAYER:
			HitEnemy();
			break;

		case BULLET_TYPE_ENEMY:
			HitPlayer();
			break;

		default:
			assert(false);
			break;
		}
		HitBlock();

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
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife, int nDamage, BULLET_TYPE type)
{
	CBullet* pBullet = new CBullet;

	if (pBullet == nullptr) {return nullptr;}
	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos�ݒ�
	pBullet->SetSize(size); //�T�C�Y�ݒ�
	pBullet->SetRot(rot);
	pBullet->m_move = move; //�ړ��ʑ��
	pBullet->SetLife(nLife); //�������
	pBullet->SetDamage(nDamage); //�З͑��
    pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pBullet->m_type = type; //�e�̐ݒ�
	pBullet->SetType(OBJECT_TYPE_BULLET); //�^�C�v�ݒ�
	pBullet->Init();

	return pBullet;
}

