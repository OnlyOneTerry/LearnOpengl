#pragma once
#include "GraphicItemBase.h"
#include"../common/urdfDef.h"
const int STL_LABEL_SIZE = 80;
class GraphicItemStl :public GraphicItemBase
{
public:
	GraphicItemStl(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f));
	~GraphicItemStl();
	void initVAOVBO();
	void drawCall();
	void setStlFilePath(std::string path);
	//解析stl模型数据
	bool openBinary(const std::string &p_FileName, urdf::STLDocument &p_STLDocument);
private:
	std::string file_path_;//stl模型路径
};

