#pragma once
#include "GraphicItemBase.h"

class GraphicItemCircle :public GraphicItemBase
{
public:
	GraphicItemCircle(std::string vertexPath, std::string fragmentPath, glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f));
	~GraphicItemCircle();
	void initVAOVBO();
	void drawCall();
	void setOrgin(glm::vec3 origin);
	//圆上的点
	std::vector<PL::TVertex> getUnitCircleVertices();
	void buildCircleFaceVertices(std::vector<PL::TVertex>& vertices);

private:
    int   sector_count_ = 72;
    float pier_radius_ = 1.0f;
    float pier_height_ = 0.3f;
	glm::vec3 pier_origin_ = glm::vec3(0.0f,0.0f,0.0f);//圆心
	glm::vec3 pier_rotate_axis_ = glm::vec3(1.0f,0.0f,0.0f);//旋转轴
	float rotate_angle = 90.0f;
};

