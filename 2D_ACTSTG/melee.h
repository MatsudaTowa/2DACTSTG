//=============================================
//
//近接攻撃[melee.h]
//Auther Matsuda Towa
//
//=============================================
#include"main.h"
#include "object3D.h"
class CMelee : public CObject3D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int MELEE_PRIORITY = 4; //描画順
	CMelee(int nPriority = MELEE_PRIORITY);
	~CMelee()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//近接攻撃作成
	static CMelee* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife);

private:
	void HitMelee();
	float m_fAngle;
	float m_fLength;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};