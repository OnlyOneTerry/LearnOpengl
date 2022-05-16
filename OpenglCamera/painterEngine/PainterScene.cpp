#include "PainterScene.h"
#include "GraphicItemBase.h"
#include "GraphicItemLine.h"
#include "GraphicItemTriangle.h"
#include "GraphicItemCube.h"
#include "GraphicItemPoint.h"
#include "GraphicItemCircle.h"

PainterScene::PainterScene() :camera_(glm::vec3(0.0f, 0.0f, 5.0f))
{
	
}

PainterScene::~PainterScene()
{
	
}

void PainterScene::initScene()
{
	//initVAOVBO();
	//渲染循环
	while (!glfwWindowShouldClose(window_))
	{
		processInput(window_);
		glEnable(GL_DEPTH_TEST);
		//初始化场景背景色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
#if 0
		Shader circleShader("D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/circle.vs","D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/circle.fs");
#endif

		//坐标转换
		//创建变换矩阵
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = camera_.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera_.Zoom), (float)scr_width_ / scr_height_, near_, far_);
		
#if 0
		//绘制圆
		circleShader.use();
		circleShader.setMat4("model", model);
		circleShader.setMat4("view", view);
		circleShader.setMat4("projection", projection);
		circleShader.setVec3("color", glm::vec3(1.0f,0.0f,1.0f));
		glBindVertexArray(VAO);
		//glDrawArrays(GL_LINES, 0, _pierVertices.size());
		glDrawArrays(GL_TRIANGLES, 0, _pierVertices.size());
#endif 


#if 1
		for (int i = 0; i < itemVec_.size(); i++)
		{
			itemVec_[i]->setModel("model", model);
			itemVec_[i]->setView("view", view);
			itemVec_[i]->setProjection("projection", projection);
			itemVec_[i]->drawCall();
		}
#endif 
		//交换渲染缓冲
		glfwSwapBuffers(window_);
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
	if (!is_mouse_pressed_) return;

	if (first_mouse_)
	{
		last_x_ = xpos;
		last_y_ = ypos;
		first_mouse_ = false;
	}

	float xoffset = xpos - last_x_;
	float yoffset = last_y_ - ypos; // reversed since y-coordinates go from bottom to top

	last_x_ = xpos;
	last_y_ = ypos;

	camera_.ProcessMouseRotate(xoffset, yoffset);
	//camera_.ProcessMouseMovement(xoffset, yoffset);
}
void PainterScene::mouse_button_callback(GLFWwindow* window, int button, int action, int modes)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			//std::cout << "..............left mouse pressed .............." << std::endl;
			is_mouse_pressed_ = true;
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
			is_mouse_pressed_ = false;
			first_mouse_ = true;
		default:
			break;
		}
	}
}

void PainterScene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera_.ProcessMouseScroll(yoffset);
}

void PainterScene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void PainterScene::setNear(float nearDis)
{
	near_ = nearDis;
}
void PainterScene::setFar(float farDis)
{
	far_ = farDis;
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
	window = glfwCreateWindow(scr_width_, scr_height_, "LearnOpenGL", NULL, NULL);
	window_ = window;
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
	return window_;
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

void PainterScene::addPoint(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemPoint* PointItem = new GraphicItemPoint(vsPath, fsPath,color);
	PointItem->setVertexData(vertexData);
	PointItem->initVAOVBO();
	itemVec_.push_back(PointItem);
}

void PainterScene::addLine(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath,color);
	lineItem->setVertexData(vertexData);
	lineItem->initVAOVBO();
	itemVec_.push_back(lineItem);
}

void PainterScene::addCube(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCube* cubeItem = new GraphicItemCube(vsPath, fsPath,color);
	cubeItem->setVertexData(vertexData);
	cubeItem->initVAOVBO();
	itemVec_.push_back(cubeItem);
}

void PainterScene::addTriangle(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemTriangle* triangleItem = new GraphicItemTriangle(vsPath, fsPath,color);
	triangleItem->setVertexData(vertexData);
	triangleItem->initVAOVBO();
	itemVec_.push_back(triangleItem);
}

void PainterScene::addCircle(std::vector<PL::TVertex> vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCircle* circleItem = new GraphicItemCircle(vsPath, fsPath, color);
	circleItem->setVertexData(vertexData);
	circleItem->initVAOVBO();
	itemVec_.push_back(circleItem);
}


void PainterScene::initVAOVBO()
{
	_pierVertices = getUnitCircleVertices();

	//buildCylinderVertices(_pierVertices);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, _pierVertices.size() * sizeof(PL::TVertex), &_pierVertices[0], GL_STATIC_DRAW);

	//位置属性
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(PL::TVertex),(void*)0);
	glEnableVertexAttribArray(0);

	//法线 属性
	//glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(TVertex),(void*)offsetof(TVertex, TVertex::Normal));
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(PL::TVertex),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

std::vector<PL::TVertex> PainterScene::getUnitCircleVertices()
{
	const float PI = 3.1415926f;
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle = 0.0f;

	glm::vec3 position;
	glm::vec3 normal;
	PL::TVertex tVertex;

	std::vector<PL::TVertex> unitCircleVertices;
	for (int i = 0;i<= sectorCount;i++)
	{
		sectorAngle = i * sectorStep;
		position.x = pierRadius * cos(sectorAngle);
		position.y = 0.0f;
		position.z = pierRadius * sin(sectorAngle);

		normal.x = cos(sectorAngle);
		normal.y = 0.0f;
		normal.z = sin(sectorAngle);

		tVertex.Position = position;
		tVertex.Normal = normal;
		unitCircleVertices.push_back(tVertex);
	}
	return unitCircleVertices;
}

void PainterScene::buildCylinderVertices(std::vector<PL::TVertex>& vertices)
{
	std::vector<PL::TVertex> unitVertices = getUnitCircleVertices();

	// 获取上、下圆周点数组
	std::vector<PL::TVertex> vctTop;
	std::vector<PL::TVertex> vctBot;

	PL::TVertex tVertex;
	for (int i = 0; i < unitVertices.size(); ++i)
	{
		tVertex.Position = unitVertices[i].Position;
		tVertex.Position.y = pierHeight;
		tVertex.Normal = unitVertices[i].Normal;
		vctTop.push_back(tVertex);
	}

	//顶部圆形
	glm::vec3 position;
	for (int i = 0; i < vctTop.size() - 1; ++i)
	{
		glm::vec3 position(0.0f,pierHeight,0.0f);
		glm::vec3 normal(0.0f, 1.0f, 0.0f);
		tVertex.Position = position;
		tVertex.Normal = normal;
		vertices.push_back(tVertex);

		tVertex.Position = vctTop[i].Position;
		vertices.push_back(tVertex);

		tVertex.Position = vctTop[i + 1].Position;
		vertices.push_back(tVertex);
	}


}
