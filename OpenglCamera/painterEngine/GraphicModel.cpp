#include "GraphicModel.h"

GraphicModel::GraphicModel(display_utils::ModelType mType)
{
	model_type_ = mType;
}

GraphicModel::~GraphicModel()
{

}

display_utils::ModelType GraphicModel::getModelType()
{
	return model_type_;
}




