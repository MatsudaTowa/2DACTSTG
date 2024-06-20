////=============================================
////
////3DTemplate[enemy.cpp]
////Auther Matsuda Towa
////
////=============================================
//#include "enemy.h"
//#include "manager.h"
//#include "explosion.h"
//#include "bullet.h"
//
////画像分割数
//const int CEnemy::TEX_SPLIT_X = 1;
////画像分割数
//const int CEnemy::TEX_SPLIT_Y = 1;
////画像切り替わりカウント
//const int CEnemy::ANIMATION_FRAME = 5;
////通常の移動速度
//const float CEnemy::DEFAULT_MOVE = 3.0f;
//
////テクスチャ初期化
//LPDIRECT3DTEXTURE9 CEnemy::m_pTextureTemp = nullptr;
//
//
//
////=============================================
////コンストラクタ
////=============================================
//CEnemy::CEnemy(int nPriority):CMove_Texture(nPriority)
//{
//}
//
////=============================================
////デストラクタ
////=============================================
//CEnemy::~CEnemy()
//{
//}
//
////=============================================
////初期化
////=============================================
//HRESULT CEnemy::Init()
//{
//	//サイズ取得
//	D3DXVECTOR2 size = GetSize();
//
//	//対角線
//	m_fLength = sqrtf(size.x * size.x + size.y * size.y);
//
//	//角度
//	m_fAngle = atan2f(size.x, size.y);
//
//	//テクスチャ移動量取得
//	D3DXVECTOR2 tex_move = GetTexMove();
//	tex_move.x = 1.0f / (float)TEX_SPLIT_X;
//	tex_move.y = 1.0f / (float)TEX_SPLIT_Y;
//	//テクスチャ移動量代入
//	SetTexMove(tex_move);
//
//	//テクスチャ座標取得
//	D3DXVECTOR2 tex_pos = GetTexPos();
//	tex_pos.x = 1.0f;
//	tex_pos.y = 1.0f;
//	//テクスチャ座標代入
//	SetTexPos(tex_pos);
//
//	//アニメーションフレーム代入
//	SetAnimFrame(ANIMATION_FRAME);
//
//	//頂点設定
//	SetVtx(1.0f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), m_fAngle, m_fLength);
//	return S_OK;
//}
//
////=============================================
////終了
////=============================================
//void CEnemy::Uninit()
//{
//	CObject2D::Uninit();
//}
//
//
////=============================================
////更新
////=============================================
//void CEnemy::Update()
//{
//
//	D3DXVECTOR2 size = GetSize();
//
//	//テクスチャ情報取得
//	D3DXVECTOR2 tex_pos = GetTexPos();
//	D3DXVECTOR2 tex_move = GetTexMove();
//
//	AnimationTex(tex_pos, tex_move);
//	//アニメーション後のテクスチャ座標取得
//	tex_pos = GetTexPos();
//	//アニメーションを繰り返す
//	if (tex_pos.x >= 1.0f)
//	{
//		tex_pos.x = 0.0f;
//	}
//	SetTexPos(tex_pos);
//
//	//エネミー移動処理
//	EnemyMove();
//
//	SetSize(size);
//	//対角線
//	m_fLength = sqrtf(size.x * size.x + size.y * size.y);
//
//	//角度
//	m_fAngle = atan2f(size.x, size.y);
//
//	//頂点座標
//	SetVtx(1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fAngle, m_fLength);
//}
//
////=============================================  
////描画
////=============================================
//void CEnemy::Draw()
//{
//	CObject2D::Draw();
//}
//
////=============================================
////エネミー生成
////=============================================
//CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nLife)
//{
//	CEnemy* pEnemy = new CEnemy;
//	if (pEnemy != nullptr)
//	{
//		pEnemy->SetPos(pos); //pos設定
//		pEnemy->SetSize(size); //サイズ設定
//		pEnemy->BindTexture(m_pTextureTemp);
//		pEnemy->m_nLife = nLife;
//		pEnemy->m_move = move;
//		pEnemy->SetType(OBJECT_TYPE_ENEMY); //タイプ設定
//		pEnemy->Init();
//	}
//
//	return pEnemy;
//}
//
////=============================================
////エネミー移動処理
////=============================================
//void CEnemy::EnemyMove()
//{
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR2 size = GetSize();
//
//	pos += m_move;
//	if (pos.x + size.x >= SCREEN_WIDTH || pos.x - size.x <= 0)
//	{
//		m_move.x *= -1.0f;
//	}
//	if (pos.y + size.y >= SCREEN_HEIGHT || pos.y - size.y <= 0)
//	{
//		m_move.y *= -1.0f;
//	}
//	//座標を更新
//	SetPos(pos);
//}
//
////=============================================
////当たり判定
////=============================================
//void CEnemy::HitBullet()
//{
//	D3DXVECTOR3 pos = GetPos();
//	m_nLife--;
//	if (m_nLife <= 0)
//	{
//		Release();
//	}
//
//}
//
////=============================================
////テクスチャロード
////=============================================
//HRESULT CEnemy::Load()
//{
//	CRenderer* pRender = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRender->GetDevice();
//	if (m_pTextureTemp == nullptr)
//	{
//		//テクスチャの読み込み
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\TEXTURE\\download_image_1714032505054.png",
//			&m_pTextureTemp);
//	}
//	return S_OK;
//}
//
////=============================================
////テクスチャアンロード
////=============================================
//HRESULT CEnemy::UnLoad()
//{
//	if (m_pTextureTemp != nullptr)
//	{
//
//		m_pTextureTemp->Release();
//		m_pTextureTemp = nullptr;
//	}
//
//	return S_OK;
//}
