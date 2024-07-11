#include "timer.h"
#include "manager.h"

//テクスチャパス
const std::string CTimer::TEXTURE_NAME = "data\\TEXTURE\\number_test.png";

//=============================================
//コンストラクタ
//=============================================
CTimer::CTimer(int nPriority):CObject2D(nPriority), m_nFrameCnt(0),m_nCurrentTime(0)
{//イニシャライザーでプライオリティ設定、フレームカウントと今の時間を初期化
}

//=============================================
//デストラクタ
//=============================================
CTimer::~CTimer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTimer::Init()
{
	//親クラスの初期化
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(0.1f, 1.0f));

	//頂点設定
	SetTimerVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTimer::Uninit()
{
	//親クラスの終了
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CTimer::Update()
{
	//親クラスの更新
	CObject2D::Update();

	m_nFrameCnt++;

	if (m_nFrameCnt >= 60)
	{
		m_nCurrentTime++;
		m_nFrameCnt = 0;
	}



	//頂点設定
	SetTimerVtx(1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}

//=============================================
//描画
//=============================================
void CTimer::Draw()
{
	//親クラスの描画
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTimer*pTimer = new CTimer();

	//nullならnullを返す
	if(pTimer == nullptr) {return nullptr;}

	CTexture* pTexture = CManager::GetTexture();

	pTimer->SetPos(pos); //pos代入
	pTimer->SetSize(size); //size代入
	pTimer->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pTimer->SetType(OBJECT_TYPE_TIMER); //タイプ設定
	pTimer->Init();

	return pTimer;
}

//=============================================
//タイマー用の頂点生成
//=============================================
void CTimer::SetTimerVtx(float rhw, D3DCOLOR col)
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
	pVtx[0].pos = D3DXVECTOR3(GetPos().x - GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GetPos().x + GetSize().x
		, GetPos().y - GetSize().y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GetPos().x - GetSize().x
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


	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];
	int One = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		a_PosTexU[nCnt] = m_nCurrentTime / One % 10;
		One *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		float fDigit0, fDigit1;
		fDigit0 = a_PosTexU[nCnt] * 0.1f;
		fDigit1 = fDigit0 + 0.1f;
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(fDigit0, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fDigit1, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fDigit0, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fDigit1, 1.0f);
	}

	//アンロック
	GetVtxBuff()->Unlock();
}
