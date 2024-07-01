//=============================================
//
//3DTemplate[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "camera.h"
#include "manager.h"
#include "effect.h"

//通常の移動速度
const float CEnemy::DEFAULT_MOVE = 1.0f;
//通常の移動速度
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//エネミーを破棄される座標
const float CEnemy::DEADZONE_Y = -100.0f;

//モデルパス
const std::string CEnemy::MODEL_NAME = "data\\MODEL\\enemy_test.x";

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy::m_pMesh = nullptr;

DWORD CEnemy::m_dwNumMat = 0;

//=============================================
//コンストラクタ
//=============================================
CEnemy::CEnemy(int nPriority):CCharacter(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CEnemy::~CEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CEnemy::Init()
{
	//移動量初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ムーブ値代入
	SetMove(move);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CEnemy::Update()
{

	//重力処理
	Gravity();

	//移動処理
	EnemyMove();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//過去の位置
	D3DXVECTOR3 oldpos = GetOldPos();

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//移動量を更新(減速）
	move *= 1.0f - DAMPING_COEFFICIENT;

	SetMove(move);

	oldpos = pos;

	//過去の位置代入
	SetOldPos(oldpos);

	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), 30);

	pos += move;

	//座標を更新
	SetPos(pos);

	//D3DXVECTOR3 minpos = GetMinPos();
	//D3DXVECTOR3 maxpos = GetMaxPos();

	//プレイヤーとの接触処理
	HitPlayer();

	//ブロックとの接触処理
	HitBlock();

	if (pos.y < DEADZONE_Y)
	{//破棄処理
		Release();
	}

}

//=============================================
//描画
//=============================================
void CEnemy::Draw()
{
	CObjectX::Draw();
}

//=============================================
//生成
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot)
{
	CEnemy* pEnemy = new CEnemy;

	// nullならnullを返す
	if (pEnemy == nullptr) { return nullptr; }

	//モデルを取得
	CModel* pModel = CManager::GetModel();

	pEnemy->SetPos(pos); //pos設定
	pEnemy->SetRot(rot); //rot設定

	//Xファイル読み込み
	pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat, //マテリアル取得
	pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat, //マテリアル数取得
	pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh); //メッシュ情報取得

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //オブジェクトのタイプ設定

	pEnemy->Init(); //エネミーの初期化処理

	return pEnemy;
}

//=============================================
//弾との当たり判定
//=============================================
void CEnemy::HitBullet()
{
	Release();
}

//=============================================
//移動処理
//=============================================
void CEnemy::EnemyMove()
{
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
	vecDirection.x -= 1.0f;
	vecDirection.z -= 0.0f;

	//移動量取得
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//オブジェクト2Dからrotを取得
	D3DXVECTOR3 rot = GetRot();

	//着地してるか取得
	bool bLanding = GetLaunding();

	move.x += sinf(rotMoveY) * DEFAULT_MOVE;
	move.z += cosf(rotMoveY) * DEFAULT_MOVE;
	rot.y = rotMoveY + D3DX_PI;

	//rotを代入
	SetRot(rot); //移動量代入
	SetMove(move);

	//着地してるか代入
	SetLanding(bLanding);
}
