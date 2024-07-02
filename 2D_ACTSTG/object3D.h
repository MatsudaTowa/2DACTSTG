//=============================================
//
//3DTemplate[object3D.h]
//Auther Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_H_ //これが定義されてないとき

#define _OBJECT3D_H_
#include "main.h"
#include "object.h"

//=============================================
//2Dオブジェクトクラス
//=============================================
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	//posの代入
	void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//rotの代入
	void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	//サイズの代入
	void SetSize(D3DXVECTOR3 size)
	{
		m_size = size;
	}

	//テクスチャ座標の代入
	void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	//ワールドマトリックスの代入
	void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	//頂点座標の代入
	void SetVtx(D3DXVECTOR3 nor, D3DCOLOR col);

	//頂点座標の代入
	void SetVtx(D3DXVECTOR3 nor,float fAngle, float fLength, D3DCOLOR col);

	//posの取得
	D3DXVECTOR3& GetPos();

	//rotの取得
	D3DXVECTOR3& GetRot();

	//サイズの取得
	D3DXVECTOR3& GetSize();

	//テクスチャ座標の取得
	D3DXVECTOR2& GetTexPos();

	//頂点情報取得
	LPDIRECT3DVERTEXBUFFER9& GetVtxBuff();

	//テクスチャ情報取得
	LPDIRECT3DTEXTURE9& GetTexture();

	//ワールドマトリックス取得
	D3DXMATRIX& GetMtxWorld();

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ

	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //方向
	D3DXVECTOR3 m_size; //サイズ
	D3DXVECTOR2 m_tex_pos; //tex座標

	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
};
#endif