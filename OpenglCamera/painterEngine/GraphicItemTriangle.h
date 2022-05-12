#pragma once
#include "GraphicItemBase.h"
class GraphicItemTriangle :public GraphicItemBase
{
public:
	GraphicItemTriangle(std::string vertexPath, std::string fragmentPath, glm::vec3 color=glm::vec3(1.0f,1.0f,1.0f));
	~GraphicItemTriangle();
	void initVAOVBO();
	void drawCall();
};

