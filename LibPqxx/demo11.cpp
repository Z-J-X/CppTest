#if 0
#include <iostream>
#include <pqxx/pqxx>
#include <thread>

thread_local std::shared_ptr<pqxx::connection> ptrC = std::make_shared<pqxx::connection>("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
thread_local std::shared_ptr<pqxx::work> ptrW = std::make_shared<pqxx::work>(*ptrC);

void func()
{
    while (true)
    {
        try
        {
            if (!ptrC->is_open())
            {
                std::cout << "reconnect ..." << std::endl;
                ptrW.reset();
                ptrC = std::make_shared< pqxx::connection>("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
                ptrW = std::make_shared<pqxx::work>(*ptrC);
            }

            std::cout << std::this_thread::get_id() << ":" << ptrC->sock() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            while (true)
            {
                pqxx::result R{ ptrW->exec(R"(SELECT * FROM c_ar_meter)") };
                
                std::cout << std::this_thread::get_id() << ":" << ptrC->sock() << " ----- Found " << R.size() << std::endl;
            }
        }
        catch (pqxx::broken_connection const& e)//连接异常捕获
        {
            std::cout << "broken_connection : " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

int main()
{
    try
    {
        std::thread T1(func);
        std::thread T2(func);
        std::thread T3(func);

        T1.join();
        T2.join();
        T3.join();
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
#endif