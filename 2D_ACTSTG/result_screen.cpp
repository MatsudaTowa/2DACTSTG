//=============================================
//
//3DTemplate[result_Screen.h]
//Auther Matsuda Towa
//
//=============================================
#include "result_screen.h"
#include "manager.h"

//texパス
const std::string CResult_Screen::TEXTURE_NAME = "data\\TEXTURE\\result_test.png";

//=============================================
//コンストラクタ
//=============================================
CResult_Screen::CResult_Screen(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CResult_Screen::~CResult_Screen()
{
}

//=============================================
//初期化
//=============================================
HRESULT CResult_Screen::Init()
{
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//サイズを代入
	SetSize(size);

	//頂点設定
	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CResult_Screen::Uninit()
{
	CObject2D::Uninit();

}

//=============================================
//更新
//=============================================
void CResult_Screen::Update()
{
}

//=============================================
//描画
//=============================================
void CResult_Screen::Draw()
{
	CObject2D::Draw();
}

//=============================================
//生成
//=============================================
CResult_Screen* CResult_Screen::Create(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetTexture();
	CResult_Screen* pResult_Screen = new CResult_Screen;
	//CObject *pObject = Getobject();
	if (pResult_Screen != nullptr)
	{
		pResult_Screen->SetPos(pos); //pos設定

		pResult_Screen->SetType(OBJECT_TYPE_RESULT); //タイプ設定

		pResult_Screen->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

		pResult_Screen->Init();

	}
	return pResult_Screen;
}
