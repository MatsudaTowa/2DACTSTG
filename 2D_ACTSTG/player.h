//=============================================
//
//3DTemplate[player.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_H_
#include "main.h"
#include "character.h"
//�v���C���[�N���X
class CPlayer : public CCharacter
{
public:
	static const int PLAYER_PRIORITY = 8; //�`�揇

	CPlayer(int nPriority = PLAYER_PRIORITY);
	~CPlayer()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�v���C���[�쐬
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	static const std::string MODEL_NAME;	//���f���̖��O
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEFAULT_JUMP; //�ʏ펞�̃W�����v��
	static const int MAX_JUMPCNT; //�W�����v��
	static const float DEADZONE_Y; //������߂�����v���C���[�j��

	void ReSpawn(); //���X�|�[��
	void PlayerMove(); //�v���C���[�ړ�����
	void ShotBullet(D3DXVECTOR3 pos,bool bWay); //�e���ˏ���
	void PerformMelee(D3DXVECTOR3 pos, bool bWay); //�ߐڍU������

	bool m_bSize; //�T�C�Y�ύX���邩�ǂ���
	bool m_OldPress; //���N���b�N������Ă邩�ǂ���
	int m_nJumpCnt; //�W�����v�J�E���g

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����
};
#endif