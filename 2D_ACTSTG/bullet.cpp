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
const std::string CBullet::TEXTURE_NAME ="data\\TEXTURE\\slash.png";

//=============================================
//コンストラクタ
//=============================================
CBullet::CBullet(int nPriority):CBillboard(nPriority)
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
	//サイズ取得
	D3DXVECTOR3 size = GetSize();

	//対角線
	m_fLength = sqrtf(size.x * size.x + size.y * size.y);

	//角度
	m_fAngle = atan2f(size.x, size.y);

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}

//=============================================
//終了
//=============================================
void CBullet::Uninit()
{
	//親クラスの終了
	CObject3D::Uninit();
}

//=============================================
//更新
//=============================================
void CBullet::Update()
{
	if (m_nLife > 0)
	{//ライフがあれば処理実行
		m_nLife--;
		D3DXVECTOR3 pos = GetPos();
		//CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 8.0f, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);
		pos += m_move;
		//座標を更新
		SetPos(pos);
		//頂点座標
		SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//当たったかチェック
		HitBullet();
	}
	else
	{
		Uninit();
		//CExplosion*pExplosion = CExplosion::Create(pos,D3DXVECTOR2(20.0f,20.0f));
	}
}

//=============================================  
//描画
//=============================================
void CBullet::Draw()
{
	//親クラスの描画
	CObject3D::Draw();
}

//=============================================
//弾作成
//=============================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife)
{
	CBullet* pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		CTexture* pTexture = CManager::GetTexture();

		pBullet->SetPos(pos); //pos設定
		pBullet->SetSize(size); //サイズ設定
		pBullet->SetRot(rot);
		pBullet->m_move = move; //移動量代入
		pBullet->m_nLife = nLife; //寿命代入
     	pBullet->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
		pBullet->SetType(OBJECT_TYPE_BULLET); //タイプ設定
		pBullet->Init();
	}

	return pBullet;
}

//=============================================
//弾の当たり判定
//=============================================
void CBullet::HitBullet()
{
	D3DXVECTOR3 Bulletpos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Bulletsize = GetSize();

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


				if (Bulletpos.x + Bulletsize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
					&&Bulletpos.x - Bulletsize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x)
				{
					if (Bulletpos.z - Bulletsize.z< pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& Bulletpos.z + Bulletsize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& Bulletpos.y - Bulletsize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Bulletpos.y + Bulletsize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//当たり判定(X)
						pEnemy->HitBullet();
						//弾の削除
						Uninit();
					}
				}


				else if (Bulletpos.z + Bulletsize.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
					&&Bulletpos.z - Bulletsize.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z)
				{
					if (Bulletpos.x - Bulletsize.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& Bulletpos.x + Bulletsize.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& Bulletpos.y - Bulletsize.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& Bulletpos.y + Bulletsize.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//当たり判定(Z)
						pEnemy->HitBullet();
						//弾の削除
						Uninit();
					}
				}
			}

				//CEnemy* pEnemy = (CEnemy*)pObj;
				//pEnemy->GetPos(); //位置取得
				//pEnemy->GetSize(); //サイズ取得
				//if (Bulletpos.x - Bulletsize.x >= pEnemy->GetPos().x - pEnemy->GetSize().x
				//	&& Bulletpos.x + Bulletsize.x <= pEnemy->GetPos().x + pEnemy->GetSize().x
				//	&& Bulletpos.y - Bulletsize.y >= pEnemy->GetPos().y - pEnemy->GetSize().y
				//	&& Bulletpos.y + Bulletsize.y <= pEnemy->GetPos().y + pEnemy->GetSize().y)
				//{//敵と弾が当たった時
				//	pEnemy->HitBullet();
				//	//弾の削除
				//	Release();
				//}
			
		}
	}
}
