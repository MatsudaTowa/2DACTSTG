//=============================================
//
//敵の処理[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "camera.h"
#include "manager.h"
#include "player.h"
#include "effect.h"
#include "bullet.h"
#include "item.h"
#include "flow.h"
#include "score.h"
#include "game.h"

//通常の移動速度
const float CEnemy::DEFAULT_MOVE = 0.3f;
//移動抵抗
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//エネミーを破棄される座標
const float CEnemy::DEADZONE_Y = -100.0f;

//モデルパス
const std::string CEnemy::MODEL_NAME = "data\\MODEL\\enemy_test.x";

//モデルパス
const std::string CEnemy::FLOW_MODEL_NAME = "data\\MODEL\\flowenemy_test.x";

//モデルパス
const std::string CEnemy::BOSS_MODEL_NAME = "data\\MODEL\\boss.x";

//ステート切り替えフレーム
const int CEnemy::STATE_FRAME = 30;

//テクスチャ初期化
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy::m_pMesh = nullptr;

DWORD CEnemy::m_dwNumMat = 0;

//エネミーの総数
int CEnemy::m_nNumEnemy = 0;

//=============================================
//コンストラクタ
//=============================================
CEnemy::CEnemy(int nPriority):CCharacter(nPriority), m_bLockOn(false)
{
	//総数加算
	m_nNumEnemy++;
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

#ifdef _DEBUG
	//当たり判定可視化
	m_pColisionView = CColision_View::Create(GetPos(), GetMinPos(), GetMaxPos(), D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
#endif
	m_pAttackEffect = nullptr;
	m_pLockOn = nullptr;
	return S_OK;
}

//=============================================
//終了
//=============================================
void CEnemy::Uninit()
{
	//親クラスの終了
	CObjectX::Uninit();

	//総数減らす
	m_nNumEnemy--;

}

//=============================================
//更新
//=============================================
void CEnemy::Update()
{
	if (m_Type != CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS)
	{//飛ぶ奴以外なら
		//重力処理
		Gravity();
	}

	//移動処理
	EnemyMove();

	//位置取得
	D3DXVECTOR3 pos = GetPos();

	//過去の位置
	D3DXVECTOR3 oldpos = GetOldPos();

	//移動量取得
	D3DXVECTOR3 move = GetMove();

	//状態取得
	CCharacter::CHARACTER_STATE state = GetState();

	
	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//状態のカウント数取得
		int nStateCnt = GetStateCnt();

		//ステート変更カウント進める
		nStateCnt++;

		if (nStateCnt >= STATE_FRAME)
		{
			//通常に戻す
			state = CCharacter::CHARACTER_STATE::CHARACTER_NORMAL;

			//ステートカウントリセット
			nStateCnt = 0;

			//状態代入
			SetState(state);
		}

		//ステートカウント代入
		SetStateCnt(nStateCnt);
	}

	//移動量を更新(減速）
	move *= 1.0f - DAMPING_COEFFICIENT;

	SetMove(move);

	oldpos = pos;

	//過去の位置代入
	SetOldPos(oldpos);

	//エフェクト生成
	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), 30);

	pos += move;

	//座標を更新
	SetPos(pos);

#ifdef _DEBUG
	//可視化された当たり判定を動かす
	m_pColisionView->SetPos(pos);
#endif
	bool bNear = PlayerDistance();

	if (bNear)
	{//近かったら
		if (m_pAttackEffect == nullptr)
		{//生成されてなかったら
			m_pAttackEffect = CAttack_Effect::Create(GetPos(), D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	
	if(m_pLockOn != nullptr)
	{//照準をエネミーに合わせて動かす
		m_pLockOn->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f));
	}

	if (m_pAttackEffect != nullptr)
	{//照準をエネミーに合わせて動かす
		m_pAttackEffect->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f));
	}
	//プレイヤーとの接触処理
	HitPlayer();

	//エネミーとの接触処理
	HitEnemy();

	//ブロックとの接触処理
	HitBlock();

	//床との接触処理
	HitField();

	if (pos.y < DEADZONE_Y)
	{//破棄処理
		Uninit();
	}
}

