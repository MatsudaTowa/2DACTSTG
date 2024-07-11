////=============================================
////
////数字管理「number.h」
//// Author松田永久
////
////=============================================
////#ifndef _NUMBER_H_ //これが定義されてないとき
////#define _NUMBER_H_
////#include "main.h"
////#include "object2D.h"
////
////=============================================
////ナンバークラス
////=============================================
////class CNumber
////{
////public:
////	static const std::string TEXTURE_NAME;	//テクスチャの名前
////	CNumber();
////	~CNumber();
////	HRESULT Init();
////	void Uninit();
////	void Update();
////	void Draw();
////
////	static CNumber*Create(D3DXVECTOR3 pos,D3DXVECTOR2 size);
////
////	桁数の設定処理
////	void SetDigit(int nDigit)
////	{
////		m_nDigit = nDigit;
////	}
////
////	桁数の取得処理
////	int GetDigit();
////
////private:
////	int m_nStaretNumber; //始まりの数字
////	int m_nDigit; //桁数
////};
////
////#endif // DEBUG