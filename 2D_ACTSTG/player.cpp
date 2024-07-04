//=============================================
//
//3DTemplate[player.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "field.h"
#include "camera.h"
#include "melee.h"

//���f���p�X
const std::string CPlayer::MODEL_NAME = "data\\MODEL\\face.x";

//�ʏ�̈ړ����x
const float CPlayer::DEFAULT_MOVE = 1.0f;
//�ʏ�̈ړ����x
const float CPlayer::DAMPING_COEFFICIENT = 0.3f;

//�ʏ�̃W�����v��
const float CPlayer::DEFAULT_JUMP = 25.0f;

//�W�����v��
const int CPlayer::MAX_JUMPCNT = 2;

//�v���C���[�����X�|�[���������W
const float CPlayer::DEADZONE_Y = -100.0f;

//�e�N�X�`��������
LPDIRECT3DTEXTURE9 CPlayer::m_pTextureTemp = nullptr;

LPD3DXBUFFER CPlayer::m_pBuffMat = nullptr;

LPD3DXMESH CPlayer::m_pMesh = nullptr;

DWORD CPlayer::m_dwNumMat = 0;
//=============================================
//�R���X�g���N�^
//=============================================
CPlayer::CPlayer(int nPriority):CCharacter(nPriority),m_nJumpCnt(0)
{//�C�j�V�����C�U�[�ŃW�����v�J�E���g������
	
}

//=============================================
//�f�X�g���N�^
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//������
//=============================================
HRESULT CPlayer::Init()
{
	CRenderer* pRender = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	m_bSize = false;

	//�ړ��ʏ�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//���[�u�l���
	SetMove(move);

	return S_OK;
}

//=============================================
//�I��
//=============================================
void CPlayer::Uninit()
{
	//�e�N���X�̏I���������Ă�
	CObjectX::Uninit();
}

//=============================================
//�X�V
//=============================================
void CPlayer::Update()
{
	//�d�͏���
	Gravity();

	//�ړ�����
	PlayerMove();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�ߋ��̈ʒu
	D3DXVECTOR3 oldpos = GetOldPos();

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//�ړ��ʂ��X�V(�����j
	move *= 1.0f - DAMPING_COEFFICIENT;

	//�ړ��ʑ��
	SetMove(move);

	//�ߋ��̈ʒu�ɍ��̈ʒu����
	oldpos = pos;

	//�ߋ��̈ʒu���
	SetOldPos(oldpos);

	//�G�t�F�N�g����
	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x,pos.y + 8.0f,pos.z), D3DXVECTOR3(10.0f, 10.0f ,0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), 30);

	//�ړ��ʒǉ�
	pos += move;

	//���W���X�V
	SetPos(pos);

	//�ő�ŏ��l�擾
	D3DXVECTOR3 minpos = GetMinPos();
	D3DXVECTOR3 maxpos = GetMaxPos();
	
	//�u���b�N�Ƃ̐ڐG����
	HitBlock();

	//�G�l�~�[�Ƃ̐ڐG����
	HitEnemy();

	if (GetLaunding())
	{//���n���Ă�Ȃ�
		//�W�����v�����Z�b�g
		m_nJumpCnt = 0;
	}

	if (pos.y < DEADZONE_Y)
	{//���X�|�[������
		ReSpawn();
	}
	
	//Turn(); //��]����
	//SizeChange(); //�g�k

	//�}�E�X�̏��擾
	CInputMouse* pMouse = CManager::GetMouse();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

	if (pMouse->GetTrigger(0))
	{//�E�N���b�N�����͂��ꂽ��
		if (bWay == true)
		{//�E����
			CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f),D3DXVECTOR3(20.0f,50.0f,0.0f),30);
		}
		else if (bWay == false)
		{//������
			CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXVECTOR3(sinf(GetRot().y + D3DX_PI) * 7.0f, 0.0f, cosf(GetRot().y + D3DX_PI) * 7.0f),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(20.0f, 50.0f, 0.0f), 30);
		}
	}

	if (pMouse->GetTrigger(1))
	{//���N���b�N�����͂��ꂽ��
		if (bWay == true)
		{//�E����
			CMelee* pMelee = CMelee::Create(D3DXVECTOR3(pos.x + GetMaxPos().x, pos.y + 10.0f, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 2.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30);
		}
		else if (bWay == false)
		{//������
			CMelee* pMelee = CMelee::Create(D3DXVECTOR3(pos.x + GetMinPos().x, pos.y + 10.0f, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, GetRot().y * 4.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 30);
		}
	}

}

//=============================================
//�`��
//=============================================
void CPlayer::Draw()
{
	//�e�N���X�̕`����Ă�
	CObjectX::Draw();
}

//=============================================
//����
//=============================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CModel* pModel = CManager::GetModel();

	CPlayer* pPlayer = new CPlayer;

	// null�Ȃ�null��Ԃ�
	if (pPlayer == nullptr) {return nullptr;}

	pPlayer->SetPos(pos); //pos�ݒ�
	pPlayer->SetRot(rot); //rot�ݒ�

	//x�t�@�C���ǂݍ���
	pPlayer->BindXFile(pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pBuffMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).dwNumMat,
					pModel->GetModelInfo(pModel->Regist(&MODEL_NAME)).pMesh);

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //�^�C�v�ݒ�

	pPlayer->Init(); //����������
	
	return pPlayer;
}

