#include"../painterEngine/PainterScene.h"
#include "../common/commonDef.h"
#include <direct.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <learnopengl/model.h>
#include <list>

#include "../urdfParse/tinyxml.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int modes);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void curse_poscallback(GLFWwindow *window, double x, double y);

PainterScene painterScene;

int main()
{
	painterScene.initWindow();
	GLFWwindow* window = painterScene.getWindow();
	if (window)
	{
		//绑定回调函数
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetScrollCallback(window, scroll_callback);
		//glfwSetCursorPosCallback(window, curse_poscallback);//获取鼠标位置
	}
	else
	{
		return -1;
	}
	bool loadSucc = painterScene.loadOPenglFun();
	if (!loadSucc)
	{
		std::cout << "failed to load glad" << std::endl;
		return -1;
	}
#if 1
	//添加图元

	std::vector<float> pointData = {
	   0.0f,0.0f,3.0f
	};

	std::vector<display_utils::TVertex> circleData;

	std::vector<float> lineData1 =
	{
	   -10.0f,0.0f,0.0f,
	   10.0f,0.0f,0.0f
	};

	std::vector<float> tr1 = {
		-0.5f, -0.5f, -2.0f,
		 0.5f, -0.5f, -2.0f,
		 0.0f,  0.5f, -2.0f
	};
	std::vector<float> tr2 = {
		-0.5f, -0.5f, -4.0f,
		 0.5f, -0.5f, -4.0f,
		 0.0f,  0.5f, -4.0f
	};
	std::vector<float> tr3 = {
		-0.5f, -0.5f, 2.0f,
		 0.5f, -0.5f, 2.0f,
		 0.0f,  0.5f, 2.0f
	};

	std::vector<float> cubeData = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
	};

	char *path = NULL;
	path = _getcwd(NULL, 1);
	std::string baseDir(path);
	baseDir = baseDir + "\\shaders\\";
	//painterScene.addPoint(pointData, baseDir + "point.vs", baseDir + "point.fs", glm::vec3(1.0f, 1.0f, 0.0f));
	//painterScene.addLine(lineData1, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(1.0f, 1.0f, 1.0f));
    //painterScene.addCircle(glm::vec3(0.0f,0.2f,-4.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	//painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	//painterScene.addCircle(glm::vec3(0.0f,0.2f,-3.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	//painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	//painterScene.addCircle(glm::vec3(0.0f,0.2f,-2.3f),1.0f,16, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	//painterScene.addTriangle(tr2, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 0.0f));
	//painterScene.addTriangle(tr3, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 1.0f));
	//painterScene.addCube(cubeData, baseDir + "cube.vs", baseDir + "cube.fs", glm::vec3(0.0f, 1.0f, 0.0f));
	//painterScene.addSphere(glm::vec3(0.0f, 0.0f, 4.0f),0.5f, baseDir + "ball.vs", baseDir + "ball.fs", glm::vec3(0.0f, 1.0f, 1.0f));
	//painterScene.addSphere(glm::vec3(0.0f, 0.0f, -4.0f), 0.8f, baseDir + "ball.vs", baseDir + "ball.fs", glm::vec3(0.0f, 1.0f, 1.0f));

	painterScene.addModel("D:/urdfResource/","D:/urdfResource/abb_irb6700_support/urdf/irb6700_150_320.urdf", display_utils::MODE_STL, baseDir + "stl.vs", baseDir + "stl.fs");
	painterScene.addGrid(30, 30, 30, 30, baseDir + "line.vs", baseDir + "line.fs");
#endif
	//初始化场景
	painterScene.initScene();

	return 0;
}



void curse_poscallback(GLFWwindow *window, double x, double y)
{
	//std::cout << "(pos:" << x << "," << y << ")" << std::endl;
	//painterScene.curse_poscallback(window, x, y);
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	painterScene.framebuffer_size_callback(window, width, height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	painterScene.mouse_callback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int modes)
{
	painterScene.mouse_button_callback(window, button, action, modes);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	painterScene.scroll_callback(window, xoffset, yoffset);
}


