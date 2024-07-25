////=============================================
//// 
////�e�q�֌W�̃p�[�c[model.h]
////Auther Matsuda Towa
////
////=============================================
//#ifndef _MODEL_PARTS_H_ //���ꂪ��`����ĂȂ��Ƃ�
//
//#define _MODEL_PARTS_H_
//#include "main.h"
//#include "objectX.h"
//
//class CModel_Parts:public CObjectX
//{
//public:
//	static const int MAX_MODEL = 256; //���f���̐�
//
//	//���f�����\���̒�`
//	typedef struct
//	{
//		LPD3DXMESH pMesh; //���b�V�����
//		LPD3DXBUFFER pBuffMat; //�}�e���A�����
//		DWORD dwNumMat; //�}�e���A����;
//		std::string* ModelName; //���f���l�[���ۑ��p
//	}MODEL_INFO;
//	CModel_Parts();
//	~CModel_Parts();
//	void Unload(); //���f���j��
//	int Regist(const std::string* pModel);
//	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,const std::string* pModel);
//	void SetParent(CModel_Parts*pParent);
//	MODEL_INFO GetModelInfo(int nIdx); //���f�����擾
//private:
//	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
//	MODEL_INFO m_ModelInfo[MAX_MODEL]; //���f�����
//	int m_nNumAll; //���f������
//
//	D3DXVECTOR3 m_pos;
//	D3DXVECTOR3 m_rot;
//	D3DXVECTOR3 m_minpos; //pos�ŏ��l
//	D3DXVECTOR3 m_maxpos; //pos�ő�l
//	CModel_Parts*m_pParent; //�e�p�[�c�ւ̃|�C���^
//};
//#endif