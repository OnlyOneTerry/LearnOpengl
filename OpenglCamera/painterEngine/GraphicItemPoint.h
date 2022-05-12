#pragma once
#include "GraphicItemBase.h"

class GraphicItemPoint :public GraphicItemBase
{
public:
	GraphicItemPoint(std::string vertexPath, std::string fragmentPath);
	~GraphicItemPoint();

	void initVAOVBO();
	void drawCall();

};

