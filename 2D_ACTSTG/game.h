//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //‚±‚ê‚ª’è‹`‚³‚ê‚Ä‚È‚¢‚Æ‚«

#define _GAME_H_
#include "main.h"
#include "scene.h"
class CGame:public CScene
{
public:
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};
#endif