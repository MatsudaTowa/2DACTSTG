//=============================================
//
//数字管理「number.h」
// Author松田永久
//
//=============================================
#ifndef _NUMBER_H_ //これが定義されてないとき
#define _NUMBER_H_
#include "main.h"

//=============================================
//ナンバークラス
//=============================================
class CNumber
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	CNumber();
	~CNumber();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw(LPDIRECT3DTEXTURE9 pTex, LPDIRECT3DVERTEXBUFFER9 pBuff);

	//数字のポリゴン生成処理
	static void SetNumVtx(LPDIRECT3DVERTEXBUFFER9 pBuff,float rhw, D3DCOLOR col, D3DXVECTOR3 pos ,D3DXVECTOR2 size,float fMinTexU,float fMaxTexU);

	//桁数の設定処理
	void SetDigit(int nDigit)
	{
		m_nDigit = nDigit;
	}

	//最初の番号の設定処理
	void SetStartNumber(int nStartNum)
	{
		m_nStaretNum = nStartNum;
	}

	//桁数の取得処理
	int GetDigit();

	//最初の数字取得
	int GetStartNum();

private:
	int m_nStaretNum; //始まりの数字
	int m_nDigit; //桁数
};

#endif // DEBUG