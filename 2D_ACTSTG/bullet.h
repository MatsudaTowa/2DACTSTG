//=============================================
//
//3DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BULLET_H_

class CBullet : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int BULLET_PRIORITY = 4; //�`�揇

	typedef enum
	{
		BULLET_TYPE_PLAYER = 0,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_MAX,
	}BULLET_TYPE;

	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�e�쐬
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife,int nDamage, BULLET_TYPE type);
private:
	BULLET_TYPE m_type;
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif