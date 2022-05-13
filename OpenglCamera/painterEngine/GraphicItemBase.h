#pragma once

#include <learnopengl/shader.h>
#include <vector>
#include <string>
#include "../common/commonDef.h"

class GraphicItemBase
{
public:
	GraphicItemBase(std::string vertexPath, std::string fragmentPath, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	virtual ~GraphicItemBase();
	void setVertexData(std::vector<PL::TVertex>& vertexs);
    virtual void initVAOVBO()=0;
	virtual void drawCall()=0;
	virtual void setModel(std::string name, glm::mat4 model);
	virtual void setView(std::string name, glm::mat4 view);
	virtual void setProjection(std::string name, glm::mat4 projection);
protected:
	// ≥ı ºªØVAO
    unsigned int vbo_, vao_;
	Shader* shader_;
	//std::vector<float> vertices_;
	std::vector<PL::TVertex> vertices_;
};

