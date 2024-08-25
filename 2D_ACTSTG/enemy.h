//=============================================
//
//敵の処理[enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //これが定義されてないとき

#define _ENEMY_H_
#include "main.h"
#include "character.h"
#include "colision_view.h"

//=============================================
//エネミークラス
//=============================================
class CEnemy : public CCharacter
{
public:
	static const int ENEMY_PRIORITY = 4; //描画順
	static const float DEFAULT_MOVE; //通常時の移動	 

	static const int NORMAL_SHOT_FRAME = 180; //発射するカウント
	//エネミーの列挙定義
	typedef enum
	{
		ENEMY_TYPE_NORMAL = 0,
		ENEMY_TYPE_FLOW,
		ENEMY_TYPE_MAX,
	}ENEMY_TYPE;

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	virtual void EnemyMove() = 0; //エネミー移動処理

	//エネミー作成
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const ENEMY_TYPE& type);

	void Damage(int nDamage); //当たり判定

	bool PlayerDistance(); //プレイヤーとの距離を測る関数

	ENEMY_TYPE m_Type; //エネミーの種類

	static int m_nNumEnemy; //エネミーの総数

private:
	static const std::string MODEL_NAME;	//モデルの名前  
	static const std::string FLOW_MODEL_NAME;	//モデルの名前  
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEADZONE_Y; //これを過ぎたら破棄
	static const int EFFECT_LIFE = 3; //エフェクトの体力

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数

	CColision_View*m_pColisionView; //エネミーの当たり判定
};

//=============================================
//通常の敵クラス
//=============================================
class CNormalEnemy : public CEnemy
{
public:
	static const int NORMAL_ENEMY_TURNFRAME = 90; //ノーマルのエネミーの移動折り返しフレーム
	static const int ENEMY_NORMAL_LIFE = 5; //エネミーの体力

	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	~CNormalEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;
private:
	int m_nShotCnt; //弾を発射するカウント
	int m_nTurnFrameCnt; //折り返しフレームをカウントする変数
	bool m_bOldWay; //過去の方向
};

//=============================================
//集中斬撃の敵クラス
//=============================================
class CFlowEnemy : public CEnemy
{
public:
	static const int FLOW_ENEMY_TURNFRAME = 120; //ノーマルのエネミーの移動折り返しフレーム
	static const int ENEMY_FLOW_LIFE = 3; //エネミーの体力

	CFlowEnemy(int nPriority = ENEMY_PRIORITY);
	~CFlowEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;
private:
	int m_nTurnFrameCnt; //折り返しフレームをカウントする変数
	bool m_bOldWay; //過去の方向
};
#endif