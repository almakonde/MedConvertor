
#include "SimText.h"

/*
GLenum texture_target=GL_TEXTURE_2D;
GLenum internal_format=GL_RGBA32F_ARB;
GLenum texture_format=GL_RGBA;
*/
void checkGLErrors (const char *label);

bool checkFramebufferStatus() {
    GLenum status;
    status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            return true;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
	    printf("Framebuffer incomplete, incomplete attachment\n");
            return false;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
	    printf("Unsupported framebuffer format\n");
            return false;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
	    printf("Framebuffer incomplete, missing attachment\n");
            return false;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
	    printf("Framebuffer incomplete, attached images must have same dimensions\n");
            return false;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
	    printf("Framebuffer incomplete, attached images must have same format\n");
            return false;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
	    printf("Framebuffer incomplete, missing draw buffer\n");
            return false;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
	    printf("Framebuffer incomplete, missing read buffer\n");
            return false;
    }
    return false;
}

/**
 * Sets up a floating point texture with NEAREST filtering.
 * (mipmaps etc. are unsupported for floating point textures)
 */
void SimText::setupTexture(unsigned int texID)
{
    // make active and bind
    glBindTexture(texture_target,texID);
    // turn off filtering and wrap modes
    glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // define texture with floating point format
    glTexImage2D(texture_target,0,internal_format,width,height,0,texture_format,GL_FLOAT,0);
}


/**
 * Transfers data to texture. 
 * Check web page for detailed explanation on the difference between ATI and NVIDIA.
 */
void SimText::transferToTexture(unsigned int texID,float*arr) 
{
	if(texID==-1)texID=texture[!writeTex];
    glBindTexture(texture_target, texID);
    glTexSubImage2D(texture_target,0,0,0,width,height,texture_format,GL_FLOAT,arr);
	
}
/*
void SimText::Attach(SimText* txt)
{
	glUniform1i(shader_program->getUniLoc(txt->tex_name),txt->ID_to_use);
}
*/
SimText::SimText(const GLchar*t_name,int w,int h,ShaderProgram* spr,int ID_to_Use):tex_name(t_name),ID_to_use(ID_to_Use)
{
	writeTex=1;
	shader_program = spr;
	texture_target=GL_TEXTURE_2D;
	internal_format=GL_RGBA32F_ARB;
	texture_format=GL_RGBA;

	shader_program->Use();
	shader_program->SetVar(tex_name,(unsigned int)ID_to_use);
	shader_program->UnUse();

	width=w;
	height=h;
    // create FBO (off-screen framebuffer)
    glGenFramebuffersEXT(1, &fb); 
    // bind offscreen framebuffer (that is, skip the window-specific render target)
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);

    // viewport transform for 1:1 pixel=texel=data mapping
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1,0.0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);

    glGenTextures(2, texture);

    setupTexture(texture[0]);
    

    setupTexture(texture[1]);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE); 
    

    // check if something went completely wrong
    checkGLErrors ("createFBOandTextures()");
	//Simulation();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
};

SimText::~SimText()
{
    glDeleteTextures (2,texture);
    glDeleteFramebuffersEXT (1,&fb);
}

void SimText::Simulation(float* arr)
{
 glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
    // attach texture

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, texture_target, texture[writeTex],0);

    // viewport transform for 1:1 pixel=texel=data mapping
    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0,1,0.0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,width,height);
    
    glDrawBuffer (GL_COLOR_ATTACHMENT0_EXT);
    //glUseProgram(shader.h_program);
	shader_program->Use();

    glActiveTexture(GL_TEXTURE0+ID_to_use);
    glBindTexture(texture_target, texture[!writeTex]);
	shader_program->SetVar(tex_name,(unsigned int)ID_to_use);
    

    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);	        glVertex2f(0.0, 0.0);
    glTexCoord2f(1, 0.0);	        glVertex2f(1, 0.0);
    glTexCoord2f(1, 1);	glVertex2f(1, 1);
    glTexCoord2f(0.0, 1);	        glVertex2f(0.0, 1);
    glEnd();


     checkFramebufferStatus();
	
    checkGLErrors(tex_name);

	if(arr)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glReadPixels(0, 0, width, height,texture_format,GL_FLOAT,arr);
	}

    glUseProgram(0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glActiveTexture(GL_TEXTURE0);

    // swap textures
    writeTex=!writeTex;

	//glPopMatrix();
    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
}
void SimText::UploadTexture(float *arr)
{
	glActiveTexture(GL_TEXTURE0+ID_to_use);
    setupTexture(texture[!writeTex]);
    transferToTexture(texture[!writeTex],arr);
	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(texture_target,texture[!writeTex]);
//	gluBuild2DMipmaps(texture_target, 4, width,height, texture_format, GL_FLOAT,arr);


}
void SimText::UploadTexture1(float *arr)
{
	glActiveTexture(GL_TEXTURE0+ID_to_use);
    setupTexture(texture[writeTex]);
    transferToTexture(texture[writeTex],arr);
	glActiveTexture(GL_TEXTURE0);


}
void SimText::DownloadTexture(float *arr)
{
	glLoadIdentity();
	glDisable(GL_BLEND);

	shader_program->Use();
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadPixels(0, 0, width, height,texture_format,GL_FLOAT,arr);

    glUseProgram(0);

	glEnable(GL_BLEND);
}
unsigned int SimText::GetTexture()
{
	return texture[!writeTex];
}

/////////////////////////////////////////////////////


void Text::setupTexture(unsigned int texID)
{
    // make active and bind
    glBindTexture(texture_target,texID);
    // turn off filtering and wrap modes
    glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // define texture with floating point format
    glTexImage2D(texture_target,0,internal_format,width,height,0,texture_format,GL_FLOAT,0);
}

void Text::transferToTexture(unsigned int texID,float*arr) 
{
	glBindTexture(texture_target, texID);
    glTexSubImage2D(texture_target,0,0,0,width,height,texture_format,GL_FLOAT,arr);
	
}
Text::Text(int w,int h,float *arr)
{
	texture_target=GL_TEXTURE_2D;
	internal_format=GL_RGBA32F_ARB;
	texture_format=GL_RGBA;

	width=w;
	height=h;
    glGenTextures(1, &texture);
    setupTexture(texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE); 
	if(arr)UploadTexture(arr);
};

Text::~Text()
{
    glDeleteTextures (1,&texture);
}

void Text::UploadTexture(float *arr)
{
    setupTexture(texture);
    transferToTexture(texture,arr);
	//glBindTexture(texture_target,texture);
	//gluBuild2DMipmaps(texture_target, 4, width,height, texture_format, GL_FLOAT,arr);


}
unsigned int Text::GetTexture()
{
	return texture;
}