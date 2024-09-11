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
const std::string CBullet::PANETRARING_TEXTURE_NAME ="data\\TEXTURE\\slash_test.png";
const std::string CBullet::ELEC_TEXTURE_NAME ="data\\TEXTURE\\elekball.png";

//=============================================
//コンストラクタ
//=============================================
CBullet::CBullet(int nPriority):CAttack_Manager(nPriority)
{
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
	
	//使用しているとき
	OnActive();

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
//使用されてる時の処理
//=============================================
void CBullet::OnActive()
{
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

		//埋まってるかのチェック変数
		bool bHitUnder = false;

		bHitUnder = HitGround();

		switch (m_Allegiance)
		{
		case BULLET_ALLEGIANCE_PLAYER:
			bHitCheck = HitEnemy();
			if (bHitCheck == true)
			{
				Uninit();
			}
			break;

		case BULLET_ALLEGIANCE_ENEMY:
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

		//当たり判定チェック
		bHitCheck = HitBlock();

		if (bHitCheck == true)
		{//当たってたら
			Uninit();
		}
	}
	else
	{
		//終了
		Uninit();
	}
}

//=============================================
//弾作成
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size
,int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type)
{
	CBullet* pBullet = nullptr;

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet = new CPanetRaring_Slash;
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet = new CElecBullet;
		break;

	default:
		break;
	}

	if (pBullet == nullptr) {return nullptr;}

	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos設定
	pBullet->SetSize(size); //サイズ設定
	pBullet->SetRot(rot);
	pBullet->m_move = move; //移動量代入
	pBullet->SetLife(nLife); //寿命代入
	pBullet->SetDamage(nDamage); //威力代入

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&PANETRARING_TEXTURE_NAME)));
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&ELEC_TEXTURE_NAME)));
		break;

	default:
		break;
	}
	pBullet->m_Allegiance = Allegiance; //弾の設定
	pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
	pBullet->Init();

	return pBullet;
}

//=============================================
//移動量取得
//=============================================
D3DXVECTOR3 CBullet::GetMove()
{
	return m_move;
}

//=============================================
//敵か自分か取得
//=============================================
CBullet::BULLET_ALLEGIANCE CBullet::GetBulletAllegiance()
{
	return m_Allegiance;
}

//=============================================
//コンストラクタ
//=============================================
CPanetRaring_Slash::CPanetRaring_Slash(int nPriority):CBullet(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CPanetRaring_Slash::~CPanetRaring_Slash()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPanetRaring_Slash::Init()
{
	//親クラスの初期化
	CBullet::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPanetRaring_Slash::Uninit()
{
	//親クラスの終了
	CBullet::Uninit();
}

//=============================================
//更新
//=============================================
void CPanetRaring_Slash::Update()
{
	//親クラスの更新
	CBullet::Update();

	//体力取得
	int nLife = GetLife();

	if (nLife > 0)
	{//ライフがあれば処理実行

		//埋まってるかのチェック変数
		bool bHitUnder = false;

		bHitUnder = HitGround();
	}
}

//=============================================
//描画
//=============================================
void CPanetRaring_Slash::Draw()
{
	//親クラスの描画
	CBullet::Draw();
}


//=============================================
//コンストラクタ
//=============================================
CElecBullet::CElecBullet(int nPriority) :CBullet(nPriority),m_Electype(CElecBullet::ELECTYPE::TYPE_NONE)
{//イニシャライザーでプライオリティ設定、タイプ初期化
}

//=============================================
//デストラクタ
//=============================================
CElecBullet::~CElecBullet()
{
}

//=============================================
//初期化
//=============================================
HRESULT CElecBullet::Init()
{
	//親クラスの初期化
	CBullet::Init();

	//スタンバイ状態に
	m_Electype = CElecBullet::ELECTYPE::TYPE_STAND_BY;

	return S_OK;
}

//=============================================
//終了
//=============================================
void CElecBullet::Uninit()
{
	//親クラスの終了
	CBullet::Uninit();
}

//=============================================
//更新
//=============================================
void CElecBullet::Update()
{
	if (m_Electype == CElecBullet::ELECTYPE::TYPE_MOVE)
	{
		SetMove(D3DXVECTOR3(-3.0f,0.0f,0.0f));
		//親クラスの更新
		CBullet::Update();
	}
	else if (m_Electype == CElecBullet::ELECTYPE::TYPE_STAND_BY)
	{
		//使用しているとき
		OnActive();
	}
}

//=============================================
//描画
//=============================================
void CElecBullet::Draw()
{
	//親クラスの描画
	CBullet::Draw();
}

//=============================================
//生成
//=============================================
CElecBullet* CElecBullet::ElecCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife, int nDamage, BULLET_ALLEGIANCE Allegiance, BULLET_TYPE type)
{
	CElecBullet* pBullet = new CElecBullet;

	if (pBullet == nullptr) { return nullptr; }

	CTexture* pTexture = CManager::GetTexture();

	pBullet->SetPos(pos); //pos設定
	pBullet->SetSize(size); //サイズ設定
	pBullet->SetRot(rot);
	pBullet->SetLife(nLife); //寿命代入
	pBullet->SetDamage(nDamage); //威力代入

	switch (type)
	{
	case CBullet::BULLET_TYPE::BULLET_TYPE_PANETRARING_SLASH:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&PANETRARING_TEXTURE_NAME)));
		break;

	case CBullet::BULLET_TYPE::BULLET_TYPE_ELECBULLET:
		pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&ELEC_TEXTURE_NAME)));
		break;

	default:
		break;
	}
	pBullet->SetBulletAllegiance(Allegiance); //弾の設定
	pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
	pBullet->Init();

	return pBullet;
}

void CElecBullet::SetElecType(ELECTYPE type)
{
	m_Electype = type;
}