//=============================================
//描画
//=============================================
void CEnemy::Draw()
{
	//親クラスの描画
	CCharacter::Draw();
}

//=============================================
//生成
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMY_TYPE_NORMAL:
		pEnemy = new CNormalEnemy;
		break;
	case ENEMY_TYPE_FLOW:
		pEnemy = new CFlowEnemy;
		break;
	case ENEMY_TYPE_BOSS:
		pEnemy = new CBossEnemy;
		break;
	default:
		break;
	}

	// nullならnullを返す
	if (pEnemy == nullptr) { return nullptr; }

	pEnemy->m_Type = type; //エネミーのタイプ設定

	pEnemy->SetPos(pos); //pos設定
	pEnemy->SetRot(rot); //rot設定
	pEnemy->SetType(OBJECT_TYPE_ENEMY); //オブジェクトのタイプ設定

	//モデルを取得
	CModel* pModel = CManager::GetModel();

	switch (pEnemy->m_Type)
	{
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
		//Xファイル読み込み
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat, //マテリアル取得
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat, //マテリアル数取得
			pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh); //メッシュ情報取得
		break;
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLOW:
		//Xファイル読み込み
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&FLOW_MODEL_NAME)).pBuffMat, //マテリアル取得
			pModel->GetModelInfo(pModel->Regist(&FLOW_MODEL_NAME)).dwNumMat, //マテリアル数取得
			pModel->GetModelInfo(pModel->Regist(&FLOW_MODEL_NAME)).pMesh); //メッシュ情報取得
		break;
	case CEnemy::ENEMY_TYPE::ENEMY_TYPE_BOSS:
		//Xファイル読み込み
		pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&BOSS_MODEL_NAME)).pBuffMat, //マテリアル取得
			pModel->GetModelInfo(pModel->Regist(&BOSS_MODEL_NAME)).dwNumMat, //マテリアル数取得
			pModel->GetModelInfo(pModel->Regist(&BOSS_MODEL_NAME)).pMesh); //メッシュ情報取得
		break;
	default:
		break;
	}

	pEnemy->Init(); //エネミーの初期化処理

	return pEnemy;
}

//=============================================
//ダメージを受けたとき
//=============================================
void CEnemy::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > 0 && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//ダメージ状態以外でHPが残ってたら
		nLife -= nDamage;

		//ダメージ状態に変更
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//状態代入
		SetState(state);

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HPが0以下だったら
		//破棄
		CItem* pItem = nullptr;

		switch (m_Type)
		{
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL:
			pItem = CItem::Create(CItem::ITEMTYPE_PANETRARING_SLASH, D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), GetRot());
			break;
		case CEnemy::ENEMY_TYPE::ENEMY_TYPE_FLOW:
			pItem = CItem::Create(CItem::ITEMTYPE_FLOW, D3DXVECTOR3(GetPos().x, GetPos().y + 10.0f, GetPos().z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), GetRot());
			break;
		default:
			break;
		}

#ifdef _DEBUG
		//可視化された当たり判定破棄
		m_pColisionView->Uninit();
#endif // _DEBUG
		
		if (m_pLockOn != nullptr)
		{//照準破棄
			m_pLockOn->Uninit();
			m_pLockOn = nullptr;
			m_bLockOn = false;
		}

		if (m_pAttackEffect != nullptr)
		{//攻撃エフェクト破棄
			m_pAttackEffect->Uninit();
			m_pAttackEffect = nullptr;
		}

		CScore*pScore = CGame::GetScore();

		pScore->AddScore(100);

		Uninit();
	}
}

//=============================================
//プレイヤーとの距離を測る
//=============================================
bool CEnemy::PlayerDistance()
{
	bool bNear = false; //近かったらtrueを返す

	bool bWay = GetWay(); //向きを取得

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

				float fDistance = 0.0f; //プレイヤーとの距離
				
				fDistance = GetPos().x - pPlayer->GetPos().x;

				if (fDistance >= 0.0f && fDistance < 120.0f)
				{//エネミーのminに近い
					bNear = true;
					
					bWay = false; //向きをプレイヤーのほうに切り替える
				}
				else if (fDistance <= 0.0f && fDistance > -120.0f)
				{//エネミーのmaxに近い
					bNear = true;

					bWay = true; //向きをプレイヤーのほうに切り替える
				}
				else
				{//近くない
					bNear = false;
				}
			}
		}
	}

	//向きを代入
	SetWay(bWay);
	return bNear;
}

