//=============================================
//
//3DTemplate[block.h]
//Auther Matsuda Towa
//
//=============================================
#include "block.h"
#include "manager.h"
#include "player.h"

//モデルパス
const std::string CBlock::MODEL_NAME = "data\\MODEL\\box.x";

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CBlock::m_pTextureTemp = nullptr;

LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;

LPD3DXMESH CBlock::m_pMesh = nullptr;

DWORD CBlock::m_dwNumMat = 0;

//=============================================
//コンストラクタ
//=============================================
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CBlock::~CBlock()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBlock::Init()
{
	//親クラスの初期化処理
	CObjectX::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBlock::Uninit()
{
	//親クラスの終了処理
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CBlock::Update()
{
	//親クラスの更新処理
	CObjectX::Update();
}

//=============================================
//描画
//=============================================
void CBlock::Draw()
{
	//親クラスの描画処理
	CObjectX::Draw();
}

//=============================================
//ブロック生成
//=============================================
CBlock* CBlock::Create(BLOCKTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, bool bBreak)
{

	CBlock* pBlock = new CBlock;
	if (pBlock == nullptr) {return nullptr;}
	
	CModel* pModel = CManager::GetModel();

	pBlock->m_type = type;
	pBlock->SetPos(pos); //pos設定
	pBlock->SetRot(rot); //pos設定
	pBlock->m_nLife = nLife; //寿命代入
	pBlock->m_bBreak = bBreak; //壊せるかどうか
	//pBlock->BindTexture(m_pTextureTemp);

	//Xファイル読み込み
	pBlock->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	pBlock->SetType(OBJECT_TYPE_BLOCK); //タイプ設定
	pBlock->Init();
	

	return pBlock;
}

//=============================================
//当たり判定
//=============================================
void CBlock::HitBlock()
{
	//D3DXVECTOR3 pos = GetPos();

	////サイズ取得
	//D3DXVECTOR3 minpos = GetMinPos();
	//D3DXVECTOR3 maxpos = GetMaxPos();

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	//オブジェクト取得
	//	CObject* pObj = CObject::Getobject(4, nCnt);
	//	if (pObj != nullptr)
	//	{//ヌルポインタじゃなければ
	//		//タイプ取得
	//		CObject::OBJECT_TYPE type = pObj->GetType();
	//		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
	//		{
	//			CPlayer* pPlayer = (CPlayer*)pObj;
	//			pPlayer->GetPos(); //位置取得

	//			//サイズ取得
	//			pPlayer->GetMinPos();
	//			pPlayer->GetMaxPos();
	//			if (Bulletpos.x - Bulletsize.x >= pPlayer->GetPos().x - pPlayer->GetMinPos().x
	//				&& Bulletpos.x + Bulletsize.x <= pPlayer->GetPos().x + pPlayer->GetMaxPos().x
	//				&& Bulletpos.y - Bulletsize.y >= pPlayer->GetPos().z - pEnemy->GetSize().y
	//				&& Bulletpos.y + Bulletsize.y <= pPlayer->GetPos().z + pEnemy->GetSize().y)
	//			{//敵と弾が当たった時
	//				pEnemy->HitBullet();
	//				//弾の削除
	//				Release();
	//				CExplosion* pExplosion = CExplosion::Create(Bulletpos, D3DXVECTOR2(20.0f, 20.0f));
	//			}
	//		}
	//	}
	//}
}



