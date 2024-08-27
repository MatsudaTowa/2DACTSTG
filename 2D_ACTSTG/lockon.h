//=============================================
//
//照準[lockon.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _LOCKON_H_ //これが定義されてないとき

#define _LOCKON_H_
#include "main.h"
#include "billboard.h"

class CLockOn : public CBillboard
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int LOCKON_PRIORITY = 10; //描画順
	CLockOn(int nPriority = LOCKON_PRIORITY);
	~CLockOn()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//エフェクト作成
	static CLockOn* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	D3DXCOLOR m_col;
};
#endif