#pragma once
#include "GraphicItemBase.h"

class GraphicItemPoint :public GraphicItemBase
{
public:
	GraphicItemPoint(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color=glm::vec3(1.0f,1.0f,0.0f));
	~GraphicItemPoint();

	void initVAOVBO();
	void drawCall();

};

