//=============================================
//
//�Q�[�W�Ǘ�[gauge.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"

//�����_���[�N���X
class CGauge : public CObject2D
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	static const int GAUGE_PRIORITY = 81;  //�`�揇
	static const float MAX_GAUGE_WIDE;  //�Q�[�W�̍ő�l
	CGauge(int nPriority = GAUGE_PRIORITY);
	~CGauge()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void AddGauge();
	void SubGauge(float fCost);
	void SetGaugeVtx(float rhw, D3DCOLOR col);
	static CGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	//static LPDIRECT3DTEXTURE9 m_pTexture;
};
#endif