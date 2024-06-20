//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "field.h"

//モデルパス
const std::string CPlayer::MODEL_NAME = "data\\MODEL\\sphere.x";

//通常の移動速度
const float CPlayer::DEFAULT_MOVE = 0.5f;
//通常の移動速度
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CPlayer::DEFAULT_JUMP = 22.0f;

//ジャンプ回数
const int CPlayer::MAX_JUMPCNT = 2;

//当たり判定補正値
const float CPlayer::COLISION_CORRECTION = 15.5f;

//重力値
const float CPlayer::GRAVITY_MOVE = 0.8f;
//重力最大値
const float CPlayer::GRAVITY_MAX = 32.0f;

//プレイヤーをリスポーンされる座標
const float CPlayer::DEADZONE_Y = -100.0f;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;
//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority):CObjectX(nPriority),m_nJumpCnt(0)
{//イニシャライザーでジャンプカウント初期化
	m_bLanding = false; //着地
}

//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	LPDIRECT3DTEXTURE9 pTex;
	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\PlayerAnimation.png",
	//	&pTex);

	//CObjectX::BindTexture(pTex);


	m_bSize = false;

	//移動量初期化
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	return S_OK;
}


//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	//if (m_bLanding != true)
	//{//着地してなかったら重力処理実行
		Gravity();
	//}

	PlayerMove();

	D3DXVECTOR3 pos = GetPos();

	//移動量を更新(減速）
	m_move *= 1.0f - DAMPING_COEFFICIENT;

	m_oldpos = pos;

	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x,pos.y + 8.0f,pos.z), D3DXVECTOR3(10.0f, 10.0f ,0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);

	pos += m_move;

	//座標を更新
	SetPos(pos);

	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();
	
	HitBlock(m_oldpos);

	if (pos.y < DEADZONE_Y)
	{//リスポーン処理
		ReSpawn();
	}
	
	//Turn(); //回転処理
	//SizeChange(); //拡縮

	CInputMouse* pMouse = CManager::GetMouse();

	if (pMouse->GetTrigger(0))
	{
		CBullet*pBullet = CBullet::Create(pos, D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
										D3DXVECTOR3(10.0f,10.0f,0.0f),30);
	}

}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CModel* pModel = CManager::GetModel();

	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //pos設定
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);
	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定
	pPlayer->Init();
	
	return pPlayer;
}

//=============================================
//リスポーン
//=============================================
void CPlayer::ReSpawn()
{
	D3DXVECTOR3 PlayerPos = GetPos();
	PlayerPos = D3DXVECTOR3(50.0f, 0.5f, 0.0f);
	SetPos(PlayerPos);
}

//=============================================
//重力処理
//=============================================
void CPlayer::Gravity()
{
	if (m_move.y < GRAVITY_MAX)
	{
		m_move.y -= GRAVITY_MOVE;
	}
}

//=============================================
//移動処理
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += 1.0f;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= 1.0f;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += 1.0f;
	}


	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		m_move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		m_move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		//rot.x = rotMoveY + D3DX_PI;
		//rotを代入
		SetRot(rot);
		//if (g_Player.rot.y <= -D3DX_PI)
		//{
		//	g_Player.rot.y = D3DX_PI;
		//}
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//ジャンプ数以下だったら
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			m_move.y = DEFAULT_JUMP;
			m_bLanding = false; //空中
			m_nJumpCnt++; //ジャンプ数加算
		}
	}

}

//=============================================
//回転
//=============================================
void CPlayer::Turn()
{
	//オブジェクト2Dからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.z += 0.05f;

	if (rot.z >= D3DX_PI)
	{
		rot.z = -D3DX_PI;
	}
	
	//rotを代入
	SetRot(rot);
}

//=============================================
//拡縮
//=============================================
void CPlayer::SizeChange()
{
	//オブジェクト2Dからsizeを取得

}

//=============================================
//当たり判定
//=============================================
void CPlayer::HitBlock(D3DXVECTOR3 oldpos)
{
	D3DXVECTOR3 PlayerPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 PlayerMin = GetMinPos();
	D3DXVECTOR3 PlayerMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CBlock::BLOCK_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//ブロックとの当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_BLOCK)
			{
				CBlock* pBlock = (CBlock*)pObj;
				if (oldpos.x + PlayerMax.x <= pBlock->GetPos().x + pBlock->GetMinPos().x 
					&&PlayerPos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x)
				{
					if (oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
						&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
					{//当たり判定(X)
						PlayerPos.x = oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (oldpos.x + PlayerMin.x >= pBlock->GetPos().x + pBlock->GetMaxPos().x
					&& PlayerPos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x)
				{
					 if (oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z 
					&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z 
					&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y 
					&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y )
					{//当たり判定(X)
						PlayerPos.x = oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (oldpos.z + PlayerMax.z <= pBlock->GetPos().z + pBlock->GetMinPos().z
					&& PlayerPos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
				{
					if (oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//当たり判定(Z)
						PlayerPos.z = oldpos.z;
						m_move.z = 0.0f;
					}
				}

				if (oldpos.z + PlayerMin.z >= pBlock->GetPos().z + pBlock->GetMaxPos().z
					&& PlayerPos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z)
				{
					if ( oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& oldpos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//当たり判定(Z)
						PlayerPos.z = oldpos.z;
						m_move.z = 0.0f;
					}
				}
				if (oldpos.y + PlayerMin.y >= pBlock->GetPos().y + pBlock->GetMaxPos().y
					&& PlayerPos.y + PlayerMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y)
				{//当たり判定(Y)上
					if (oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						PlayerPos.y = oldpos.y;
						m_bLanding = true; //着地
						m_move.y = 0.0f;
						m_nJumpCnt = 0; //ジャンプ数リセット
					}
				}
				if (oldpos.y + PlayerMax.y <= pBlock->GetPos().y + pBlock->GetMinPos().y
					&& PlayerPos.y + PlayerMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
				{//当たり判定(Y)下
					if (oldpos.x + PlayerMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& oldpos.x + PlayerMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& oldpos.z + PlayerMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& oldpos.z + PlayerMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						PlayerPos.y = oldpos.y;
					}
				}
			}

			//床との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = (CField*)pObj;
				if (oldpos.y + PlayerMin.y >= pField->GetPos().y
					&& PlayerPos.y + PlayerMin.y <= pField->GetPos().y)
				{
					if (oldpos.x + PlayerMin.x < pField->GetPos().x + pField->GetSize().x
						&& oldpos.x + PlayerMax.x > pField->GetPos().x - pField->GetSize().x
						&& oldpos.z + PlayerMin.z < pField->GetPos().z + pField->GetSize().z
						&& oldpos.z + PlayerMax.z > pField->GetPos().z - pField->GetSize().z)
					{//当たり判定(Y)
						PlayerPos.y = oldpos.y;
						m_move.y = 0.0f;
						m_bLanding = true; //着地
						m_nJumpCnt = 0; //ジャンプ数リセット
					}
				}


				
			}
		}
	}
	SetPos(PlayerPos);
}
