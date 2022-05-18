#pragma once
#include "GraphicItemBase.h"

class GraphicItemBezier :public GraphicItemBase
{
public:

public:
	GraphicItemBezier(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f));
	~GraphicItemBezier();

	void lerp(display_utils::Point2& dest, const display_utils::Point2& a, const display_utils::Point2& b, const float t);

	void initVAOVBO();

	void drawCall();

	void bezier(display_utils::Point2 &dest, const display_utils::Point2& a, const display_utils::Point2& b, const display_utils::Point2& c, const display_utils::Point2& d, const float t);

	void genearteBezier();

	void setControlPoints(std::vector<display_utils::Point2>& controlPoints);
private:
	std::vector<display_utils::Point2> bezierPoints_;

	std::vector<display_utils::Point2> controlPoints_;

};

