#pragma once
#include "GraphicModel.h"
#include "GraphicItemStl.h"
#include "../common/urdfDef.h"
#include "../urdfParse/UrdfParser.h"
#include <vector>
#include <map>
#include <stack>

class GraphicUrdfModel :public GraphicModel
{
public:
	GraphicUrdfModel(display_utils::ModelType mType);
	~GraphicUrdfModel();

	void loadModel(std::string filePath, std::string vsPath, std::string fsPath);

	void stringSplit(const std::string& str, const std::string& splits, std::vector<std::string>& res);

	void getColorAndAphaFromString(std::string clrStr, glm::vec3& color, float& alpha);
	void getVec3FromString(std::string clrStr, glm::vec3& value);

	std::string readFileIntoString(char* filename);

	urdf::TFTreeNodeData* createTFTree();
	void createTreeNodes();
	void calcTransformMatrix(glm::mat4& model, glm::vec3 rpy, glm::vec3 coor, glm::vec3 position);
	void getNodeMatrix(glm::mat4& model, std::stack<urdf::TFTreeNodeData*> stack);
	std::vector<GraphicItemBase*>& getStlVec();
	void setPackageDir(std::string dir);
	bool getPathNodesByKey(urdf::TFTreeNodeData* node, std::string targetName, std::stack<urdf::TFTreeNodeData*>& stack);
private:
	urdf::RobotModel model_;
	std::vector<GraphicItemBase*> stl_vec_;
	std::map< GraphicItemBase*, std::string> stl_name_map_;
	glm::vec3 baseCoordinate_ = { 1.0f,1.0f,1.0f };//基座坐标系；
	std::vector<std::string> link_name_vec_;//记录已经创建的节点名称
	std::vector<urdf::TFTreeNodeData*> node_vec_;//tf树节点
	std::string package_dir_;
};
