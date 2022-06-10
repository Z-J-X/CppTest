#include"PqxxHandle.h"
#include<thread>
#include<iostream>

thread_local std::shared_ptr<pqxx::connection> PqxxHandle::ptrConnect = nullptr;
thread_local std::shared_ptr<pqxx::work> PqxxHandle::ptrWork = nullptr;


PqxxHandle::PqxxHandle(): m_ptrWork(new boost::asio::io_service::work(m_io))
{
	
}

PqxxHandle::~PqxxHandle()
{
	for (auto ptrThread : m_vecThreads)
		ptrThread->join();
	ptrWork.reset();
	ptrConnect.reset();
}

void PqxxHandle::Init(std::string_view strUrl, int iNums)
{
    if (m_strUrl.empty())
    {
        m_strUrl = strUrl;
        for (int i = 0; i < iNums; i++)
            m_vecThreads.push_back(std::make_shared<std::thread>([this]() {
            m_io.run();
                }));
    }
}


void PqxxHandle::GetDevInfo(std::string_view strEui, std::shared_ptr<IResCb> ptrIResCb)
{
    m_io.post([=]() {
        std::shared_ptr<pqxx::result> ptrRes = nullptr;
        std::stringstream ss;
        while (true)
        {
            try
            {
                if (ptrConnect == nullptr || !ptrConnect->is_open())
                {
                    std::cout << "connect ..." << std::endl;
                    ptrWork.reset();
                    ptrConnect = std::make_shared<pqxx::connection>(m_strUrl.data());
                    ptrWork = std::make_shared<pqxx::work>(*ptrConnect);
                }

                ptrRes = std::make_shared<pqxx::result>(ptrWork->exec_params_n(1, "SELECT * FROM h_wg_iot_ns_device where device_eui = $1 limit 1", strEui.data()));                                              
                break;
            }
            catch (pqxx::broken_connection const& ec)//连接异常捕获
            {
                std::cout << "Lost connection from postgres : " << m_strUrl << ec.what() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            catch (pqxx::sql_error const& ec)//sql异常捕获
            {
                ss << "Database error: " << ec.what() << std::endl
                    << "Query was     : " << ec.query() << std::endl
                    << "sqlstate      : " << ec.sqlstate() << std::endl;
                break;
            }
            catch (std::exception const& ec)
            {
                ss << "Database error: " << ec.what() << std::endl;
                break;
            }
        }
        if (ptrIResCb != nullptr)
            ptrIResCb->res_cb(ptrRes, ss.str());
        for (auto field : ptrRes->at(0))
        {
            std::cout << field.name() << ":" << field.c_str() << std::endl;
        }
		});
}

