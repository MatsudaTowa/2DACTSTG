//=============================================
//
//攻撃管理クラス[attack_manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "enemy.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CAttack_Manager::CAttack_Manager(int nPriority) : CBillboard(nPriority),m_nLife(0),m_nDamage(0)
{//イニシャライザーでプライオリティ設定、体力とダメージ初期化
}

//=============================================
//デストラクタ
//=============================================
CAttack_Manager::~CAttack_Manager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CAttack_Manager::Init()
{
	//親クラスの初期化
	CObject3D::Init();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CAttack_Manager::Uninit()
{
	//親クラスの終了処理
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CAttack_Manager::Update()
{
	//親クラスの更新処理
	CObject3D::Update();

	if (m_nLife > 0)
	{
		m_nLife--;
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
void CAttack_Manager::Draw()
{
	//親クラスの描画処理
	CObject3D::Draw();
}

//=============================================
//攻撃当たり判定(エネミー)
//=============================================
void CAttack_Manager::HitEnemy()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
			{
				CEnemy* pEnemy = (CEnemy*)pObj;

				if (Attackpos.x + Attacksize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
					&& Attackpos.x - Attacksize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x)
				{
					if (Attackpos.z - Attacksize.z< pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& Attackpos.z + Attacksize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& Attackpos.y - Attacksize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//当たり判定(X)
						pEnemy->Damage(m_nDamage);
						//近接攻撃の削除
						Uninit();
					}
				}


				else if (Attackpos.z + Attacksize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
					&& Attackpos.z - Attacksize.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z)
				{
					if (Attackpos.x - Attacksize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& Attackpos.x + Attacksize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& Attackpos.y - Attacksize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//当たり判定(Z)
						pEnemy->Damage(m_nDamage);
						//近接攻撃の削除
						Uninit();
					}
				}
			}
		}
	}
}

//=============================================
//攻撃当たり判定(プレイヤー)
//=============================================
void CAttack_Manager::HitPlayer()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;

				if (Attackpos.x + Attacksize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
					&& Attackpos.x - Attacksize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x)
				{
					if (Attackpos.z - Attacksize.z< pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& Attackpos.z + Attacksize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
						&& Attackpos.y - Attacksize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
					{//当たり判定(X)
						pPlayer->Damage(m_nDamage);
						//近接攻撃の削除
						Uninit();
					}
				}


				else if (Attackpos.z + Attacksize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
					&& Attackpos.z - Attacksize.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z)
				{
					if (Attackpos.x - Attacksize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x
						&& Attackpos.x + Attacksize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
						&& Attackpos.y - Attacksize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Attackpos.y + Attacksize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y
						)
					{//当たり判定(Z)
						pPlayer->Damage(m_nDamage);
						//近接攻撃の削除
						Uninit();
					}
				}
			}
		}
	}
}

//=============================================
//体力取得
//=============================================
int CAttack_Manager::GetLife()
{
	return m_nLife;
}

//=============================================
//ダメージ取得
//=============================================
int CAttack_Manager::GetDamage()
{
	return m_nDamage;
}
