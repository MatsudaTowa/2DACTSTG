////=============================================
//// 
////親子関係のパーツ[model.h]
////Auther Matsuda Towa
////
////=============================================
//#include "model_parts.h"
//#include "manager.h"
//
////=============================================
////コンストラクタ
////=============================================
//CModel_Parts::CModel_Parts()
//{
//}
//
////=============================================
////デストラクタ
////=============================================
//CModel_Parts::~CModel_Parts()
//{
//}
//
////=============================================
////削除
////=============================================
//void CModel_Parts::Unload()
//{
//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
//	{
//		if (m_ModelInfo[nCnt].pBuffMat != nullptr)
//		{//マテリアル破棄
//			m_ModelInfo[nCnt].pBuffMat->Release();
//			m_ModelInfo[nCnt].pBuffMat = nullptr;
//			m_ModelInfo[nCnt].dwNumMat = 0;
//		}
//		if (m_ModelInfo[nCnt].pMesh != nullptr)
//		{//メッシュ破棄
//			m_ModelInfo[nCnt].pMesh->Release();
//			m_ModelInfo[nCnt].pMesh = nullptr;
//		}
//
//		if (m_ModelInfo[nCnt].ModelName != nullptr)
//		{//モデルネーム破棄
//			m_ModelInfo[nCnt].ModelName = nullptr;
//		}
//	}
//	m_nNumAll = 0;
//}
//
////=============================================
////モデル登録
////=============================================
//int CModel_Parts::Regist(const std::string* pModel)
//{
//	int nIdx;
//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
//	{
//		if (m_ModelInfo[nCnt].pBuffMat == nullptr
//			&& m_ModelInfo[nCnt].pMesh == nullptr)
//		{
//			LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//			//Xファイルの読み込み
//			D3DXLoadMeshFromX(pModel->c_str(),
//				D3DXMESH_SYSTEMMEM,
//				pDevice,
//				NULL,
//				&m_ModelInfo[nCnt].pBuffMat,
//				NULL,
//				&m_ModelInfo[nCnt].dwNumMat,
//				&m_ModelInfo[nCnt].pMesh);
//
//			//引数のファイルパスを保存
//			m_ModelInfo[nCnt].ModelName = (std::string*)pModel;
//			nIdx = nCnt;	//番号の保存
//			m_nNumAll++;	//総数のカウントアップ
//			break;
//		}
//		else if (m_ModelInfo[nCnt].ModelName == pModel)
//		{//引数のモデルが存在するなら
//
//			//番号を代入してbreak
//			nIdx = nCnt;
//			break;
//		}
//	}
//	return nIdx;
//}
//
////=============================================
////生成
////=============================================
//CModel_Parts* CModel_Parts::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const std::string* pModel)
//{
//	CModel_Parts*pModelParts = new CModel_Parts;
//
//	if (pModelParts == nullptr)
//	{
//		return nullptr;
//	}
//
//	pModelParts->m_pos = pos; //頂点代入
//	pModelParts->m_rot = rot; //頂点代入
//
//	//Xファイル読み込み
//	pModelParts->BindXFile(pModelParts->GetModelInfo(pModelParts->Regist(pModel)).pBuffMat, //マテリアル取得
//		pModelParts->GetModelInfo(pModelParts->Regist(pModel)).dwNumMat, //マテリアル数取得
//		pModelParts->GetModelInfo(pModelParts->Regist(pModel)).pMesh); //メッシュ情報取得
//
//	return pModelParts;
//}
//
////=============================================
////親パーツの設定
////=============================================
//void CModel_Parts::SetParent(CModel_Parts* pParent)
//{
//	m_pParent = pParent;
//}
//
//CModel_Parts::MODEL_INFO CModel_Parts::GetModelInfo(int nIdx)
//{
//	return m_ModelInfo[nIdx];
//}
//
