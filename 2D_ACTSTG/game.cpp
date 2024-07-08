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
//#include "bg.h"
#include "bullet.h"
//#include "explosion.h"
#include "effect.h"
#include "gauge_fream.h"
#include "enemy.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CGame::CGame()
{
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
	//ブロック生成
	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//ゲージのフレームUI生成
	CGauge_Fream* pGauge_Fream = CGauge_Fream::Create(D3DXVECTOR3(980.0f,80.0f,0.0f),D3DXVECTOR2(280.0f,120.0f));

	//地面生成
	CField* pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));

	//プレイヤー生成
	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エネミー生成
	CEnemy* pEnemy = CEnemy::Create(D3DXVECTOR3(-100.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL);
	pEnemy = CEnemy::Create(D3DXVECTOR3(100.0f, 10.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL);
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
	CObject::UpdateAll();

	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
	}
}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}
