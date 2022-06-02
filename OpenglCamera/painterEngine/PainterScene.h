#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <iostream>
#include "../common/commonDef.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <list>

class GraphicItemBase;
class GraphicModel;

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
	void curse_poscallback(GLFWwindow *window, double x, double y);
	void renderModel(glm::mat4& view, glm::mat4& projection);
	void renderGrid(glm::mat4& view, glm::mat4& projection);
	void renderItems(std::vector<GraphicItemBase*>& itemVec,glm::mat4& view, glm::mat4& projection);
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
	void addPoint(std::vector<float>& vertexData, std::string vsPath, std::string fsPath,glm::vec3 color);
	void addLine(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCube(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addTriangle(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCircle(glm::vec3 center,float r,int sectorCount, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addSphere(glm::vec3 center, float r, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addBezier(std::vector<display_utils::Point2>& controlPoints, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addModel(std::string packageDir,std::string modelPath, display_utils::ModelType type, std::string vsPath, std::string fsPath);
	void addGrid(float width, float height, int row, int col, std::string vsPath, std::string fsPath, glm::vec3 origin = { 0.0f,0.0f,0.0f }, glm::vec3 color = {1.0f,1.0f,1.0f});
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
	//控制网格显示隐藏
	bool show_grid_ = true;
	//要渲染的图元
	std::vector<GraphicItemBase*> item_vec_;
	std::vector<GraphicModel*> model_vec_;
	std::vector<GraphicItemBase*> grid_vec_;
public:

	//模型解析

	unsigned int stlVAO, stlVBO;
	void initStlVAOVBO();
	std::vector<float> stlVertiecs;

	//解析stl模型数据
	const int STL_LABEL_SIZE = 80;
	bool openBinary(const std::string &p_FileName, display_utils::STLDocument &p_STLDocument);
	

	//plane 
	unsigned int planeVAO, planeVBO;
	unsigned int texture1=0;
	void initPlaneVAOVBO();
	void initTexture();

	std::vector<float> planeVertices = {
	 -15.0f,0.0f,-15.0f,0.0f,1.0f,
	  15.0f,0.0f,-15.0f,1.0f,1.0f,
	  15.0f,0.0f, 15.0f,1.0f,0.0f,
	  		  	  
     -15.0f,0.0f,-15.0f,0.0f,1.0f,
	 -15.0f,0.0f, 15.0f,0.0f,0.0f,
	  15.0f,0.0f, 15.0f,1.0f,0.0f
	};
};

