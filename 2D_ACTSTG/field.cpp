//=============================================
//
//3DTemplate[field.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "field.h"
#include "manager.h"

//texパス
const std::string CField::TEXTURE_NAME = "data\\TEXTURE\\images (2).jpg";
//テクスチャ初期化
LPDIRECT3DTEXTURE9 CField::m_pTextureTemp = nullptr;

//=============================================
//コンストラクタ
//=============================================
CField::CField(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CField::~CField()
{
}

//=============================================
//初期化
//=============================================
HRESULT CField::Init()
{
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f,1.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CField::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CField::Update()
{
}

//=============================================
//描画
//=============================================
void CField::Draw()
{
	CObject3D::Draw();

}

//=============================================
//生成
//=============================================
CField* CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTexture* pTexture = CManager::GetTexture();

	CField* pField = new CField;
	if (pField != nullptr)
	{
		pField->SetPos(pos); //pos設定
		pField->SetSize(size); //サイズ設定
		pField->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
		pField->SetType(OBJECT_TYPE_FIELD); //タイプ設定
		pField->Init();
	}

	return pField;
}