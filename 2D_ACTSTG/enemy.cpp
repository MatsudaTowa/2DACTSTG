//=============================================
//
//�G�̏���[enemy.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "enemy.h"
#include "camera.h"
#include "manager.h"
#include "player.h"
#include "effect.h"
#include "bullet.h"
#include "item.h"

//�ʏ�̈ړ����x
const float CEnemy::DEFAULT_MOVE = 0.5f;
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

//�G�l�~�[�̑���
int CEnemy::m_nNumEnemy = 0;

//=============================================
//�R���X�g���N�^
//=============================================
CEnemy::CEnemy(int nPriority):CCharacter(nPriority),m_nShotCnt(0)
{
	//�������Z
	m_nNumEnemy++;
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
	//�e�N���X�̏I��
	CObjectX::Uninit();

	//�������炷
	m_nNumEnemy--;

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

	//�G�t�F�N�g����
	CEffect* pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), 30);

	pos += move;

	//���W���X�V
	SetPos(pos);

	//�v���C���[�Ƃ̋����𑪂�
	bool bDistance = PlayerDistance();

	if (bDistance == true)
	{//�߂�������
		//�������擾
		bool bWay = GetWay();

		//�V���b�g�J�E���g���Z
		m_nShotCnt++;

		if (m_nShotCnt >= NORMAL_SHOT_FRAME)
		{//�t���[�����ɒB������
			//�e����
			ShotBullet(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), bWay, 1, CBullet::BULLET_TYPE_ENEMY);

			//�V���b�g�J�E���g���Z�b�g
			m_nShotCnt = 0;
		}
	}

	//�v���C���[�Ƃ̐ڐG����
	HitPlayer();

	//�u���b�N�Ƃ̐ڐG����
	HitBlock();

	//���Ƃ̐ڐG����
	HitField();

	if (pos.y < DEADZONE_Y)
	{//�j������
		Uninit();
	}
}

//=============================================
//�`��
//=============================================
void CEnemy::Draw()
{
	//�e�N���X�̕`��
	CObjectX::Draw();
}

//=============================================
//����
//=============================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot, const ENEMY_TYPE& type)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMY_TYPE_NORMAL:
		pEnemy = new CNormalEnemy;
	default:
		assert(true);
		break;
	}

	// null�Ȃ�null��Ԃ�
	if (pEnemy == nullptr) { return nullptr; }

	//���f�����擾
	CModel* pModel = CManager::GetModel();

	pEnemy->m_Type = type; //�G�l�~�[�̃^�C�v�ݒ�

	//�G�l�~�[�̗̑͐ݒ�
	pEnemy->SetLife(ENEMY_DEFAULT_LIFE);

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
//�_���[�W���󂯂��Ƃ�
//=============================================
void CEnemy::Damage(int nDamage)
{
	//�̗͎擾
	int nLife = GetLife();

	if (nLife > 0)
	{//HP���c���Ă���
		nLife -= nDamage;

		//�̗͑��
		SetLife(nLife);
	}
	if (nLife <= 0)
	{//HP��0�ȉ���������
		//�j��
		CItem*pItem = CItem::Create(CItem::ITEMTYPE_PANETRARING_SLASH, D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z),D3DXVECTOR3(10.0f,10.0f,0.0f),GetRot());
		Uninit();
	}
}

//=============================================
//�v���C���[�Ƃ̋����𑪂�
//=============================================
bool CEnemy::PlayerDistance()
{
	bool bNear = false; //�߂�������true��Ԃ�

	bool bWay = GetWay(); //�������擾

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj != nullptr)
		{//�k���|�C���^����Ȃ����
			//�^�C�v�擾
			CObject::OBJECT_TYPE type = pObj->GetType();

			//�G�Ƃ̓����蔻��
			if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)pObj;

				float fDistance = 0.0f; //�v���C���[�Ƃ̋���
				
				fDistance = GetPos().x - pPlayer->GetPos().x;

				if (fDistance >= 0.0f && fDistance < 100.0f)
				{//�G�l�~�[��min�ɋ߂�
					bNear = true;
					
					bWay = false; //�������v���C���[�̂ق��ɐ؂�ւ���
				}
				else if (fDistance <= 0.0f && fDistance > -100.0f)
				{//�G�l�~�[��max�ɋ߂�
					bNear = true;

					bWay = true; //�������v���C���[�̂ق��ɐ؂�ւ���
				}
				else
				{//�߂��Ȃ�
					bNear = false;
				}
			}
		}
	}

	//��������
	SetWay(bWay);
	return bNear;
}

//=============================================
//�R���X�g���N�^
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority),m_nTurnFrameCnt(0), m_bOldWay(false)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//������
//=============================================
HRESULT CNormalEnemy::Init()
{
	//�e�N���X�̏�����
	CEnemy::Init();
	return S_OK;
}

//=============================================
//�I��
//=============================================
void CNormalEnemy::Uninit()
{
	//�e�N���X�̏I��
	CEnemy::Uninit();
}

//=============================================
//�X�V
//=============================================
void CNormalEnemy::Update()
{
	//�e�N���X�̍X�V
	CEnemy::Update();
}

//=============================================
//�`��
//=============================================
void CNormalEnemy::Draw()
{
	//�e�N���X�̕`��
	CEnemy::Draw();
}

//=============================================
//�ړ�����
//=============================================
void CNormalEnemy::EnemyMove()
{
	//�J�E���g���Z
	m_nTurnFrameCnt++;

	//�������擾
	bool bWay = GetWay();

	if (m_bOldWay != bWay)
	{//�ߋ��̌����ƈ������t���[�����Z�b�g
		m_nTurnFrameCnt = 0;
	}

	if (m_nTurnFrameCnt >= NORMAL_ENEMY_TURNFRAME)
	{//�w��t���[�����ɓ��B������

		//�i�ޕ�����؂�ւ���
		bWay = bWay ? false : true;
		SetWay(bWay);

		//�ߋ��̌����ɍ��̌�������
		m_bOldWay = bWay;
		//�J�E���g���Z�b�g
		m_nTurnFrameCnt = 0;
	}

	//�ړ��p�P�ʃx�N�g��������
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (bWay == true)
	{//�E�����ɐi�ނȂ�
		vecDirection.x += 1.0f;
		vecDirection.z += 0.0f;
	}
	else if (bWay == false)
	{//�������ɐi�ނȂ�
		vecDirection.x -= 1.0f;
		vecDirection.z -= 0.0f;
	}


	//�ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();
	float rotMoveY = atan2f(vecDirection.x, vecDirection.z);

	//�I�u�W�F�N�g2D����rot���擾
	D3DXVECTOR3 rot = GetRot();

	//���n���Ă邩�擾
	bool bLanding = GetLaunding();

	move.x += sinf(rotMoveY) * CEnemy::DEFAULT_MOVE;
	move.z += cosf(rotMoveY) * CEnemy::DEFAULT_MOVE;
	rot.y = rotMoveY + D3DX_PI;

	SetRot(rot); //rot����
	SetMove(move);//�ړ��ʑ��

	//���n���Ă邩���
	SetLanding(bLanding);
}
