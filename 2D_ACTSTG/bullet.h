//=============================================
//
//3DTemplate[bullet.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //Ç±ÇÍÇ™íËã`Ç≥ÇÍÇƒÇ»Ç¢Ç∆Ç´

#define _BULLET_H_

class CBullet : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//ÉeÉNÉXÉ`ÉÉÇÃñºëO
	static const int BULLET_PRIORITY = 4; //ï`âÊèá

	//ìGÇ©é©ï™Ç©ÇÃîªífÇ∑ÇÈóÒãì
	typedef enum
	{
		BULLET_ALLEGIANCE_PLAYER = 0,
		BULLET_ALLEGIANCE_ENEMY,
		BULLET_ALLEGIANCE_MAX,
	}BULLET_ALLEGIANCE;

	//íeÇÃéÌóﬁ
	typedef enum
	{
		BULLET_TYPE_PANETRARING_SLASH = 0,
		BULLET_TYPE_ELECBULLET,
		BULLET_TYPE_MAX,
	}BULLET_TYPE;

	CBullet(int nPriority = BULLET_PRIORITY);
	~CBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//íeçÏê¨
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot, D3DXVECTOR3 size,int nLife,int nDamage, BULLET_ALLEGIANCE Allegiance,BULLET_TYPE type);

	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	void SetBulletType(BULLET_ALLEGIANCE Allegiance)
	{
		m_Allegiance = Allegiance;
	}

	D3DXVECTOR3 GetMove();

	BULLET_ALLEGIANCE GetBulletType();
private:
	BULLET_ALLEGIANCE m_Allegiance;
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};

class CPanetRaring_Slash : public CBullet
{
public:
	CPanetRaring_Slash(int nPriority = BULLET_PRIORITY);
	~CPanetRaring_Slash()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

class CElecBullet : public CBullet
{
public:
	CElecBullet(int nPriority = BULLET_PRIORITY);
	~CElecBullet()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif