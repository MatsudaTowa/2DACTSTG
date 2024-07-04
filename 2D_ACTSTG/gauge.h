//=============================================
//
//ゲージ管理[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //これが定義されてないとき

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"

//レンダラークラス
class CGauge : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int GAUGE_PRIORITY = 81;  //描画順
	static const float MAX_GAUGE_WIDE;  //ゲージの最大値
	CGauge(int nPriority = GAUGE_PRIORITY);
	~CGauge()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void AddGauge();
	void SubGauge(float fCost);
	void SetGaugeVtx(float rhw, D3DCOLOR col);
	static CGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	//static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif