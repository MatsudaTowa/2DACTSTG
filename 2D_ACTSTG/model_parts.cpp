////=============================================
//// 
////�e�q�֌W�̃p�[�c[model.h]
////Auther Matsuda Towa
////
////=============================================
//#include "model_parts.h"
//#include "manager.h"
//
////=============================================
////�R���X�g���N�^
////=============================================
//CModel_Parts::CModel_Parts()
//{
//}
//
////=============================================
////�f�X�g���N�^
////=============================================
//CModel_Parts::~CModel_Parts()
//{
//}
//
////=============================================
////�폜
////=============================================
//void CModel_Parts::Unload()
//{
//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
//	{
//		if (m_ModelInfo[nCnt].pBuffMat != nullptr)
//		{//�}�e���A���j��
//			m_ModelInfo[nCnt].pBuffMat->Release();
//			m_ModelInfo[nCnt].pBuffMat = nullptr;
//			m_ModelInfo[nCnt].dwNumMat = 0;
//		}
//		if (m_ModelInfo[nCnt].pMesh != nullptr)
//		{//���b�V���j��
//			m_ModelInfo[nCnt].pMesh->Release();
//			m_ModelInfo[nCnt].pMesh = nullptr;
//		}
//
//		if (m_ModelInfo[nCnt].ModelName != nullptr)
//		{//���f���l�[���j��
//			m_ModelInfo[nCnt].ModelName = nullptr;
//		}
//	}
//	m_nNumAll = 0;
//}
//
////=============================================
////���f���o�^
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
//			//X�t�@�C���̓ǂݍ���
//			D3DXLoadMeshFromX(pModel->c_str(),
//				D3DXMESH_SYSTEMMEM,
//				pDevice,
//				NULL,
//				&m_ModelInfo[nCnt].pBuffMat,
//				NULL,
//				&m_ModelInfo[nCnt].dwNumMat,
//				&m_ModelInfo[nCnt].pMesh);
//
//			//�����̃t�@�C���p�X��ۑ�
//			m_ModelInfo[nCnt].ModelName = (std::string*)pModel;
//			nIdx = nCnt;	//�ԍ��̕ۑ�
//			m_nNumAll++;	//�����̃J�E���g�A�b�v
//			break;
//		}
//		else if (m_ModelInfo[nCnt].ModelName == pModel)
//		{//�����̃��f�������݂���Ȃ�
//
//			//�ԍ���������break
//			nIdx = nCnt;
//			break;
//		}
//	}
//	return nIdx;
//}
//
////=============================================
////����
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
//	pModelParts->m_pos = pos; //���_���
//	pModelParts->m_rot = rot; //���_���
//
//	//X�t�@�C���ǂݍ���
//	pModelParts->BindXFile(pModelParts->GetModelInfo(pModelParts->Regist(pModel)).pBuffMat, //�}�e���A���擾
//		pModelParts->GetModelInfo(pModelParts->Regist(pModel)).dwNumMat, //�}�e���A�����擾
//		pModelParts->GetModelInfo(pModelParts->Regist(pModel)).pMesh); //���b�V�����擾
//
//	return pModelParts;
//}
//
////=============================================
////�e�p�[�c�̐ݒ�
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
