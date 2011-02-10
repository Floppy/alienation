// List.h: interface for the CList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__A54478A6_ED8D_42DE_8232_E72735015B4D__INCLUDED_)
#define AFX_LIST_H__A54478A6_ED8D_42DE_8232_E72735015B4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUI/ListItem.h"
#include <vector>
using namespace std;

class CList  
{
public:
	void addField(char * strField, int iKey);
	char * getItemSelected(int iField);
	int sizeSelected();
   int selected();
   CList();
   virtual ~CList();
   
private:
   void addListItem(CListItem *poListItem);
   vector<CListItem *> m_arrListItems;
   int m_iSelected;
};

#endif // !defined(AFX_LIST_H__A54478A6_ED8D_42DE_8232_E72735015B4D__INCLUDED_)