//=============================================
//���X�|�[��
//=============================================
void CPlayer::ReSpawn()
{
	//�������g��pos�擾
	D3DXVECTOR3 PlayerPos = GetPos();

	PlayerPos = D3DXVECTOR3(-450.0f, 0.5f, 0.0f);

	//pos���
	SetPos(PlayerPos);
}

//=============================================
//�ړ�����
//=============================================
void CPlayer::PlayerMove()
{
	CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	//�J�����^�C�v�擾
	CCamera::CANERA_TYPE pCameraType = CCamera::GetType();

	//�ǂ��������Ă邩�擾
	bool bWay = GetWay();

	switch (pCameraType)
	{//�T�C�h�r���[�̎��͉��ɂ��������Ȃ��悤�ɐݒ�
	case CCamera::CANERA_TYPE::TYPE_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	case CCamera::CANERA_TYPE::TYPE_PARALLEL_SIDEVIEW:
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	default:
		if (pKeyboard->GetPress(DIK_W))
		{
			vecDirection.z += 1.0f;
		}
		if (pKeyboard->GetPress(DIK_S))
		{
			vecDirection.z -= 1.0f;
		}
		if (pKeyboard->GetPress(DIK_A))
		{
			vecDirection.x -= 1.0f;
			bWay = false;
		}
		else if (pKeyboard->GetPress(DIK_D))
		{
			vecDirection.x += 1.0f;
			bWay = true;
		}
		break;
	}

	//�ǂ��������Ă邩���
	SetWay(bWay);

	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	if (vecDirection.x == 0.0f && vecDirection.z == 0.0f)
	{ // �����ĂȂ��B
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

		//�I�u�W�F�N�g2D����rot���擾
		D3DXVECTOR3 rot = GetRot();

		move.x += sinf(rotMoveY) * DEFAULT_MOVE;
		move.z += cosf(rotMoveY) * DEFAULT_MOVE;
		rot.y = rotMoveY + D3DX_PI;
		//rot����
		SetRot(rot);
		//if (g_Player.rot.y <= -D3DX_PI)
		//{
		//	g_Player.rot.y = D3DX_PI;
		//}
	}
	if (m_nJumpCnt < MAX_JUMPCNT)
	{//�W�����v���ȉ���������
		if (pKeyboard->GetTrigger(DIK_SPACE))
		{
			move.y = DEFAULT_JUMP;
			bLanding = false; //��
			m_nJumpCnt++; //�W�����v�����Z
		}
	}

	//�ړ��ʑ��
	SetMove(move);

	//���n���Ă邩���
	SetLanding(bLanding);

}

//=============================================
//��]
//=============================================
void CPlayer::Turn()
{
	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	rot.z += 0.05f;

	if (rot.z >= D3DX_PI)
	{
		rot.z = -D3DX_PI;
	}
	
	//rot����
	SetRot(rot);
}

//=============================================
//�g�k
//=============================================
void CPlayer::SizeChange()
{
	//�I�u�W�F�N�g2D����size���擾

}

