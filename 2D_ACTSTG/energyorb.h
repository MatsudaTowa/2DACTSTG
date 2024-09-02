//=============================================
//
//�G�l���M�[�񕜃I�[�u[energyorb.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _ENERGYORB_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _ENERGYORB_H_
#include "main.h"
#include "billboard.h"
#include "button_UI.h"
class CEnergyOrb : public CBillboard
{
public:
	static const std::string ENERGY_ORB_TEXTURE_NAME;	//�e�N�X�`���̖��O

	static const int ENERGY_ORB_PRIORITY = 3; //�`�揇

	CEnergyOrb(int nPriority = ENERGY_ORB_PRIORITY);
	~CEnergyOrb()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	//�u���b�N�쐬
	static CEnergyOrb* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);
private:

	void HitOrb(); //�I�[�u�Ƃ̓����蔻��
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
};
#endif