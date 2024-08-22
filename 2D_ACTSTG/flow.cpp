//=============================================
//
//�W���a��[flow.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "flow.h"
#include "renderer.h"
#include"manager.h"

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CFlow::m_pTextureTemp = nullptr;
const std::string CFlow::TEXTURE_NAME = "data\\TEXTURE\\flow_test.png";

//=============================================
//�R���X�g���N�^
//=============================================
CFlow::CFlow(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CFlow::~CFlow()
{
}

//=============================================
//������
//=============================================
HRESULT CFlow::Init()
{
	//�e�N���X�̏�����
	CAttack_Manager::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CFlow::Uninit()
{
	//�e�N���X�̏I��
	CAttack_Manager::Uninit();
}

//=============================================
//�X�V
//=============================================
void CFlow::Update()
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
		switch (m_type)
		{
		case FLOW_TYPE_PLAYER:
			bHitCheck = HitEnemy();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		case FLOW_TYPE_ENEMY:
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
void CFlow::Draw()
{
	//�e�N���X�̕`��
	CAttack_Manager::Draw();
}

//=============================================
//����
//=============================================
CFlow* CFlow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,FLOW_TYPE type)
{
	CFlow* pFlow = new CFlow;

	if (pFlow == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pFlow->SetPos(pos); //pos�ݒ�
	pFlow->SetSize(size); //�T�C�Y�ݒ�
	pFlow->SetRot(rot);
	pFlow->SetLife(nLife); //�������
	pFlow->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pFlow->m_type = type; //�e�̐ݒ�
	pFlow->SetType(OBJECT_TYPE_FLOW); //�^�C�v�ݒ�
	pFlow->Init();

	return pFlow;
}
