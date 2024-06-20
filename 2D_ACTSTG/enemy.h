////=============================================
////
////3DTemplate[enemy.h]
////Auther Matsuda Towa
////
////=============================================
//#ifndef _ENEMY_H_ //これが定義されてないとき
//
//#define _ENEMY_H_
//#include "main.h"
//#include "object2D.h"
////レンダラークラス
//class CEnemy : public CMove_Texture
//{
//public:
//	static const int EFFECT_PRIORITY = 4; //描画順
//
//	static const int TEX_SPLIT_X; //テクスチャの分割数
//	static const int TEX_SPLIT_Y; //テクスチャの分割数
//	static const int ANIMATION_FRAME; //アニメーションフレーム数
//	CEnemy(int nPriority = EFFECT_PRIORITY);
//	~CEnemy()override;
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//
//	//エネミー作成
//	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 size,int nLife);
//
//	static HRESULT Load(); //テクスチャのロード
//	static HRESULT UnLoad(); //テクスチャのアンロード
//	void HitBullet(); //当たり判定
//
//private:
//	static const float DEFAULT_MOVE; //通常時の移動
//
//	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
//
//	void EnemyMove(); //エネミー移動処理
//
//	D3DXVECTOR3 m_move; //速度
//	float m_fLength; //対角線
//	float m_fAngle; //角度
//	int m_nLife;
//};
//#endif