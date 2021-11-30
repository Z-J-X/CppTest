#if 0
#include<boost/regex.hpp>
#include<string>
using namespace std;
template < typename charT>
inline bool boost_match(const charT * pattern, const charT * text, unsigned int flags = boost::regex::normal, boost::match_results<const charT*>*result = NULL)
{
	    boost::basic_regex<charT, boost::regex_traits<charT> > expression(pattern, flags);
	    if (NULL == result)
		        return boost::regex_match(text, expression);
	   return boost::regex_match(text, *result, expression);
}

template < typename charT>
inline bool boost_search(const charT * pattern, const charT * text, unsigned int flags = boost::regex::normal, boost::match_results<const charT*>*result = NULL)
{
	    boost::basic_regex<charT, boost::regex_traits<charT> > expression(pattern, flags);
	   if (NULL == result)
		        return boost::regex_search(text, expression);
	    return boost::regex_search(text, *result, expression);
	}
static const string protocol = "(?:(mailto|ssh|ftp|https?)://)?";
static const string hostname = "(?:[a-z0-9](?:[-a-z0-9]*[a-z0-9])?\\.)+(?:com|net|edu|biz|gov|org|in(?:t|fo)|(?-i:[a-z][a-z]))";
static const string ip = "(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])";
static const string port = "(?::(\\d{1,5}))?";
static const string path = "(/.*)?";
static const string pattern = protocol + "((?:" + hostname + "|" + ip + "))" + port + path;

int main()
{
    using namespace boost;

    //形式1: 带协议名,服务器为名称,不带端口号
    bool ret;
    string text = "http://www.cppblog.com/qinqing1984";
    boost::cmatch what;
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "http");
    assert(what[2].str() == "www.cppblog.com");
    assert(what[3].str() == "");
    assert(what[4].str() == "/qinqing1984");

    //形式2: 不带协议名,服务器为名称,带端口号
    text = "www.cppblog.com:80/qinqing1984";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "");
    assert(what[2].str() == "www.cppblog.com");
    assert(what[3].str() == "80");
    assert(what[4].str() == "/qinqing1984");

    //形式3: 不带协议名,服务器为名称,不带路径
    text = "www.cppblog.com:80";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "");
    assert(what[2].str() == "www.cppblog.com");
    assert(what[3].str() == "80");
    assert(what[4].str() == "");

    //形式4: 协议为https,服务器为IP,带端口号
    text = "https://192.168.1.1:443/index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "https");
    assert(what[2].str() == "192.168.1.1");
    assert(what[3].str() == "443");
    assert(what[4].str() == "/index.html");

    //形式5: 端口超过5位数
    text = "ftp://192.168.1.1:888888";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    //形式6: 没有协议名
    text = "//192.168.1.1/index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    //形式7: 没有服务器
    text = "http:///index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    //形式8: 不合法的服务器
    text = "cppblog/index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    return 0;
}
#endif