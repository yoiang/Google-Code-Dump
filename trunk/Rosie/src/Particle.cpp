#include "Particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

/*
int setCheckTexture(void)
{
    int texWidth = 256;
    int texHeight = 256;
    GLubyte *texPixels, *p;
    int texSize;
    int i, j;
    int radius;

    texSize = texWidth*texHeight*4*sizeof(GLubyte);
    texPixels = (GLubyte *) malloc(texSize);
    if (texPixels == NULL) 
    {
	  return false;
    }

    p = texPixels;
    for (i=0; i<texHeight; ++i) 
    {
	  for (j=0; j<texWidth; ++j) 
      {
	    GLuint dist = hypot(float(i - (texHeight / 2)),float(j - (texWidth / 2)));
        
        float color = 255-(dist*1.8);
        if (color < 0) color = 0;
        p[0] = color;
        p[1] = color;
        p[2] = color;
        p[3] = color;   
        p+=4;
	  }
    }

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texPixels);

    free(texPixels);
    
    return true;
}
*/