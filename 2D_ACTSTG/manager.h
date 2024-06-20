//=============================================
//
//3DTemplate[maneger.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //これが定義されてないとき

#define _MANAGER_H_
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "fade.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	//シーン設定
	static void SetMode(CScene::MODE mode);

	//レンダラー取得
	static CRenderer*GetRenderer();
	//キーボード情報取得
	static CInputKeyboard* GetKeyboard();
	//マウス情報取得
	static CInputMouse* GetMouse();
	//カメラ取得
	static CCamera* GetCamera();
	//ライト取得
	static CLight* GetLight();
	//テクスチャ取得
	static CTexture* GetTexture();
	//モデル取得
	static CModel* GetModel();
private:
	static CScene* m_pScene; //現在のシーン
	//static CFade* m_pFade;
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pKeyboard;
	static CInputMouse* m_pMouse;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CTexture* m_pTexture;
	static CModel* m_pModel;

};

#endif