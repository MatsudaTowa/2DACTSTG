//=============================================
//
//アイテム処理[item.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "item.h"
#include "effect.h"
#include "manager.h"
#include "player.h"

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CItem::m_pTextureTemp = nullptr;
const std::string CItem::TEXTURE_NAME = "data\\TEXTURE\\item_book000.png";

//=============================================
//コンストラクタ
//=============================================
CItem::CItem(int nPriority):CBillboard(nPriority)
{
}
//=============================================
//デストラクタ
//=============================================
CItem::~CItem()
{
}

//=============================================
//初期化
//=============================================
HRESULT CItem::Init()
{
	//親クラスの初期化
	CBillboard::Init();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================
//終了
//=============================================
void CItem::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//=============================================
void CItem::Update()
{
	//親クラスの更新
	CBillboard::Update();

	HitItem();

}

//=============================================
//描画
//=============================================
void CItem::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
//生成
//=============================================
CItem* CItem::Create(ITEMTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	CItem* pItem = new CItem;

	if (pItem == nullptr) { return nullptr; }
	CTexture* pTexture = CManager::GetTexture();

	pItem->SetPos(pos); //pos設定
	pItem->SetSize(size); //size設定
	pItem->SetRot(rot); //rot設定

	pItem->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));	//テクスチャの設定

	pItem->SetType(OBJECT_TYPE_ITEM); //タイプ設定

	pItem->m_ItemType = type; //アイテムタイプ設定

	pItem->Init();
}

//=============================================
//当たり判定
//=============================================
void CItem::HitItem()
{
	//位置取得
	D3DXVECTOR3 Itempos = GetPos();
	//サイズ取得
	D3DXVECTOR3 Itemsize = GetSize();

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

				if (Itempos.x + Itemsize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
					&& Itempos.x - Itemsize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x)
				{
					if (Itempos.z - Itemsize.z< pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& Itempos.z + Itemsize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
						&& Itempos.y - Itemsize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Itempos.y + Itemsize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
					{//当たり判定(X)
						pPlayer->m_Attack = CPlayer::PLAYER_ATTACK_PANETRARING_SLASH;
						//アイテムの削除
						Uninit();
					}
				}


				else if (Itempos.z + Itemsize.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
					&& Itempos.z - Itemsize.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z)
				{
					if (Itempos.x - Itemsize.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x
						&& Itempos.x + Itemsize.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
						&& Itempos.y - Itemsize.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& Itempos.y + Itemsize.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y
						)
					{//当たり判定(Z)
						pPlayer->m_Attack = CPlayer::PLAYER_ATTACK_PANETRARING_SLASH;
						//アイテムの削除
						Uninit();
					}
				}
			}
		}
	}
}
