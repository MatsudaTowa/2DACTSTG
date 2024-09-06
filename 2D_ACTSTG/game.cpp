//=============================================
//
//3DTemplate[game.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "player.h"
#include "player_test.h"
#include "bullet.h"
#include "effect.h"
#include "gauge_fream.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"

//エネミーのファイル
const std::string CGame::ENEMY_FILE = "data\\FILE\\enemy.txt";

//エディット設定
CEdit* CGame::m_pEdit = nullptr;

//タイム設定
CTimer* CGame::m_pTimer = nullptr;

//=============================================
//コンストラクタ
//=============================================
CGame::CGame():m_nResultDelay(0),m_bEdit(false)
{//イニシャライザーでプライオリティ設定、エディットしてない状態に変更

	//読み込むエネミーの情報初期化
	m_LoadEnemy.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_LoadEnemy.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_LoadEnemy.type = CEnemy::ENEMY_TYPE::ENEMY_TYPE_NORMAL;
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{

	if (m_pEdit == nullptr)
	{
		m_pEdit = new CEdit;
	}

	if (m_pTimer == nullptr)
	{
		m_pTimer = new CTimer;

		m_pTimer->Init();
	}

	//ブロック生成
	CBlock* pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(0.0, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(10.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	pBlock = CBlock::Create(CBlock::BLOCKTYPE_DEFAULT, D3DXVECTOR3(5.0f, 50.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3, false);

	//ゲージのフレームUI生成
	CGauge_Fream* pGauge_Fream = CGauge_Fream::Create(D3DXVECTOR3(980.0f,80.0f,0.0f),D3DXVECTOR2(280.0f,120.0f));

	//地面生成
	CField* pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));

	//プレイヤー生成
	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(-900.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),5);

	//プレイヤー生成
	//CPlayer_test* pPlayer_test = CPlayer_test::Create(D3DXVECTOR3(-450.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);

	//エネミー生成
	LoadEnemy(&CGame::ENEMY_FILE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		m_bEdit = m_bEdit ? false : true;

		CCamera*pCamera = CManager::GetCamera();

		pCamera->ResetCamera();
	}

	if (m_bEdit)
	{
		m_pEdit->Update();
	}
	
	//if (m_bEdit == false)
	//{
		CObject::UpdateAll();

		if (m_pTimer != nullptr)
		{
			m_pTimer->Update();
		}
	//}

	if (CPlayer::m_PlayerDeath || CEnemy::m_nNumEnemy <= 0)
	{//プレイヤーが死ぬかエネミーを全部殺したら
		//カウント加算
		m_nResultDelay++;
		if (m_nResultDelay >= DELAY_CNT)
		{
			//ディレイカウントリセット
			m_nResultDelay = 0;

			//リザルト遷移
			CManager::SetMode(CScene::MODE::MODE_RESULT);
		}
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		CManager::SetMode(CScene::MODE::MODE_RESULT);
	}
#endif // DEBUG


}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//敵の読み込み
//=============================================
void CGame::LoadEnemy(const std::string* pFileName)
{
	char aDataSearch[ENEMY_TXT_MAX];
	char aEqual[ENEMY_TXT_MAX]; //[＝]読み込み用
	int nNumEnemy; //エネミーの数

	//ファイルの読み込み
	FILE* pFile = fopen(pFileName->c_str(), "r");

	if (pFile == NULL)
	{//種類の情報のデータファイルが開けなかった場合
		//処理を終了する
		return;
	}
	//ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); //検索

		if (!strcmp(aDataSearch, "END"))
		{//読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_ENEMY"))
		{//モデル数読み込み
			fscanf(pFile, "%s", &aEqual[0]);
			fscanf(pFile, "%d", &nNumEnemy);
		}
		if (!strcmp(aDataSearch, "ENEMYSET"))
		{
			//項目ごとのデータを代入
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); //検索

				if (!strcmp(aDataSearch, "END_ENEMYSET"))
				{
					//エネミー生成
					CEnemy* pEnemy = CEnemy::Create(m_LoadEnemy.pos, m_LoadEnemy.rot, m_LoadEnemy.type);
					break;
				}
				else if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.pos.x,
						&m_LoadEnemy.pos.y,
						&m_LoadEnemy.pos.z);
				}
				else if (!strcmp(aDataSearch, "ROT"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%f %f %f",
						&m_LoadEnemy.rot.x,
						&m_LoadEnemy.rot.y,
						&m_LoadEnemy.rot.z);
				}
				else if (!strcmp(aDataSearch, "TYPE"))
				{
					fscanf(pFile, "%s", &aEqual[0]);
					fscanf(pFile, "%d", &m_LoadEnemy.type);
				}
			}
		}
	}
}
