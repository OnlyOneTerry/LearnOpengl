#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <iostream>
#include "../common/commonDef.h"

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
	void addCircle(glm::vec3 origin,std::vector<display_utils::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addSphere(glm::vec3 center, std::string vsPath, std::string fsPath, glm::vec3 color);
public:
	Camera camera_;
private:
	//初始化窗口大小
	int scr_width_ = 1500;
	int scr_height_ = 1000;
	double last_x_ = 0.0f;
	double last_y_ = 0.0f;
	float  near_ = 0.1f;
	float  far_ = 200.0f; 
	float delta_time_ = 0.0f;
	float last_frame_ = 0.0f;
	bool is_mouse_pressed_ = false;
	bool first_mouse_ = false;
	GLFWwindow* window_ptr = nullptr;
	bool move_camera_ = false;
	//要渲染的图元
	std::vector<GraphicItemBase*> itemVec_;
public:

	////////测试画圆
	unsigned int VBO, VAO;
	void initVAOVBO();
	const int sectorCount = 72;
	const float pierRadius = 1.0f;
	const float pierHeight = 5.0f;
	std::vector<display_utils::TVertex> _pierVertices;
	//圆上的点
	std::vector<display_utils::TVertex> getUnitCircleVertices();
	void buildCylinderVertices(std::vector<display_utils::TVertex>& vertices);

	//测试画球
	void generateSphereVertices();
	void generateSphereVerticesIndex();
	void initSphereVAOVBO();

	unsigned int sphereVBO, sphereVAO;
	GLuint element_buffer_object;//EBO
	const GLfloat PI = 3.14159265358;
	//将球横纵划分成50*50的网格
	const int Y_SEGMENTS = 50;
	const int X_SEGMENTS = 50;
	std::vector<float> sphereVertices;
	std::vector<int> sphereIndices;

	//测试画心
	void initHeartVAOVBO();
	void generateHeartVertices();
	
	unsigned int heartVAO;
	unsigned int heartVBO;
	std::vector<float> hearVertices = {
	    -1.26, 0, 0.26,
		-1.44, 0, -0.11,
		0.12, 0, -1.55,
		1.12, 0, -0.45,
		0.65, 0, 0.03,
		0.9, 0, 1.41,
		-0.85, 0, 0.69,
		-1.67, 0, -0.0,
		-0.39, 0, -1.2,
		1.17, 0, -0.95,
		0.5, 0, 0.0,
		1.17, 0, 0.95,
		-0.39, 0, 1.2,
		-1.67, 0, 0.0,
		-0.85, 0, -0.69,
		0.9, 0, -1.41,
		0.65, 0, -0.03,
		1.12, 0, 0.45,
		0.12, 0, 1.55,
	   -1.44, 0, 0.11
	};

};

