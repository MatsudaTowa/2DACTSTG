//=============================================
//
//3DTemplate[scene.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _SCENE_H_ //これが定義されてないとき

#define _SCENE_H_
#include "main.h"

//=============================================
//  クラス定義
//=============================================
class CScene
{
public:

	//画面の種類の列挙
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;

	// メンバ関数
	CScene();
	virtual ~CScene();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// 静的メンバ関数
	static CScene* Create(MODE mode);

private:

	// メンバ変数
	MODE m_Mode; //現在のモード
};
#endif