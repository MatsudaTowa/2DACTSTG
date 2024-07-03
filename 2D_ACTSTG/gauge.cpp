//=============================================
//
//ゲージ管理[gauge.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "gauge_fream.h"
#include "gauge.h"
#include "manager.h"

//ゲージの最大値
const float CGauge::MAX_GAUGE_WIDE = 370.0f;

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
	SetGaugeVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

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

	if (GetSize().x <= MAX_GAUGE_WIDE)
	{//最大値以下なら加算
		AddGauge();
	}

	//頂点設定
	SetGaugeVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
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
//ゲージ増加処理
//=============================================
void CGauge::AddGauge()
{
	//自分自身のサイズ取得
   D3DXVECTOR2 size = GetSize();

   size.x += 10.0f;

   //サイズ代入
   SetSize(size);
}

//=============================================
//ゲージ減少処理
//=============================================
void CGauge::SubGauge()
{

}

//=============================================
//ゲージの頂点生成
//=============================================
void CGauge::SetGaugeVtx(float rhw, D3DCOLOR col)
{
    CRenderer* pRender = CManager::GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

    if (GetVtxBuff() == nullptr)
    {
        pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &GetVtxBuff(), NULL);
    }
    VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得

	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x
		, GetPos().y + GetSize().y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y + GetSize().y
		, 0.0f);

	//rhwの設定
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	GetVtxBuff()->Unlock();
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
