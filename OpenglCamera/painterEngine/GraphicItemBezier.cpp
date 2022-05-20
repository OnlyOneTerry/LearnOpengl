#include "GraphicItemBezier.h"
#include <GLFW/glfw3.h>

GraphicItemBezier::GraphicItemBezier(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath,fragmentPath,color)
{

}

GraphicItemBezier::~GraphicItemBezier()
{

}

void GraphicItemBezier::lerp(display_utils::Point2 & dest, const display_utils::Point2 & a, const display_utils::Point2 & b, const float t)
{
	dest.x = a.x + (b.x - a.x)*t;
	dest.y = a.y + (b.y - a.y)*t;
}


void GraphicItemBezier::initVAOVBO()
{
	genearteBezier();
	if (float_vertices_.size() < 1) return;
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	glBufferData(GL_ARRAY_BUFFER, float_vertices_.size() * sizeof(float), &float_vertices_[0], GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void GraphicItemBezier::drawCall()
{
    glm::vec3 color = glm::vec3(sin(glfwGetTime()),cos(glfwGetTime()),1.0f);
	shader_->setVec3("color", color);
	glBindVertexArray(vao_);
	int num = float_vertices_.size() / 3;
	glPointSize(3);
	//glDrawArrays(GL_LINES, 0, num);
	glDrawArrays(GL_POINTS, 0, num);
}

void GraphicItemBezier::bezier(display_utils::Point2 &dest, const display_utils::Point2& a, const display_utils::Point2& b, const display_utils::Point2& c, const display_utils::Point2& d, const float t)
{
	display_utils::Point2 ab, bc, cd, abbc, bccd;
	lerp(ab, a, b, t);           // point between a and b (green)
	lerp(bc, b, c, t);           // point between b and c (green)
	lerp(cd, c, d, t);           // point between c and d (green)
	lerp(abbc, ab, bc, t);       // point between ab and bc (blue)
	lerp(bccd, bc, cd, t);       // point between bc and cd (blue)
	lerp(dest, abbc, bccd, t);   // point on the bezier-curve (black)
}

void GraphicItemBezier::genearteBezier()
{
	//display_utils::Point2 a = { -2, 0 };
	//display_utils::Point2 b = { -2, 2 };
	//display_utils::Point2 c = { 2, 2 };
	//display_utils::Point2 d = { 3, -2 };	


	for (int i = 0; i < 100; ++i)
	{
		display_utils::Point2 p;
		float t = static_cast<float>(i) / 99.0;
		//bezier(p, a, b, c, d, t);
		if (controlPoints_.size() == 4)
		{
			bezier(p, controlPoints_[0], controlPoints_[1], controlPoints_[2], controlPoints_[3], t);
		}
		else
		{
			return;
		}
		printf("%f %f\n", p.x, p.y);
		bezierPoints_.push_back(p);
	}

	for (int i = 0; i < bezierPoints_.size(); i++)
	{
		display_utils::Point2 p = bezierPoints_[i];

		float_vertices_.push_back(p.x);
		float_vertices_.push_back(p.y);
		float_vertices_.push_back(0.0f);

		if (i < bezierPoints_.size() - 1)
		{
			display_utils::Point2 pNext = bezierPoints_[i + 1];
			float_vertices_.push_back(pNext.x);
			float_vertices_.push_back(pNext.y);
			float_vertices_.push_back(0.0f);
		}

	}
}

void GraphicItemBezier::setControlPoints(std::vector<display_utils::Point2>& controlPoints)
{
	controlPoints_ = controlPoints;
}
