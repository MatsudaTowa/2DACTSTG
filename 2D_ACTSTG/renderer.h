//=============================================
//
//3DTemplate[renderer.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _RENDERER_H_ //これが定義されてないとき

#define _RENDERER_H_

//レンダラークラス
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd,BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS(int nCntFPS);
	LPDIRECT3DDEVICE9 GetDevice(); //3Dデバイス取得
private:
	LPDIRECT3D9	m_pD3D; //Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3Dデバイスへのポインタ
	LPD3DXFONT m_pFont; //フォントへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMain; //頂点バッファへのポインタ
};
#endif