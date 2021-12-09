#include<iostream>
#include<boost/asio.hpp>
#include<boost/asio/ip/tcp.hpp>
int main()
{
    try
    {
        auto host = boost::asio::ip::host_name();//��ȡ������
        std::cout << host << std::endl;
        boost::asio::io_service m_io;
        boost::asio::ip::tcp::resolver m_re(m_io);
        boost::asio::ip::tcp::resolver::query m_q(host, "");//��ַ�Ͷ˿ں�
        boost::asio::ip::tcp::resolver::iterator it = m_re.resolve(m_q);//ͬ������
        decltype(it) end;
        boost::system::error_code ec = boost::asio::error::host_not_found;
        for (; ec && it != end; it++)
        {
            std::cout << it->endpoint().address() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
