// Engine.h: interface for the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SDS_ENGINE_H
#define SDS_ENGINE_H

#include "Equipment/Equipment.h"

using namespace std;

class CEngine : public CEquipment  
{
public:

   CEngine();
   
   virtual ~CEngine();
   
   /**
    * Load a engine object from a Lua file.
    * @param strFileName The Lua file to load from.
    * @param type The engine type to create.
    * @return A pointer to a new engine object
    */
   static CEngine* load(const char* strFileName);

private:

};

#endif // SDS_ENGINE_H
