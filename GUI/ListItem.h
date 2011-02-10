// ListItem.h: interface for the CListItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTITEM_H__DA16C11C_1FB1_4808_BBBA_48B4F8EB5CBC__INCLUDED_)
#define AFX_LISTITEM_H__DA16C11C_1FB1_4808_BBBA_48B4F8EB5CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

class CListItem  
{
public:
	char * getItem(int iNumber);
	int noOfItems();
	void addItem(char *strItem);
	int key();
   CListItem(int iKey);
   CListItem();
   virtual ~CListItem();
   

private:
   int m_iKey;
   vector<char *> m_strItems;
};

#endif // !defined(AFX_LISTITEM_H__DA16C11C_1FB1_4808_BBBA_48B4F8EB5CBC__INCLUDED_)
