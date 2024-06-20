//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //これが定義されてないとき

#define _PLAYER_H_
#include "main.h"
#include "objectX.h"
//プレイヤークラス
class CPlayer : public CObjectX
{
public:
	static const std::string MODEL_NAME;	//モデルの名前

	static const int PLAYER_PRIORITY = 8; //描画順

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//プレイヤー作成
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	static const float DEFAULT_MOVE; //通常時の移動
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEFAULT_JUMP; //通常時のジャンプ力
	static const int MAX_JUMPCNT; //ジャンプ回数
	static const float COLISION_CORRECTION; //当たり判定補正値
	static const float GRAVITY_MOVE; //重力値
	static const float GRAVITY_MAX; //重力最大値
	static const float DEADZONE_Y; //これを過ぎたらプレイヤー破棄

	void ReSpawn(); //リスポーン
	void Gravity(); //重力処理
	void PlayerMove(); //プレイヤー移動処理
	void Turn();	//回転処理
	void SizeChange();	//サイズ変更処理
	void HitBlock(D3DXVECTOR3 oldpos); //ブロック当たり判定

	D3DXVECTOR3 m_move; //速度
	D3DXVECTOR3 m_oldpos; //過去の位置
	bool m_bSize; //サイズ変更するかどうか
	bool m_bLanding; //着地してるかどうか
	bool m_bWay; //どっち向いてるか(true:右false:左)
	int m_nJumpCnt; //ジャンプカウント

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数;
};
#endif