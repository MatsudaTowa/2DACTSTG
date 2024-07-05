//=============================================
//
//3DTemplate[enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //これが定義されてないとき

#define _ENEMY_H_
#include "main.h"
#include "character.h"
//エネミークラス
class CEnemy : public CCharacter
{
public:
	static const int ENEMY_PRIORITY = 4; //描画順

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//エネミー作成
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

	void HitDamage(int nDamage); //当たり判定

private:
	static const std::string MODEL_NAME;	//モデルの名前
	static const float DEFAULT_MOVE; //通常時の移動	   
	static const float DAMPING_COEFFICIENT; //移動抵抗
	static const float DEADZONE_Y; //これを過ぎたら破棄
	static const int EFFECT_LIFE = 3; //エフェクトの体力
	static const int ENEMY_DEFAULT_LIFE = 5; //エネミーの体力


	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	void EnemyMove(); //エネミー移動処理

	int m_nLife;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	static	DWORD m_dwNumMat; //マテリアル数
};
#endif