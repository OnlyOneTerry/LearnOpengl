#pragma once
#include "GraphicItemBase.h"
class GraphicItemCube : public GraphicItemBase
{
public:
	GraphicItemCube(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color=glm::vec3(1.0f, 0.5f, 0.2f));
	~GraphicItemCube();

	void initVAOVBO();
	void drawCall();
};

