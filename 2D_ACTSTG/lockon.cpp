//=============================================
//
//照準[lockon.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "lockon.h"
#include "manager.h"

//texパス
const std::string CLockOn::TEXTURE_NAME = "data\\TEXTURE\\lockon.png";

//=============================================
//コンストラクタ
//=============================================
CLockOn::CLockOn(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CLockOn::~CLockOn()
{
}

//=============================================
//初期化
//=============================================
HRESULT CLockOn::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), m_col);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CLockOn::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CLockOn::Update()
{
	//親クラスの更新
	CObject3D::Update();
}

//=============================================
//描画
//=============================================
void CLockOn::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//生成
//=============================================
CLockOn* CLockOn::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	CLockOn* pLockOn = new CLockOn;

	// nullならnullを返す
	if (pLockOn == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	pLockOn->SetPos(pos); //pos設定

	pLockOn->SetSize(size); //サイズ設定

	pLockOn->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャの設定

	pLockOn->m_col = col; //カラーの設定

	pLockOn->SetType(OBJECT_TYPE_LOCKON); //オブジェクトのタイプ設定

	pLockOn->Init(); //エフェクトの初期化処理

	return pLockOn;
}
