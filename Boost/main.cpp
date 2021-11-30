#include <boost/asio.hpp> 
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

int main()
{
    try
    {
        boost::asio::io_service m_io;
        boost::asio::ip::tcp::resolver m_re(m_io);
        boost::asio::ip::tcp::resolver::query m_q("::", "80");//��ַ�Ͷ˿ں�
        boost::asio::ip::tcp::resolver::iterator it = m_re.resolve(m_q);//ͬ������
        decltype(it) end;
        boost::system::error_code ec = boost::asio::error::host_not_found;
        for (; ec && it != end; it++)
        {
            std::cout << (it->endpoint().protocol() == boost::asio::ip::tcp::v6()) << std::endl;
            //sock.close();
            //sock.connect(*it,ec);
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}
