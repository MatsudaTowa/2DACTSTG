//=============================================
//
//3DTemplate[input.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "input.h"

//静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=============================================
//コンストラクタ
//=============================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CInput::~CInput()
{
}

//=============================================
//初期化
//=============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInput::Uninit()
{
	//入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice = nullptr;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//↓からキーボード

//=============================================
//コンストラクタ
//=============================================
CInputKeyboard::CInputKeyboard()
{
}

//=============================================
//デストラクタ
//=============================================
CInputKeyboard::~CInputKeyboard()
{
}


//=============================================
//初期化
//=============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance,hWnd);
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//=============================================
//更新
//=============================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX]; //入力情報
	int nCntKey;
	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey]; //リリース
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードのアクセス権を獲得
	}
}

//=============================================
//キーボードの情報を取得
//=============================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) != 0;
}
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
}
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) != 0;
}

//↓からマウス

//=============================================
//コンストラクタ
//=============================================
CInputMouse::CInputMouse()
{
}

//=============================================
//デストラクタ
//=============================================
CInputMouse::~CInputMouse()
{
}

//=============================================
//初期化
//=============================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// デバイスの設定
	DIPROPDWORD diprop;
	m_MousePos = { 0.0f,0.0f,0.0f };
	m_MouseMove = { 0.0f,0.0f,0.0f };
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;


	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return E_FAIL;
	}

	//マウスのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInputMouse::Uninit()
{
	CInput::Uninit();
}

//=============================================
//更新
//=============================================
void CInputMouse::Update()
{
BYTE aMouseState[NUM_MOUSE_MAX]; //入力情報
	DIMOUSESTATE zdiMouseState;
	int nCntMouse;
	for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
	{
		//入力デバイスからデータを取得
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
		{

			m_KeyStateRelease.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & ~zdiMouseState.rgbButtons[nCntMouse];
			m_KeyStateTrigger.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & zdiMouseState.rgbButtons[nCntMouse];
			m_KeyState.rgbButtons[nCntMouse] = zdiMouseState.rgbButtons[nCntMouse]; //キーボードのプレス情報を保存
		}
		else
		{
			m_pDevice->Acquire(); //キーボードのアクセス権を獲得
		}
	}

	//ZeroMemory(&pMouseMove, sizeof(POINT));

	D3DXVECTOR3 OldMousePos = m_MousePos;

	POINT pMouseMove;

	GetCursorPos(&pMouseMove);

	m_MousePos.x = (float)pMouseMove.x;
	m_MousePos.y = (float)pMouseMove.y;

	m_MouseMove.x = m_MousePos.x - OldMousePos.x;
	m_MouseMove.y = m_MousePos.y - OldMousePos.y;
	m_MouseMove.z = m_MousePos.z - OldMousePos.z;
}

//=============================================
//マウスの情報を取得
//=============================================
bool CInputMouse::GetPress(int nKey)
{
	return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
}
bool CInputMouse::GetTrigger(int nKey)
{
	return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
}
bool CInputMouse::GetRelease(int nKey)
{
	return(m_KeyStateRelease.rgbButtons[nKey] & 0x80) != 0;
}
D3DXVECTOR3 CInputMouse::GetMouseMove(void)
{
	return(m_MouseMove);
}

//↓からpad

//=============================================
//コンストラクタ
//=============================================
CInputPad::CInputPad():m_Connect(false)
{
}

//=============================================
//デストラクタ
//=============================================
CInputPad::~CInputPad()
{
}

//=============================================
//初期化
//=============================================
HRESULT CInputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_Connect = false;

	//メモリのクリア
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&m_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInputのステートを設定(有効にする)
	XInputEnable(true);

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &m_joyKeyState) == ERROR_SUCCESS)
	{
		m_Connect = true;
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInputPad::Uninit()
{
	//XInputのステートを設定(無効にする)
	XInputEnable(false);
}

//=============================================
//コンストラクタ
//=============================================
void CInputPad::Update()
{
	XINPUT_STATE joykeyState; //ジョイパッドの入力情報

		//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		m_Connect = true;
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joyKeyState.Gamepad.wButtons;
		m_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;    // トリガー処理
		m_ajoyKeyStateRelease.Gamepad.wButtons = ~Button & OldButton;    // リリース処理
		joykeyState.Gamepad.wButtons |= GetJoypadStick(m_joyKeyState.Gamepad.sThumbLX, m_joyKeyState.Gamepad.sThumbLY, JOYPAD_ZONE);

		// 現在の時間を取得する
		m_aJoypadCurrentTime.Gamepad.wButtons = timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((m_aJoypadCurrentTime.Gamepad.wButtons - m_aJoypadExecLastTime.Gamepad.wButtons) > JOYPAD_SPEED))
		{
			// 最後に真を返した時間を保存
			m_aJoypadExecLastTime.Gamepad.wButtons = m_aJoypadCurrentTime.Gamepad.wButtons;

			// キーボードのリピート情報を保存
			m_joyKeyStateRepeat = joykeyState;
		}
		else
		{
			// キーボードのリピート情報を保存
			m_joyKeyStateRepeat.Gamepad.wButtons = 0;
		}

		m_joyKeyState = joykeyState;                // プレス処理
	}
	else
	{
		m_Connect = false;
	}
}

