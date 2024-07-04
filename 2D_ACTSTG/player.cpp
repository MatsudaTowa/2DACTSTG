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
#include "camera.h"
#include "melee.h"

//モデルパス
const std::string CPlayer::MODEL_NAME = "data\\MODEL\\face.x";

//通常の移動速度
const float CPlayer::DEFAULT_MOVE = 1.0f;
//通常の移動速度
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//通常のジャンプ力
const float CPlayer::DEFAULT_JUMP = 25.0f;

//ジャンプ回数
const int CPlayer::MAX_JUMPCNT = 2;

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
CPlayer::CPlayer(int nPriority):CCharacter(nPriority),m_nJumpCnt(0)
{//イニシャライザーでジャンプカウント初期化
	
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

	m_bSize = false;

	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//ムーブ値代入
	SetMove(move);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	//重力処理
	Gravity();

	//移動処理
	PlayerMove();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//過去の位置
	D3DXVECTOR3 oldpos = GetOldPos();

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//移動量を更新(減速）
	move *= 1.0f - DAMPING_COEFFICIENT;

	//移動量代入
	SetMove(move);

	//過去の位置に今の位置を代入
	oldpos = pos;

	//過去の位置代入
	SetOldPos(oldpos);

	//エフェクト生成
	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x,pos.y + 8.0f,pos.z), D3DXVECTOR3(10.0f, 10.0f ,0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);

	//移動量追加
	pos += move;

	//座標を更新
	SetPos(pos);

	//最大最小値取得
	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();
	
	//ブロックとの接触処理
	HitBlock();

	//エネミーとの接触処理
	HitEnemy();

	if (GetLaunding())
	{//着地してるなら
		//ジャンプ数リセット
		m_nJumpCnt = 0;
	}

	if (pos.y < DEADZONE_Y)
	{//リスポーン処理
		ReSpawn();
	}
	
	//Turn(); //回転処理
	//SizeChange(); //拡縮

	//マウスの情報取得
	CInputMouse* pMouse = CManager::GetMouse();

	//どっち向いてるか取得
	bool bWay = GetWay();

	if (pMouse->GetTrigger(0))
	{//右クリックが入力されたら
		if (bWay == true)
		{//右向き
			CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f),D3DXVECTOR3(20.0f,50.0f,0.0f),30);
		}
		else if (bWay == false)
		{//左向き
			CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(20.0f, 50.0f, 0.0f), 30);
		}
	}

	if (pMouse->GetTrigger(1))
	{//左クリックが入力されたら
		if (bWay == true)
		{//右向き
			CMelee* pMelee = CMelee::Create(D3DXVECTOR3(pos.x + GetMaxPos().x, pos.y + 10.0f, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30);
		}
		else if (bWay == false)
		{//左向き
			CMelee* pMelee = CMelee::Create(D3DXVECTOR3(pos.x + GetMinPos().x, pos.y + 10.0f, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30);
		}
	}

}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	//親クラスの描画を呼ぶ
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CModel* pModel = CManager::GetModel();

	CPlayer* pPlayer = new CPlayer;

	// nullならnullを返す
	if (pPlayer == nullptr) {return nullptr;}

	pPlayer->SetPos(pos); //pos設定
	pPlayer->SetRot(rot); //rot設定

	//xファイル読み込み
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	pPlayer->Init(); //初期化処理
	
	return pPlayer;
}

//=============================================
//リスポーン
//=============================================
void CPlayer::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos代入
	SetPos(PlayerPos);
}

//=============================================
//移動処理
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//カメラタイプ取得
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//どっち向いてるか取得
	bool bWay = GetWay();

	switch (pCameraType)
	{//サイドビューの時は横にしか動かないように設定
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	default:
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
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	}

	//どっち向いてるか代入
	SetWay(bWay);

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//着地してるか取得
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//オブジェクト2Dからrotを取得
		D3DXVECTOR3 rot = GetRot();

		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.y = rotMoveY + D3DX_PI;
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
			move.y = DEFAULT_JUMP;
			bLanding = false; //空中
			m_nJumpCnt++; //ジャンプ数加算
		}
	}

	//移動量代入
	SetMove(move);

	//着地してるか代入
	SetLanding(bLanding);

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

