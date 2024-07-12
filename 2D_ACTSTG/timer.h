////=============================================
////
////タイマー処理「timer.h」
//// Author松田永久
////
////=============================================
//#ifndef _TIMER_H_ //これが定義されてないとき
//#define _TIMER_H_
//#include "main.h"
//#include "object2D.h"
//#include "number.h"
//
////=============================================
////タイマークラス
////=============================================
//class CTimer :public CObject2D
//{
//public:
//	static const std::string TEXTURE_NAME;	//テクスチャの名前
//	static const int TIMER_PRIORITY = 81;  //描画順
//	static const int LIMIT_TIME = 180;  //制限時間
//	static const int NUM_DIGIT = 3;  //桁数
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
//	int m_nFrameCnt; //何フレーム経ったかカウントする変数
//	int m_nCurrentTime; //今の時間
//	static CNumber* m_pNumber[NUM_DIGIT];
//};
//
//#endif // DEBUG