// Include standard headers
#include <stdio.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);

	/*GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);*/

	//GLuint programID = LoadShaders("E:/share7/TransformVertexShader.vertexshader","E:/share7/ColorFragmentShader.fragmentshader");

	//GLint vertexID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	//GLint texID = glGetAttribLocation(programID, "vertexUV");


	//static const GLfloat g_vertex_buffer_data[] =
	//{ 
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	1.0f,-1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	1.0f,-1.0f, 1.0f
	//};
	//static const GLfloat g_uv_buffer_data[] = //ÎÆÀí×ø±ê»º³åÊý×é
	//{
	//	1.000004f, 0.671847f,
	//	0.999958f, 0.336064f,
	//	0.667979f, 0.335851f,
	//	0.667969f, 0.671889f,
	//	1.000004f, 0.671847f,
	//	0.667979f, 0.335851f
	//};

	/*GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data) , g_vertex_buffer_data, GL_STATIC_DRAW);*/

	/*GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);*/

	/*GLint iWidth,iHeight,iChannel;
	FILE *pFile=fopen("E:/Texture/sky.jpg","rb");
	const unsigned char* pImageData=stbi_load_from_file(pFile,&iWidth,&iHeight,&iChannel,0);

	GLuint TextureID;
	glGenTextures(1,&TextureID);
	glBindTexture(GL_TEXTURE_2D,TextureID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,iWidth,iHeight,0,GL_RGB,GL_UNSIGNED_BYTE,pImageData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);*/

	//Create a texture
	GLuint renderedTexture;
	GLint texWidth=400,texHeight=350;
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texWidth, texHeight, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//Create a FBO
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, renderedTexture,0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	// Create and compile our GLSL program from the shaders
	//GLuint quad_programID = LoadShaders( "E:/share7/Passthrough.vertexshader", "E:/share7/WobblyTexture.fragmentshader" );
	//GLuint vertexID2 = glGetAttribLocation(quad_programID, "vertexPosition_modelspace");
	//GLuint rtexID = glGetUniformLocation(quad_programID, "renderedTexture");
	//GLuint timeID = glGetUniformLocation(quad_programID, "time");

	do{
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);//äÖÈ¾Ö¡»º³å

		glViewport(0,0,windowWidth,windowHeight); 

		glClearColor(1, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);

		glColor4f(1, 0, 0, 1);
		glVertex3d( 0,  1, 0);
		glVertex3d(-1, -1, 0);
		glVertex3d( 1, -1, 0);

		glEnd();

		/*glUseProgram(programID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glUniform1i(TextureID, 0);

		glEnableVertexAttribArray(vertexID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(vertexID,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		glEnableVertexAttribArray(texID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(texID,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 6); 

		glDisableVertexAttribArray(vertexID);
		glDisableVertexAttribArray(texID);*/

		//=====////äÖÈ¾µ½ÆÁÄ»ÉÏ
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glViewport(0,0,windowWidth,windowHeight);

		glClearColor( 0, 0, 1, 0 );
		glClear( GL_COLOR_BUFFER_BIT);
		
		glBegin(GL_POLYGON);

		glColor3f(1, 1, 1);

		glTexCoord2f(1, 1);
		glVertex3d( 1,  1, 0);

		glTexCoord2f(0, 1);
		glVertex3d(-1,  1, 0);

		glTexCoord2f(0, 0);
		glVertex3d(-1, -1, 0);

		glTexCoord2f(1, 0);
		glVertex3d( 1, -1, 0);

		glEnd();

		/*glUseProgram(quad_programID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);

		glUniform1i(rtexID, 0);
		glUniform1f(timeID, (float)(glfwGetTime()*10.0f) );

		glEnableVertexAttribArray(vertexID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(vertexID,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 6); 

		glDisableVertexAttribArray(vertexID);*/

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	/*glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);*/

	glDeleteFramebuffers(1, &FramebufferName);
	//glDeleteTextures(1, &renderedTexture);
	//glDeleteBuffers(1, &quad_vertexbuffer);
	/*glDeleteVertexArrays(1, &VertexArrayID);*/

	glfwTerminate();

	return 0;
}