//=============================================
//lock-on処理
//=============================================
void CEnemy::LockOn()
{
	if (m_bLockOn != true)
	{
		m_pLockOn = CLockOn::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(70.0f, 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_bLockOn = true;
}

//=============================================
//集中斬撃を照準に合わせて出す
//=============================================
void CEnemy::LockOn_Flow()
{
	if (m_pLockOn != nullptr)
	{
		int nFlowLife = 0;
		if (m_pLockOn->GetSize().x <= m_pLockOn->MIN_DAMAGE_LOCKON_SIZE
			&& m_pLockOn->GetSize().x > m_pLockOn->MEDIUM_DAMAGE_LOCKON_SIZE)
		{//最小ダメージのとき
			nFlowLife = 30;
		}
		else if (m_pLockOn->GetSize().x <= m_pLockOn->MEDIUM_DAMAGE_LOCKON_SIZE
			&& m_pLockOn->GetSize().x > m_pLockOn->MAX_DAMAGE_LOCKON_SIZE)
		{//中ダメージのとき
			nFlowLife = 60;
		}
		else if (m_pLockOn->GetSize().x <= m_pLockOn->MAX_DAMAGE_LOCKON_SIZE)
		{//中ダメージのとき
			nFlowLife = 90;
		}
		CFlow*pFlow = CFlow::Create(D3DXVECTOR3(m_pLockOn->GetPos().x, m_pLockOn->GetPos().y + 5.0f, -10.0f),
			D3DXVECTOR3(20.0f, 20.0f, 0.0f), nFlowLife,1,CFlow::FLOW_TYPE::FLOW_TYPE_PLAYER);

		m_pLockOn->Uninit();
		m_pLockOn = nullptr;
		m_bLockOn = false;
	}
}

//=============================================
//コンストラクタ
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority),m_nTurnFrameCnt(0), m_bOldWay(false), m_nShotCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CNormalEnemy::Init()
{
	//親クラスの初期化
	CEnemy::Init();
	SetLife(ENEMY_NORMAL_LIFE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CNormalEnemy::Uninit()
{
	//親クラスの終了
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CNormalEnemy::Update()
{
	//親クラスの更新
	CEnemy::Update();

	//プレイヤーとの距離を測る
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//近かったら
		//向きを取得
		bool bWay = GetWay();

		//ショットカウント加算
		m_nShotCnt++;

		if (m_pAttackEffect != nullptr)
		{
			//サイズ変更
			m_pAttackEffect->SizeChange(((float)m_nShotCnt / (float)NORMAL_SHOT_FRAME));
		}

		if (m_nShotCnt >= NORMAL_SHOT_FRAME)
		{//フレーム数に達したら

			//弾発射
			ShotBullet(GetPos(),2.0f, D3DXVECTOR3(6.0f, 12.0f, 0.0f), bWay, 1, CBullet::BULLET_ALLEGIANCE_ENEMY,CBullet::BULLET_TYPE_PANETRARING_SLASH);

			//エフェクトサイズリセット
			if (m_pAttackEffect != nullptr)
			{
				//サイズ変更
				m_pAttackEffect->SizeReset();
			}

			//ショットカウントリセット
			m_nShotCnt = 0;
		}
	}
	else if (bDistance == false)
	{
		if (m_pAttackEffect != nullptr)
		{
			//サイズ変更
			m_pAttackEffect->SizeChange(((float)m_nShotCnt / (float)NORMAL_SHOT_FRAME));
		}
		//ショットカウントダウン
		if (m_nShotCnt > 0)
		{
			m_nShotCnt--;
		}
	}
}

//=============================================
//描画
//=============================================
void CNormalEnemy::Draw()
{
	//親クラスの描画を呼ぶ
	CCharacter::Draw();
}

//=============================================
//移動処理
//=============================================
void CNormalEnemy::EnemyMove()
{
	//カウント加算
	m_nTurnFrameCnt++;

	//向きを取得
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//過去の向きと違ったらフレームリセット
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= NORMAL_ENEMY_TURNFRAME)
	{//指定フレーム数に到達したら

		//進む方向を切り替える
		bWay = bWay ? false : true;
		SetWay(bWay);

		//過去の向きに今の向きを代入
		m_bOldWay = bWay;
		//カウントリセット
		m_nTurnFrameCnt = 0;
	}

	//移動用単位ベクトル初期化
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//右向きに進むなら
		vecDirection.x += 1.0f;
		vecDirection.z += 0.0f;
	}
	else if (bWay == false)
	{//左向きに進むなら
		vecDirection.x -= 1.0f;
		vecDirection.z -= 0.0f;
	}

	//移動量取得
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//オブジェクト2Dからrotを取得
	D3DXVECTOR3 rot = GetRot();

	//着地してるか取得
	bool bLanding = GetLaunding();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
	}
	else
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
	}

	rot.y = rotMoveY + D3DX_PI;

	//プレイヤーとの距離を測る
	bool bDistance = PlayerDistance();

	SetRot(rot); //rotを代入

	//if (bDistance == false)
	{
		SetMove(move);//移動量代入
	}

	//着地してるか代入
	SetLanding(bLanding);
}

