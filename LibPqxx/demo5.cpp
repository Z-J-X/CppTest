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
        auto R4 = pip.insert("SELECT * FROM c_ar_meter1111");//�����ڵı�
        //pip.complete();//�ȴ�����sqlִ�����

        if (pip.is_finished(R4))//��ѯĳ����ѯ����Ƿ�ִ����ɣ�ע����ִ����ɣ����������гɹ�
            std::cout << "Success" << std::endl;

        while (!pip.empty())
        {
            //���д��������쳣���������׳�����pipΪ�ջ�����retrieve���׳��쳣"Attempt to retrieve result from empty pipeline."
            auto R = pip.retrieve();//�����ȴ�һ��ִ����ɵ�sql
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