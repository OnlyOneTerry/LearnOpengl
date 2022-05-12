#pragma once

#include <learnopengl/shader.h>
#include <vector>
#include <string>

class GraphicItemBase
{
public:
	GraphicItemBase(std::string vertexPath,std::string fragmentPath);
	virtual ~GraphicItemBase();
	void setVertexData(std::vector<float>& vertexs);
    virtual void initVAOVBO();
	virtual void drawCall();
	virtual void setModel(std::string name, glm::mat4 model);
	virtual void setView(std::string name, glm::mat4 view);
	virtual void setProjection(std::string name, glm::mat4 projection);
protected:
	// ≥ı ºªØVAO
    unsigned int _VBO, _VAO;
	Shader* _shader;
	std::vector<float> _vertices;
};

