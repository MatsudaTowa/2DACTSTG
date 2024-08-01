//=============================================
//
//�A�C�e������[item.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "item.h"
#include "effect.h"
#include "manager.h"
#include "player.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CItem::m_pTextureTemp = nullptr;
const std::string CItem::TEXTURE_NAME = "data\\TEXTURE\\item_book000.png";

//=============================================
//�R���X�g���N�^
//=============================================
CItem::CItem(int nPriority):CBillboard(nPriority)
{
}
//=============================================
//�f�X�g���N�^
//=============================================
CItem::~CItem()
{
}

//=============================================
//������
//=============================================
HRESULT CItem::Init()
{
	//�e�N���X�̏�����
	CBillboard::Init();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CItem::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//=============================================
void CItem::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	HitItem();

}

//=============================================
//�`��
//=============================================
void CItem::Draw()
{
	//�e�N���X�̕`��
	CBillboard::Draw();
}

//=============================================
//����
//=============================================
CItem* CItem::Create(ITEMTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CItem* pItem = new CItem;

	if (pItem == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pItem->SetPos(pos); //pos�ݒ�
	pItem->SetSize(size); //size�ݒ�
	pItem->SetRot(rot); //rot�ݒ�

	pItem->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));	//�e�N�X�`���̐ݒ�

	pItem->SetType(OBJECT_TYPE_ITEM); //�^�C�v�ݒ�

	pItem->m_ItemType = type; //�A�C�e���^�C�v�ݒ�

	pItem->Init();
}

//=============================================
//�����蔻��
//=============================================
void CItem::HitItem()
{
	//�ʒu�擾
	D3DXVECTOR3 Itempos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Itemsize = GetSize();

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

				if (Itempos.x + Itemsize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
					&& Itempos.x - Itemsize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x)
				{
					if (Itempos.z - Itemsize.z< pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& Itempos.z + Itemsize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
						&& Itempos.y - Itemsize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Itempos.y + Itemsize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
					{//�����蔻��(X)
						pPlayer->m_Attack = CPlayer::PLAYER_ATTACK_PANETRARING_SLASH;
						//�A�C�e���̍폜
						Uninit();
					}
				}


				else if (Itempos.z + Itemsize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
					&& Itempos.z - Itemsize.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z)
				{
					if (Itempos.x - Itemsize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x
						&& Itempos.x + Itemsize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
						&& Itempos.y - Itemsize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Itempos.y + Itemsize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y
						)
					{//�����蔻��(Z)
						pPlayer->m_Attack = CPlayer::PLAYER_ATTACK_PANETRARING_SLASH;
						//�A�C�e���̍폜
						Uninit();
					}
				}
			}
		}
	}
}
