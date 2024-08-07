//=============================================
//
//�����蔻��Ǘ�[colision.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _COLISION_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _COLISION_H_

//=============================================
//�����蔻��N���X
//=============================================
class CColision
{
public:
	CColision();
	~CColision();
	static bool CheckColision(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //�|���S�����m�����蔻��`�F�b�N�֐�
	static bool CheckColision(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //���f���ƃ|���S�������蔻��`�F�b�N�֐�
	static bool CheckColision(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos,D3DXVECTOR3 AMaxPos, 
								D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //���f�����m�����蔻��`�F�b�N�֐�
	static bool CheckColisionLanding(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //���n�̓����蔻��`�F�b�N�֐�
	static bool CheckColisionLanding(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize); //���f���ƃ|���S�����n�̓����蔻��`�F�b�N�֐�
	static bool CheckColisionLanding(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos); //���f�����m�����蒅�n�̔���`�F�b�N�֐�
};
#endif