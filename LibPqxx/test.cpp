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

        //pqxx::row R{ W.exec1(R"(SELECT * FROM c_ar_meter where meter_no = 't000000000012')") };
        std::string strMeterNo = "t000000000012";
        auto R{ W.exec_params(R"(Insert into test Values($1,$2,$3,$4))",1,"Test","1",nullptr)};

        std::cout << R.size() << std::endl;

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