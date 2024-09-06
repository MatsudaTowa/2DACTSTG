//=============================================
//
//照準[button_UI.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _BUTTON_UI_H_ //これが定義されてないとき

#define _BUTTON_UI_H_
#include "main.h"
#include "billboard.h"

class CButton_UI : public CBillboard
{
public:
	typedef enum
	{
		BUTTON_TYPE_NONE = 0,
		BUTTON_TYPE_PAD_Y,
		BUTTON_TYPE_KEYBOARD_F,
		BUTTON_TYPE_MAX,
	}BUTTON_TYPE;

	static const std::string TEXTURE_NAME_PAD_Y;	//テクスチャの名前
	static const std::string TEXTURE_NAME_KEYBOARD_F;	//テクスチャの名前
	static const int BUTTON_UI_PRIORITY = 20; //描画順
	CButton_UI(int nPriority = BUTTON_UI_PRIORITY);
	~CButton_UI()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void ChangeSize();
	//エフェクト作成
	static CButton_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTON_TYPE type);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif