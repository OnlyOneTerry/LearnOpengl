#include "UrdfParser.h"
#include <iostream>

UrdfParser::UrdfParser()
{

}


UrdfParser::~UrdfParser()
{

}

UrdfParser UrdfParser::getInstance()
{
	static UrdfParser urdfParse;
	return urdfParse;
}

void UrdfParser::parseUrdf(const std::string& xml_string, urdf::RobotModel& model)
{
	TiXmlDocument xml_doc;
	xml_doc.Parse(xml_string.c_str());

	if (xml_doc.Error())
	{
		std::cout << "xml_cod parse Err:" << xml_doc.ErrorDesc() << std::endl;
		return;
	}

	TiXmlElement* robot_xml = xml_doc.FirstChildElement("robot");
	if (!robot_xml)
	{
		std::cout << "robo_xml Err: could not find the 'robot' element in the xml file" << std::endl;
		return;
	}

	const char* name = robot_xml->Attribute("name");
	if (!name)
	{
		std::cout << "no name given for the robot." << std::endl;
		return;
	}
	else
	{
		std::cout << "root name is ----" << name << std::endl;
	}

	const char* version = robot_xml->Attribute("version");

	//std::cout << "version is :" << version << std::endl;
	//获取所有link
	for (TiXmlElement* link_xml = robot_xml->FirstChildElement("link"); link_xml; link_xml = link_xml->NextSiblingElement("link"))
	{
		urdf::Link link;
		parseLink(link, link_xml);
		model.link_array.push_back(link);
	}

	//获取所有joint

	for (TiXmlElement* joint_xml = robot_xml->FirstChildElement("joint"); joint_xml; joint_xml = joint_xml->NextSiblingElement("joint"))
	{
		urdf::Joint joint;
		parseJoint(joint, joint_xml);
		model.joint_array.push_back(joint);
	}
	//获取所有
	std::cout << " parese model finished....." << std::endl;
}

void UrdfParser::parseLink(urdf::Link& link, TiXmlElement* config)
{
	const char *name_char = config->Attribute("name");
	if (!name_char)
	{
		std::cout << "No name given for the link." << std::endl;
		link.name = "";
	}
	else {
		link.name = std::string(name_char);
	}

	// Inertial (optional)
	TiXmlElement *i = config->FirstChildElement("inertial");
	if (i)
	{

	}

	// Multiple Visuals (optional)
	for (TiXmlElement* vis_xml = config->FirstChildElement("visual"); vis_xml; vis_xml = vis_xml->NextSiblingElement("visual"))
	{
		urdf::Visual vis;
		if (parseVisual(vis, vis_xml))
		{
			link.visual_array.push_back(vis);
		}
		else
		{
			std::cout << "Could not parse visual element for Link " << link.name.c_str() << std::endl;
		}

	}

	// Multiple Collisions (optional)
	for (TiXmlElement* col_xml = config->FirstChildElement("collision"); col_xml; col_xml = col_xml->NextSiblingElement("collision"))
	{
		urdf::Collision col;
		if (parseCollision(col, col_xml))
		{
			link.collision_array.push_back(col);
			std::cout << "link.collision size is --------:" << link.collision_array.size() << std::endl;
		}
		else
		{
			std::cout << "Could not parse collision element for Link " << link.name.c_str() << std::endl;
		}
	}
}
bool UrdfParser::parseCollision(urdf::Collision& collision, TiXmlElement* config)
{
	//Origin
	TiXmlElement* o = config->FirstChildElement("origin");
	if (o)
	{
		if (!parseOrigin(collision.origin, o))
			return false;
	}

	//Geometry
	TiXmlElement* geom = config->FirstChildElement("geometry");
	collision.geometry = parseGeometry(geom);

	// Material
	TiXmlElement *mat = config->FirstChildElement("material");
	if (mat) {
		//get material name
		if (!mat->Attribute("name")) {
			std::cout << "Collision material must contain a name attribute";
		}

		if (!parseMaterial(collision.material, mat))
		{
			std::cout << "Collision material must contain a name attribute";
			return false;
		}
	}
}
bool UrdfParser::parseVisual(urdf::Visual& vis, TiXmlElement * config)
{
	//Origin
	TiXmlElement* o = config->FirstChildElement("origin");
	if (o)
	{
		if (!parseOrigin(vis.origin, o))
		{

		}
		//return false;
	}

	//Geometry
	TiXmlElement* geom = config->FirstChildElement("geometry");
	vis.geometry = parseGeometry(geom);

	// Material
	TiXmlElement *mat = config->FirstChildElement("material");
	if (mat) {
		//get material name
		if (!mat->Attribute("name")) {
			//std::cout << "Visual material must contain a name attribute";
		}

		if (!parseMaterial(vis.material, mat))
		{
			//std::cout << "Visual material must contain a name attribute";
			//return false;
		}
	}
	return true;
}
bool UrdfParser::parseMaterial(urdf::Material&material, TiXmlElement * config)
{
	bool has_rgb = false;
	bool has_filename = false;


	if (!config->Attribute("name"))
	{
		std::cout << "Material has no name attribute" << std::endl;
		//return false;
	}

	material.name = config->Attribute("name");

	// texture
	TiXmlElement *t = config->FirstChildElement("texture");
	if (t)
	{
		if (t->Attribute("filename"))
		{
			material.texture_filename = t->Attribute("filename");
			has_filename = true;
		}
	}

	// color
	TiXmlElement *c = config->FirstChildElement("color");
	if (c)
	{
		if (c->Attribute("rgba")) {

			material.color = c->Attribute("rgba");
		}
	}

	if (!has_rgb && !has_filename) {

		//return false;
	}
	return true;
}
urdf::Geometry UrdfParser::parseGeometry(TiXmlElement* g)
{
	urdf::Geometry geom;
	if (!g) return geom;

	TiXmlElement *shape = g->FirstChildElement();
	if (!shape)
	{
		std::cout << "Geometry tag contains no child element." << std::endl;
		return geom;
	}

	std::string type_name = shape->Value();
	if (type_name == "sphere")
	{/*
		Sphere *s = new Sphere();
		geom.reset(s);
		if (parseSphere(*s, shape))
			return geom;*/
	}
	else if (type_name == "box")
	{
		/*Box *b = new Box();
		geom.reset(b);
		if (parseBox(*b, shape))
			return geom;*/
	}
	else if (type_name == "cylinder")
	{
		/*Cylinder *c = new Cylinder();
		geom.reset(c);
		if (parseCylinder(*c, shape))
			return geom;*/
	}
	else if (type_name == "mesh")
	{
		urdf::Mesh mesh;
		if (parseMesh(mesh, shape))
		{
			geom.mesh = mesh;
		}
		return geom;
	}
	else
	{
		std::cout << "Unknown geometry type '%s'", type_name.c_str();
		return geom;
	}
}
bool UrdfParser::parseMesh(urdf::Mesh& mesh, TiXmlElement* m)
{
	if (!m->Attribute("filename")) {
		std::cout << "Mesh must contain a filename attribute" << std::endl;
		//return false;
	}
	else {
		mesh.filename = m->Attribute("filename");
		std::cout<< "Mesh  filename -------"<< mesh.filename.c_str() << std::endl;
	}
	return true;
}
bool UrdfParser::parseOrigin(urdf::Origin& origin, TiXmlElement* xml)
{
	if (xml)
	{
		const char* xyz_str = xml->Attribute("xyz");
		if (xyz_str != NULL)
		{
			origin.xyz_str = xyz_str;
		}

		const char* rpy_str = xml->Attribute("rpy");
		if (rpy_str != NULL)
		{
			origin.rotation_str = rpy_str;
		}
	}
	else {
		std::cout << "xml is null" << std::endl;
		return false;
	}

	return true;
}

bool UrdfParser::parseJoint(urdf::Joint& joint, TiXmlElement* config)
{
	const char* name_char = config->Attribute("name");
	if (!name_char)
	{
		joint.name = "";
	}
	else {
		joint.name = std::string(name_char);
	}

	//get origin
	TiXmlElement* origin_xml = config->FirstChildElement("origin");
	if (!origin_xml)
	{
		std::cout << "no origin" << std::endl;
	}
	else
	{
		if (!parseOrigin(joint.origin, origin_xml))
		{
			std::cout << "failed to parse joint origin " << std::endl;
			return false;
		}
	}

	//get Parent link
	TiXmlElement* parent_xml = config->FirstChildElement("parent");
	if (parent_xml)
	{
		const char* pname = parent_xml->Attribute("link");
		if (!pname)
		{
			std::cout << "no parent link name specified for joint link" << joint.name.c_str() << std::endl;
		}
		else
		{
			joint.parent_link_name = parent_xml->Attribute("link");
		}
	}
	else
	{
		std::cout << "no parent specified for joint link" << joint.name.c_str() << std::endl;
	}

	//get Child link
	TiXmlElement* child_xml = config->FirstChildElement("child");
	if (child_xml)
	{
		const char* cname = child_xml->Attribute("link");
		if (!cname)
		{
			std::cout << "no child link name specified for joint link" << joint.name.c_str() << std::endl;
		}
		else
		{
			joint.child_link_name = child_xml->Attribute("link");
		}
	}
	else
	{
		std::cout << "no child specified for joint link" << joint.name.c_str() << std::endl;
	}

	// Get Joint type
	const char* type_char = config->Attribute("type");
	if (!type_char)
	{
		std::cout << "joint "<< joint.name.c_str() << " has no type, check to see if it's a reference.";
		return false;
	}

	std::string type_str = type_char;
	if (type_str == "planar")
		joint.type = urdf::JointType::PLANAR;
	else if (type_str == "floating")
		joint.type = urdf::JointType::FLOATING;
	else if (type_str == "revolute")
		joint.type = urdf::JointType::REVOLUTE;
	else if (type_str == "continuous")
		joint.type = urdf::JointType::CONTINUOUS;
	else if (type_str == "prismatic")
		joint.type = urdf::JointType::PRISMATIC;
	else if (type_str == "fixed")
		joint.type = urdf::JointType::FIXED;
	else
	{
		std::cout<< "joint"<< joint.name.c_str() << "Joint [%s] has no known type [%s]";
		return false;
	}

	//get joint Axis
	if (joint.type != urdf::JointType::FLOATING && joint.type != urdf::JointType::FIXED)
	{
		// axis
		TiXmlElement *axis_xml = config->FirstChildElement("axis");
		if (!axis_xml) {
			std::cout << " no axis elemement for Joint link " << joint.name.c_str() << ", defaulting to (1,0,0) axis";
			joint.axis = std::string("1.0 0.0 0.0");
		}
		else {
			if (axis_xml->Attribute("xyz")) {
				joint.axis = axis_xml->Attribute("xyz");
			}
		}
	}

	// Get limit
	TiXmlElement *limit_xml = config->FirstChildElement("limit");
	if (limit_xml)
	{
		if (!parseJointLimits(joint.limit, limit_xml))
		{
			std::cout << "Could not parse limit element for joint" << joint.name.c_str() << std::endl; ;
			return false;
		}
	}
	else if (joint.type == urdf::JointType::REVOLUTE)
	{
		std::cout << "Joint " << joint.name.c_str() << " is of type REVOLUTE but it does not specify limits" << std::endl;
		return false;
	}
	else if (joint.type == urdf::JointType::PRISMATIC)
	{
		std::cout << "Joint" << joint.name.c_str() << " is of type PRISMATIC without limits" << std::endl;
		return false;
	}
}

bool UrdfParser::parseJointLimits(urdf::JointLimits& jl, TiXmlElement* config)
{
	// Get lower joint limit
	const char* lower_str = config->Attribute("lower");
	if (lower_str == NULL) {
		std::cout << "urdfdom.joint_limit: no lower, defaults to 0";
		jl.lower = 0;
	}
	else
	{
		try {
			jl.lower = strToDouble(lower_str);
		}
		catch (std::runtime_error &) {
			std::cout << "lower value (%s) is not a valid float" << lower_str << std::endl;
			return false;
		}
	}

	// Get upper joint limit
	const char* upper_str = config->Attribute("upper");
	if (upper_str == NULL) {
		std::cout << "urdfdom.joint_limit: no upper, , defaults to 0" << std::endl;
		jl.upper = 0;
	}
	else
	{
		try {
			jl.upper = strToDouble(upper_str);
		}
		catch (std::runtime_error &) {
			std::cout << "upper value (%s) is not a valid float" << upper_str << std::endl;
			return false;
		}
	}

	// Get joint effort limit
	const char* effort_str = config->Attribute("effort");
	if (effort_str == NULL) {
		std::cout << "joint limit: no effort" << std::endl;
		return false;
	}
	else
	{
		try {
			jl.effort = strToDouble(effort_str);
		}
		catch (std::runtime_error &) {
			std::cout << "effort value (%s) is not a valid float" << effort_str << std::endl;
			return false;
		}
	}

	// Get joint velocity limit
	const char* velocity_str = config->Attribute("velocity");
	if (velocity_str == NULL) {
		std::cout << "joint limit: no velocity" << std::endl;
		return false;
	}
	else
	{
		try {
			jl.velocity = strToDouble(velocity_str);
		}
		catch (std::runtime_error &) {
			std::cout << "velocity value (%s) is not a valid float" << velocity_str << std::endl;
			return false;
		}
	}

	return true;
}

double UrdfParser::strToDouble(std::string str)
{
  double n = atof(str.c_str());
  return n;
}
