//=============================================
//
//3DTemplate[title_screen.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TITLE_SCREEN_H_ //これが定義されてないとき

#define _TITLE_SCREEN_H_
#include "main.h"
#include "object2D.h"

//レンダラークラス
class CTitle_Screen : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int TITLE_SCREEN_PRIORITY = 90;  //描画順
	CTitle_Screen(int nPriority = TITLE_SCREEN_PRIORITY);
	~CTitle_Screen()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Screen* Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif