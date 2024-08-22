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

//=============================================
//�G�l�~�[�N���X
//=============================================
class CEnemy : public CCharacter
{
public:
	static const int ENEMY_PRIORITY = 4; //�`�揇
	static const float DEFAULT_MOVE; //�ʏ펞�̈ړ�	 

	static const int NORMAL_SHOT_FRAME = 120; //���˂���J�E���g
	//�G�l�~�[�̗񋓒�`
	typedef enum
	{
		ENEMY_TYPE_NORMAL = 0,
		ENEMY_TYPE_MAX,
	}ENEMY_TYPE;

	CEnemy(int nPriority = ENEMY_PRIORITY);
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	virtual void EnemyMove() = 0; //�G�l�~�[�ړ�����

	//�G�l�~�[�쐬
	static CEnemy* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const ENEMY_TYPE& type);

	void Damage(int nDamage); //�����蔻��

	bool PlayerDistance(); //�v���C���[�Ƃ̋����𑪂�֐�

	ENEMY_TYPE m_Type; //�G�l�~�[�̎��

	static int m_nNumEnemy; //�G�l�~�[�̑���

private:
	static const std::string MODEL_NAME;	//���f���̖��O  
	static const float DAMPING_COEFFICIENT; //�ړ���R
	static const float DEADZONE_Y; //������߂�����j��
	static const int EFFECT_LIFE = 3; //�G�t�F�N�g�̗̑�
	static const int ENEMY_DEFAULT_LIFE = 5; //�G�l�~�[�̗̑�

	static LPDIRECT3DTEXTURE9 m_pTextureTemp;

	static LPD3DXMESH m_pMesh;
	static 	LPD3DXBUFFER m_pBuffMat; //�}�e���A�����
	static	DWORD m_dwNumMat; //�}�e���A����

	int m_nShotCnt; //�e�𔭎˂���J�E���g

};

//=============================================
//�ʏ�̓G�N���X
//=============================================
class CNormalEnemy : public CEnemy
{
public:
	static const int NORMAL_ENEMY_TURNFRAME = 90; //�m�[�}���̃G�l�~�[�̈ړ��܂�Ԃ��t���[��

	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	~CNormalEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void EnemyMove() override;
private:
	int m_nTurnFrameCnt; //�܂�Ԃ��t���[�����J�E���g����ϐ�
	bool m_bOldWay; //�ߋ��̕���
};
#endif