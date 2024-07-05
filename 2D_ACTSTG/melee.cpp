//=============================================
//
//�ߐڍU��[melee.h]
//Auther Matsuda Towa
//
//=============================================
#include "melee.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================
CMelee::CMelee(int nPriority) :CObject3D(nPriority),m_nLife(0)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CMelee::~CMelee()
{
}

//=============================================
//������
//=============================================
HRESULT CMelee::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();
	
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}


//=============================================
//�I��
//=============================================
void CMelee::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CMelee::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();

	if (m_nLife > 0)
	{//���C�t������Ώ������s
		m_nLife--;

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//�I�u�W�F�N�g�擾
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);

			if (pObj != nullptr)
			{//�k���|�C���^����Ȃ����
				//�^�C�v�擾
				CObject::OBJECT_TYPE type = pObj->GetType();
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					CPlayer* pPlayer = (CPlayer*)pObj;

					//�������g��pos�擾
					D3DXVECTOR3 pos = GetPos();

					//�v���C���[��pos�������ɑ��
					pos.y = pPlayer->GetPos().y + pPlayer->GetMaxPos().y * 0.5f;
					pos.z = pPlayer->GetPos().z;

					if (pPlayer->GetWay() == true)
					{//�E�����Ă�Ȃ�
						pos.x = pPlayer->GetPos().x + pPlayer->GetMaxPos().x;
					}
					else if (pPlayer->GetWay() == false)
					{//�������Ă�Ȃ�
						pos.x = pPlayer->GetPos().x + pPlayer->GetMinPos().x;
					}
					//pos����
					SetPos(pos);
				}
			}

		}

		//�����������`�F�b�N
		HitMelee();
	}
	else
	{//���C�t���Ȃ��Ȃ�����
		//�I������
		Uninit();
	}
}

//=============================================  
//�`��
//=============================================
void CMelee::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//�ߐڍU���쐬
//=============================================
CMelee* CMelee::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife)
{
	CMelee* pMelee = new CMelee;
	//null�Ȃ�null��Ԃ�
   if(pMelee ==nullptr) {return nullptr;}

   pMelee->SetPos(pos); //pos�ݒ�
   pMelee->SetSize(size); //�T�C�Y�ݒ�
   pMelee->SetRot(rot); //�����ݒ�
   pMelee->m_nLife = nLife; //�������

   pMelee->SetType(OBJECT_TYPE_MELEE); //�^�C�v�ݒ�

   pMelee->Init(); //������

   return pMelee;
 }

//=============================================
//�ߐڍU���̓����蔻��
//=============================================
void CMelee::HitMelee()
{
	//�ʒu�擾
	D3DXVECTOR3 Meleepos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Meleesize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				CEnemy* pEnemy = (CEnemy*)pObj;

				if (Meleepos.x + Meleesize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
					&& Meleepos.x - Meleesize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x)
				{
					if (Meleepos.z - Meleesize.z< pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& Meleepos.z + Meleesize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& Meleepos.y - Meleesize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Meleepos.y + Meleesize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//�����蔻��(X)
						pEnemy->HitDamage(1);
						//�ߐڍU���̍폜
						Uninit();
					}
				}


				else if (Meleepos.z + Meleesize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
					&& Meleepos.z - Meleesize.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z)
				{
					if (Meleepos.x - Meleesize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& Meleepos.x + Meleesize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& Meleepos.y - Meleesize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Meleepos.y + Meleesize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//�����蔻��(Z)
						pEnemy->HitDamage(1);
						//�ߐڍU���̍폜
						Uninit();
					}
				}
			}
		}
	}
}
