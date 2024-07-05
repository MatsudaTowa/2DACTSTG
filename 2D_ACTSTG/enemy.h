//=============================================
//
//3DTemplate[enemy.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENEMY_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENEMY_H_
#include "main.h"
#include "character.h"
//�G�l�~�[�N���X
class CEnemy : public CCharacter
{
public:
	static const int ENEMY_PRIORITY = 4; //�`�揇

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//�G�l�~�[�쐬
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);

	void HitDamage(int nDamage); //�����蔻��

private:
	static const std::string MODEL_NAME;	//���f���̖��O
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�	   
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEADZONE_Y; //������߂�����j��
	static const int EFFECT_LIFE = 3; //�G�t�F�N�g�̗̑�
	static const int ENEMY_DEFAULT_LIFE = 5; //�G�l�~�[�̗̑�


	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	void EnemyMove(); //�G�l�~�[�ړ�����

	int m_nLife;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����
};
#endif