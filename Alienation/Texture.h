// Texture.h: interface for the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__8395B95E_91B1_4EDB_BBB6_4FB7757FCBA3__INCLUDED_)
#define AFX_TEXTURE_H__8395B95E_91B1_4EDB_BBB6_4FB7757FCBA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <string.h>

class CTexture  
{
public:
	void setActive(unsigned int t);
	bool load(char *strDir, char **astrFnames, int iNoOfFiles);
	CTexture(int iNum);
	virtual ~CTexture();
	void loadImage(char *strFilename);				// Loads A Bitmap Image
	int m_iNoOfTextures;
	unsigned int * m_puiTexture;
};

#endif // !defined(AFX_TEXTURE_H__8395B95E_91B1_4EDB_BBB6_4FB7757FCBA3__INCLUDED_)
