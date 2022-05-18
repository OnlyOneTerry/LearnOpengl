#pragma once
#include "GraphicItemBase.h"
class GraphicItemBezier :public GraphicItemBase
{
public:
	struct point
	{
		float x;
		float y;
	};
public:
	GraphicItemBezier(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f));
	~GraphicItemBezier();

	void lerp(point& dest, const point& a, const point& b, const float t);

	void initVAOVBO();

	void drawCall();

	void bezier(point &dest, const point& a, const point& b, const point& c, const point& d, const float t);

	int genearteBezier();
private:
	std::vector<point> bezierPoints_;

};

