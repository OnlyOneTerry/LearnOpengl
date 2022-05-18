#pragma once
#include "GraphicItemBase.h"

class GraphicItemLine :public GraphicItemBase
{
public:
	GraphicItemLine(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color=glm::vec3(0.0f,0.0f,1.0f));
	~GraphicItemLine();
	void initVAOVBO();
	void drawCall();

};

