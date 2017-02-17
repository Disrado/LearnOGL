//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Shaders
const GLchar* vertexShaderSource =
	"#version 330 core\n"
	"layout(location = 0) in vec3 position;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";

const GLchar* fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

int main()
{
	glfwInit();

	//set all required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create window
	GLFWwindow *window = glfwCreateWindow(800, 600, "OPENGL", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	//init GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	
	//Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	
//Build and compile our shader program--------//
	
//--------Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

//	GLint succes;
//	GLchar infolog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);
//	if (!succes) {
//	 	glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
//	 	std::cout << "Vertex Shader compilation failed\n" << infolog << std::endl;
//	}
	
//--------Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*GLint succes;
	GLchar infolog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);
	if (!succes) {
	 	glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
	 	std::cout << "Fragment Shader compilation failed\n" << infolog << std::endl;
	}*/

//--------Shader Program
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	/*GLint succes;
	GLchar infolog[512];
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &succes);
	if (!succes) {
	 	glGetShaderInfoLog(shaderProgram, 512, NULL, infolog);
	 	std::cout << "Shader progrem link failed\n" << infolog << std::endl;
	}*/
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
//----	Set up vertex and buffers data and attribute pointers  ----//

/*
	----Triangle----
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, //Left
		 0.5f, -0.5f, 0.0f, //Right
		 0.0f,  0.5f, 0.0f, //Top
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
*/

	//----Rectangle----
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f, //Top right
		 0.5f, -0.5f, 0.0f, //Bottom right
		-0.5f, -0.5f, 0.0f, //Bottom left
		-0.5f,  0.5f, 0.0f  //Top left
	};

	GLuint indices[] = { //Start from 0!
		0, 1, 3, //First triangle
		1, 2, 3  //Second triangle
	};

	GLuint VAO, VBO, IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Bind the  vertex array object first and set vertex buffers data and attribute pointers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);	



//----Game Loop----//	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //for triangle 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //for rectangle
		glBindVertexArray(0);

		//Swaps buffers
		glfwSwapBuffers(window);
	}
	
	//Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	
	//clearing any resources allocated by GLFW 
	glfwTerminate();	
	return 0;
}

//Is called whenever a key is pressed
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
