//=============================================
//
//�v���C���[�̏W���U���͈̔�[flow_range.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "flow_range.h"
#include "manager.h"

//=============================================
//�R���X�g���N�^
//=============================================
CFlow_Range::CFlow_Range(int nPriority):CObject3D(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CFlow_Range::~CFlow_Range()
{
}

//=============================================
//������
//=============================================
HRESULT CFlow_Range::Init()
{
	//�e�N���X�̏�����
	CObject3D::Init();

	//���_�ݒ�
	SetVtxFlow_Range(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.7f));
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CFlow_Range::Uninit()
{
	//�e�N���X�̏I��
	CObject3D::Uninit();
}

//=============================================
//�X�V
//=============================================
void CFlow_Range::Update()
{
	//�e�N���X�̍X�V
	CObject3D::Update();

	//�}�E�X�̏��擾
	CInputMouse* pMouse = CManager::GetMouse();

	//���_�ݒ�
	SetVtxFlow_Range(D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(0.5f, 0.0f, 0.0f, 0.7f));

	if (pMouse->GetRelease(0))
	{
		Uninit();
	}

}

//=============================================
//�`��
//=============================================
void CFlow_Range::Draw()
{
	//�e�N���X�̕`��
	CObject3D::Draw();
}

//=============================================
//����
//=============================================
CFlow_Range* CFlow_Range::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 Minpos, D3DXVECTOR3 Maxpos)
{
	CFlow_Range* pFlow_Range = new CFlow_Range;
	//null�Ȃ�null��Ԃ�
	if (pFlow_Range == nullptr) { return nullptr; }

	pFlow_Range->SetPos(pos); //pos�ݒ�
	pFlow_Range->m_Minpos = Minpos; //�ŏ��l���
	pFlow_Range->m_Maxpos = Maxpos; //�ő�l���
	pFlow_Range->SetRot(rot); //�����ݒ�

	pFlow_Range->SetType(OBJECT_TYPE_FLOW_RANGE); //�^�C�v�ݒ�

	pFlow_Range->Init(); //������

	return pFlow_Range;
}

//========================================
//�ŏ��l�擾
//========================================
D3DXVECTOR3& CFlow_Range::GetMinPos()
{
	return m_Minpos;
}

//========================================
//�ő�l�擾
//========================================
D3DXVECTOR3& CFlow_Range::GetMaxPos()
{
	return m_Maxpos;
}

//========================================
//��p�̒��_����
//========================================
void CFlow_Range::SetVtxFlow_Range(D3DXVECTOR3 nor, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();
	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	pBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Minpos.x
		, m_Maxpos.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Maxpos.x
		, m_Maxpos.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Minpos.x
		, m_Minpos.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Maxpos.x
		, m_Minpos.y
		, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = nor;

	//���_�J���[�̐ݒ�
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	//�A�����b�N
	pBuff->Unlock();

	SetVtxBuff(pBuff);

}

//========================================
//�T�C�Y�ύX
//========================================
void CFlow_Range::SizeUp(bool bWay)
{
	if (bWay == true)
	{//�E������������
		m_Maxpos.x += 1.0f;
	}
	else if (bWay == false)
	{//��������������
		m_Minpos.x -= 1.0f;
	}
}
