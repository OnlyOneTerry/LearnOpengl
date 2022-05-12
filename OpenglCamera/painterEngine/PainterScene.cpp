#include "PainterScene.h"
#include "GraphicItemBase.h"
#include "GraphicItemLine.h"
#include "GraphicItemTriangle.h"
#include "GraphicItemCube.h"
#include "GraphicItemPoint.h"

PainterScene::PainterScene() :_camera(glm::vec3(0.0f, 0.0f, 5.0f))
{
	
}

PainterScene::~PainterScene()
{
	
}

void PainterScene::initScene()
{
	//��Ⱦѭ��
	while (!glfwWindowShouldClose(_window))
	{
		processInput(_window);
		//��ʼ����������ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//����ת��
		//�����任����
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = _camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(_camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, _near, _far);

		for (int i = 0; i < _itemVec.size(); i++)
		{
			_itemVec[i]->setModel("model", model);
			_itemVec[i]->setModel("view", view);
			_itemVec[i]->setModel("projection", projection);
			_itemVec[i]->drawCall();
		}

		//������Ⱦ����
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	exitToClear();
}

void PainterScene::exitToClear()
{
	glfwTerminate();
}
void PainterScene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void PainterScene::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!isMousePressed) return;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	_camera.ProcessMouseRotate(xoffset, yoffset);
}
void PainterScene::mouse_button_callback(GLFWwindow* window, int button, int action, int modes)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			//std::cout << "..............left mouse pressed .............." << std::endl;
			isMousePressed = true;
		default:
			break;
		}
	}
	if (action == GLFW_RELEASE)
	{
		//std::cout << "..............left mouse released .............." << std::endl;
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			isMousePressed = false;
			firstMouse = true;
		default:
			break;
		}
	}
}

void PainterScene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	_camera.ProcessMouseScroll(yoffset);
}

void PainterScene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void PainterScene::setNear(float nearDis)
{
	_near = nearDis;
}
void PainterScene::setFar(float farDis)
{
	_far = farDis;
}
//��ʼ������
GLFWwindow* PainterScene::initWindow()
{
	//��ʼ��glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	//���� window

	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	_window = window;
	if (window == nullptr)
	{
		std::cout << "failed to  create GLFW window" << std::endl;
		glfwTerminate();
		return window;
	}
	//���ô���������
	glfwMakeContextCurrent(window);

	return window;
}
GLFWwindow * PainterScene::getWindow()
{
	return _window;
}
//����opengl����ָ��
bool  PainterScene::loadOPenglFun()
{
	//����glad����Opengl����ָ��

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initalize GLAD" << std::endl;
		return false;
	}

	return true;
}

void PainterScene::addPoint(std::vector<float> vertexData, std::string vsPath, std::string fsPath)
{
	GraphicItemPoint* PointItem = new GraphicItemPoint(vsPath, fsPath);
	PointItem->setVertexData(vertexData);
	PointItem->initVAOVBO();
	_itemVec.push_back(PointItem);
}

void PainterScene::addLine(std::vector<float> vertexData, std::string vsPath, std::string fsPath)
{
	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath);
	lineItem->setVertexData(vertexData);
	lineItem->initVAOVBO();
	_itemVec.push_back(lineItem);
}

void PainterScene::addCube(std::vector<float> vertexData, std::string vsPath, std::string fsPath)
{
	GraphicItemCube* cubeItem = new GraphicItemCube(vsPath, fsPath);
	cubeItem->setVertexData(vertexData);
	cubeItem->initVAOVBO();
	_itemVec.push_back(cubeItem);
}

void PainterScene::addTriangle(std::vector<float> vertexData, std::string vsPath, std::string fsPath)
{
	GraphicItemTriangle* triangleItem = new GraphicItemTriangle(vsPath, fsPath);
	triangleItem->setVertexData(vertexData);
	triangleItem->initVAOVBO();
	_itemVec.push_back(triangleItem);
}