//=============================================
//接続されてるか取得
//=============================================
bool CInputPad::GetConnet()
{
	return m_Connect;
}

//=============================================
//プレス情報取得
//=============================================
bool CInputPad::GetPress(JOYKEY Key)
{
	return (m_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=============================================
//トリガー情報取得
//=============================================
bool CInputPad::GetTrigger(JOYKEY Key)
{
	return (m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=============================================
//リリース情報取得
//=============================================
bool CInputPad::GetRelease(JOYKEY Key)
{
	return(m_ajoyKeyStateRelease.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//=============================================
//コンストラクタ
//=============================================
XINPUT_STATE* CInputPad::GetXInputState(void)
{
	return &m_XInput;
}

//=============================================
//コンストラクタ
//=============================================
void CInputPad::UpdateStick(void)
{
	//キーボードの状態を取得
	if (XInputGetState(0, &m_XInput) == ERROR_SUCCESS)
	{
		for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
		{
			float fX, fY; //スティックのX軸、Y軸

			switch (nCntStick)
			{
			case STICKTYPE_LEFT:
				fX = (GetXInputState()->Gamepad.sThumbLX);
				fY = (GetXInputState()->Gamepad.sThumbLY);
				break;
			case STICKTYPE_RIGHT:
				fX = (GetXInputState()->Gamepad.sThumbRX);
				fY = (GetXInputState()->Gamepad.sThumbRY);
				break;
			}

			//角度を取得
			m_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

			//スティックの倒し具合を取得
			m_stick.afTplDiameter[nCntStick] = fabsf(fX);

			if (m_stick.afTplDiameter[nCntStick] < fabsf(fY))
			{
				m_stick.afTplDiameter[nCntStick] = fabsf(fY);
			}

			m_stick.afTplDiameter[nCntStick] /= 32768.0f; //倒している状態の初期値

			//方向入力フラグを初期化
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				m_bAngle[nCntStick][nCntAngle] = false;
			}

			if (m_stick.afTplDiameter[nCntStick] > 0.1f)
			{
				//角度が四分割で上に位置する時、上フラグを真にする
				if ((m_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (m_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
				{
					m_bAngle[nCntStick][STICKANGLE_UP] = true;
				}

				//角度が四分割で下に位置する時、下フラグを真にする
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
				{
					m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
				}

				//角度が四分割で左に位置する時、左フラグを真にする
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (m_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
				{
					m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
				}

				//角度が四分割で右に位置する時、右フラグを真にする
				else if ((m_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
				{
					m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
				}
			}

			//角度に応じた入力処理
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				//スティックのトリガー情報を保存
				m_stick.abAngleTrigger[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & m_bAngle[nCntStick][nCntAngle];

				//スティックのリリース情報を保存
				m_stick.abAngleRelease[nCntStick][nCntAngle] = (m_stick.abAnglePress[nCntStick][nCntAngle] ^ m_bAngle[nCntStick][nCntAngle]) & ~m_bAngle[nCntStick][nCntAngle];

				//現在の時間を取得
				m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

				if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > JOYPAD_SPEED))
				{
					//最後に真を返した時間を保存
					m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];

					//スティックのリピート情報を保存
					m_stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
				}
				else
				{
					//スティックのリピート情報を保存
					m_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
				}

				//スティックのプレス情報を保存
				m_stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
		}
	}
}

//=============================================
//コンストラクタ
//=============================================
CInputPad::STICKINPUT CInputPad::GetStick(void)
{
	return m_stick;
}

//=============================================
//コンストラクタ
//=============================================
float CInputPad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //角度

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

//=============================================
//コンストラクタ
//=============================================
WORD CInputPad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}
