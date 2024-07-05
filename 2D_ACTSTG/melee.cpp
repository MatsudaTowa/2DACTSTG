//=============================================
//
//近接攻撃[melee.h]
//Auther Matsuda Towa
//
//=============================================
#include "melee.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CMelee::CMelee(int nPriority) :CObject3D(nPriority),m_nLife(0)
{
}

//=============================================
//デストラクタ
//=============================================
CMelee::~CMelee()
{
}

//=============================================
//初期化
//=============================================
HRESULT CMelee::Init()
{
	//親クラスの初期化
	CObject3D::Init();
	
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//対角線
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//角度
	m_fAngle = atan2f(size.x, size.y);

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}


//=============================================
//終了
//=============================================
void CMelee::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CMelee::Update()
{
	//親クラスの更新
	CObject3D::Update();

	if (m_nLife > 0)
	{//ライフがあれば処理実行
		m_nLife--;

		for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);

			if (pObj != nullptr)
			{//ヌルポインタじゃなければ
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
				{
					CPlayer* pPlayer = (CPlayer*)pObj;

					//自分自身のpos取得
					D3DXVECTOR3 pos = GetPos();

					//プレイヤーのposを自分に代入
					pos.y = pPlayer->GetPos().y + pPlayer->GetMaxPos().y * 0.5f;
					pos.z = pPlayer->GetPos().z;

					if (pPlayer->GetWay() == true)
					{//右向いてるなら
						pos.x = pPlayer->GetPos().x + pPlayer->GetMaxPos().x;
					}
					else if (pPlayer->GetWay() == false)
					{//左向いてるなら
						pos.x = pPlayer->GetPos().x + pPlayer->GetMinPos().x;
					}
					//posを代入
					SetPos(pos);
				}
			}

		}

		//当たったかチェック
		HitMelee();
	}
	else
	{//ライフがなくなったら
		//終了処理
		Uninit();
	}
}

//=============================================  
//描画
//=============================================
void CMelee::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//近接攻撃作成
//=============================================
CMelee* CMelee::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife)
{
	CMelee* pMelee = new CMelee;
	//nullならnullを返す
   if(pMelee ==nullptr) {return nullptr;}

   pMelee->SetPos(pos); //pos設定
   pMelee->SetSize(size); //サイズ設定
   pMelee->SetRot(rot); //方向設定
   pMelee->m_nLife = nLife; //寿命代入

   pMelee->SetType(OBJECT_TYPE_MELEE); //タイプ設定

   pMelee->Init(); //初期化

   return pMelee;
 }

//=============================================
//近接攻撃の当たり判定
//=============================================
void CMelee::HitMelee()
{
	//位置取得
	D3DXVECTOR3 Meleepos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Meleesize = GetSize();

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

				if (Meleepos.x + Meleesize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
					&& Meleepos.x - Meleesize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x)
				{
					if (Meleepos.z - Meleesize.z< pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& Meleepos.z + Meleesize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& Meleepos.y - Meleesize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Meleepos.y + Meleesize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//当たり判定(X)
						pEnemy->HitDamage(1);
						//近接攻撃の削除
						Uninit();
					}
				}


				else if (Meleepos.z + Meleesize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
					&& Meleepos.z - Meleesize.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z)
				{
					if (Meleepos.x - Meleesize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& Meleepos.x + Meleesize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& Meleepos.y - Meleesize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Meleepos.y + Meleesize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//当たり判定(Z)
						pEnemy->HitDamage(1);
						//近接攻撃の削除
						Uninit();
					}
				}
			}
		}
	}
}
