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
            return false;//������ɣ�����Ҫ�����¼�ȥ����
        }

        //���ڿ���ע�����Զ���ص��࣬
        //���Ե�����trueʱ�����֪ͨ�����࣬
        //������false�򲻻�֪ͨ�����࣬
        //������ⷵ��flase��ʾ�ڴ˻ص����Ѿ��������쳣��
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
        std::this_thread::sleep_for(std::chrono::seconds(10));//���ݿ� down
        pqxx::result R{ W.exec(R"(SELECT * FROM c_ar_meter)") };
    }
    catch (pqxx::sql_error const& e)//sql�쳣����
    {
        std::cerr
            << "Database error: " << e.what() << std::endl
            << "Query was     : " << e.query() << std::endl
            << "sqlstate      : " << e.sqlstate() << std::endl;
        return 3;
    }
    catch (pqxx::broken_connection const& e)//�����쳣����
    {
        std::cout << "broken_connection : " << e.what() << std::endl;
        return 2;
    }
    catch (std::exception const& e)//�����쳣
    {
        std::cerr << "std::exception: " << e.what() << std::endl;

        return 1;
    }
}
#endif