//=============================================
//
//エネルギー回復オーブ[energyorb.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENERGYORB_H_ //これが定義されてないとき

#define _ENERGYORB_H_
#include "main.h"
#include "billboard.h"
#include "button_UI.h"
class CEnergyOrb : public CBillboard
{
public:
	static const std::string ENERGY_ORB_TEXTURE_NAME;	//テクスチャの名前

	static const int ENERGY_ORB_PRIORITY = 3; //描画順

	CEnergyOrb(int nPriority = ENERGY_ORB_PRIORITY);
	~CEnergyOrb()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//ブロック作成
	static CEnergyOrb* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
private:

	void HitOrb(); //オーブとの当たり判定
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif