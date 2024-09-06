//=============================================
//
//3DTemplate[title.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _TITLE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _TITLE_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include "title_screen.h"
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
	//�v���C���[
	CPlayer*m_pPlayer;

	CTitle_Screen*m_pTitleScreen[2];
};
#endif