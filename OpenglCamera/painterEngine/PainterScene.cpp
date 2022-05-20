#include "PainterScene.h"
#include "GraphicItemBase.h"
#include "GraphicItemLine.h"
#include "GraphicItemTriangle.h"
#include "GraphicItemCube.h"
#include "GraphicItemPoint.h"
#include "GraphicItemCircle.h"
#include "GraphicItemSphere.h"
#include "GraphicItemBezier.h"

PainterScene::PainterScene() :camera_(glm::vec3(0.0f, 0.0f, 10.0f))
{
	
}

PainterScene::~PainterScene()
{
	
}

void PainterScene::initScene()
{
	//initBeizerVAOVBO();
	initStlVAOVBO();
	//渲染循环
	while (!glfwWindowShouldClose(window_ptr))
	{
		float currentFrame = glfwGetTime();
		delta_time_ = currentFrame - last_frame_;
		last_frame_ = currentFrame;

		processInput(window_ptr);
		glEnable(GL_DEPTH_TEST);
		//初始化场景背景色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
#if 1
		Shader stlShader("D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/circle.vs","D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/circle.fs");
#endif

		//坐标转换
		//创建变换矩阵
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = camera_.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera_.Zoom), (float)scr_width_ / scr_height_, near_, far_);
		
#if 0
		//绘制贝塞尔
		beizerShader.use();
		beizerShader.setMat4("model", model);
		beizerShader.setMat4("view", view);
		beizerShader.setMat4("projection", projection);
		beizerShader.setVec3("color", glm::vec3(1.0f, 0.0f, 1.0f));
		glBindVertexArray(beizerVAO);
		glPointSize(5);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		int num = beizerVertices_.size() / 3;
		glDrawArrays(GL_LINES, 0,num);
#endif 

#if 1
		//绘制stl
		stlShader.use();
		stlShader.setMat4("model", model);
		stlShader.setMat4("view", view);
		stlShader.setMat4("projection", projection);
		stlShader.setVec3("color", glm::vec3(1.0f, 0.0f, 1.0f));
		glBindVertexArray(stlVAO);
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		int num = stlVertiecs.size() / 3;
		glDrawArrays(GL_TRIANGLES, 0, num);
#endif 

#if 0
		for (int i = 0; i < itemVec_.size(); i++)
		{
			itemVec_[i]->useShader();
			itemVec_[i]->setModel("model", model);
			itemVec_[i]->setView("view", view);
			itemVec_[i]->setProjection("projection", projection);
			itemVec_[i]->drawCall();
		}
#endif 
		//交换渲染缓冲
		glfwSwapBuffers(window_ptr);
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
	if (move_camera_)
	{
		camera_.ProcessMouseMovement(xoffset, yoffset);
	}
	else
	{
		camera_.ProcessMouseRotate(xoffset, yoffset);

	}

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
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		move_camera_ = true;
	}
	else
	{
		move_camera_ = false;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_.ProcessKeyboard(FORWARD, delta_time_);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_.ProcessKeyboard(BACKWARD, delta_time_);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_.ProcessKeyboard(LEFT, delta_time_);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_.ProcessKeyboard(RIGHT, delta_time_);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera_.resetPosition(0.0f, 0.0f, 10.0f);
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

#ifdef __APdisplay_utilsE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	//创建 window

	GLFWwindow* window = nullptr;
	window = glfwCreateWindow(scr_width_, scr_height_, "LearnOpenGL", NULL, NULL);
	window_ptr = window;
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
	return window_ptr;
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

void PainterScene::addPoint(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemPoint* PointItem = new GraphicItemPoint(vsPath, fsPath,color);
	PointItem->setVertexData(vertexData);
	PointItem->initVAOVBO();
	itemVec_.push_back(PointItem);
}

void PainterScene::addLine(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath,color);
	lineItem->setVertexData(vertexData);
	lineItem->initVAOVBO();
	itemVec_.push_back(lineItem);
}

void PainterScene::addCube(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCube* cubeItem = new GraphicItemCube(vsPath, fsPath,color);
	cubeItem->setVertexData(vertexData);
	cubeItem->initVAOVBO();
	itemVec_.push_back(cubeItem);
}

