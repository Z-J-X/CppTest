#if 0
#include <iostream>
#include <pqxx/pqxx>
#include <thread>

int main()
{
    try
    {
        pqxx::connection C("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
        pqxx::work W{ C };
        pqxx::pipeline pip(W);
        pip.retain(20);
        auto R1 = pip.insert("SELECT meter_id,meter_no FROM c_ar_meter");
        auto R2 = pip.insert("SELECT * FROM Test");
        auto R3 = pip.insert("SELECT * FROM c_ar_meter");
        auto R4 = pip.insert("SELECT * FROM c_ar_meter1111");//不存在的表
        //pip.complete();//等待所有sql执行完成

        if (pip.is_finished(R4))//查询某个查询语句是否执行完成，注意是执行完成，并不是运行成功
            std::cout << "Success" << std::endl;

        while (!pip.empty())
        {
            //所有处理结果的异常会在这里抛出，当pip为空还继续retrieve会抛出异常"Attempt to retrieve result from empty pipeline."
            auto R = pip.retrieve();//阻塞等待一个执行完成的sql
            std::cout << R.first << std::endl;
            pqxx::result r = R.second;
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}

#endif