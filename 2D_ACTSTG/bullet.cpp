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
const std::string CBullet::TEXTURE_NAME ="data\\TEXTURE\\slash.png";

//=============================================
//�R���X�g���N�^
//=============================================
CBullet::CBullet(int nPriority):CBillboard(nPriority)
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
	//�T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	//�Ίp��
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//�p�x
	m_fAngle = atan2f(size.x, size.y);

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CBullet::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CBullet::Update()
{
	D3DXVECTOR3 pos = GetPos();
	//CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 8.0f, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);
	pos += m_move;
	//���W���X�V
	SetPos(pos);
	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	HitBullet();

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	else
	{
		Uninit();
		//CExplosion*pExplosion = CExplosion::Create(pos,D3DXVECTOR2(20.0f,20.0f));
	}
}

//=============================================  
//�`��
//=============================================
void CBullet::Draw()
{
	CObject3D::Draw();
}

//=============================================
//�e�쐬
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife)
{
	CBullet* pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		CTexture* pTexture = CManager::GetTexture();

		pBullet->SetPos(pos); //pos�ݒ�
		pBullet->SetSize(size); //�T�C�Y�ݒ�
		pBullet->SetRot(rot);
		pBullet->m_move = move; //�ړ��ʑ��
		pBullet->m_nLife = nLife; //�������
     	pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
		pBullet->SetType(OBJECT_TYPE_BULLET); //�^�C�v�ݒ�
		pBullet->Init();
	}

	return pBullet;
}

//=============================================
//�e�Ƃ̓����蔻��
//=============================================
void CBullet::HitBullet()
{
	D3DXVECTOR3 Bulletpos = GetPos();
	//�T�C�Y�擾
	D3DXVECTOR3 Bulletsize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject*pObj =CObject::Getobject(4,nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				//CEnemy* pEnemy = (CEnemy*)pObj;
				//pEnemy->GetPos(); //�ʒu�擾
				//pEnemy->GetSize(); //�T�C�Y�擾
				//if (Bulletpos.x - Bulletsize.x >= pEnemy->GetPos().x - pEnemy->GetSize().x
				//	&& Bulletpos.x + Bulletsize.x <= pEnemy->GetPos().x + pEnemy->GetSize().x
				//	&& Bulletpos.y - Bulletsize.y >= pEnemy->GetPos().y - pEnemy->GetSize().y
				//	&& Bulletpos.y + Bulletsize.y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
				//{//�G�ƒe������������
				//	pEnemy->HitBullet();
				//	//�e�̍폜
				//	Release();
				//}
			}
		}
	}
}
