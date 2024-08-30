//=============================================
//
//3DTemplate[game.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_H_
#include "main.h"
#include "scene.h"
#include "edit.h"
#include "timer.h"
#include "enemy.h"

class CGame:public CScene
{
public:

	//�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	}LOAD_ENEMY;

	static const std::string ENEMY_FILE;	//�G�l�~�[�̃t�@�C��
	static const int DELAY_CNT = 30; //���U���g�ɔ�Ԃ܂ł̃f�B���C
	static const int ENEMY_TXT_MAX = 2048; //�G��ǂݍ��ލۂ̓ǂݍ��߂�ő啶����
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
	int m_nResultDelay; //���U���g�ւ̃f�B���C
	bool m_bEdit; //�G�f�B�b�g���Ă邩�ǂ���
	LOAD_ENEMY m_LoadEnemy; //�ǂݍ��ނƂ��ɕK�v�ȃG�l�~�[�̏��
	static CEdit*m_pEdit;
	static CTimer*m_pTimer;

	void LoadEnemy(const std::string* pFileName);
};
#endif