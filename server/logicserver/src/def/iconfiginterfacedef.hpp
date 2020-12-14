#ifndef __ICONFIGINTERFACEDEF_HPP__
#define __ICONFIGINTERFACEDEF_HPP__

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "def/basedef.hpp"

#define LOAD_XML boost::property_tree::xml_parser::read_xml

typedef boost::property_tree::ptree		PTree;

const std::string  CONFIG_BASE_DIR = "./config/";

#endif // !__ICONFIGINTERFACEDEF_HPP__
