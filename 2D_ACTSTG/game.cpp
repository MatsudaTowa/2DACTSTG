//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "player_test.h"
//#include "bg.h"
#include "bullet.h"
//#include "explosion.h"
#include "effect.h"
#include "gauge_fream.h"
#include "colision.h"
#include "timer.h"
#include "enemy.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//�G�f�B�b�g�ݒ�
CEdit* CGame::m_pEdit = nullptr;

//=============================================
//�R���X�g���N�^
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//�C�j�V�����C�U�[�Ńv���C�I���e�B�ݒ�A�G�f�B�b�g���ĂȂ���ԂɕύX
}

//=============================================
//�f�X�g���N�^
//=============================================
CGame::~CGame()
{
}

//=============================================
//������
//=============================================
HRESULT CGame::Init()
{

	if (m_pEdit == nullptr)
	{
		m_pEdit = new CEdit;
	}
	//�u���b�N����
	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//CTimer*pTimer =CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f,100.0f,0.0f),D3DXVECTOR2(30.0f,50.0f));

	//�Q�[�W�̃t���[��UI����
	CGauge_Fream* pGauge_Fream = CGauge_Fream::Create(D3DXVECTOR3(980.0f,80.0f,0.0f),D3DXVECTOR2(280.0f,120.0f));

	//�n�ʐ���
	CField* pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//�v���C���[����
	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//�v���C���[����
	//CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	//�G�l�~�[����
	CEnemy* pEnemy = CEnemy::Create(D3DXVECTOR3(-100.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL);
	pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL);
	pEnemy = CEnemy::Create(D3DXVECTOR3(300.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLOW);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CGame::Uninit()
{
	CObject::ReleaseAll();
}

//=============================================
//�X�V
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetCamera();

		pCamera->ResetCamera();
	}

	if (m_bEdit)
	{
		m_pEdit->Update();
	}
	
	//if (m_bEdit == false)
	//{
		CObject::UpdateAll();
	//}

	if (CPlayer::m_PlayerDeath || CEnemy::m_nNumEnemy <= 0)
	{//�v���C���[�����ʂ��G�l�~�[��S���E������
		//�J�E���g���Z
		m_nResultDelay++;
		if (m_nResultDelay >= DELAY_CNT)
		{
			//�f�B���C�J�E���g���Z�b�g
			m_nResultDelay = 0;

			//���U���g�J��
			CManager::SetMode(CScene::MODE::MODE_RESULT);
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
	}
#endif // DEBUG


}

//=============================================
//�`��
//=============================================
void CGame::Draw()
{

}
