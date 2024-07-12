////=============================================
////
////�����Ǘ��unumber.cpp�v
//// Author���c�i�v
////
////=============================================
//#include "number.h"
//#include "manager.h"
//
////=============================================
////�R���X�g���N�^
////=============================================
//CNumber::CNumber()
//{
//}
//
////=============================================
////�f�X�g���N�^
////=============================================
//CNumber::~CNumber()
//{
//}
//
////=============================================
////������
////=============================================
//HRESULT CNumber::Init()
//{
//
//	return S_OK;
//}
//
//
////=============================================
////�I��
////=============================================
//void CNumber::Uninit()
//{
//}
//
////=============================================
////�X�V
////=============================================
//void CNumber::Update()
//{
//}
//
////=============================================
////�`��
////=============================================
//void CNumber::Draw(LPDIRECT3DTEXTURE9 pTex, LPDIRECT3DVERTEXBUFFER9 pBuff)
//{
//	CRenderer* pRender = CManager::GetRenderer();
//
//	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, pBuff, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, pTex);
//	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
//	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
//
//	//�|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		0,
//		2);
//
//	//�e�N�X�`���g�厞�̐F����`���
//	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//}
//
////=============================================
////�����̃|���S������
////=============================================
//void CNumber::SetNumVtx(LPDIRECT3DVERTEXBUFFER9 pBuff, float rhw, D3DCOLOR col, D3DXVECTOR3 pos, D3DXVECTOR2 size, float fMinTexU, float fMaxTexU)
//{
//	CRenderer* pRender = CManager::GetRenderer();
//
//	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
//	if (pBuff == nullptr)
//	{
//		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pBuff, NULL);
//	}
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
//
//	pBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//���_���W�̐ݒ�
//	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x
//		, pos.y - size.y
//		, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x
//		, pos.y - size.y
//		, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x
//		, pos.y + size.y
//		, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x
//		, pos.y + size.y
//		, 0.0f);
//
//	//rhw�̐ݒ�
//	pVtx[0].rhw = rhw;
//	pVtx[1].rhw = rhw;
//	pVtx[2].rhw = rhw;
//	pVtx[3].rhw = rhw;
//
//	//���_�J���[�̐ݒ�
//	pVtx[0].col = col;
//	pVtx[1].col = col;
//	pVtx[2].col = col;
//	pVtx[3].col = col;
//
//	//�e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(fMinTexU, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(fMaxTexU, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(fMinTexU, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(fMaxTexU, 1.0f);
//	
//	//�A�����b�N
//	pBuff->Unlock();
//}
//
//
////=============================================
////�����擾
////=============================================
//int CNumber::GetDigit()
//{
//	return m_nDigit;
//}
//
////=============================================
////�ŏ��̔ԍ��擾
////=============================================
//int CNumber::GetStartNum()
//{
//	return m_nStaretNum;
//}
