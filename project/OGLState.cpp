#include "OGLState.h"

#ifdef NME_ANY_GL

static int sgTexture = 0;
static int sgOGLTexture = 0;

static bool sgTexEnable = false;
static bool sgOGLTexEnable = false;

static bool sgBlendEnable = false;
static bool sgOGLBlendEnable = false;

static GLenum sgBlendSrc = 0;
static GLenum sgOGLBlendSrc = 0;

static GLenum sgBlendDest = 0;
static GLenum sgOGLBlendDest = 0;

static bool sgVertexEnabled = false;

#ifdef NME_OPENGL
enum { AlwaysSetState = 1 };
#else
enum { AlwaysSetState = 0 };
#endif

void nmeDrawArrays(GLenum inMode, int inN)
{
   if (AlwaysSetState || sgTexEnable!=sgOGLTexEnable)
   {
      if (sgTexEnable)
      {
         glEnable(GL_TEXTURE_2D);
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      }
      else
      {
         glDisable(GL_TEXTURE_2D);
         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
      sgOGLTexEnable = sgTexEnable;
   }
   if (sgTexEnable)
   {
      if (AlwaysSetState || sgTexture!=sgOGLTexture)
      {
         glBindTexture(GL_TEXTURE_2D,sgTexture);
         sgOGLTexture = sgTexture;
      }
   }
   if (AlwaysSetState || sgBlendEnable!=sgOGLBlendEnable)
   {
      if (sgBlendEnable)
         glEnable(GL_BLEND);
      else
         glDisable(GL_BLEND);
      sgOGLBlendEnable = sgBlendEnable;
   }
   if (sgBlendEnable)
   {
      if (AlwaysSetState || sgBlendSrc!=sgOGLBlendSrc || sgBlendDest!=sgOGLBlendDest)
      {
         glBlendFunc(sgOGLBlendSrc=sgBlendSrc, sgOGLBlendDest=sgBlendDest);
      }
   }

   if (!sgVertexEnabled)
   {
      glEnableClientState(GL_VERTEX_ARRAY);
      sgVertexEnabled = true;
   }

   glDrawArrays(inMode, 0, inN);
}

void nmeClearTexture(int inID)
{
   if (AlwaysSetState || sgTexture==inID)
   {
      glBindTexture(GL_TEXTURE_2D,0);
      sgOGLTexture = sgTexture = 0;
   }
}

void nmeEnableTexture(bool inEnable)
{
   sgTexEnable = inEnable;
}

void nmeSetTexture(int inID,bool inBindNow)
{
   sgTexture = inID;
   if (AlwaysSetState || inBindNow)
   {
      if (AlwaysSetState || sgTexture!=sgOGLTexture)
      {
         glBindTexture(GL_TEXTURE_2D,sgTexture);
         sgOGLTexture = sgTexture;
      }
   }
}


void nmeSetBlend(bool inEnable, GLenum inSrc, GLenum inDest )
{
   sgBlendEnable = inEnable;
   sgBlendSrc = inSrc;
   sgBlendDest = inDest;
}





#endif
