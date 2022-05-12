#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <iostream>

class GraphicItemBase;

class PainterScene
{
public:
	PainterScene();
	~PainterScene();
	void initScene();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int modes);
	void processInput(GLFWwindow* window);

	//初始化窗口
	GLFWwindow* initWindow();
	GLFWwindow* getWindow();
	//退出清理
	void exitToClear();
	//加载opengl函数指针
	bool  loadOPenglFun();
	//告诉gpu如何读取数据
	void initCubeVAOVBO();

	//添加绘制接口
	void addLine(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
	void addCube(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
	void addTriangle(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
public:
	Camera _camera;
	double lastX=0.0f;
	double lastY=0.0f;

	bool isMousePressed = false;
	bool firstMouse = false;
private:
	//初始化窗口大小
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;
	unsigned int cubeVBO, cubeVAO;

	GLFWwindow* _window = nullptr;
	//要渲染的数据点
	//绘制立方体
	float cubeVertices[108]=
	{
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
	
	std::vector<GraphicItemBase*> _itemVec;
};

