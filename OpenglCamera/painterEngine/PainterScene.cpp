#include "PainterScene.h"
#include "GraphicItemBase.h"
#include "GraphicItemLine.h"
#include "GraphicItemTriangle.h"
#include "GraphicItemCube.h"
#include "GraphicItemPoint.h"
#include "GraphicItemCircle.h"
#include "GraphicItemSphere.h"
#include "GraphicItemBezier.h"
#include "GraphicUrdfModel.h"
#include <stb_image.h>


PainterScene::PainterScene() :camera_(glm::vec3(0.0f, 2.0f, 10.0f))
{
	
}

PainterScene::~PainterScene()
{
	for (int i = 0; i < item_vec_.size(); i++)
	{
		if (item_vec_[i])
		{
			delete item_vec_[i];
		}
	}
}

void PainterScene::initScene()
{

	//initStlVAOVBO();

	//initPlaneVAOVBO();
    //initTexture();
#if 0
	Shader planeShader("D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/plane.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/plane.fs");
	planeShader.setInt("texture1", texture1);
#endif

	//渲染循环
	while (!glfwWindowShouldClose(window_ptr))
	{
		float currentFrame = glfwGetTime();
		delta_time_ = currentFrame - last_frame_;
		last_frame_ = currentFrame;

		processInput(window_ptr);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);

		//初始化场景背景色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		//坐标转换
		//创建变换矩阵
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = camera_.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera_.Zoom), (float)scr_width_ / scr_height_, near_, far_);

#if 0
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

		//绘制plane
		planeShader.use();
		planeShader.setMat4("model", model);
		planeShader.setMat4("view", view);
		planeShader.setMat4("projection", projection);
		planeShader.setVec3("color", glm::vec3(0.5f, 0.5f, 0.5f));
		glBindVertexArray(planeVAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindTexture(GL_TEXTURE_2D, texture1);
		int num = planeVertices.size() / 3;
		glDrawArrays(GL_TRIANGLES, 0, num);
#endif 

#if 1
		renderItems(item_vec_, view, projection);
		if (show_grid_)
		{
			renderGrid(view, projection);
		}
#endif 
		//交换渲染缓冲
		glfwSwapBuffers(window_ptr);
		glfwPollEvents();
		
		float winX=0.0f, winY=0.0f, winZ=0.0f;
#if 0
		if (is_mouse_pressed_)
		{
			//glReadPixels((int)winX, scr_height_ - (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			glReadPixels(scr_width_, scr_height_ , 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			//标准化到-1到1之间，裁剪坐标系坐标值范围 -1到1
			float x = (2.0f*winX) / scr_width_ - 1.0f;
			float y = 1.0f - (2.0f*winY) / scr_height_;
			float z = winZ * 2.0 - 1.0f;

			if (1)
			{
				//float w = (2.0 * near1) * 100 / (far1 + near1 - z * (far1 - near1));//深度值 depth
				//x,y,z 都乘以一个w变换到标准化坐标前的坐标
				std::cout << "standard space :" << " x: " << x << "  y: " << y << "  z:" << z << std::endl;
				float w = near_ * far_ / (near_*winZ - far_ * winZ + far_);
				glm::vec3 worldPostion = glm::inverse(view)*glm::inverse(projection)*w*glm::vec4(x, y, z, 1);
				std::cout << "word space :" << " x: " << worldPostion.r << "  y: " << worldPostion.g << "  z:" << worldPostion.b << "  w:" << w << std::endl;
			}
		}
#endif

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
		camera_.ProcessMouseMovement(-xoffset, -yoffset);
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

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		show_grid_ = false;
	}
	else
	{
		show_grid_ = true;
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

void PainterScene::curse_poscallback(GLFWwindow *window, double x, double y)
{

}

void PainterScene::renderModel(glm::mat4& view, glm::mat4& projection)
{
	for (int i = 0; i < model_vec_.size(); i++)
	{
		//std::vector<GraphicModel*>& itemVec = model_vec_[i];
	}
}

void PainterScene::renderGrid(glm::mat4 & view, glm::mat4 & projection)
{
	renderItems(grid_vec_, view, projection);
}


void PainterScene::renderItems(std::vector<GraphicItemBase*>& itemVec, glm::mat4& view,glm::mat4& projection)
{
	for (int i = 0; i < itemVec.size(); i++)
	{
		if (!itemVec[i]) continue;
		itemVec[i]->useShader();
		itemVec[i]->setViewPos(camera_.Position);
		itemVec[i]->setShaderVec3("viewPos", camera_.Position);
		itemVec[i]->setShaderVec3("lightColor", itemVec[i]->getLightColor());
		itemVec[i]->setShaderVec3("lightPos", itemVec[i]->getLightPos());
		itemVec[i]->setShaderMat4("model", itemVec[i]->getModelMatrix());
		itemVec[i]->setShaderMat4("view", view);
		itemVec[i]->setShaderMat4("projection", projection);
		itemVec[i]->drawCall();
	}
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
	glfwWindowHint(GLFW_SAMPLES, 4);

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
	item_vec_.push_back(PointItem);
}

void PainterScene::addLine(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath,color);
	lineItem->setVertexData(vertexData);
	lineItem->initVAOVBO();
	item_vec_.push_back(lineItem);
}

