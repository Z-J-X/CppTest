//#include <Ice/Ice.h>
//#include <Printer.h>
//using namespace std;
//using namespace Demo;
//
//class PrinterI : public Printer
//{
//public:
//    virtual void printString(string s, const Ice::Current&) override;
//};
//void PrinterI::printString(string s, const Ice::Current&)
//{
//    cout << s << endl;
//}
//
//int main(int argc, char* argv[])
//{
//    try
//    {
//        //��ʼ��ͨѶ��
//        Ice::CommunicatorHolder ich(argc, argv);
//
//        auto a =ich->getProperties();
//        
//        //��ʼ��������
//        auto adapter = ich->createObjectAdapterWithEndpoints("SimplePrinterAdapter", "ssl -p 10000");
//        //����̳еĽӿ���
//        auto servant = make_shared<PrinterI>();
//        //��������ע��̳еĽӿ���
//        adapter->add(servant, Ice::stringToIdentity("SimplePrinter"));
//        //����������
//        adapter->activate();
//        /*�ȴ�ֱ��ͨѶ���ر�
//          �˵��ý���������̣߳�ֱ��������ʵ����ֹ��
//          ������ͨ���������ر�����ʱ��������Ӧĳ���źš�
//          (���ڣ������ǲ�����Ҫ������ʱ�����ǽ�ֱ�������������ж�����)*/
//        ich->waitForShutdown();
//    }
//    catch (const std::exception& e)
//    {
//        cerr << e.what() << endl;
//        return 1;
//    }
//    return 0;
//}


#include <Ice/Ice.h>
#include <Printer.h>
#include <stdexcept>

using namespace std;
using namespace Demo;

int main(int argc, char* argv[])
{
    try
    {
        Ice::CommunicatorHolder ich(argc, argv);
        //��ʹ��һ���������󶨶���ı�ʶ����IP��ַ���˿ں�
        auto base = ich->stringToProxy("SimplePrinter:ssl -p 10000");
        //�������ȷ���Ƿ������ Printer ����������򷵻�һ�����������û���򷵻�NULL
        auto printer = Ice::checkedCast<PrinterPrx>(base);
        if (!printer)
        {
            throw std::runtime_error("Invalid proxy");
        }
        //��ʼ����
        printer->printString("Hello World!");
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
