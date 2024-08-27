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
class CGame:public CScene
{
public:
	static const int DELAY_CNT = 30; //リザルトに飛ぶまでのディレイ
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	int m_nResultDelay; //リザルトへのディレイ
	bool m_bEdit; //エディットしてるかどうか
	static CEdit*m_pEdit;
};
#endif