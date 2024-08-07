//=============================================
//
//当たり判定管理[colision.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _COLISION_H_ //これが定義されてないとき

#define _COLISION_H_

//=============================================
//当たり判定クラス
//=============================================
class CColision
{
public:
	CColision();
	~CColision();
	static bool CheckColision(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //ポリゴン同士当たり判定チェック関数
	static bool CheckColision(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //モデルとポリゴン当たり判定チェック関数
	static bool CheckColision(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos,D3DXVECTOR3 AMaxPos, 
								D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //モデル同士当たり判定チェック関数
	static bool CheckColisionLanding(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //着地の当たり判定チェック関数
	static bool CheckColisionLanding(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //モデルとポリゴン着地の当たり判定チェック関数
	static bool CheckColisionLanding(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //モデル同士当たり着地の判定チェック関数
};
#endif