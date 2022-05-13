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

	std::vector<float> pointData = {
	   0.0f,0.0f,3.0f
	};

	std::vector<PL::TVertex> lineData;
	PL::TVertex vertex1;
	vertex1.Position = glm::vec3(-2.5f, 2.5f, 0.0f);
	vertex1.Normal = glm::vec3(0.0f, 0.0f, 0.0f);

	PL::TVertex vertex2;
	vertex2.Position = glm::vec3(-2.5f, 4.5f, 0.0f);
	vertex2.Normal = glm::vec3(0.0f, 0.0f, 0.0f);

	lineData.push_back(vertex1);
	lineData.push_back(vertex2);

	std::vector<float> lineData1 = {
		  -2.5f,2.5f,0.0f,
	      -2.5f,4.5f,0.0f
	};

	std::vector<float> lineData2 = {
		  1.5f,2.5f,0.0f,
		  1.5f,4.5f,0.0f
	};


	std::vector<float> triangleData = {
	  -0.5f,-0.5f,-2.0f,
	   0.5f,-0.5f,-2.0f,
	   0.0f,0.5f,-2.0f
	};

   std::vector<float> triangle2Data = {
	  -0.5f,-0.5f,-4.0f,
	   0.5f,-0.5f,-4.0f,
	   0.0f,0.5f,-4.0f
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

	//painterScene.addPoint(pointData, baseDir +"point.vs", baseDir + "point.fs",glm::vec3(1.0f,1.0f,0.0f));
	painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	painterScene.addCircle(lineData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));
	//painterScene.addLine(lineData2, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(1.0f, 1.0f, 0.0f));
 //   painterScene.addTriangle(triangleData, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 1.0f));
 //   painterScene.addTriangle(triangle2Data, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 0.0f));
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
