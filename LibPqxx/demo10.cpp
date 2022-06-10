#if 0
#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/except>
#include <thread>

int run(std::shared_ptr<pqxx::connection>& ptrC, std::shared_ptr<pqxx::work>& ptrW)
{
    while (true)
    {
        try
        {
            if (!ptrC->is_open())
            {
                ptrW.reset();
                std::cout << "reconnect ..." << std::endl;
                //在同一生命周期内创建两个对象，先构造A，然后构造B，析构时会先析构B再析构A.
                //在创建work时必须先要有connection，释放时先释放work,他会取消与conn的绑定，若先释放conn的话，work释放时会去访问以释放的conn发生未定义行为
                ptrC = std::make_shared< pqxx::connection>("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
                ptrW = std::make_shared<pqxx::work>(*ptrC);
            }
            
            ptrW->exec("SELECT * FROM c_ar_meter");
            std::cout << "exec ok" << std::endl;
            break;
        }
        catch (pqxx::broken_connection const& e)//连接异常捕获
        {
            std::cout << "broken_connection : " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    try
    {
        auto ptrC = std::make_shared< pqxx::connection>("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
        auto ptrW = std::make_shared<pqxx::work>(*ptrC);
        while (true)
        {
            run(ptrC, ptrW);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (pqxx::sql_error const& e)//sql异常捕获
    {
        std::cerr
            << "Database error: " << e.what() << std::endl
            << "Query was     : " << e.query() << std::endl
            << "sqlstate      : " << e.sqlstate() << std::endl;
        return 2;
    }
    catch (std::exception const& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;

        return 1;
    }
}

#endif