//=============================================
//コンストラクタ
//=============================================
CFlowEnemy::CFlowEnemy(int nPriority) :CEnemy(nPriority), m_nTurnFrameCnt(0), m_bOldWay(false), m_bLockOnShot(false)
{
}

//=============================================
//デストラクタ
//=============================================
CFlowEnemy::~CFlowEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CFlowEnemy::Init()
{
	//親クラスの初期化
	CEnemy::Init();
	SetLife(ENEMY_FLOW_LIFE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CFlowEnemy::Uninit()
{
	if (m_bLockOnShot == true)
	{
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

					pPlayer->Delete_LockOn();
				}
			}
		}
	}
	//親クラスの終了
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CFlowEnemy::Update()
{
	//親クラスの更新
	CEnemy::Update();

	//プレイヤーとの距離を測る
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//近かったら
		//向きを取得
		bool bWay = GetWay();
		m_bLockOnShot = true;

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

					pPlayer->LockOn();

					pPlayer->LockOn_ChangeSize((1.0f- (float)m_nShotCnt / (float)NORMAL_SHOT_FRAME));

					//ショットカウント加算
					m_nShotCnt++;

					if (m_nShotCnt >= NORMAL_SHOT_FRAME)
					{//フレーム数に達したら
						//弾発射

						if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
						{
							pPlayer->LockOn_Flow();
						}

						//ショットカウントリセット
						m_nShotCnt = 0;
					}

				}
			}
		}
	}
	else if(bDistance == false)
	{
		if (m_bLockOnShot == true)
		{
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

						pPlayer->Delete_LockOn();
					}
				}
			}
		}
		//ショットカウントダウン
		if (m_nShotCnt >= 0)
		{
			m_nShotCnt--;
		}
	}
}

//=============================================
//描画
//=============================================
void CFlowEnemy::Draw()
{
	//親クラスの描画
	CEnemy::Draw();
}

//=============================================
//移動処理
//=============================================
void CFlowEnemy::EnemyMove()
{
	//カウント加算
	m_nTurnFrameCnt++;

	//向きを取得
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//過去の向きと違ったらフレームリセット
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= FLOW_ENEMY_TURNFRAME)
	{//指定フレーム数に到達したら

		//進む方向を切り替える
		bWay = bWay ? false : true;
		SetWay(bWay);

		//過去の向きに今の向きを代入
		m_bOldWay = bWay;
		//カウントリセット
		m_nTurnFrameCnt = 0;
	}

	//移動用単位ベクトル初期化
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//右向きに進むなら
		vecDirection.x += 1.0f;
		vecDirection.z += 0.0f;
	}
	else if (bWay == false)
	{//左向きに進むなら
		vecDirection.x -= 1.0f;
		vecDirection.z -= 0.0f;
	}

	//移動量取得
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//オブジェクト2Dからrotを取得
	D3DXVECTOR3 rot = GetRot();

	//着地してるか取得
	bool bLanding = GetLaunding();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE * 0.5f;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE * 0.5f;
	}
	else
	{
		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
	}
	rot.y = rotMoveY + D3DX_PI;

	//プレイヤーとの距離を測る
	bool bDistance = PlayerDistance();

	SetRot(rot); //rotを代入

	if (bDistance == false)
	{
		SetMove(move);//移動量代入
	}


	//着地してるか代入
	SetLanding(bLanding);
}

