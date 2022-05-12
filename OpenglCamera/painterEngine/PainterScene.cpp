#include "PainterScene.h"
#include "GraphicItemBase.h"
#include "GraphicItemLine.h"
#include "GraphicItemTriangle.h"
#include "GraphicItemCube.h"


PainterScene::PainterScene() :_camera(glm::vec3(0.0f, 0.0f, 5.0f))
{
	
}

PainterScene::~PainterScene()
{
	
}

void PainterScene::initScene()
{
#if 0
	if (!_window)
	{
		std::cout << "failed to create windows" << std::endl;
		return ;
	}
	bool loadSucc = loadOPenglFun();
	if (!loadSucc)
	{
		std::cout << "failed to load glad" << std::endl;
		return ;
	}
	//创建Shader
    Shader* cubeShader = new Shader("D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/cube.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/cube.fs");

	//初始化方体VAO VBO
	initCubeVAOVBO();
#endif

	//渲染循环
	while (!glfwWindowShouldClose(_window))
	{
		processInput(_window);
		//初始化场景背景色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//创建变换矩阵
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.1f, 0.0f, 0.0f));
		view = _camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 200.0f);

# if 0
		//将model,view,projection传入shader
		cubeShader->setMat4("model", model);
		cubeShader->setMat4("view", view);
		cubeShader->setMat4("projection", projection);

		//激活shader
		cubeShader->use();
		//激活要启用的VAO
		glBindVertexArray(VAO);
		//drawCall
		glDrawArrays(GL_TRIANGLES, 0, 36);
#endif

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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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
void PainterScene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

void PainterScene::initVAOVBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//绑定当前VAO
	glBindVertexArray(VAO);
	//绑定VBO到当前VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//GPU开辟空间并传入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void PainterScene::initLineVAOVBO()
{
	glGenVertexArrays(1, &LineVAO);
	glGenBuffers(1, &LineVBO);
	//绑定当前VAO
	glBindVertexArray(LineVAO);
	//绑定VBO到当前VAO
	glBindBuffer(GL_ARRAY_BUFFER, LineVBO);
	//GPU开辟空间并传入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void PainterScene::initCubeVAOVBO()
{
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	//绑定当前VAO
	glBindVertexArray(cubeVAO);
	//绑定VBO到当前VAO
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	//GPU开辟空间并传入数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
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
