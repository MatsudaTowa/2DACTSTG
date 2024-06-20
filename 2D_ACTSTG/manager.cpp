//=============================================
//
//3DTemplate[manager.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "manager.h"
#include "renderer.h"
#include "fade.h"

//シーン設定
CScene* CManager::m_pScene = nullptr;

//シーン設定
CFade* CManager::m_pFade = nullptr;

//レンダラー設定
CRenderer*CManager::m_pRenderer = nullptr;

//キーボード設定
CInputKeyboard*CManager::m_pKeyboard = nullptr;

//マウス設定
CInputMouse* CManager::m_pMouse = nullptr;

//カメラ設定
CCamera*CManager::m_pCamera = nullptr;

//ライト設定
CLight*CManager::m_pLight = nullptr;

//テクスチャ設定
CTexture* CManager::m_pTexture = nullptr;

//モデル設定
CModel* CManager::m_pModel = nullptr;

//=============================================
//コンストラクタ
//=============================================
CManager::CManager()
{
}

//=============================================
//デストラクタ
//=============================================
CManager::~CManager()
{
}

//=============================================
//初期化
//=============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	//生成＆初期化
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer();
		m_pRenderer->Init(hWnd,bWindow);
	}
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard();

		//キーボードの初期化処理
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CInputMouse();

		//マウスの初期化処理
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//カメラ生成
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera();
		m_pCamera->Init();
	}

	//ライト生成
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight();
		m_pLight->Init();
	}

	//テクスチャ生成
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture();
	}

	//モデル生成
	if (m_pModel == nullptr)
	{
		m_pModel = new CModel();
	}

	//最初のシーン設定
	if (m_pFade == nullptr)
	{
		m_pFade = new CFade();
	}

	m_pFade->SetFade(CScene::MODE::MODE_TITLE);

	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CManager::Uninit()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pModel != nullptr)
	{
		m_pModel->Unload();
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
	}

	//キーボードの終了処理
	m_pKeyboard->Uninit();
	//マウスの終了処理
	m_pMouse->Uninit();
}

//=============================================
//更新処理
//=============================================
void CManager::Update()
{
	//更新処理
	m_pRenderer->Update();
	m_pCamera->Update();
	m_pKeyboard->Update();
	m_pMouse->Update();

	//シーンの更新
	if (m_pFade != nullptr)
	{
		m_pFade->Update();

	}

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
}

//=============================================
//描画処理
//=============================================
void CManager::Draw()
{
	//描画処理
	m_pRenderer->Draw();

	if (m_pFade != nullptr)
	{
		m_pFade->Draw();

	}

	//シーンの描画
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}

//=============================================
//シーン設定
//=============================================
void CManager::SetMode(CScene::MODE mode)
{

	//シーン終了
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//シーン切り替え
	if (m_pScene == nullptr)
	{
		m_pScene = CScene::Create(mode);
	}
}

//=============================================
//レンダラー取得
//=============================================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================
//キーボード情報取得
//=============================================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================
//マウス情報取得
//=============================================
CInputMouse* CManager::GetMouse()
{
	return m_pMouse;
}

//=============================================
//カメラ取得
//=============================================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//=============================================
//ライト取得
//=============================================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//=============================================
//テクスチャ取得
//=============================================
CTexture* CManager::GetTexture()
{
	return m_pTexture;
}

//=============================================
//モデル取得
//=============================================
CModel* CManager::GetModel()
{
	return m_pModel;
}
