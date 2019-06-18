/*=============================================================================

		3D描画[ Sprite3D.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Sprite3D.h"

/*-----------------------------------------------------------------------------
関数名:		CSprite3D::CSprite2D(int Priolity)
引数:		int Priolity	優先度
戻り値:
説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CSprite3D::CSprite3D(int Priolity) :CScene(Priolity)
{
	m_VtxBuff = NULL;							// 頂点バッファ
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	回転
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	拡大率
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	大きさ
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	法線
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//	色
	m_TexturePattern = 0;						//	テクスチャパターン
	m_TextureAnimationCount = 0.0f;				//	テクスチャアニメーションカウンタ
	m_TextureAnimationTime = 0.0f;				//	テクスチャアニメーションタイム
}

/*-----------------------------------------------------------------------------
関数名:		CSprite3D* CSprite3D::Create(int Priolity)
引数:		int Priolity	優先度
戻り値:		return sprite3D;	クラスのポインタ
説明:		生成
-----------------------------------------------------------------------------*/
CSprite3D* CSprite3D::Create(int Priolity)
{
	CSprite3D* sprite3D;

	sprite3D = new CSprite3D(Priolity);

	sprite3D->Init();	//	初期化

	return sprite3D;
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CSprite3D::Init(void)
{
	MakeVerTex();	//	頂点の作成
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CSprite3D::Uninit(void)
{
	if (m_VtxBuff != NULL)
	{	//	頂点バッファ

		m_VtxBuff->Release();	// 解放
		m_VtxBuff = NULL;
	}

	CScene::Release();	//	オブジェクト自身の解放
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CSprite3D::Update(void)
{
	SetUpVerTex();	//	頂点の設定
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CSprite3D::Draw(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// 頂点バッファをデータストリームに設定
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(m_TextureId).Texture);

	SetWorld(Device);	//	ワールド座標変換

	// 描画
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::TextureAnimation(void)
引数:
戻り値:
説明:		テクスチャアニメーション
-----------------------------------------------------------------------------*/
void CSprite3D::TextureAnimation(void)
{
	CTextureManager::TEXTUREINFO TextureInfo = CManager::GetTextureManager()->GetTextureInfo(m_TextureId);

	m_TexturePattern = (int)m_TextureAnimationCount % (int)TextureInfo.Div.x;

	m_TextureAnimationCount += m_TextureAnimationTime;
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::MakeVerTex(void)
引数:
戻り値:
説明:		頂点の作成
-----------------------------------------------------------------------------*/
void CSprite3D::MakeVerTex(void)
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// 頂点バッファの生成
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "頂点バッファの生成に失敗", "Sprite3D.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点座標の設定
	pVtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, m_Size.z);
	pVtx[1].Pos = D3DXVECTOR3(m_Size.x, m_Size.y, m_Size.z);
	pVtx[2].Pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, -m_Size.z);
	pVtx[3].Pos = D3DXVECTOR3(m_Size.x, -m_Size.y, -m_Size.z);


	//	法線
	pVtx[0].Nor = m_Normal;
	pVtx[1].Nor = m_Normal;
	pVtx[2].Nor = m_Normal;
	pVtx[3].Nor = m_Normal;


	// 頂点カラー
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	// テクスチャ座標
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);


	//	バッファをアンロック
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::SetUpVerTex(void)
引数:
戻り値:
説明:		頂点の設定
-----------------------------------------------------------------------------*/
void CSprite3D::SetUpVerTex(void)
{
	CTextureManager::TEXTUREINFO TextureInfo = CManager::GetTextureManager()->GetTextureInfo(m_TextureId);

	const int tw = (int)(TextureInfo.Div.x);
	const int th = (int)(TextureInfo.Div.y);
	const int tcx = m_TexturePattern % (int)TextureInfo.Div.x;
	const int tcy = (int)(m_TexturePattern / TextureInfo.Div.x) % (int)TextureInfo.Div.y;
	const int tcw = 1;
	const int tch = 1;

	const float v0 = (float)tcy / th;
	const float u0 = (float)tcx / tw;
	const float u1 = (float)(tcx + tcw) / tw;
	const float v1 = (float)(tcy + tch) / th;

	// 頂点情報を設定
	// 構造体のポインタ宣言
	VERTEX_3D* pVtx;

	// バッファをロックし、仮想アドレスを取得
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	頂点座標の設定
	pVtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, m_Size.z);
	pVtx[1].Pos = D3DXVECTOR3(m_Size.x, m_Size.y, m_Size.z);
	pVtx[2].Pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, -m_Size.z);
	pVtx[3].Pos = D3DXVECTOR3(m_Size.x, -m_Size.y, -m_Size.z);


	//	法線
	pVtx[0].Nor = m_Normal;
	pVtx[1].Nor = m_Normal;
	pVtx[2].Nor = m_Normal;
	pVtx[3].Nor = m_Normal;


	// 頂点カラー
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	// テクスチャ座標
	pVtx[0].Tex = D3DXVECTOR2(u0, v0);
	pVtx[1].Tex = D3DXVECTOR2(u1, v0);
	pVtx[2].Tex = D3DXVECTOR2(u0, v1);
	pVtx[3].Tex = D3DXVECTOR2(u1, v1);


	//	バッファをアンロック
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
関数名:		void CSprite3D::SetWorld(LPDIRECT3DDEVICE9 Device)
引数:		LPDIRECT3DDEVICE9 Device	デバイス
戻り値:
説明:		ワールド座標変換
-----------------------------------------------------------------------------*/
void CSprite3D::SetWorld(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxPos;

	D3DXMatrixIdentity(&mtxWorld);	//	行列を単位行列にする

	//	拡大行列を作る
	D3DXMatrixScaling(&mtxScl,	//拡大行列
		m_Scale.x,	//	X軸拡大
		m_Scale.y,	//	Y軸拡大
		m_Scale.z);	//	Z軸拡大

	//	回転行列を作る
	D3DXMatrixRotationYawPitchRoll(&mtxRot,	//	回転行列
		D3DXToRadian(m_Rotation.y), //	Y軸回転
		D3DXToRadian(m_Rotation.x), //	X軸回転
		D3DXToRadian(m_Rotation.z)); //	Z軸回転

	//	平行移動行列を作る
	D3DXMatrixTranslation(&mtxPos,	//	平行移動行列
		m_Position.x,	//	X軸移動
		m_Position.y,	//	Y軸移動
		m_Position.z);	//	Z軸移動


	//	掛ける
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);

	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}