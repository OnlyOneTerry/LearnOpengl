#include"../painterEngine/PainterScene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int modes);

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
	std::vector<float> lineData = {
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

	painterScene.addLine(lineData, "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/line.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/line.fs");
	painterScene.addLine(lineData2, "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/line.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/line.fs");
    painterScene.addTriangle(triangleData, "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/triangle.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/triangle.fs");
    painterScene.addTriangle(triangle2Data, "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/triangle.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/triangle.fs");
	painterScene.addCube(cubeData, "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/cube.vs", "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/cube.fs");

#endif
	//初始化场景
	painterScene.initScene();
	getchar();
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

