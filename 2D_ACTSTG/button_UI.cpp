#include "button_UI.h"
#include "manager.h"

//texパス
const std::string CButton_UI::TEXTURE_NAME_PAD_Y = "data\\TEXTURE\\acquisition_y.png";
const std::string CButton_UI::TEXTURE_NAME_KEYBOARD_F = "data\\TEXTURE\\acquisition_F.png";

//=============================================
//コンストラクタ
//=============================================
CButton_UI::CButton_UI(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CButton_UI::~CButton_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CButton_UI::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f,1.0f,1.0f,0.8f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CButton_UI::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CButton_UI::Update()
{
	//親クラスの更新
	CObject3D::Update();

	ChangeSize();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
}

//=============================================
//描画
//=============================================
void CButton_UI::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//サイズ変更
//=============================================
void CButton_UI::ChangeSize()
{
}

//=============================================
//生成
//=============================================
CButton_UI* CButton_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTON_TYPE type)
{
	CButton_UI* pButton_UI = new CButton_UI;

	// nullならnullを返す
	if (pButton_UI == nullptr) { return nullptr; }

	//テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	pButton_UI->SetPos(pos); //pos設定

	pButton_UI->SetSize(size); //サイズ設定

	switch (type)
	{
	case CButton_UI::BUTTON_TYPE::BUTTON_TYPE_PAD_Y:
		pButton_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_PAD_Y))); //テクスチャの設定	
		break;
	case CButton_UI::BUTTON_TYPE::BUTTON_TYPE_KEYBOARD_F:
		pButton_UI->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME_KEYBOARD_F))); //テクスチャの設定	
		break;
	default:
		break;
	}

	pButton_UI->SetType(OBJECT_TYPE_BUTTON_UI); //オブジェクトのタイプ設定

	pButton_UI->Init(); //エフェクトの初期化処理

	return pButton_UI;
}
