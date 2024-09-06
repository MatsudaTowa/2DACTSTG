//=============================================
//
//3DTemplate[title.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TITLE_H_ //これが定義されてないとき

#define _TITLE_H_
#include "main.h"
#include "scene.h"
#include "player.h"
class CTitle :public CScene
{
public:
	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	//プレイヤー
	CPlayer*pPlayer;
};
#endif