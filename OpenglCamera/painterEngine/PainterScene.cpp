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
	//渲染循环
	while (!glfwWindowShouldClose(_window))
	{
		processInput(_window);
		//初始化场景背景色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//坐标转换
		//创建变换矩阵
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = _camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(_camera.Zoom), (float)_SCR_WIDTH / _SCR_HEIGHT, _near, _far);

		for (int i = 0; i < _itemVec.size(); i++)
		{
			_itemVec[i]->setModel("model", model);
			_itemVec[i]->setModel("view", view);
			_itemVec[i]->setModel("projection", projection);
			_itemVec[i]->drawCall();
		}

		//交换渲染缓冲
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
	if (!_isMousePressed) return;

	if (_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	float xoffset = xpos - _lastX;
	float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top

	_lastX = xpos;
	_lastY = ypos;

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
			_isMousePressed = true;
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
			_isMousePressed = false;
			_firstMouse = true;
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
//初始化窗口
GLFWwindow* PainterScene::initWindow()
{
	//初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	//创建 window

	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(_SCR_WIDTH, _SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	_window = window;
	if (window == nullptr)
	{
		std::cout << "failed to  create GLFW window" << std::endl;
		glfwTerminate();
		return window;
	}
	//设置窗口上下文
	glfwMakeContextCurrent(window);

	return window;
}
GLFWwindow * PainterScene::getWindow()
{
	return _window;
}
//加载opengl函数指针
bool  PainterScene::loadOPenglFun()
{
	//调用glad加载Opengl函数指针

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initalize GLAD" << std::endl;
		return false;
	}

	return true;
}

void PainterScene::addPoint(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemPoint* PointItem = new GraphicItemPoint(vsPath, fsPath,color);
	PointItem->setVertexData(vertexData);
	PointItem->initVAOVBO();
	_itemVec.push_back(PointItem);
}

void PainterScene::addLine(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath,color);
	lineItem->setVertexData(vertexData);
	lineItem->initVAOVBO();
	_itemVec.push_back(lineItem);
}

void PainterScene::addCube(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCube* cubeItem = new GraphicItemCube(vsPath, fsPath,color);
	cubeItem->setVertexData(vertexData);
	cubeItem->initVAOVBO();
	_itemVec.push_back(cubeItem);
}

void PainterScene::addTriangle(std::vector<float> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemTriangle* triangleItem = new GraphicItemTriangle(vsPath, fsPath,color);
	triangleItem->setVertexData(vertexData);
	triangleItem->initVAOVBO();
	_itemVec.push_back(triangleItem);
}