////通常の移動速度
//const float CBossEnemy::DEFAULT_MOVE_Y = 0.5f;

//弾を生成する円周の半径
const float CBossEnemy::CREATE_RADIUS = 50.0f;

//=============================================
//コンストラクタ
//=============================================
CBossEnemy::CBossEnemy(int nPriority):CEnemy(nPriority), m_nTurnFrameCnt(0), m_nNumBullet(0),m_bOldWay(false), m_bShot(false), m_nShotCnt(0)
{
	/*for (int nCnt = 0; nCnt < CBossEnemy::CREATE_BULLET; nCnt++)
	{
		pBullet[nCnt] = nullptr;
	}*/
}

//=============================================
//デストラクタ
//=============================================
CBossEnemy::~CBossEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CBossEnemy::Init()
{
	//親クラスの初期化
	CEnemy::Init();
	SetLife(ENEMY_BOSS_LIFE);
	return S_OK;
}

//=============================================
//終了
//=============================================
void CBossEnemy::Uninit()
{
	//親クラスの終了
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CBossEnemy::Update()
{
	//親クラスの更新
	CEnemy::Update();

	//プレイヤーとの距離を測る
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//近かったら
		//向きを取得
		bool bWay = GetWay();

		//ショットカウント加算
		m_nShotCnt++;

		if (m_nShotCnt >= BOSS_SHOT_FRAME)
		{//フレーム数に達したら
			
			//for (int nCnt = 0; nCnt < CBossEnemy::CREATE_BULLET; nCnt++)
			//{//既定の数、弾生成
			if (m_nNumBullet < CBossEnemy::CREATE_BULLET  && m_bShot == false)
			{
				D3DXVECTOR3 CreatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CreatePos.x = CREATE_RADIUS * sinf((D3DX_PI * 2.0f) * ((1.0f / CBossEnemy::CREATE_BULLET) * m_nNumBullet));
				CreatePos.y = CREATE_RADIUS * cosf((D3DX_PI * 2.0f) * ((1.0f / CBossEnemy::CREATE_BULLET) * m_nNumBullet));

				//ボスの位置を基準にする
				CreatePos += GetPos() + (GetMaxPos() * 0.5f);

				if (bWay == true)
				{//右向き
					/*pBullet[m_nNumBullet] = */CElecBullet::ElecCreate(CreatePos,D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f),
					D3DXVECTOR3(10.0f, 10.0f, 0.0f), 60, 1, CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_ELECBULLET);
				}
				else if (bWay == false)
				{//左向き
					/*pBullet[m_nNumBullet] = */CElecBullet::ElecCreate(CreatePos, D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f),
						D3DXVECTOR3(10.0f, 10.0f, 0.0f), 60, 1, CBullet::BULLET_ALLEGIANCE_ENEMY, CBullet::BULLET_TYPE_ELECBULLET);
				}

				m_nNumBullet++;
			}
			if (m_bShot == true)
			{
				//if (pBullet[m_nNumBullet - 1] != nullptr)
				//{
					//pBullet[m_nNumBullet - 1]->SetElecType(CElecBullet::ELECTYPE::TYPE_MOVE);
				//}
				m_nNumBullet--;
				if (m_nNumBullet <= 0)
				{
					m_nNumBullet = 0;
					m_bShot = false;
				}
			}

			if (m_nNumBullet >= CBossEnemy::CREATE_BULLET)
			{
				m_bShot = true;
			}

			//ショットカウントリセット
			m_nShotCnt = 0;
		}
	}
}

//=============================================
//描画
//=============================================
void CBossEnemy::Draw()
{
	//親クラスの描画
	CEnemy::Draw();
}

void CBossEnemy::EnemyMove()
{
}
