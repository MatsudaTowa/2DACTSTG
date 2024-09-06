//=============================================
//
//3DTemplate[title.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "title.h"
#include "title_screen.h"
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
#include "manager.h"
#include "sound.h"

//=============================================
//コンストラクタ
//=============================================
CTitle::CTitle()
{
}

//=============================================
//デストラクタ
//=============================================
CTitle::~CTitle()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTitle::Init()
{
    //地面生成
    CField* pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

    //プレイヤー生成
    pPlayer = new CPlayer;  
    pPlayer->SetPlayer(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
    
    CSound*pSound = CManager::GetSound();

    pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM_TITLE);

    return S_OK;
}

//=============================================
//終了
//=============================================
void CTitle::Uninit()
{
    CSound* pSound = CManager::GetSound();
    //サウンドの停止
    pSound->StopSound();
    CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CTitle::Update()
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
//描画
//=============================================
void CTitle::Draw()
{
}
