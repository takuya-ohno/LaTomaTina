/*=============================================================================

		��ʑJ��[ Mode.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _MODE_H_
#define _MODE_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CMode
{
public:
	virtual void Init(void) = 0;	//	������
	virtual void Uninit(void) = 0;	//	�I��
	virtual void Update(void) = 0;	//	�X�V
	virtual void Draw(void) = 0;	//	�`��
};
#endif
