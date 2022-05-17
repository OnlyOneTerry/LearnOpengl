#pragma once
#include "GraphicItemBase.h"



class GraphicItemSphere :public GraphicItemBase
{
public:
	GraphicItemSphere(std::string vertexPath, std::string fragmentPath, glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f));
	~GraphicItemSphere();

	void initVAOVBO();
	void drawCall();

	void generateSphereVertices();
	void generateSphereVerticesIndex();
private:
	int y_segements_ = 50;
	int x_segements_ = 50;

};

