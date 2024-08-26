//=============================================
//
//攻撃管理クラス[attack_manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "attack_manager.h"
#include "enemy.h"
#include "colision.h"
#include "player.h"
#include "block.h"

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
	//SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

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
bool CAttack_Manager::HitEnemy()
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

				CColision::COLISION ColisionCheck = CColision::CheckItemColision(Attackpos, Attacksize, pEnemy->GetPos(),pEnemy->GetMinPos(),pEnemy->GetMaxPos());

				if (ColisionCheck != CColision::COLISION::COLISON_NONE)
				{//当たってたら
					pEnemy->Damage(m_nDamage);
					return true;
				}
			}
		}
	}
}

//=============================================
//攻撃当たり判定(プレイヤー)
//=============================================
bool CAttack_Manager::HitPlayer()
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

				CColision::COLISION ColisionCheck = CColision::CheckItemColision(Attackpos, Attacksize, pPlayer->GetPos(), pPlayer->GetMinPos(), pPlayer->GetMaxPos());

				if (ColisionCheck != CColision::COLISION::COLISON_NONE)
				{//当たってたら
					#ifdef _DEBUG
					break;
					#endif // _DEBUG

					pPlayer->Damage(m_nDamage);
					return true;
				}

			}
		}
	}
}

//=============================================
//攻撃当たり判定(ブロック)
//=============================================
bool CAttack_Manager::HitBlock()
{
	//位置取得
	D3DXVECTOR3 Attackpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Attacksize = GetSize();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//敵との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;

				CColision::COLISION ColisionCheck = CColision::CheckItemColision(Attackpos, Attacksize, pBlock->GetPos(), pBlock->GetMinPos(), pBlock->GetMaxPos());

				if (ColisionCheck != CColision::COLISION::COLISON_NONE)
				{//当たってたら
					//攻撃の削除
					return true;
				}
				else
				{
					return false;
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
