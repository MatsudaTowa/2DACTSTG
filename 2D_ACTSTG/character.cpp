//=============================================
//
//3DTemplate[character.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "character.h"
#include "block.h"
#include "field.h"

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
				if (m_oldpos.x + CharacterMax.x <= pBlock->GetPos().x + pBlock->GetMinPos().x
					&& CharacterPos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
					{//当たり判定(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.x + CharacterMin.x >= pBlock->GetPos().x + pBlock->GetMaxPos().x
					&& CharacterPos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x)
				{
					if (m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
					{//当たり判定(X)
						CharacterPos.x = m_oldpos.x;
						m_move.x = 0.0f;
					}
				}

				if (m_oldpos.z + CharacterMax.z <= pBlock->GetPos().z + pBlock->GetMinPos().z
					&& CharacterPos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
				{
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//当たり判定(Z)
						CharacterPos.z = m_oldpos.z;
						m_move.z = 0.0f;
					}
				}

				if (m_oldpos.z + CharacterMin.z >= pBlock->GetPos().z + pBlock->GetMaxPos().z
					&& CharacterPos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z)
				{
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y
						&& m_oldpos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y
						)
					{//当たり判定(Z)
						CharacterPos.z = m_oldpos.z;
						m_move.z = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMin.y >= pBlock->GetPos().y + pBlock->GetMaxPos().y
					&& CharacterPos.y + CharacterMin.y < pBlock->GetPos().y + pBlock->GetMaxPos().y)
				{//当たり判定(Y)上
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
						m_bLanding = true; //着地
						m_move.y = 0.0f;
					}
				}
				if (m_oldpos.y + CharacterMax.y <= pBlock->GetPos().y + pBlock->GetMinPos().y
					&& CharacterPos.y + CharacterMax.y > pBlock->GetPos().y + pBlock->GetMinPos().y)
				{//当たり判定(Y)下
					if (m_oldpos.x + CharacterMin.x < pBlock->GetPos().x + pBlock->GetMaxPos().x
						&& m_oldpos.x + CharacterMax.x > pBlock->GetPos().x + pBlock->GetMinPos().x
						&& m_oldpos.z + CharacterMin.z < pBlock->GetPos().z + pBlock->GetMaxPos().z
						&& m_oldpos.z + CharacterMax.z > pBlock->GetPos().z + pBlock->GetMinPos().z)
					{
						CharacterPos.y = m_oldpos.y;
					}
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
