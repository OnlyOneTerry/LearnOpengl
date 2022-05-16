#include"../painterEngine/PainterScene.h"
#include "../common/commonDef.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int modes);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
PainterScene painterScene;

int main()
{
	painterScene.initWindow();
	GLFWwindow* window = painterScene.getWindow();
	if (window)
	{
		//绑定回调函数
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}
	else
	{
		return -1;
	}
	bool loadSucc = painterScene.loadOPenglFun();
	if (!loadSucc)
	{
		std::cout << "failed to load glad" << std::endl;
		return -1;
	}
#if 1
	//添加图元

	//std::vector<float> pointData = {
	//   0.0f,0.0f,3.0f
	//};

	std::vector<PL::TVertex> pointData0;
	PL::TVertex p0;
	p0.Position = glm::vec3(0.3f,1.2f,0.5f);
	p0.Normal = glm::vec3(0.0f,0.0f,0.0f);
	pointData0.push_back(p0);

	std::vector<PL::TVertex> pointData1;
	PL::TVertex p1;
	p1.Position = glm::vec3(0.3f,1.2f,0.8f);
	p1.Normal = glm::vec3(0.0f,0.0f,0.0f);
	pointData1.push_back(p1);

	std::vector<PL::TVertex> circleData;

	std::vector<float> lineData =
	{
	   -1.3f,1.3f,-1.0f,
	   1.3f,1.3f,-1.0f,
	};


	std::vector<float> tr1 = { 
		-0.5f, -0.5f, -2.0f,
		 0.5f, -0.5f, -2.0f,
		 0.0f,  0.5f, -2.0f
	};
	std::vector<float> tr2 = {
		-0.5f, -0.5f, -4.0f,
		 0.5f, -0.5f, -4.0f,
		 0.0f,  0.5f, -4.0f
	};
	std::vector<float> tr3 = {
		-0.5f, -0.5f, 2.0f,
		 0.5f, -0.5f, 2.0f,
		 0.0f,  0.5f, 2.0f
	};

	std::vector<float> cubeData = {
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

	std::string baseDir = "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/";

	//painterScene.addPoint(pointData0, baseDir +"point.vs", baseDir + "point.fs",glm::vec3(1.0f,1.0f,0.0f));
     painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	 painterScene.addCircle(glm::vec3(0.0f,0.2f,-4.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	 painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	 painterScene.addCircle(glm::vec3(0.0f,0.2f,-0.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	 painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	 painterScene.addCircle(glm::vec3(0.0f,0.2f,-2.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
    //painterScene.addTriangle(tr2, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 0.0f));
    //painterScene.addTriangle(tr3, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 0.0f));
	//painterScene.addCube(cubeData, baseDir + "cube.vs", baseDir + "cube.fs", glm::vec3(0.0f, 1.0f, 0.0f));

#endif
	//初始化场景
	painterScene.initScene();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	painterScene.framebuffer_size_callback(window, width, height);
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	painterScene.mouse_callback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int modes)
{
	painterScene.mouse_button_callback(window, button, action, modes);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	painterScene.scroll_callback(window, xoffset, yoffset);
}
