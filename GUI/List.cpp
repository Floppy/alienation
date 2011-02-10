// List.cpp: implementation of the CList class.
//
//////////////////////////////////////////////////////////////////////

#include "List.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CList::CList()
{

}

CList::~CList()
{

}

int CList::selected()
{
   return m_arrListItems[m_iSelected]->key();
}

void CList::addListItem(CListItem *poListItem)
{
   m_arrListItems.push_back(poListItem);
}

int CList::sizeSelected()
{
   return m_arrListItems[m_iSelected]->noOfItems();
}

char * CList::getItemSelected(int iField)
{
   return m_arrListItems[m_iSelected]->getItem(iField);
}

void CList::addField(char *strField, int iKey)
{
   
}