void PainterScene::addTriangle(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemTriangle* triangleItem = new GraphicItemTriangle(vsPath, fsPath,color);
	triangleItem->setVertexData(vertexData);
	triangleItem->initVAOVBO();
	itemVec_.push_back(triangleItem);
}

void PainterScene::addCircle(glm::vec3 center, float r, int sectorCount, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCircle* circleItem = new GraphicItemCircle(vsPath, fsPath, color);
	circleItem->setRadius(r);
	circleItem->setSectorCount(sectorCount);
	circleItem->setOrgin(center);
	circleItem->initVAOVBO();
	itemVec_.push_back(circleItem);
}

void PainterScene::addSphere(glm::vec3 center, float r, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemSphere* sphereItem = new GraphicItemSphere(vsPath, fsPath, color);
	sphereItem->setOrigin(center);
	sphereItem->setRadius(r);
	sphereItem->initVAOVBO();
	itemVec_.push_back(sphereItem);
}

void PainterScene::addBezier(std::vector<display_utils::Point2>& controlPoints, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemBezier* bezierItem = new GraphicItemBezier(vsPath, fsPath, color);
	bezierItem->setControlPoints(controlPoints);
	bezierItem->initVAOVBO();
	itemVec_.push_back(bezierItem);
}



void PainterScene::initBeizerVAOVBO()
{
	genearteBezier();

	glGenVertexArrays(1, &beizerVAO);
	glGenBuffers(1, &beizerVBO);

	glBindVertexArray(beizerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, beizerVBO);

	glBufferData(GL_ARRAY_BUFFER, beizerVertices_.size() * sizeof(float), &beizerVertices_[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

}

void PainterScene::initStlVAOVBO()
{

	std::string file = "D:/base_link.stl";
	//DoTheImportThing(file);
	display_utils::STLDocument stlDoc;
	openBinary(file,stlDoc);


	glGenVertexArrays(1, &stlVAO);
	glGenBuffers(1, &stlVBO);

	glBindVertexArray(stlVAO);
	glBindBuffer(GL_ARRAY_BUFFER, stlVBO);
	
	glBufferData(GL_ARRAY_BUFFER, stlVertiecs.size() * sizeof(float), &stlVertiecs[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

bool PainterScene::openBinary(const std::string &p_FileName, display_utils::STLDocument &p_STLDocument)
{
		p_STLDocument.clear();
		FILE *fp;
		int numFacet;
		int error = fopen_s(&fp, p_FileName.c_str(), "rb");
		float normal[3];
		float point1[3];
		display_utils::STLDocument::STLPoint stlPoint;
		display_utils::STLDocument::STLFacet stlFacet;
		if (0 == error)//成功打开文件
		{
			fseek(fp, STL_LABEL_SIZE, SEEK_SET);//跳过开头
			fread(&numFacet, sizeof(int), 1, fp);//读取facet的数目
			for (int facetIndex = 0; facetIndex < numFacet; ++facetIndex)
			{
				unsigned short attr; //用来储存属性,实际上把这个值丢弃了
				fread(normal, sizeof(float), 3, fp);//读取facet的法向量
				stlFacet.m_Normal = normal;
				for (int i = 0; i < 3; ++i)
				{
					fread(point1, sizeof(float), 3, fp);//读取vertex
					stlFacet.m_PointList[i] = point1;
					stlPoint = point1;
					p_STLDocument.m_VertexList.push_back(stlPoint);

					stlVertiecs.push_back(stlPoint.x);
					stlVertiecs.push_back(stlPoint.y);
					stlVertiecs.push_back(stlPoint.z);
				}
				fread(&attr, sizeof(unsigned short), 1, fp);//读取属性
				p_STLDocument.m_FacetList.push_back(stlFacet);
			}
		}
		fclose(fp);



		//std::cout << "point size is : " << p_STLDocument.m_VertexList.size() << std::endl;
		//std::cout << "face size is : " << p_STLDocument.m_FacetList.size() << std::endl;

		return true;

}