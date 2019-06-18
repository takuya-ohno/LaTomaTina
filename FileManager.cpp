/*=============================================================================

		ファイル管理[ Singleton.cpp ]

-------------------------------------------------------------------------------
		■　製作者
			大野拓也

		■　作成日
			2017/08/25
-------------------------------------------------------------------------------
		■　更新日
			2017/08/18
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "FileManager.h"
#include <assert.h>

/*-----------------------------------------------------------------------------
関数名:		FILE* CFileManager::OpenFile(const char* FileName, const char *Mode)
引数:		const char* FileName		ファイル名
			const char *Mode			モード
戻り値:		return fp;		ファイルポインタ
説明:		ファイルを閉じる
-----------------------------------------------------------------------------*/
FILE* CFileManager::OpenFile(const char* FileName, const char *Mode)
{
	FILE *fp;

	fp = fopen(FileName, Mode);

	if (fp == NULL)
	{	//	エラーチェック

		assert(!"[ FileManager.cpp ]  ファイルがありませんでした");
		return NULL;
	}

	return fp;
}

/*-----------------------------------------------------------------------------
関数名:		bool CFileManager::CloseFile(FILE* File)
引数:		FILE* File		ファイル名
戻り値:		return true;	成功
			return false;	失敗
説明:		ファイルを閉じる
-----------------------------------------------------------------------------*/
bool CFileManager::CloseFile(FILE* File)
{
	bool Check = false;
	int CloseCheck = 0;
	fclose(File);

	if (CloseCheck == 0) Check = true;

	return Check;
}