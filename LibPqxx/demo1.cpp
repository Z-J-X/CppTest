#if 0
#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        // Connect to the database.
        //postgresql://�û���:����@��ַ/���ݿ�����
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
            strMeterNo = row[1].as<std::string>(strMeterNo);//�����ʼֵ�������Ϊ���򷵻�ֵΪ�������ĳ�ʼֵ
            strMeterId = row["meter_id"].as<std::string>(strMeterId);//���ݿ���ʵ����number���ͣ����ǿ���ת��Ϊstring
            //txt = row[1].as<std::string>();//�������ʼֵ����Ϊ�������쳣
            //std::cout << row[1].c_str() << std::endl;//��ѯ��������ֵ��Ĭ��Ϊstring,���Կ���ֱ��Ĭ����ʽ���
            std::cout << strMeterId << ":" << strMeterNo << std::endl;
        }

        // Perform a query and check that it returns no result.
        //���ڲ���Ҫ���ؽ������ʹ��exec0
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