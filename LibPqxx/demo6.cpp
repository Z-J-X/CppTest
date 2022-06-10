#if 0
#include <iostream>
#include <pqxx/pqxx>
#include <thread>
class SpendTime
{
public:
    SpendTime() :_curTimePoint(std::chrono::steady_clock::now())
    {
    }

    ~SpendTime() {
        auto curTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - _curTimePoint);
        std::cout << "SpendTime = " << duration.count() << "ms" << std::endl;
    }

private:
    std::chrono::steady_clock::time_point _curTimePoint;
};

void Test1(pqxx::connection& C)
{
    SpendTime tt;
    pqxx::work W{ C };
    pqxx::pipeline pip(W);
    pip.retain(20);
    auto R1 = pip.insert("SELECT meter_id,meter_no FROM c_ar_meter");
    auto R2 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R3 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R4 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R5 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R6 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R7 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R8 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R9 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R10 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R11 = pip.insert("SELECT meter_id,meter_no FROM c_ar_meter");
    auto R12 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R13 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R14 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R15 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R16 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R17 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R18 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R19 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");

    pip.complete();
    while (!pip.empty())
    {
        auto R = pip.retrieve();
        //std::cout << R.first << std::endl;
        pqxx::result r = R.second;
    }

}

void Test2(pqxx::connection& C)
{
    SpendTime tt;
    pqxx::work W{ C };
    pqxx::pipeline pip(W);
    pip.retain(20);
    auto R1 = pip.insert("SELECT meter_id,meter_no FROM c_ar_meter");
    auto R2 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R3 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R4 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R5 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R6 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R7 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R8 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R9 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R10 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R11 = pip.insert("SELECT meter_id,meter_no FROM c_ar_meter");
    auto R12 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R13 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R14 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R15 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R16 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R17 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R18 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");
    auto R19 = pip.insert("SELECT * FROM m_wg_data_lp_collected_his");

    while (!pip.empty())
    {
        auto R = pip.retrieve();
        //std::cout << R.first << std::endl;
        pqxx::result r = R.second;
    }
}

void Test3(pqxx::connection& C)
{
    SpendTime tt;
    // Start a transaction.
    pqxx::work W{ C };

    // Perform a query and retrieve all results.
    pqxx::result R1{ W.exec("SELECT meter_id,meter_no FROM c_ar_meter") };
    pqxx::result R2{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R3{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R4{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R5{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R6{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R7{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R8{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R9{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R10{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R11{ W.exec("SELECT meter_id,meter_no FROM c_ar_meter") };
    pqxx::result R12{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R13{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R14{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R15{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R16{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R17{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R18{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
    pqxx::result R19{ W.exec(R"(SELECT * FROM m_wg_data_lp_collected_his)") };
}

int main()
{
    try
    {
        pqxx::connection C("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
        Test1(C);
        Test2(C);
        Test3(C);
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}

#endif