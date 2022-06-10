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
        //pqxx::stream_from::query() or pqxx::stream_from::raw_table()/pqxx::stream_from::table() create
        auto stream = pqxx::stream_from::query(W, "SELECT meter_id,meter_no FROM c_ar_meter");
        //auto stream = pqxx::stream_from::raw_table(W,"c_ar_meter", "meter_id,meter_no");
        std::tuple< std::string, std::string> row;
        while (stream >> row)
            std::cout << std::get<0>(row) << ":" << std::get<1>(row) << std::endl;//流式处理
        stream.complete();
        W.commit();
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}

#endif