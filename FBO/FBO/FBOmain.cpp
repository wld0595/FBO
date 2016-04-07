// Include standard headers
#include <stdio.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <common/shader.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

typedef struct 
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat u;
	GLfloat v;
}Vertex;

int main( void )
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW.\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 1024, 768, "Render To Texture", NULL, NULL);
	if( window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	int windowWidth,windowHeight;
	glfwGetWindowSize(window,&windowWidth,&windowHeight);
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	glewExperimental = true; 
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_TEXTURE_2D);

	//vertex data
	Vertex g_VertexBufferDataQ[]={
		{-1.0,1.0,0.0, 0.0,1.0},
		{1.0,1.0,0.0,  1.0,1.0},
		{-1.0,-1.0,0.0,   0.0,0.0},
		{1.0,-1.0,0.0,   1.0,0.0},
	};

	Vertex g_VertexBufferDataT[]={
		{-1.0,-1.0,0.0, 0.0,0.0},
		{1.0,-1.0,0.0,  0.0,0.0},
		{0.0,1.0,0.0,   0.0,0.0},
		
	};

	GLuint VertexArrayID;
	//===Generate the vertex array
	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint VertexBufferQ;
	glGenBuffers(1,&VertexBufferQ);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferQ);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_VertexBufferDataQ),g_VertexBufferDataQ,GL_STATIC_DRAW);

	GLuint VertexBufferT;
	glGenBuffers(1,&VertexBufferT);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferT);
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_VertexBufferDataT),g_VertexBufferDataT,GL_STATIC_DRAW);

	GLuint ProgramIDT = LoadShaders("VertexShaderT.vertexshader","FragmentShaderT.fragmentshader");
	GLint VertexPositionIDT=glGetAttribLocation(ProgramIDT,"vertexPosition_modelspace");

	GLuint ProgramIDQ = LoadShaders("VertexShaderQ.vertexshader","FragmentShaderQ.fragmentshader");
	GLint VertexPositionIDQ=glGetAttribLocation(ProgramIDQ,"vertexPosition_modelspace");

	GLint UVIDQ=glGetAttribLocation(ProgramIDQ,"vertexUV");

	GLint TextureIndexQ       =glGetUniformLocation(ProgramIDQ, "myTextureSampler");

	////Create a texture
	GLuint renderedTexture;
	//GLint texWidth=windowWidth,texHeight=windowHeight;
	GLint texWidth=832,texHeight=416;
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texWidth, texHeight, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Create a FBO
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, renderedTexture,0);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	do{
		
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glViewport(0,0,texWidth,texHeight); 

 		glUseProgram(ProgramIDT);

 		glEnableVertexAttribArray(VertexPositionIDT);

 		glBindBuffer(GL_ARRAY_BUFFER,VertexBufferT);
 		glVertexAttribPointer(VertexPositionIDT,3,GL_FLOAT,GL_FALSE,20,(void *)0);
 		glDrawArrays(GL_TRIANGLE_STRIP,0,3);
 
 		glDisableVertexAttribArray(VertexPositionIDT);

		//=====////‰÷»æµΩ∆¡ƒª…œ
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		glClearColor( 1, 1, 1, 0 );
		glClear( GL_COLOR_BUFFER_BIT);

		glViewport(0,0,windowWidth,windowHeight); 
		
		glUseProgram(ProgramIDQ);
 		glActiveTexture(GL_TEXTURE0);
 		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glUniform1i(TextureIndexQ,0);

		glEnableVertexAttribArray(VertexPositionIDQ);
		glBindBuffer(GL_ARRAY_BUFFER,VertexBufferQ);
		glVertexAttribPointer(VertexPositionIDQ,3,GL_FLOAT,GL_FALSE,20,(void *)0);

		glEnableVertexAttribArray(UVIDQ);
		/*glBindBuffer(GL_ARRAY_BUFFER,VertexBufferQ);*/
		glVertexAttribPointer(UVIDQ,2,GL_FLOAT,GL_FALSE,20,(void *)12);

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		glDisableVertexAttribArray(VertexPositionIDQ);
		glDisableVertexAttribArray(UVIDQ);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	/*glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &renderedTexture);*/
	
	glfwTerminate();

	return 0;
}

