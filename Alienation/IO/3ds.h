#ifndef SDS_3DS_H
#define SDS_3DS_H

#include "config.h"
#include "Math/Vector.h"
#include "3D/FMesh.h"
#include "3D/Model.h"
#include "3D/Material.h"

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <map>
#include <string>

namespace NSDIO {

   using namespace std;
   
   /**
    * 3DS Indices.
    * Here is our structure for our 3DS indicies (since .3DS stores 4 unsigned shorts).
    */
   class CIndices {
      
   public:
      
      unsigned short a, b, c, bVisible;
      
   };
   
   /**
    * A chunk in a 3DS file
    */
   class CChunk {

   public:

      unsigned short m_uiID;
      
      unsigned int m_iLength;
      
      unsigned int m_iBytesRead;
      
   };

   /**
    * Load a CModel from a 3DS file.
    */
   class CLoad3DS {
      
   public:
      
      /** 
       * Constructor.
       */
      CLoad3DS();								
      
      /** 
       * Load a CModel from a .3DS file. 
       * @param pModel A valid CModel to load into.
       * @param strFileName The filename to load.
       * @return true if tile loaded OK.
       */
      bool import3DS(CModel *pModel, const char *strFileName);
      
   private:
         
      /** 
       * Get a string from the current chunk.
       * @param pString A buffer to load the string into.
       * @return The length of the string loaded
       */
      int getString(char *pString);
         
      /** 
       * Read data from file into a CChunk object.
       */
      void readChunk(CChunk *);
         
      /** 
       * Load an arbitrary chunk.
       * Used for top-level stuff only.
       */
      void processNextChunk(CModel *pModel, CChunk *);
         
      /** 
       * Load an object chunk.
       */
      void processNextObjectChunk(CModel *pModel, CChunk *);
         
      /** 
       * Load a mesh chunk.
       */
      void processNextMeshChunk(CFMesh *pMesh, CChunk *);
         
      /** 
       * Load a material chunk.
       */
      void loadMaterialChunk(CChunk *pPreviousChunk);
         
      /** 
       * Load a texture chunk.
       */
      void processNextTextureChunk(CMaterial &pModel, CChunk *pPreviousChunk);
         
      /** 
       * Read a colour from a colour chunk.
       * @param pChunk A chunk of type _3DS_MATERIAL_AMBIENT, _3DS_MATERIAL_DIFFUSE or _3DS_MATERIAL_SPECULAR.
       * @return The colour in the chunk.
       */
      CRGBAColour readColorChunk(CChunk *pChunk);
         
      /** 
       * Read vertex data chunk.
       */
      void readVertices(CFMesh *pObject, CChunk *);
         
      /** 
       * Read face data chunk.
       */
      void readFaces(CFMesh *pObject, CChunk *);
         
      /** 
       * Read texture coordinates.
       */
      void readTexCoords(CFMesh *pObject, CChunk *);
         
      /** 
       * Read object material chunk.
       */
      void readObjectMaterial(CFMesh *pObject, CChunk *pPreviousChunk);
         
      /** 
       * Swallow unwanted chunk data.
       * @param pChunk The chunk to discard.
       */
      void swallowChunk(CChunk * pChunk);
         
      /** 
       * Clean up all temporary data.
       */
      void cleanUp();
         
   protected:
         
      FILE *m_pFilePointer;
         
      CChunk* m_pCurrentChunk;
         
      CChunk* m_pTempChunk;
         
      /**
       * Currently-loaded materials.
       * Materials are identified by name, and stored separately from objects, so 
       * we need a map from names to materials so that we can identify the correct 
       * CMaterial for a mesh.
       */
      map<string,CMaterial> m_oMaterials;
         
   };
      
}

#endif // SDS_3DS_H
