#if 0
#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        pqxx::connection C("postgresql://ami:ami@10.32.233.138:5432/ami_empower");

        std::cout << "Connected to " << C.dbname() << '\n';
        pqxx::work W{ C };
        {
            //根据lambda参数自动 转换类型
            W.for_each("SELECT meter_id,meter_no FROM c_ar_meter", [](int dept_id, std::string_view name) {
                std::cout << name << " : " << dept_id << std::endl;
                });
        }
        std::cout << "-------------------------------------------------------------\n" << std::endl;
        {
            pqxx::result R{ W.exec(R"(SELECT meter_id,meter_no FROM c_ar_meter)") };
            //根据lambda参数自动 转换类型
            R.for_each([](int dept_id, std::string_view name) {
                std::cout << name << " : " << dept_id << std::endl;
                });
        }
        std::cout << "-------------------------------------------------------------\n" << std::endl;
        {
            pqxx::row r = W.exec1("SELECT 1, 2, 'Hello'");
            auto [one, two, hello] = r.as<int, int, std::string>();
            std::cout << (one + two) << ' ' << hello.length() << std::endl;
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