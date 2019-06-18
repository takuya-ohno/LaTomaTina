/*=============================================================================



-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "TextureManager.h"
#include "Mode.h"
#include "GameScene.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "PlayerUi.h"

#define MAX_POS (470.0f)

/*-----------------------------------------------------------------------------
関数名:		CPlayerUI* CPlayerUI::Create(int Priolity)
引数:
戻り値:		return ground;	クラスのポインタ
説明:		生成
-----------------------------------------------------------------------------*/
CPlayerUI* CPlayerUI::Create(int Priolity)
{
	CPlayerUI* playerui;

	playerui = new CPlayerUI(Priolity);

	playerui->Init();

	return playerui;
}

/*-----------------------------------------------------------------------------
関数名:		void CPlayerUI::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CPlayerUI::Init(void)
{
	CSprite2D::Init();

	CSprite2D::SetAnimationTime(0.15f);
}

/*-----------------------------------------------------------------------------
関数名:		void CPlayerUI::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CPlayerUI::Uninit(void)
{
	CSprite2D::Uninit();
}

/*-----------------------------------------------------------------------------
関数名:		void CTruck::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CPlayerUI::Update(void)
{
	D3DXVECTOR3 pos = CScene::GetPosition();

	pos.y += 0.15f;

	if (pos.y > MAX_POS)
	{
		pos.y = MAX_POS;
		CGameScene::GameClear();
	}

	CScene::SetPosition(pos);

	CSprite2D::TextureAnimation();

	CSprite2D::Update();
}

/*-----------------------------------------------------------------------------
関数名:		void CTruck::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CPlayerUI::Draw(void)
{
	CSprite2D::Draw();
}
