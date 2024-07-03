//=============================================
//
//ゲージ管理[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "gauge.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CGauge::CGauge(int nPriority):CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge::~CGauge()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge::Init()
{
    //親クラスの初期化を呼ぶ
    CObject2D::Init();

    //頂点設定
    SetVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

    return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge::Uninit()
{
    //親クラスの終了呼ぶ
    CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge::Update()
{
    //親クラスの更新呼ぶ
    CObject2D::Update();
}

//=============================================
//描画
//=============================================
void CGauge::Draw()
{
    //親クラスの描画呼ぶ
    CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
    CTexture* pTexture = CManager::GetTexture();
    CGauge* pGauge = new CGauge;

    // nullならnullを返す
    if (pGauge == nullptr) { return nullptr; }

    pGauge->SetPos(pos); //pos設定

    pGauge->SetSize(size); //size設定

    pGauge->SetType(OBJECT_TYPE_GAUGE); //タイプ設定

    //pGauge->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

    pGauge->Init();
}
