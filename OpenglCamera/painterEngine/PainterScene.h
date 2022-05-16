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
	//���ý�ƽ��Զƽ��
	void setNear(float nearDis);
	void setFar(float farDis);
	//��ʼ������
	GLFWwindow* initWindow();
	GLFWwindow* getWindow();
	//�˳�����
	void exitToClear();
	//����opengl����ָ��
	bool  loadOPenglFun();
	//��ӻ��ƽӿ�
	void addPoint(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath,glm::vec3 color);
	void addLine(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCube(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addTriangle(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCircle(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
public:
	Camera camera_;
private:
	//��ʼ�����ڴ�С
	int scr_width_ = 1200;
	int scr_height_ = 800;
	double last_x_ = 0.0f;
	double last_y_ = 0.0f;
	float  near_ = 0.1f;
	float  far_ = 200.0f; 
	bool is_mouse_pressed_ = false;
	bool first_mouse_ = false;
	GLFWwindow* window_ = nullptr;
	//Ҫ��Ⱦ�����ݵ�
	std::vector<GraphicItemBase*> itemVec_;
public:

	////////����
	unsigned int VBO, VAO;
	void initVAOVBO();
	const int sectorCount = 72;
	const float pierRadius = 1.0f;
	const float pierHeight = 5.0f;
	std::vector<PL::TVertex> _pierVertices;
	//Բ�ϵĵ�
	std::vector<PL::TVertex> getUnitCircleVertices();
	void buildCylinderVertices(std::vector<PL::TVertex>& vertices);

};

