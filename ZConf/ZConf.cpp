#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp> 
#include <boost/filesystem.hpp> 
#include"ZConf.h"

ZConf& ZConf::getInstance()
{
	static ZConf instance;
	return instance;
}

ZConf::ZConf()
{
	ReadConf();
}

void ZConf::ReadConf()
{
	boost::property_tree::ptree pp, pSingleton, pBatch;
	if (!boost::filesystem::exists("ZConf.ini"))//查看文件是否存在
	{
		pSingleton.put("RemoteIpAddr", "10.32.31.30");
		pSingleton.put("RemotePort", "8002");
		pSingleton.put("ServerModel", "0");
		pSingleton.put("IntfNum", "1");
		pSingleton.put("KeepAlive", "1");
		pSingleton.put("KeepAliveSec", "90");
		pSingleton.put("Step", "1");
		pSingleton.put("MeterIdStart", "42051609313");
		pSingleton.put("MeterType", "10");
		pSingleton.put("SubMeterIdStart", "800000000000");
		pSingleton.put("SubMeterCnt", "0");
		pSingleton.put("SendSpeed", "500");
		pSingleton.put("AutoReport", "0");
		pSingleton.put("Time", "2020-12-15");
		pSingleton.put("TraceStreamCode", "0");
		pSingleton.put("Code", "X");

		pBatch.put("AppName", "IVYAmmeterTool.exe");
		pBatch.put("InfoRefreshTime", "10");
		pBatch.put("MaxIntfNum", "10000");

		pp.put_child("Singleton", pSingleton);
		pp.put_child("Batch", pBatch);

		boost::property_tree::write_ini("ZConf.ini", pp);
	}

	boost::property_tree::read_ini("ZConf.ini", pp);

	pSingleton = pp.get_child("Singleton");
	m_param.m_strRemoteIpAddr = pSingleton.get<std::string>("RemoteIpAddr", "10.32.31.30");
	m_param.m_nRemotePort = pSingleton.get<unsigned int>("RemotePort", 8002);
	m_param.m_bServerModel = pSingleton.get<bool>("ServerModel", false);
	m_param.m_nIntfNum = pSingleton.get<unsigned int>("IntfNum", 1);
	m_param.m_bKeepAlive = pSingleton.get<bool>("KeepAlive", true);
	m_param.m_nKeepAliveSec = pSingleton.get<unsigned int>("KeepAliveSec", 90);
	m_param.m_nStep = pSingleton.get<unsigned int>("Step", 1);
	m_param.m_strMeterIdStart = pSingleton.get<std::string>("MeterIdStart", "42051609313");
	m_param.m_nMeterType = pSingleton.get<unsigned int>("MeterType", 10);
	m_param.m_strSubMeterIdStart = pSingleton.get<std::string>("SubMeterIdStart", "800000000000");
	m_param.m_nMeterCnt = pSingleton.get<unsigned int>("SubMeterCnt", 0);
	m_param.m_nSendSpeed = pSingleton.get<unsigned int>("SendSpeed", 500);
	m_param.m_bAutoReport = pSingleton.get<bool>("AutoReport", false);
	m_param.m_strTime = pSingleton.get<std::string>("Time", "2020-12-15");
	m_param.m_bTraceStreamCode = pSingleton.get<bool>("TraceStreamCode", false);
	m_param.m_strCode = pSingleton.get<std::string>("Code", "X");
}