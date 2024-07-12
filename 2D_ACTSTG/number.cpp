////=============================================
////
////数字管理「number.cpp」
//// Author松田永久
////
////=============================================
//#include "number.h"
//#include "manager.h"
//
////=============================================
////コンストラクタ
////=============================================
//CNumber::CNumber()
//{
//}
//
////=============================================
////デストラクタ
////=============================================
//CNumber::~CNumber()
//{
//}
//
////=============================================
////初期化
////=============================================
//HRESULT CNumber::Init()
//{
//
//	return S_OK;
//}
//
//
////=============================================
////終了
////=============================================
//void CNumber::Uninit()
//{
//}
//
////=============================================
////更新
////=============================================
//void CNumber::Update()
//{
//}
//
////=============================================
////描画
////=============================================
//void CNumber::Draw(LPDIRECT3DTEXTURE9 pTex, LPDIRECT3DVERTEXBUFFER9 pBuff)
//{
//	CRenderer* pRender = CManager::GetRenderer();
//
//	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, pBuff, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャの設定
//	pDevice->SetTexture(0, pTex);
//	//テクスチャ拡大時に色を近似値にする
//	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
//
//	//ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//		0,
//		2);
//
//	//テクスチャ拡大時の色を線形補間
//	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//}
//
////=============================================
////数字のポリゴン生成
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
//	//頂点バッファをロックし頂点情報へのポインタを取得
//
//	pBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	//頂点座標の設定
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
//	//rhwの設定
//	pVtx[0].rhw = rhw;
//	pVtx[1].rhw = rhw;
//	pVtx[2].rhw = rhw;
//	pVtx[3].rhw = rhw;
//
//	//頂点カラーの設定
//	pVtx[0].col = col;
//	pVtx[1].col = col;
//	pVtx[2].col = col;
//	pVtx[3].col = col;
//
//	//テクスチャ座標の設定
//	pVtx[0].tex = D3DXVECTOR2(fMinTexU, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(fMaxTexU, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(fMinTexU, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(fMaxTexU, 1.0f);
//	
//	//アンロック
//	pBuff->Unlock();
//}
//
//
////=============================================
////桁数取得
////=============================================
//int CNumber::GetDigit()
//{
//	return m_nDigit;
//}
//
////=============================================
////最初の番号取得
////=============================================
//int CNumber::GetStartNum()
//{
//	return m_nStaretNum;
//}
