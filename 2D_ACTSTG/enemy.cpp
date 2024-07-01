//=============================================
//
//3DTemplate[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "camera.h"
#include "manager.h"
#include "effect.h"

//�ʏ�̈ړ����x
const float CEnemy::DEFAULT_MOVE = 1.0f;
//�ʏ�̈ړ����x
const float CEnemy::DAMPING_COEFFICIENT = 0.3f;

//�G�l�~�[��j���������W
const float CEnemy::DEADZONE_Y = -100.0f;

//���f���p�X
const std::string CEnemy::MODEL_NAME = "data\\MODEL\\enemy_test.x";

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;

LPD3DXBUFFER CEnemy::m_pBuffMat = nullptr;

LPD3DXMESH CEnemy::m_pMesh = nullptr;

DWORD CEnemy::m_dwNumMat = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy::CEnemy(int nPriority):CCharacter(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CEnemy::~CEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CEnemy::Init()
{
	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[�u�l���
	SetMove(move);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CEnemy::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CEnemy::Update()
{

	//�d�͏���
	Gravity();

	//�ړ�����
	EnemyMove();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ߋ��̈ʒu
	D3DXVECTOR3 oldpos = GetOldPos();

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//�ړ��ʂ��X�V(�����j
	move *= 1.0f - DAMPING_COEFFICIENT;

	SetMove(move);

	oldpos = pos;

	//�ߋ��̈ʒu���
	SetOldPos(oldpos);

	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), 30);

	pos += move;

	//���W���X�V
	SetPos(pos);

	//D3DXVECTOR3 minpos = GetMinPos();
	//D3DXVECTOR3 maxpos = GetMaxPos();

	//�v���C���[�Ƃ̐ڐG����
	HitPlayer();

	//�u���b�N�Ƃ̐ڐG����
	HitBlock();

	if (pos.y < DEADZONE_Y)
	{//�j������
		Release();
	}

}

//=============================================
//�`��
//=============================================
void CEnemy::Draw()
{
	CObjectX::Draw();
}

//=============================================
//����
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot)
{
	CEnemy* pEnemy = new CEnemy;

	// null�Ȃ�null��Ԃ�
	if (pEnemy == nullptr) { return nullptr; }

	//���f�����擾
	CModel* pModel = CManager::GetModel();

	pEnemy->SetPos(pos); //pos�ݒ�
	pEnemy->SetRot(rot); //rot�ݒ�

	//X�t�@�C���ǂݍ���
	pEnemy->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat, //�}�e���A���擾
	pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat, //�}�e���A�����擾
	pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh); //���b�V�����擾

	pEnemy->SetType(OBJECT_TYPE_ENEMY); //�I�u�W�F�N�g�̃^�C�v�ݒ�

	pEnemy->Init(); //�G�l�~�[�̏���������

	return pEnemy;
}

//=============================================
//�e�Ƃ̓����蔻��
//=============================================
void CEnemy::HitBullet()
{
	Release();
}

//=============================================
//�ړ�����
//=============================================
void CEnemy::EnemyMove()
{
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);
	vecDirection.x -= 1.0f;
	vecDirection.z -= 0.0f;

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	move.x += sinf(rotMoveY) * DEFAULT_MOVE;
	move.z += cosf(rotMoveY) * DEFAULT_MOVE;
	rot.y = rotMoveY + D3DX_PI;

	//rot����
	SetRot(rot); //�ړ��ʑ��
	SetMove(move);

	//���n���Ă邩���
	SetLanding(bLanding);
}
