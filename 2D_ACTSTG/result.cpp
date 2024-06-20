//=============================================
//
//3DTemplate[result.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "result.h"
#include "result_screen.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CResult::CResult()
{
}

//=============================================
//デストラクタ
//=============================================
CResult::~CResult()
{
}

//=============================================
//初期化
//=============================================
HRESULT CResult::Init()
{
    CResult_Screen* pResult_Screen = CResult_Screen::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f));
    return S_OK;
}

//=============================================
//終了
//=============================================
void CResult::Uninit()
{
    CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CResult::Update()
{
    CObject::UpdateAll();
    CInputKeyboard* pKeyboard = CManager::GetKeyboard();
    if (pKeyboard->GetTrigger(DIK_RETURN))
    {
        CManager::SetMode(CScene::MODE::MODE_TITLE);
    }
}

//=============================================
//描画
//=============================================
void CResult::Draw()
{
}
