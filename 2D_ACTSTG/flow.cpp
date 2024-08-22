//=============================================
//
//集中斬撃[flow.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "flow.h"
#include "renderer.h"
#include"manager.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CFlow::m_pTextureTemp = nullptr;
const std::string CFlow::TEXTURE_NAME = "data\\TEXTURE\\flow_test.png";

//=============================================
//コンストラクタ
//=============================================
CFlow::CFlow(int nPriority):CAttack_Manager(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CFlow::~CFlow()
{
}

//=============================================
//初期化
//=============================================
HRESULT CFlow::Init()
{
	//親クラスの初期化
	CAttack_Manager::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CFlow::Uninit()
{
	//親クラスの終了
	CAttack_Manager::Uninit();
}

//=============================================
//更新
//=============================================
void CFlow::Update()
{
	//親クラスの更新
	CAttack_Manager::Update();

	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//ライフがあれば処理実行
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		//座標を更新
		SetPos(pos);
		//頂点座標
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//当たり判定チェック変数
		bool bHitCheck = false;
		switch (m_type)
		{
		case FLOW_TYPE_PLAYER:
			bHitCheck = HitEnemy();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		case FLOW_TYPE_ENEMY:
			bHitCheck = HitPlayer();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		default:
			assert(false);
			break;
		}
	}
	else
	{
		//終了
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CFlow::Draw()
{
	//親クラスの描画
	CAttack_Manager::Draw();
}

//=============================================
//生成
//=============================================
CFlow* CFlow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,FLOW_TYPE type)
{
	CFlow* pFlow = new CFlow;

	if (pFlow == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pFlow->SetPos(pos); //pos設定
	pFlow->SetSize(size); //サイズ設定
	pFlow->SetRot(rot);
	pFlow->SetLife(nLife); //寿命代入
	pFlow->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pFlow->m_type = type; //弾の設定
	pFlow->SetType(OBJECT_TYPE_FLOW); //タイプ設定
	pFlow->Init();

	return pFlow;
}
