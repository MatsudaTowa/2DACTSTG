////=============================================
////
////�^�C�}�[�����utimer.h�v
//// Author���c�i�v
////
////=============================================
//#ifndef _TIMER_H_ //���ꂪ��`����ĂȂ��Ƃ�
//#define _TIMER_H_
//#include "main.h"
//#include "object2D.h"
//#include "number.h"
//
////=============================================
////�^�C�}�[�N���X
////=============================================
//class CTimer :public CObject2D
//{
//public:
//	static const std::string TEXTURE_NAME;	//�e�N�X�`���̖��O
//	static const int TIMER_PRIORITY = 81;  //�`�揇
//	static const int LIMIT_TIME = 180;  //��������
//	static const int NUM_DIGIT = 3;  //����
//
//	CTimer(int nPriority = TIMER_PRIORITY);
//	~CTimer()override;
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//
//	static CTimer*Create(D3DXVECTOR3 pos,D3DXVECTOR2 size);
//private:
//	void SetTimerVtx();
//	int m_nFrameCnt; //���t���[���o�������J�E���g����ϐ�
//	int m_nCurrentTime; //���̎���
//	static CNumber* m_pNumber[NUM_DIGIT];
//};
//
//#endif // DEBUG