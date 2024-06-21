//=============================================
//
//3DTemplate[character.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //これが定義されてないとき

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
//プレイヤークラス
class CCharacter : public CObjectX
{
public:
	static const std::string MODEL_NAME;	//モデルの名前

	static const int CHARACTER_PRIORITY = 8; //描画順

	CCharacter(int nPriority = CHARACTER_PRIORITY);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Gravity(); //重力処理
	void HitBlock(); //ブロック当たり判定

	//移動量代入
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//oldpos代入
	void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	//着地してるかどうかを代入
	void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	//どっち向いてるかどうかを代入(true:右false:左)
	void SetWay(bool bWay)
	{
		m_bWay = bWay;
	}

	//移動量取得
	D3DXVECTOR3& GetMove();

	//過去の位置取得
	D3DXVECTOR3& GetOldPos();

	//着地してるかどうか取得
	bool& GetLaunding();

	//どっち向いてるかどうかを取得(true:右false:左)
	bool& GetWay();

private:
	static const float GRAVITY_MOVE; //重力値
	static const float GRAVITY_MAX; //重力最大値

	D3DXVECTOR3 m_move; //速度
	D3DXVECTOR3 m_oldpos; //過去の位置
	bool m_bLanding; //着地してるかどうか
	bool m_bWay; //どっち向いてるか(true:右false:左)
};
#endif