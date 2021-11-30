#include "ZConf.h"
#include <iostream>
int main()
{
	ZConf& c = ZConf::getInstance();
	std::cout << c.m_param.m_strMeterIdStart << std::endl;
	return 0;
}