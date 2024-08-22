//=============================================
//
//3DTemplate[character.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "player.h"
#include "enemy.h"
#include "field.h"
#include"bullet.h"
#include "colision.h"

//重力値
const float CCharacter::GRAVITY_MOVE = 1.5f;
//重力最大値
const float CCharacter::GRAVITY_MAX = 32.0f;

//=============================================
//コンストラクタ
//=============================================
CCharacter::CCharacter(int nPriority):CObjectX(nPriority)
{
    m_bLanding = false; //着地
}

//=============================================
//デストラクタ
//=============================================
CCharacter::~CCharacter()
{
}

//=============================================
//初期化
//=============================================
HRESULT CCharacter::Init()
{
    return S_OK;
}

//=============================================
//終了
//=============================================
void CCharacter::Uninit()
{
    CObjectX::Uninit();
}

//=============================================
//更新
//=============================================
void CCharacter::Update()
{
	D3DXVECTOR3 CharacterPos = GetPos();
	if (GetLaunding())
	{//着地してるなら
		//ジャンプ数リセット
		CharacterPos.y = m_oldpos.y;
		m_move.y = 0.0f;

	}
	SetPos(CharacterPos);
}

//=============================================
//描画
//=============================================
void CCharacter::Draw()
{
    CObjectX::Draw();
}


//=============================================
//重力処理
//=============================================
void CCharacter::Gravity()
{
    if (m_move.y < GRAVITY_MAX)
    {
        m_move.y -= GRAVITY_MOVE;
    }
}

