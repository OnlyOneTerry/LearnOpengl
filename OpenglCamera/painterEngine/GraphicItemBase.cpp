#include "GraphicItemBase.h"


GraphicItemBase::GraphicItemBase(std::string vertexPath, std::string fragmentPath, glm::vec3 color)
{
	shader_ = new Shader(vertexPath.c_str(), fragmentPath.c_str());
	shader_->use();
	shader_->setVec3("color", color);
}

GraphicItemBase::~GraphicItemBase()
{
	if (shader_)
		delete shader_;
	shader_ = nullptr;
}


void GraphicItemBase::setVertexData(std::vector<PL::TVertex>& vertexs)
{
	vertices_ = vertexs;
}

void GraphicItemBase::setModel(std::string name, glm::mat4 model)
{
	if (shader_)
	{
		shader_->setMat4(name, model);
	}
}

void GraphicItemBase::setView(std::string name, glm::mat4 view)
{
	if (shader_)
	{
		shader_->setMat4(name, view);
	}
}

void GraphicItemBase::setProjection(std::string name, glm::mat4 projection)
{
	if (shader_)
	{
		shader_->setMat4(name, projection);
	}
}
