#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <iostream>
#include "../common/commonDef.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <list>

class GraphicItemBase;
class GraphicModel;

class PainterScene
{
public:
	PainterScene();
	~PainterScene();
	void initScene();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int modes);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);
	//���ý�ƽ��Զƽ��
	void setNear(float nearDis);
	void setFar(float farDis);
	//��ʼ������
	GLFWwindow* initWindow();
	GLFWwindow* getWindow();
	//�˳�����
	void exitToClear();
	//����opengl����ָ��
	bool  loadOPenglFun();
	//��ӻ��ƽӿ�
	void addPoint(std::vector<float>& vertexData, std::string vsPath, std::string fsPath,glm::vec3 color);
	void addLine(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCube(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addTriangle(std::vector<float>& vertexData, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addCircle(glm::vec3 center,float r,int sectorCount, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addSphere(glm::vec3 center, float r, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addBezier(std::vector<display_utils::Point2>& controlPoints, std::string vsPath, std::string fsPath, glm::vec3 color);
	void addModel(std::string modelPath, display_utils::ModelType type, std::string vsPath, std::string fsPath);
public:
	Camera camera_;
private:
	//��ʼ�����ڴ�С
	int scr_width_ = 1500;
	int scr_height_ = 1000;
	double last_x_ = 0.0f;
	double last_y_ = 0.0f;
	float  near_ = 0.1f;
	float  far_ = 200.0f; 
	float delta_time_ = 0.0f;
	float last_frame_ = 0.0f;
	bool is_mouse_pressed_ = false;
	bool first_mouse_ = false;
	GLFWwindow* window_ptr = nullptr;
	bool move_camera_ = false;
	//Ҫ��Ⱦ��ͼԪ
	std::vector<GraphicItemBase*> item_vec_;
	std::vector<GraphicModel*> model_vec_;
public:

	//���Ի����α���������
#include <cstdio>

	struct point
	{
		float x;
		float y;
	};
	std::vector<float> beizerVertices_;
	std::vector<point> bezierPoints_;
	// simple linear interpolation between two points
	void lerp(point& dest, const point& a, const point& b, const float t)
	{
		dest.x = a.x + (b.x - a.x)*t;
		dest.y = a.y + (b.y - a.y)*t;
	}
	void initBeizerVAOVBO();

	unsigned int beizerVAO;
	unsigned int beizerVBO;
	// evaluate a point on a bezier-curve. t goes from 0 to 1.0
	void bezier(point &dest, const point& a, const point& b, const point& c, const point& d, const float t)
	{
		point ab, bc, cd, abbc, bccd;
		lerp(ab, a, b, t);           // point between a and b (green)
		lerp(bc, b, c, t);           // point between b and c (green)
		lerp(cd, c, d, t);           // point between c and d (green)
		lerp(abbc, ab, bc, t);       // point between ab and bc (blue)
		lerp(bccd, bc, cd, t);       // point between bc and cd (blue)
		lerp(dest, abbc, bccd, t);   // point on the bezier-curve (black)
	}

	// small test program.. just prints the points
	int genearteBezier()
	{
		// 4 points define the bezier-curve. These are the points used
		// for the example-images on this page.
		point a = { -2, 0 };
		point b = { -2, 3 };
		point c = { 2,  2 };
		point d = { 3, -2 };

		for (int i = 0; i < 100; ++i)
		{
			point p;
			float t = static_cast<float>(i) / 99.0;
			bezier(p, a, b, c, d, t);
			printf("%f %f\n", p.x, p.y);
			bezierPoints_.push_back(p);

		}

		for (int i = 0; i < bezierPoints_.size(); i++)
		{
			point p = bezierPoints_[i];

			beizerVertices_.push_back(p.x);
			beizerVertices_.push_back(p.y);
			beizerVertices_.push_back(-1.0f);

			if (i < bezierPoints_.size()-1)
			{
				point pNext = bezierPoints_[i + 1];
				beizerVertices_.push_back(pNext.x);
				beizerVertices_.push_back(pNext.y);
				beizerVertices_.push_back(-1.0f);
			}
		}

		return 0;
	}

	//ģ�ͽ���

	unsigned int stlVAO, stlVBO;

	void initStlVAOVBO();

	std::vector<float> stlVertiecs;

	void processMesh(aiMesh* mesh, std::vector<float>& vertices)
	{
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);
			//std::cout << "x : " << mesh->mVertices[i].x << "y : " << mesh->mVertices[i].y << "z : " << mesh->mVertices[i].z << std::endl;
		}
	}


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
			std::list<float> vertixAll;
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				std::printf("%d: %u vertices!\n", i, scene->mMeshes[i]->mNumVertices);
				processMesh(scene->mMeshes[i], stlVertiecs);
				if (scene->mMeshes[i]->HasFaces())
				{
					scene->mMeshes[i]->mFaces;
				}
					std::printf("%d: %u faces!\n", i, scene->mMeshes[i]->mNumFaces);
			}
		}
		// We're done. Everything will be cleaned up by the importer destructor
		return true;
	}

	//����stlģ������
	const int STL_LABEL_SIZE = 80;
	bool openBinary(const std::string &p_FileName, display_utils::STLDocument &p_STLDocument);
	

	//plane 
	unsigned int planeVAO, planeVBO;
	unsigned int texture1=0;
	void initPlaneVAOVBO();
	void initTexture();

	std::vector<float> planeVertices = {
	 -2.0f,0.0f,-2.0f,0.0f,1.0f,
	  2.0f,0.0f,-2.0f,1.0f,1.0f,
	  2.0f,0.0f, 2.0f,1.0f,0.0f,
	
     -2.0f,0.0f,-2.0f,0.0f,1.0f,
	 -2.0f,0.0f, 2.0f,0.0f,0.0f,
	  2.0f,0.0f, 2.0f,1.0f,0.0f
	};
};

