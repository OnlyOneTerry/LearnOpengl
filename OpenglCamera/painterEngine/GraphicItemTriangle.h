#pragma once
#include "GraphicItemBase.h"
class GraphicItemTriangle :public GraphicItemBase
{
public:
	GraphicItemTriangle(std::string vertexPath, std::string fragmentPath);
	~GraphicItemTriangle();
	void initVAOVBO();
	void drawCall();
};

