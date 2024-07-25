////=============================================
//// 
////親子関係のパーツ[model.h]
////Auther Matsuda Towa
////
////=============================================
//#ifndef _MODEL_PARTS_H_ //これが定義されてないとき
//
//#define _MODEL_PARTS_H_
//#include "main.h"
//#include "objectX.h"
//
//class CModel_Parts:public CObjectX
//{
//public:
//	static const int MAX_MODEL = 256; //モデルの数
//
//	//モデル情報構造体定義
//	typedef struct
//	{
//		LPD3DXMESH pMesh; //メッシュ情報
//		LPD3DXBUFFER pBuffMat; //マテリアル情報
//		DWORD dwNumMat; //マテリアル数;
//		std::string* ModelName; //モデルネーム保存用
//	}MODEL_INFO;
//	CModel_Parts();
//	~CModel_Parts();
//	void Unload(); //モデル破棄
//	int Regist(const std::string* pModel);
//	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,const std::string* pModel);
//	void SetParent(CModel_Parts*pParent);
//	MODEL_INFO GetModelInfo(int nIdx); //モデル情報取得
//private:
//	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
//	MODEL_INFO m_ModelInfo[MAX_MODEL]; //モデル情報
//	int m_nNumAll; //モデル総数
//
//	D3DXVECTOR3 m_pos;
//	D3DXVECTOR3 m_rot;
//	D3DXVECTOR3 m_minpos; //pos最小値
//	D3DXVECTOR3 m_maxpos; //pos最大値
//	CModel_Parts*m_pParent; //親パーツへのポインタ
//};
//#endif