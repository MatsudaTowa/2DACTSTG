//=============================================
//
//スコア処理「scorer.h」
// Author松田永久
//
//=============================================
#ifndef _SCORE_H_ //これが定義されてないとき
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"

//=============================================
//スコアクラス
//=============================================
class CScore
{
public:
	static const int NUM_DIGIT = 6;  //桁数
	static const float DIGIT_SHIFT;  //桁ごとに座標をずらす

	CScore();
	~CScore();
	HRESULT Init();
	void Uninit();
	void Update();
	void AddScore(int nValue);

private:
	void SetScore(int nScore);
	int m_nScore; //スコアの値
	D3DXVECTOR3 m_pos;
	CNumber* m_pNumber[NUM_DIGIT];
};

#endif // DEBUG