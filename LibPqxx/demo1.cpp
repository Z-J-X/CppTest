#if 0
#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        // Connect to the database.
        //postgresql://用户名:密码@地址/数据库名称
        pqxx::connection C("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
        std::cout << "Connected to " << C.dbname() << '\n';
        // Start a transaction.
        pqxx::work W{ C };

        // Perform a query and retrieve all results.
        pqxx::result R{ W.exec(R"(SELECT * FROM c_ar_meter)") };

        // Iterate over results.
        std::cout << "Found " << R.size() << " employees:\n";
        for (auto row : R)
        {
            std::string strMeterNo,strMeterId;
            strMeterNo = row[1].as<std::string>(strMeterNo);//传入初始值，若结果为空则返回值为这个传入的初始值
            strMeterId = row["meter_id"].as<std::string>(strMeterId);//数据库中实际是number类型，但是可以转换为string
            //txt = row[1].as<std::string>();//不传入初始值，若为空则抛异常
            //std::cout << row[1].c_str() << std::endl;//查询出的所有值都默认为string,所以可以直以默认形式输出
            std::cout << strMeterId << ":" << strMeterNo << std::endl;
        }

        // Perform a query and check that it returns no result.
        //由于不需要返回结果所以使用exec0
        W.exec0("UPDATE c_ar_meter SET asset_no = meter_no where meter_no = 't000000000012'");

        W.commit();
        std::cout << "OK.\n";
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
#endif