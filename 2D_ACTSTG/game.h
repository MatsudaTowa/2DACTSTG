//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //これが定義されてないとき

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "edit.h"
#include "timer.h"
#include "enemy.h"

class CGame:public CScene
{
public:

	//読み込むときに必要なエネミーの構造体
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	}LOAD_ENEMY;

	static const std::string ENEMY_FILE;	//エネミーのファイル
	static const int DELAY_CNT = 30; //リザルトに飛ぶまでのディレイ
	static const int ENEMY_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	int m_nResultDelay; //リザルトへのディレイ
	bool m_bEdit; //エディットしてるかどうか
	LOAD_ENEMY m_LoadEnemy; //読み込むときに必要なエネミーの情報
	static CEdit*m_pEdit;
	static CTimer*m_pTimer;

	void LoadEnemy(const std::string* pFileName);
};
#endif