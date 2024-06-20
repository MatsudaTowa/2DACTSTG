//=============================================
//
//3DTemplate[input.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //定義されてなかったら
#define _INPUT_H_ //２種インクルード防止
#include "main.h"

//インプットクラス
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;//端末ごとに
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボードクラス
class CInputKeyboard:public CInput
{
public:
	static const int NUM_KEY_MAX = 256; //キーボードのキー数
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//端末ごとに
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
private:
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
	BYTE m_aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報
};

//マウスクラス
class CInputMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //マウスのキー数
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//端末ごとに
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	D3DXVECTOR3 GetMouseMove(void);
private:
	DIMOUSESTATE m_KeyStateTrigger; //マウスのトリガー情報
	DIMOUSESTATE m_KeyState; //マウスのプレス情報
	DIMOUSESTATE m_zdiMouseMove; //マウスムーブ
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};
#endif // _INPUT_H_ //定義されてなかったら