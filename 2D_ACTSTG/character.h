//=============================================
//
//3DTemplate[character.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _CHARACTER_H_
#include "main.h"
#include "objectX.h"
//�v���C���[�N���X
class CCharacter : public CObjectX
{
public:
	static const std::string MODEL_NAME;	//���f���̖��O

	static const int CHARACTER_PRIORITY = 8; //�`�揇

	CCharacter(int nPriority = CHARACTER_PRIORITY);
	~CCharacter()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Gravity(); //�d�͏���
	void HitBlock(); //�u���b�N�����蔻��

	//�ړ��ʑ��
	void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	//oldpos���
	void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	}

	//���n���Ă邩�ǂ�������
	void SetLanding(bool bLanding)
	{
		m_bLanding = bLanding;
	}

	//�ǂ��������Ă邩�ǂ�������(true:�Efalse:��)
	void SetWay(bool bWay)
	{
		m_bWay = bWay;
	}

	//�ړ��ʎ擾
	D3DXVECTOR3& GetMove();

	//�ߋ��̈ʒu�擾
	D3DXVECTOR3& GetOldPos();

	//���n���Ă邩�ǂ����擾
	bool& GetLaunding();

	//�ǂ��������Ă邩�ǂ������擾(true:�Efalse:��)
	bool& GetWay();

private:
	static const float GRAVITY_MOVE; //�d�͒l
	static const float GRAVITY_MAX; //�d�͍ő�l

	D3DXVECTOR3 m_move; //���x
	D3DXVECTOR3 m_oldpos; //�ߋ��̈ʒu
	bool m_bLanding; //���n���Ă邩�ǂ���
	bool m_bWay; //�ǂ��������Ă邩(true:�Efalse:��)
};
#endif