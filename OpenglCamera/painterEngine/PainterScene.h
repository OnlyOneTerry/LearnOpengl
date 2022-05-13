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
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);
	//设置近平面远平面
	void setNear(float nearDis);
	void setFar(float farDis);
	//初始化窗口
	GLFWwindow* initWindow();
	GLFWwindow* getWindow();
	//退出清理
	void exitToClear();
	//加载opengl函数指针
	bool  loadOPenglFun();
	//添加绘制接口
	void addPoint(std::vector<float> vertexData, std::string vsPath, std::string fsPath,glm::vec3 color);
	void addLine(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCube(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addTriangle(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
public:
	Camera _camera;
private:
	//初始化窗口大小
	int _SCR_WIDTH = 1200;
	int _SCR_HEIGHT = 800;
	double _lastX = 0.0f;
	double _lastY = 0.0f;
	float  _near = 0.1f;
	float  _far = 200.0f; 
	bool _isMousePressed = false;
	bool _firstMouse = false;
	GLFWwindow* _window = nullptr;
	//要渲染的数据点
	std::vector<GraphicItemBase*> _itemVec;
};

