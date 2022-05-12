#include "GraphicItemBase.h"


GraphicItemBase::GraphicItemBase(std::string vertexPath, std::string fragmentPath)
{
	_shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
}

GraphicItemBase::~GraphicItemBase()
{

}

void GraphicItemBase::initVAOVBO()
{

}

void GraphicItemBase::drawCall()
{

}

void GraphicItemBase::setVertexData(std::vector<float>& vertexs)
{
	_vertices = vertexs;
}

void GraphicItemBase::setModel(std::string name, glm::mat4 model)
{
	if (_shader)
	{
		_shader->setMat4(name, model);
	}
}

void GraphicItemBase::setView(std::string name, glm::mat4 view)
{
	if (_shader)
	{
		_shader->setMat4(name, view);
	}
}

void GraphicItemBase::setProjection(std::string name, glm::mat4 projection)
{
	if (_shader)
	{
		_shader->setMat4(name, projection);
	}
}
