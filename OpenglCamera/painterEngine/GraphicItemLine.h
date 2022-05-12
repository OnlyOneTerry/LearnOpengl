#pragma once
#include "GraphicItemBase.h"

class GraphicItemLine :public GraphicItemBase
{
public:
	GraphicItemLine(std::string vertexPath, std::string fragmentPath);
	~GraphicItemLine();
	void initVAOVBO();
	void drawCall();

};

