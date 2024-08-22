//=============================================
//
//集中斬撃[flow.h]
//Auther Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _FLOW_H_ //これが定義されてないとき

#define _FLOW_H_

class CFlow : public CAttack_Manager
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int FLOW_PRIORITY = 4; //描画順

	typedef enum
	{
		FLOW_TYPE_PLAYER = 0,
		FLOW_TYPE_ENEMY,
		FLOW_TYPE_MAX,
	}FLOW_TYPE;

	CFlow(int nPriority = FLOW_PRIORITY);
	~CFlow()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//弾作成
	static CFlow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nLife,  FLOW_TYPE type);
private:
	FLOW_TYPE m_type;
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif