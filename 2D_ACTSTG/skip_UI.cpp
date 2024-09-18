//=============================================
//
//スキップUI[skip_UI.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "skip_UI.h"
#include "manager.h"
#include "object.h"

//texパス
const std::string CSkip_UI::BUTTON_A_TEXTURE_NAME = "data\\TEXTURE\\skip_A.png";
const std::string CSkip_UI::BUTTON_ENTER_TEXTURE_NAME = "data\\TEXTURE\\skip_enter.png";

//=============================================
//コンストラクタ
//=============================================
CSkip_UI::CSkip_UI(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CSkip_UI::~CSkip_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSkip_UI::Init()
{

	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(D3DXVECTOR2(1.0f, 1.0f));

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSkip_UI::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CSkip_UI::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();
}

//=============================================
//描画
//=============================================
void CSkip_UI::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CSkip_UI* CSkip_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CTexture* pTexture = CManager::GetTexture();
	CSkip_UI* pSkip_UI = new CSkip_UI;

	//nullならnullを返す
	if (pSkip_UI == nullptr) { return nullptr; }

	pSkip_UI->SetPos(pos); //pos設定

	pSkip_UI->SetSize(size); //size設定

	pSkip_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&BUTTON_ENTER_TEXTURE_NAME)));

	pSkip_UI->SetType(OBJECT_TYPE_TUTORIAL); //タイプ設定

	pSkip_UI->Init();

	return pSkip_UI;
}
