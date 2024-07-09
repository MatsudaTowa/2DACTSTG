//=============================================
//
//3DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

class CBullet : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int BULLET_PRIORITY = 4; //描画順
	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//弾作成
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife,int nDamage);
private:
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};