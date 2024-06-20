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
	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	CField* pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f));

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
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