void PainterScene::addCube(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCube* cubeItem = new GraphicItemCube(vsPath, fsPath,color);
	cubeItem->setVertexData(vertexData);
	cubeItem->initVAOVBO();
	item_vec_.push_back(cubeItem);
}

void PainterScene::addTriangle(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemTriangle* triangleItem = new GraphicItemTriangle(vsPath, fsPath,color);
	triangleItem->setVertexData(vertexData);
	triangleItem->initVAOVBO();
	item_vec_.push_back(triangleItem);
}

void PainterScene::addCircle(glm::vec3 center, float r, int sectorCount, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemCircle* circleItem = new GraphicItemCircle(vsPath, fsPath, color);
	circleItem->setRadius(r);
	circleItem->setSectorCount(sectorCount);
	circleItem->setOrgin(center);
	circleItem->initVAOVBO();
	item_vec_.push_back(circleItem);
}

void PainterScene::addSphere(glm::vec3 center, float r, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemSphere* sphereItem = new GraphicItemSphere(vsPath, fsPath, color);
	sphereItem->setOrigin(center);
	sphereItem->setRadius(r);
	sphereItem->initVAOVBO();
	item_vec_.push_back(sphereItem);
}

void PainterScene::addBezier(std::vector<display_utils::Point2>& controlPoints, std::string vsPath, std::string fsPath, glm::vec3 color)
{
	GraphicItemBezier* bezierItem = new GraphicItemBezier(vsPath, fsPath, color);
	bezierItem->setControlPoints(controlPoints);
	bezierItem->initVAOVBO();
	item_vec_.push_back(bezierItem);
}

void PainterScene::addModel(std::string packageDir,std::string modelPath, display_utils::ModelType type,std::string vsPath, std::string fsPath)
{
	switch (type)
	{
	case display_utils::MODE_STL:
	{
		GraphicUrdfModel* urdfModel = new GraphicUrdfModel(display_utils::MODE_STL);
		urdfModel->setPackageDir(packageDir);
		urdfModel->loadModel(modelPath, vsPath, fsPath);

		if (urdfModel->getStlVec().size() > 0)
		{
			item_vec_.insert(item_vec_.end(), urdfModel->getStlVec().begin(), urdfModel->getStlVec().end());
		}
		model_vec_.push_back(urdfModel);
	}
		break;
	case display_utils::MODE_OBJ:

		break;
	case display_utils::MODEL_NONE:
		break;
	default:
		break;
	}
}

void PainterScene::addGrid(float width, float height, int row, int col, std::string vsPath, std::string fsPath, glm::vec3 origin, glm::vec3 color)
{
	if (width <= 0 || height <= 0 || row <=0 || col <=0)
	{
		std::cout << "Warning:failed to create a grid,width or height must be positive"<<std::endl;
		return;
	}

	glm::vec3 p1 = { -width / 2.0,origin.y,-height / 2.0 };
	glm::vec3 p2 = { width / 2.0, origin.y,-height / 2.0 };
	glm::vec3 p3 = { width / 2.0, origin.y, height / 2.0 };
	glm::vec3 p4 = { -width / 2.0,origin.y, height / 2.0 };

	//生成x方向直线
	float deltaZ = height / row;
	//p1--------------------->p2
	for (int i = 0; i <= row; i++)
	{
		std::vector<float> lineData;
		lineData.push_back(p1.x);
		lineData.push_back(p1.y);
		lineData.push_back(p1.z+deltaZ * i);

		lineData.push_back(p2.x);
		lineData.push_back(p2.y);
		lineData.push_back(p2.z+deltaZ * i);

		GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath, color);
		lineItem->setVertexData(lineData);
		lineItem->initVAOVBO();
		grid_vec_.push_back(lineItem);

   /*	glm::vec3 pBegin = { p1.x,p1.y,p1.z + deltaZ * i };
		glm::vec3 pEnd = { p2.x,p2.y,p2.z + deltaZ * i };
		std::cout << " pBegin : " << pBegin.x << " " << pBegin.y << " " << pBegin.z << std::endl;
		std::cout << " pEnd : " << pEnd.x << " " << pEnd.y << " " << pEnd.z << std::endl;
	*/
	}

	//生成z方向直线
	//p1---------------------->p4
	float deltaX = width / col;
	for (int i = 0; i <= col; i++)
	{
		std::vector<float> lineData;
		lineData.push_back(p1.x + deltaX * i);
		lineData.push_back(p1.y);
		lineData.push_back(p1.z);

		lineData.push_back(p4.x + deltaX * i);
		lineData.push_back(p4.y);
		lineData.push_back(p4.z);

		GraphicItemLine* lineItem = new GraphicItemLine(vsPath, fsPath, color);
		lineItem->setVertexData(lineData);
		lineItem->initVAOVBO();
		grid_vec_.push_back(lineItem);
	}
}

void PainterScene::initStlVAOVBO()
{

	std::string file = "D:/base_link.stl";
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

void PainterScene::initPlaneVAOVBO()
{
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);

	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);

	glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), &planeVertices[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	//顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//纹理坐标
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

}

void PainterScene::initTexture()
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(std::string("D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/resources/textures/marble.jpg").c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture...." << std::endl;
	}

	stbi_image_free(data);

}
