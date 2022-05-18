#include "GraphicItemBezier.h"

GraphicItemBezier::GraphicItemBezier(std::string& vertexPath, std::string& fragmentPath, glm::vec3 color)
	:GraphicItemBase(vertexPath,fragmentPath,color)
{

}

GraphicItemBezier::~GraphicItemBezier()
{

}

void GraphicItemBezier::lerp(point & dest, const point & a, const point & b, const float t)
{
	dest.x = a.x + (b.x - a.x)*t;
	dest.y = a.y + (b.y - a.y)*t;
}


void GraphicItemBezier::initVAOVBO()
{
	genearteBezier();

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
	glBindVertexArray(vao_);
	glDrawArrays(GL_LINES, 0, float_vertices_.size());
}

void GraphicItemBezier::bezier(point &dest, const point& a, const point& b, const point& c, const point& d, const float t)
{
	point ab, bc, cd, abbc, bccd;
	lerp(ab, a, b, t);           // point between a and b (green)
	lerp(bc, b, c, t);           // point between b and c (green)
	lerp(cd, c, d, t);           // point between c and d (green)
	lerp(abbc, ab, bc, t);       // point between ab and bc (blue)
	lerp(bccd, bc, cd, t);       // point between bc and cd (blue)
	lerp(dest, abbc, bccd, t);   // point on the bezier-curve (black)
}

int GraphicItemBezier::genearteBezier()
{
	point a = { -2, 0 };
	point b = { -2, 2 };
	point c = { 2, 2 };
	point d = { 3, -2 };

	for (int i = 0; i < 100; ++i)
	{
		point p;
		float t = static_cast<float>(i) / 99.0;
		bezier(p, a, b, c, d, t);
		printf("%f %f\n", p.x, p.y);
		bezierPoints_.push_back(p);
	}

	for (int i = 0; i < bezierPoints_.size(); i++)
	{
		point p = bezierPoints_[i];

		float_vertices_.push_back(p.x);
		float_vertices_.push_back(p.y);
		float_vertices_.push_back(-1.0f);

		if (i < bezierPoints_.size() - 1)
		{
			point pNext = bezierPoints_[i + 1];
			float_vertices_.push_back(pNext.x);
			float_vertices_.push_back(pNext.y);
			float_vertices_.push_back(-1.0f);
		}

	}
	return 0;
}