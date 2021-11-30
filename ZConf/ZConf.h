#pragma once
#include<boost/noncopyable.hpp>
#include<string>
struct ZParam
{
	//Singleton
	std::string m_strRemoteIpAddr;
	std::string m_strMeterIdStart;
	std::string m_strSubMeterIdStart;
	std::string m_strTime;
	std::string m_strCode;

	unsigned int m_nRemotePort;
	unsigned int m_nIntfNum;
	unsigned int m_nKeepAliveSec;
	unsigned int m_nStep;
	unsigned int m_nMeterType;
	unsigned int m_nMeterCnt;
	unsigned int m_nSendSpeed;
	
	bool m_bServerModel;
	bool m_bKeepAlive;
	bool m_bAutoReport;
	bool m_bTraceStreamCode;

	//Batch
	/*std::string b_strAppName;
	unsigned int b_nInfoRefreshTime;
	unsigned int b_nMaxIntfNum;*/

	//Business
};
class ZConf :boost::noncopyable
{
public:
	static ZConf& getInstance();
	void ReadConf();
private:
	ZConf();
public:
	ZParam m_param;
};