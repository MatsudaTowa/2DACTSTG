//=============================================
//
//3DTemplate[bullet.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "bullet.h"
#include "manager.h"
#include "effect.h"
#include "enemy.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;
const std::string CBullet::TEXTURE_NAME ="data\\TEXTURE\\slash_test.png";

//=============================================
//コンストラクタ
//=============================================
CBullet::CBullet(int nPriority):CAttack_Manager(nPriority)
{//イニシャライザーでライフとダメージ初期化
	
}

//=============================================
//デストラクタ
//=============================================
CBullet::~CBullet()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBullet::Init()
{
	//親クラスの初期化
	CAttack_Manager::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBullet::Uninit()
{
	//親クラスの終了
	CAttack_Manager::Uninit();
}

//=============================================
//更新
//=============================================
void CBullet::Update()
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
		switch (m_type)
		{
		case BULLET_TYPE_PLAYER:
			HitEnemy();
			break;

		case BULLET_TYPE_ENEMY:
			HitPlayer();
			break;

		default:
			assert(false);
			break;
		}
		HitBlock();

	}
}

//=============================================  
//描画
//=============================================
void CBullet::Draw()
{
	//親クラスの描画
	CAttack_Manager::Draw();
}

//=============================================
//弾作成
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife, int nDamage, BULLET_TYPE type)
{
	CBullet* pBullet = new CBullet;

	if (pBullet == nullptr) {return nullptr;}
	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos設定
	pBullet->SetSize(size); //サイズ設定
	pBullet->SetRot(rot);
	pBullet->m_move = move; //移動量代入
	pBullet->SetLife(nLife); //寿命代入
	pBullet->SetDamage(nDamage); //威力代入
    pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	pBullet->m_type = type; //弾の設定
	pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
	pBullet->Init();

	return pBullet;
}

