//=============================================
//
//3DTemplate[character.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "field.h"

//�d�͒l
const float CCharacter::GRAVITY_MOVE = 1.5f;
//�d�͍ő�l
const float CCharacter::GRAVITY_MAX = 32.0f;

//=============================================
//�R���X�g���N�^
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority)
{
    m_bLanding = false; //���n
}

//=============================================
//�f�X�g���N�^
//=============================================
CCharacter::~CCharacter()
{
}

//=============================================
//������
//=============================================
HRESULT CCharacter::Init()
{
    return S_OK;
}

//=============================================
//�I��
//=============================================
void CCharacter::Uninit()
{
    CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CCharacter::Update()
{
}

//=============================================
//�`��
//=============================================
void CCharacter::Draw()
{
    CObjectX::Draw();
}


//=============================================
//�d�͏���
//=============================================
void CCharacter::Gravity()
{
    if (m_move.y < GRAVITY_MAX)
    {
        m_move.y -= GRAVITY_MOVE;
    }
}

//=============================================
//�u���b�N�Ƃ̐ڐG����
//=============================================
void CCharacter::HitBlock()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//�T�C�Y�擾
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�u���b�N�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;
				if (m_oldpos.x + CharacterMax.x <= pBlock->GetPos().x + pBlock->GetMinPos().x
					&& CharacterPos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
					{//�����蔻��(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.x + CharacterMin.x >= pBlock->GetPos().x + pBlock->GetMaxPos().x
					&& CharacterPos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
					{//�����蔻��(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.z + CharacterMax.z <= pBlock->GetPos().z + pBlock->GetMinPos().z
					&& CharacterPos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
				{
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//�����蔻��(Z)
						CharacterPos.z = m_oldpos.z;
						m_move.z = 0.0f;
					}
				}

				if (m_oldpos.z + CharacterMin.z >= pBlock->GetPos().z + pBlock->GetMaxPos().z
					&& CharacterPos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z)
				{
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//�����蔻��(Z)
						CharacterPos.z = m_oldpos.z;
						m_move.z = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMin.y >= pBlock->GetPos().y + pBlock->GetMaxPos().y
					&& CharacterPos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y)
				{//�����蔻��(Y)��
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
						m_bLanding = true; //���n
						m_move.y = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMax.y <= pBlock->GetPos().y + pBlock->GetMinPos().y
					&& CharacterPos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
				{//�����蔻��(Y)��
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
					}
				}
			}

			//���Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = (CField*)pObj;
				if (m_oldpos.y + CharacterMin.y >= pField->GetPos().y
					&& CharacterPos.y + CharacterMin.y <= pField->GetPos().y)
				{
					if (m_oldpos.x + CharacterMin.x < pField->GetPos().x + pField->GetSize().x
						&& m_oldpos.x + CharacterMax.x > pField->GetPos().x - pField->GetSize().x
						&& m_oldpos.z + CharacterMin.z < pField->GetPos().z + pField->GetSize().z
						&& m_oldpos.z + CharacterMax.z > pField->GetPos().z - pField->GetSize().z)
					{//�����蔻��(Y)
						CharacterPos.y = m_oldpos.y;
						m_move.y = 0.0f;
						m_bLanding = true; //���n
						//m_nJumpCnt = 0; //�W�����v�����Z�b�g
					}
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//�ړ��ʎ擾
//=============================================
D3DXVECTOR3& CCharacter::GetMove()
{
    return m_move;
}

//=============================================
//�ߋ��̈ʒu�擾
//=============================================
D3DXVECTOR3& CCharacter::GetOldPos()
{
    return m_oldpos;
}

//=============================================
//���n���Ă邩�ǂ����擾
//=============================================
bool& CCharacter::GetLaunding()
{
    return m_bLanding;
}

//=============================================
//�ǂ��������Ă邩�ǂ������擾(true:�Efalse:��)
//=============================================
bool& CCharacter::GetWay()
{
    return m_bWay;
}
