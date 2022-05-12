#pragma once
#include "GraphicItemBase.h"
class GraphicItemCube : public GraphicItemBase
{
public:
	GraphicItemCube(std::string vertexPath, std::string fragmentPath);
	~GraphicItemCube();

	void initVAOVBO();
	void drawCall();
};

