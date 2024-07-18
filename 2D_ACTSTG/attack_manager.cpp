//=============================================
//
//�U���Ǘ��N���X[attack_manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "enemy.h"
#include "player.h"

//=============================================
//�R���X�g���N�^
//=============================================
CAttack_Manager::CAttack_Manager(int nPriority) : CBillboard(nPriority),m_nLife(0),m_nDamage(0)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�̗͂ƃ_���[�W������
}

//=============================================
//�f�X�g���N�^
//=============================================
CAttack_Manager::~CAttack_Manager()
{
}

//=============================================
//������
//=============================================
HRESULT CAttack_Manager::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CAttack_Manager::Uninit()
{
	//�e�N���X�̏I������
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CAttack_Manager::Update()
{
	//�e�N���X�̍X�V����
	CObject3D::Update();

	if (m_nLife > 0)
	{
		m_nLife--;
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
void CAttack_Manager::Draw()
{
	//�e�N���X�̕`�揈��
	CObject3D::Draw();
}

//=============================================
//�U�������蔻��(�G�l�~�[)
//=============================================
void CAttack_Manager::HitEnemy()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

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

				if (Attackpos.x + Attacksize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
					&& Attackpos.x - Attacksize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x)
				{
					if (Attackpos.z - Attacksize.z< pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& Attackpos.z + Attacksize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& Attackpos.y - Attacksize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//�����蔻��(X)
						pEnemy->Damage(m_nDamage);
						//�ߐڍU���̍폜
						Uninit();
					}
				}


				else if (Attackpos.z + Attacksize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
					&& Attackpos.z - Attacksize.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z)
				{
					if (Attackpos.x - Attacksize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& Attackpos.x + Attacksize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& Attackpos.y - Attacksize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//�����蔻��(Z)
						pEnemy->Damage(m_nDamage);
						//�ߐڍU���̍폜
						Uninit();
					}
				}
			}
		}
	}
}

//=============================================
//�U�������蔻��(�v���C���[)
//=============================================
void CAttack_Manager::HitPlayer()
{
	//�ʒu�擾
	D3DXVECTOR3 Attackpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;

				if (Attackpos.x + Attacksize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
					&& Attackpos.x - Attacksize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x)
				{
					if (Attackpos.z - Attacksize.z< pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& Attackpos.z + Attacksize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
						&& Attackpos.y - Attacksize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
					{//�����蔻��(X)
						pPlayer->Damage(m_nDamage);
						//�ߐڍU���̍폜
						Uninit();
					}
				}


				else if (Attackpos.z + Attacksize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
					&& Attackpos.z - Attacksize.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z)
				{
					if (Attackpos.x - Attacksize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x
						&& Attackpos.x + Attacksize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
						&& Attackpos.y - Attacksize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y
						)
					{//�����蔻��(Z)
						pPlayer->Damage(m_nDamage);
						//�ߐڍU���̍폜
						Uninit();
					}
				}
			}
		}
	}
}

//=============================================
//�̗͎擾
//=============================================
int CAttack_Manager::GetLife()
{
	return m_nLife;
}

//=============================================
//�_���[�W�擾
//=============================================
int CAttack_Manager::GetDamage()
{
	return m_nDamage;
}
