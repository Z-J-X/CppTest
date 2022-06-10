#if 0
#include <boost/asio.hpp> 
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <thread>

class Demo
{
public:
    Demo() :st(io) 
    {
        st.expires_after(std::chrono::seconds(5));
        st.async_wait(std::bind(&Demo::checkDeadline, this));
    }
    ~Demo()
    {
        ptrTh->join();
    }
    void checkDeadline() //���캯��ִ����ɺ�ÿ��ִ��setTime�����뵽���������
    {
        if (st.expiry() <= boost::asio::steady_timer::clock_type::now())//�жϵ�ǰʱ���Ƿ񵽴����ʱ��㣬���������ִ����Ӧ�Ķ�ʱ����
        {
            std::cout << "Test" << std::endl;                           //do something
            st.expires_at(boost::asio::steady_timer::time_point::max());//������ɣ�������ʱ������ʱ����Ϊ���޴��Ա��´μ���ִ��
        }
        st.async_wait(std::bind(&Demo::checkDeadline, this));           //������ʱ����Ŀ����Ϊ���ⲿֻ��Ҫ����setTime�����ݹ��߼���
    }
    void setTime(int x)
    {
        st.expires_after(std::chrono::seconds(x));
    }
    void run()
    {
        ptrTh = std::make_shared<std::thread>([this]() {
            io.run();
            });
    }
private:
    boost::asio::io_context io;
    boost::asio::steady_timer st;
    std::shared_ptr<std::thread> ptrTh;
};

int main()
{
    Demo test;
    test.run();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    test.setTime(5);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    test.setTime(5);
    std::cout << "set ok" << std::endl;
}
#endif