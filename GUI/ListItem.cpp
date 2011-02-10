// ListItem.cpp: implementation of the CListItem class.
//
//////////////////////////////////////////////////////////////////////

#include "GUI/ListItem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListItem::CListItem(int iKey)
{
   m_iKey = iKey;
}

CListItem::CListItem()
{

}

CListItem::~CListItem()
{

}

int CListItem::key()
{
   return m_iKey;
}

void CListItem::addItem(char *strItem)
{
   m_strItems.push_back(strItem);
}

int CListItem::noOfItems()
{
   return m_strItems.size();
}

char * CListItem::getItem(int iNumber)
{
   return m_strItems[iNumber];
}
