//=============================================
//
//�����Ǘ��unumber.h�v
// Author���c�i�v
//
//=============================================
#ifndef _NUMBER_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _NUMBER_H_
#include "main.h"

//=============================================
//�i���o�[�N���X
//=============================================
class CNumber
{
public:
	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
	CNumber();
	~CNumber();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw(LPDIRECT3DTEXTURE9 pTex, LPDIRECT3DVERTEXBUFFER9 pBuff);

	//�����̃|���S����������
	static void SetNumVtx(LPDIRECT3DVERTEXBUFFER9 pBuff,float rhw, D3DCOLOR col, D3DXVECTOR3 pos ,D3DXVECTOR2 size,float fMinTexU,float fMaxTexU);

	//�����̐ݒ菈��
	void SetDigit(int nDigit)
	{
		m_nDigit = nDigit;
	}

	//�ŏ��̔ԍ��̐ݒ菈��
	void SetStartNumber(int nStartNum)
	{
		m_nStaretNum = nStartNum;
	}

	//�����̎擾����
	int GetDigit();

	//�ŏ��̐����擾
	int GetStartNum();

private:
	int m_nStaretNum; //�n�܂�̐���
	int m_nDigit; //����
};

#endif // DEBUG