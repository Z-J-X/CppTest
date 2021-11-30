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
//        //初始化通讯器
//        Ice::CommunicatorHolder ich(argc, argv);
//
//        auto a =ich->getProperties();
//        
//        //初始化适配器
//        auto adapter = ich->createObjectAdapterWithEndpoints("SimplePrinterAdapter", "ssl -p 10000");
//        //定义继承的接口类
//        auto servant = make_shared<PrinterI>();
//        //用适配器注册继承的接口类
//        adapter->add(servant, Ice::stringToIdentity("SimplePrinter"));
//        //启动适配器
//        adapter->activate();
//        /*等待直到通讯器关闭
//          此调用将挂起调用线程，直到服务器实现终止，
//          方法是通过调用来关闭运行时，或者响应某个信号。
//          (现在，当我们不再需要服务器时，我们将直接在命令行上中断它。)*/
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
        //出使化一个代理，并绑定对象的标识符、IP地址、端口号
        auto base = ich->stringToProxy("SimplePrinter:ssl -p 10000");
        //向服务器确认是否有这个 Printer 代理，如果有则返回一个代理对象，若没有则返回NULL
        auto printer = Ice::checkedCast<PrinterPrx>(base);
        if (!printer)
        {
            throw std::runtime_error("Invalid proxy");
        }
        //开始调用
        printer->printString("Hello World!");
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
