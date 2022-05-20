#include"../painterEngine/PainterScene.h"
#include "../common/commonDef.h"
#include <direct.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int modes);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
PainterScene painterScene;


bool DoTheImportThing(const std::string& pFile)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		//DoTheErrorLogging(importer.GetErrorString());
		std::printf("failed to import %s!\n", pFile.c_str());
			return false;
	}
	// Now we can access the file's contents. 
	//DoTheSceneProcessing(scene);
	if (scene->HasMeshes())
	{
		std::printf("has %d meshes!\n", scene->mNumMeshes);
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				std::printf("%d: %u vertices!\n", i, scene->mMeshes[i]->mNumVertices);
					if (scene->mMeshes[i]->HasFaces())
						std::printf("%d: %u faces!\n", i, scene->mMeshes[i]->mNumFaces);
			}
	}
	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

int main()
{
	std::string file = "D:/base_link.stl";
	DoTheImportThing(file);
	system("pause");

	return 0;
}

int main1()
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

	std::vector<display_utils::TVertex> circleData;

	std::vector<float> lineData =
	{
	   -1.3f,1.3f,-1.0f,
	   1.3f,1.3f,-1.0f,
	   2.3f,4.3f,-1.0f
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

	//std::string baseDir = "D:/openGl/OpenglTest/OpenglCamera/OpenglCamera/shaders/";
	char *path = NULL;
	path = _getcwd(NULL, 1);
	std::string baseDir(path);
	baseDir = baseDir + "\\shaders\\";
	//painterScene.addPoint(pointData, baseDir + "point.vs", baseDir + "point.fs", glm::vec3(1.0f, 1.0f, 0.0f));
	//painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	//painterScene.addCircle(glm::vec3(0.0f,0.2f,-4.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	//painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	//painterScene.addCircle(glm::vec3(0.0f,0.2f,-3.3f),circleData, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
	//painterScene.addLine(lineData, baseDir + "line.vs", baseDir + "line.fs", glm::vec3(0.0f, 0.0f, 1.0f));
	//painterScene.addCircle(glm::vec3(0.0f,0.2f,-2.3f),1.0f,16, baseDir + "circle.vs", baseDir + "circle.fs", glm::vec3(1.0f, 0.0f, 1.0f));  
    //painterScene.addTriangle(tr2, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 0.0f));
    //painterScene.addTriangle(tr3, baseDir + "triangle.vs", baseDir + "triangle.fs", glm::vec3(1.0f, 1.0f, 1.0f));
    painterScene.addCube(cubeData, baseDir + "cube.vs", baseDir + "cube.fs", glm::vec3(0.0f, 1.0f, 0.0f));
    //painterScene.addSphere(glm::vec3(0.0f, 0.0f, 4.0f),0.5f, baseDir + "ball.vs", baseDir + "ball.fs", glm::vec3(0.0f, 1.0f, 1.0f));
    //painterScene.addSphere(glm::vec3(0.0f, 0.0f, -4.0f), 0.8f, baseDir + "ball.vs", baseDir + "ball.fs", glm::vec3(0.0f, 1.0f, 1.0f));

	std::vector<display_utils::Point2> controlPoints;
	display_utils::Point2 a = { 0, 0.2 };
	display_utils::Point2 b = { 0.4, 0.4 };
	display_utils::Point2 c = { 0.3,  -0.2 };
	display_utils::Point2 d = { 0, -0.4 };
	controlPoints.push_back(a);
	controlPoints.push_back(b);
	controlPoints.push_back(c);
	controlPoints.push_back(d);

	painterScene.addBezier(controlPoints, baseDir + "bezier.vs", baseDir + "bezier.fs", glm::vec3(1.0f, 0.0f, 0.0f));

	std::vector<display_utils::Point2> controlPoints2;

	display_utils::Point2 a1 = { 0, -0.4 };
	display_utils::Point2 b1 = { -0.4, -0.1 };
	display_utils::Point2 c1 = { -0.35, 0.4 };
	display_utils::Point2 d1 = { 0, 0.2 };

	controlPoints2.push_back(a1);
	controlPoints2.push_back(b1);
	controlPoints2.push_back(c1);
	controlPoints2.push_back(d1);

	painterScene.addBezier(controlPoints2, baseDir + "bezier.vs", baseDir + "bezier.fs", glm::vec3(1.0f, 0.0f, 0.0f));
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
