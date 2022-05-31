#pragma once
#include "../common/commonDef.h"

class GraphicModel
{
public:
	GraphicModel(display_utils::ModelType mType);
	~GraphicModel();
	virtual void loadModel(const std::string filePath, std::string vsPath, std::string fsPath)=0;
	display_utils::ModelType getModelType();
protected:
	display_utils::ModelType model_type_ = display_utils::ModelType::MODEL_NONE;
};

