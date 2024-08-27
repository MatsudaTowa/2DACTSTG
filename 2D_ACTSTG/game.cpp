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

//エディット設定
CEdit* CGame::m_pEdit = nullptr;

//=============================================
//コンストラクタ
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//イニシャライザーでプライオリティ設定、エディットしてない状態に変更
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{

	if (m_pEdit == nullptr)
	{
		m_pEdit = new CEdit;
	}
	//ブロック生成
	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//CTimer*pTimer =CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f,100.0f,0.0f),D3DXVECTOR2(30.0f,50.0f));

	//ゲージのフレームUI生成
	CGauge_Fream* pGauge_Fream = CGauge_Fream::Create(D3DXVECTOR3(980.0f,80.0f,0.0f),D3DXVECTOR2(280.0f,120.0f));

	//地面生成
	CField* pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//プレイヤー生成
	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//プレイヤー生成
	//CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	//エネミー生成
	CEnemy* pEnemy = CEnemy::Create(D3DXVECTOR3(-100.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL);
	pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL);
	pEnemy = CEnemy::Create(D3DXVECTOR3(300.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLOW);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	CObject::ReleaseAll();
}

//=============================================
//更新
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
	{//プレイヤーが死ぬかエネミーを全部殺したら
		//カウント加算
		m_nResultDelay++;
		if (m_nResultDelay >= DELAY_CNT)
		{
			//ディレイカウントリセット
			m_nResultDelay = 0;

			//リザルト遷移
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
//描画
//=============================================
void CGame::Draw()
{

}
