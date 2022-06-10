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
    void checkDeadline() //构造函数执行完成后每次执行setTime则会进入到这个函数中
    {
        if (st.expiry() <= boost::asio::steady_timer::clock_type::now())//判断当前时间是否到达过期时间点，如果到达则执行相应的定时任务
        {
            std::cout << "Test" << std::endl;                           //do something
            st.expires_at(boost::asio::steady_timer::time_point::max());//任务完成，新增计时，将计时设置为无限大，以便下次继续执行
        }
        st.async_wait(std::bind(&Demo::checkDeadline, this));           //新增计时任务，目的是为了外部只需要调用setTime。（递归逻辑）
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