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
	//����gpu��ζ�ȡ����
	void initCubeVAOVBO();

	//��ӻ��ƽӿ�
	void addPoint(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
	void addLine(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
	void addCube(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
	void addTriangle(std::vector<float> vertexData, std::string vsPath, std::string fsPath);
public:
	Camera _camera;
	double lastX=0.0f;
	double lastY=0.0f;
	float  _near = 0.1f;
	float  _far = 200.0f;
	bool isMousePressed = false;
	bool firstMouse = false;
private:
	//��ʼ�����ڴ�С
	int SCR_WIDTH = 1200;
	int SCR_HEIGHT = 800;
	unsigned int VBO, VAO;

	GLFWwindow* _window = nullptr;
	//Ҫ��Ⱦ�����ݵ�
	//����������
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

