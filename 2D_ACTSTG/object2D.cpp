//=============================================
//
//3DTemplate[object2D.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//=============================================
//コンストラクタ
//=============================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CObject2D::~CObject2D()
{
}

//=============================================
//初期化
//=============================================
HRESULT CObject2D::Init()
{
	return S_OK;
}

//=============================================
//終了
//=============================================
void CObject2D::Uninit()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}


	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//自分自身の解放
	Release();
}

//=============================================
//更新
//=============================================
void CObject2D::Update()
{
}

//=============================================
//描画
//=============================================
void CObject2D::Draw()
{
 	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,m_pTexture);
	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

}

//=============================================
//頂点の設定
//=============================================
void CObject2D::SetVtx(float rhw, D3DCOLOR col)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}
	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y + m_size.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y + m_size.y
		, 0.0f);

	//rhwの設定
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//アンロック
	m_pVtxBuff->Unlock();

}

//=============================================
//頂点の設定(回転、拡縮を含む)
//=============================================
void CObject2D::SetVtx(float rhw, D3DCOLOR col, float fAngle, float fLength)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	//オブジェクト取得
	//	CObject* pObj = CObject::Getobject(4, nCnt);
	//	if (pObj != nullptr)
	//	{//ヌルポインタじゃなければ
	//		//タイプ取得
	//		CObject::OBJECT_TYPE type = pObj->GetType();
	//		if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
	//		{
	//			//頂点座標の設定
	//			pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				,0.0f);

	//			//頂点座標の設定
	//			pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				, 0.0f);

	//			//頂点座標の設定
	//			pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y
	//				, 0.0f);

	//			//頂点座標の設定
	//			pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
	//				, m_pos.y
	//				, 0.0f);
	//		}
	//		else
	//		{

	//		}
	//	}
	//}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - (D3DX_PI - fAngle)) * fLength
		, m_pos.y + cosf(m_rot.z - (D3DX_PI - fAngle)) * fLength
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fLength
		, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fLength
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fLength
		, m_pos.y + cosf(m_rot.z - fAngle) * fLength
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fLength
		, m_pos.y + cosf(m_rot.z + fAngle) * fLength
		, 0.0f);

	//rhwの設定
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//アンロック
	m_pVtxBuff->Unlock();
}

//=============================================
//頂点の設定(pos足元)
//=============================================
void CObject2D::SetVtx_FootPos(float rhw, D3DCOLOR col, float fAngle, float fLength)
{
	CRenderer* pRender = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
	if (m_pVtxBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	}

	VERTEX_2D* pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y - m_size.y
		, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x
		, m_pos.y
		, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x
		, m_pos.y
		, 0.0f);

	//rhwの設定
	pVtx[0].rhw = rhw;
	pVtx[1].rhw = rhw;
	pVtx[2].rhw = rhw;
	pVtx[3].rhw = rhw;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//アンロック
	m_pVtxBuff->Unlock();
}

//=============================================
//テクスチャ設定
//=============================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//=============================================
//座標取得
//=============================================
D3DXVECTOR3& CObject2D::GetPos()
{
	return m_pos;
}

//=============================================
//方向取得
//=============================================
D3DXVECTOR3& CObject2D::GetRot()
{
	return m_rot;
}

//=============================================
//サイズ取得
//=============================================
D3DXVECTOR2& CObject2D::GetSize()
{
	return m_size;
}
//=============================================
//テクスチャ座標取得
//=============================================
D3DXVECTOR2& CObject2D::GetTexPos()
{
	return m_tex_pos;
}

//=============================================
//頂点情報取得
//=============================================
LPDIRECT3DVERTEXBUFFER9& CObject2D::GetVtxBuff()
{
	return m_pVtxBuff;
}

