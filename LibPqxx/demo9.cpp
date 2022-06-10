#if 0
#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/except>
#include <thread>

class eventCb : public pqxx::errorhandler
{
public:
    eventCb(pqxx::connection& C) :errorhandler(C), m_C(C)
    {
    }

    bool operator()(char const msg[]) noexcept
    {
        std::cout << "eventCb:" << std::string(msg) << std::endl;
        if (!m_C.is_open())
        {
            //Do something
            return false;//处理完成，不需要其他事件去处理
        }

        //由于可以注册多个自定义回调类，
        //所以当返回true时会继续通知其他类，
        //若返回false则不会通知其他类，
        //个人理解返回flase表示在此回调中已经处理完异常。
        return true;
    }
public:
    pqxx::connection& m_C;
};

int main(int argc, char* argv[])
{
    try
    {
        pqxx::connection C("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
        eventCb eCb(C);
        pqxx::work W{ C };
        std::this_thread::sleep_for(std::chrono::seconds(10));//数据库 down
        pqxx::result R{ W.exec(R"(SELECT * FROM c_ar_meter)") };
    }
    catch (pqxx::sql_error const& e)//sql异常捕获
    {
        std::cerr
            << "Database error: " << e.what() << std::endl
            << "Query was     : " << e.query() << std::endl
            << "sqlstate      : " << e.sqlstate() << std::endl;
        return 3;
    }
    catch (pqxx::broken_connection const& e)//连接异常捕获
    {
        std::cout << "broken_connection : " << e.what() << std::endl;
        return 2;
    }
    catch (std::exception const& e)//其他异常
    {
        std::cerr << "std::exception: " << e.what() << std::endl;

        return 1;
    }
}
#endif