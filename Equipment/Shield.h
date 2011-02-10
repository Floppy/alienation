// Shield.h: interface for the CShield class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SDS_SHIELD_H
#define SDS_SHIELD_H

#include "Equipment/Equipment.h"

using namespace std;

enum shieldType 
{
   SHIELD_FORE,
   SHIELD_AFT,
   SHIELD_RIGHT,
   SHIELD_LEFT
};

class CShield : public CEquipment  
{
public:
	void setShieldType(int iType);
	int getShieldType();
	CShield();
	virtual ~CShield();

        /**
         * Load a shield object from a Lua file.
         * @param strFileName The Lua file to load from.
         * @param type The shield type to create.
         * @return A pointer to a new shield object
         */
        static CShield* load(const char* strFileName, shieldType type);


private:
	int m_iShieldType;
};

#endif // SDS_SHIELD_H
