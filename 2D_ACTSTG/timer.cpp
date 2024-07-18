#include "timer.h"
#include "manager.h"

//テクスチャパス
const std::string CTimer::TEXTURE_NAME = "data\\TEXTURE\\number_test.png";

//モデル設定
CNumber* CTimer::m_pNumber[NUM_DIGIT] = {};

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

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//ナンバー生成
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = new CNumber();
			m_pNumber[nCnt]->Init();
		}
		//頂点設定
		SetTimerVtx();
	}

	return S_OK;
}

//=============================================
//終了
//=============================================
void CTimer::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			delete m_pNumber[nCnt];
			m_pNumber[nCnt] = nullptr;
		}
	}

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

	CNumber::SetNumVtx(GetVtxBuff(),1.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT*0.5f,0.0f),D3DXVECTOR2(30.0f,50.0f),0.1f,0.2f);

	////頂点設定
	//SetTimerVtx();
}

//=============================================
//描画
//=============================================
void CTimer::Draw()
{
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
	pTimer->m_nCurrentTime = LIMIT_TIME;
	pTimer->Init();

	return pTimer;
}

//=============================================
//タイマー用の頂点生成
//=============================================
void CTimer::SetTimerVtx()
{

	D3DXVECTOR3 pos = GetPos();
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = m_nCurrentTime / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;
		m_pNumber[nCnt]->SetNumVtx(GetVtxBuff(),1.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), pos ,GetSize(),fMinTexU, fMaxTexU);

		//x座標をずらす
		pos.x += GetSize().x;
	}
}
