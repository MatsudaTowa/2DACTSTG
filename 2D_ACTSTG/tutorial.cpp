//=============================================
//
//�`���[�g���A��[tutorial.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "tutorial.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "player_test.h"
#include "bullet.h"
#include "effect.h"
#include "gauge_fream.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "tutorial_UI.h"
#include "item.h"
#include "manager.h"
#include "sound.h"

const std::string CTutorial::BLOCK_FILE = "data\\FILE\\block.txt";

//=============================================
//�R���X�g���N�^
//=============================================
CTutorial::CTutorial()
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CTutorial::~CTutorial()
{
}

//=============================================
//������
//=============================================
HRESULT CTutorial::Init()
{
	//�n�ʐ���
	CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//�u���b�N����
	LoadBlock(&CTutorial::BLOCK_FILE);

	//�v���C���[����
	m_pPlayer = new CPlayer;
	m_pPlayer->Init(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	CTutorial_UI::Create(D3DXVECTOR3(-900.0f,70.0f,100.0f),D3DXVECTOR3(60.0f,40.0f,0.0f),CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MOVE_KEYBOARD);
	CTutorial_UI::Create(D3DXVECTOR3(-700.0f, 70.0f, 100.0f), D3DXVECTOR3(60.0f, 20.0f, 0.0f), CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_MELEE_MOUSE);
	CTutorial_UI::Create(D3DXVECTOR3(-500.0f, 70.0f, 100.0f), D3DXVECTOR3(60.0f, 20.0f, 0.0f), CTutorial_UI::TUTORIAL_TYPE::TUTORIAL_TYPE_SLASH_MOUSE);


	CItem::Create(CItem::ITEMTYPE::ITEMTYPE_PANETRARING_SLASH, D3DXVECTOR3(-600.0f, 10.0f, 0.0f),D3DXVECTOR3(10.0f,10.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	CItem::Create(CItem::ITEMTYPE::ITEMTYPE_FLOW, D3DXVECTOR3(-550.0f, 10.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pSkipUI = CSkip_UI::Create(D3DXVECTOR3(200.0f,600.0f,0.0f),D3DXVECTOR2(150.0f,70.0f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CTutorial::Uninit()
{
	CSound* pSound = CManager::GetSound();
	//�T�E���h�̒�~
	pSound->StopSound();
	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CTutorial::Update()
{
	CObject::UpdateAll();
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();

	//CFade*pFade= CFade::GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::SetMode(CScene::MODE::MODE_GAME);
	}
}

//=============================================
//�`��
//=============================================
void CTutorial::Draw()
{
}

//=============================================
//�u���b�N�ǂݍ���
//=============================================
void CTutorial::LoadBlock(const std::string* pFileName)
{
	char aDataSearch[BLOCK_TXT_MAX];
	char aEqual[BLOCK_TXT_MAX]; //[��]�ǂݍ��ݗp
	int nNumBlock; //�u���b�N�̐�

	//�t�@�C���̓ǂݍ���
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//��ނ̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ
		//�������I������
		return;
	}
	//END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //����

		if (!strcmp(aDataSearch, "END"))
		{//�ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_BLOCK"))
		{//���f�����ǂݍ���
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumBlock);
		}
		if (!strcmp(aDataSearch, "BLOCKSET"))
		{
			//���ڂ��Ƃ̃f�[�^����
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //����

				if (!strcmp(aDataSearch, "END_BLOCKSET"))
				{
					//�G�l�~�[����
					CBlock::Create(m_LoadBlock.type, m_LoadBlock.pos, m_LoadBlock.rot, 1, false);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.pos.x,
						&m_LoadBlock.pos.y,
						&m_LoadBlock.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadBlock.rot.x,
						&m_LoadBlock.rot.y,
						&m_LoadBlock.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadBlock.type);
				}
			}
		}
	}
}