//=============================================
//ブロックとの接触判定
//=============================================
void CCharacter::HitBlock()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

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

				//着地以外の判定
				CColision::COLISION Checkcolision = CColision::CheckColision(m_oldpos, CharacterPos,CharacterMin,CharacterMax,pBlock->GetPos(),pBlock->GetMinPos(),pBlock->GetMaxPos());
				
				if (Checkcolision == CColision::COLISION::COLISON_X)
				{//x方向に当たってたら
					CharacterPos.x = m_oldpos.x;
					m_move.x = 0.0f;
				}
				if (Checkcolision == CColision::COLISION::COLISON_Z)
				{//z方向に当たってたら
					CharacterPos.z = m_oldpos.z;
					m_move.z = 0.0f;
				}
				if (Checkcolision == CColision::COLISION::COLISON_UNDER_Y)
				{//y(下)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
				}

				if (Checkcolision == CColision::COLISION::COLISON_TOP_Y)
				{//y(上)方向に当たってたら
					CharacterPos.y = m_oldpos.y;
					m_move.y = 0.0f;
					m_bLanding = true; //着地
				}
			}

			//床との当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_FIELD)
			{
				CField* pField = (CField*)pObj;
				if (m_oldpos.y + CharacterMin.y >= pField->GetPos().y
					&& CharacterPos.y + CharacterMin.y <= pField->GetPos().y)
				{
					if (m_oldpos.x + CharacterMin.x < pField->GetPos().x + pField->GetSize().x
						&& m_oldpos.x + CharacterMax.x > pField->GetPos().x - pField->GetSize().x
						&& m_oldpos.z + CharacterMin.z < pField->GetPos().z + pField->GetSize().z
						&& m_oldpos.z + CharacterMax.z > pField->GetPos().z - pField->GetSize().z)
					{//当たり判定(Y)
						CharacterPos.y = m_oldpos.y;
						m_move.y = 0.0f;
						m_bLanding = true; //着地
						//m_nJumpCnt = 0; //ジャンプ数リセット
					}
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//プレイヤーとの当たり判定
//=============================================
void CCharacter::HitPlayer()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//ヌルポインタじゃなければ
			//タイプ取得
			CObject::OBJECT_TYPE type = pObj->GetType();

			//プレイヤーとの当たり判定
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;
				if (m_oldpos.x + CharacterMax.x <= pPlayer->GetPos().x + pPlayer->GetMinPos().x
					&& CharacterPos.x + CharacterMax.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
					{//当たり判定(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.x + CharacterMin.x >= pPlayer->GetPos().x + pPlayer->GetMaxPos().x
					&& CharacterPos.x + CharacterMin.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
					{//当たり判定(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.y + CharacterMin.y >= pPlayer->GetPos().y + pPlayer->GetMaxPos().y
					&& CharacterPos.y + CharacterMin.y < pPlayer->GetPos().y + pPlayer->GetMaxPos().y)
				{//当たり判定(Y)上
					if (m_oldpos.x + CharacterMin.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
						m_bLanding = true; //着地
						m_move.y = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMax.y <= pPlayer->GetPos().y + pPlayer->GetMinPos().y
					&& CharacterPos.y + CharacterMax.y > pPlayer->GetPos().y + pPlayer->GetMinPos().y)
				{//当たり判定(Y)下
					if (m_oldpos.x + CharacterMin.x < pPlayer->GetPos().x + pPlayer->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pPlayer->GetPos().x + pPlayer->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pPlayer->GetPos().z + pPlayer->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pPlayer->GetPos().z + pPlayer->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
					}
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//敵との当たり判定
//=============================================
void CCharacter::HitEnemy()
{
	D3DXVECTOR3 CharacterPos = GetPos();

	//サイズ取得
	D3DXVECTOR3 CharacterMin = GetMinPos();
	D3DXVECTOR3 CharacterMax = GetMaxPos();

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
				if (m_oldpos.x + CharacterMax.x <= pEnemy->GetPos().x + pEnemy->GetMinPos().x
					&& CharacterPos.x + CharacterMax.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//当たり判定(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.x + CharacterMin.x >= pEnemy->GetPos().x + pEnemy->GetMaxPos().x
					&& CharacterPos.x + CharacterMin.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
					{//当たり判定(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.z + CharacterMax.z <= pEnemy->GetPos().z + pEnemy->GetMinPos().z
					&& CharacterPos.z + CharacterMax.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z)
				{
					if (m_oldpos.x + CharacterMin.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& m_oldpos.y + CharacterMin.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//当たり判定(Z)
						CharacterPos.z = m_oldpos.z;
						m_move.z = 0.0f;
					}
				}

				if (m_oldpos.z + CharacterMin.z >= pEnemy->GetPos().z + pEnemy->GetMaxPos().z
					&& CharacterPos.z + CharacterMin.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z)
				{
					if (m_oldpos.x + CharacterMin.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& m_oldpos.y + CharacterMin.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y
						)
					{//当たり判定(Z)
						CharacterPos.z = m_oldpos.z;
						m_move.z = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMin.y >= pEnemy->GetPos().y + pEnemy->GetMaxPos().y
					&& CharacterPos.y + CharacterMin.y < pEnemy->GetPos().y + pEnemy->GetMaxPos().y)
				{//当たり判定(Y)上
					if (m_oldpos.x + CharacterMin.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
						m_bLanding = true; //着地
						m_move.y = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMax.y <= pEnemy->GetPos().y + pEnemy->GetMinPos().y
					&& CharacterPos.y + CharacterMax.y > pEnemy->GetPos().y + pEnemy->GetMinPos().y)
				{//当たり判定(Y)下
					if (m_oldpos.x + CharacterMin.x < pEnemy->GetPos().x + pEnemy->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pEnemy->GetPos().x + pEnemy->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pEnemy->GetPos().z + pEnemy->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pEnemy->GetPos().z + pEnemy->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
					}
				}
			}
		}
	}
	SetPos(CharacterPos);
}

//=============================================
//弾発射処理
//=============================================
void CCharacter::ShotBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, bool bWay,int nDamage,CBullet::BULLET_TYPE type)
{
	if (bWay == true)
	{//右向き
		CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 30, nDamage, type);
	}
	else if (bWay == false)
	{//左向き
		CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
			D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(size.x, size.y, 0.0f), 30, nDamage, type);
	}
}

//=============================================
//移動量取得
//=============================================
D3DXVECTOR3& CCharacter::GetMove()
{
    return m_move;
}

//=============================================
//過去の位置取得
//=============================================
D3DXVECTOR3& CCharacter::GetOldPos()
{
    return m_oldpos;
}

//=============================================
//着地してるかどうか取得
//=============================================
bool& CCharacter::GetLaunding()
{
    return m_bLanding;
}

//=============================================
//どっち向いてるかどうかを取得(true:右false:左)
//=============================================
bool& CCharacter::GetWay()
{
    return m_bWay;
}

//=============================================
//体力取得
//=============================================
int& CCharacter::GetLife()
{
	return m_nLife;
}
