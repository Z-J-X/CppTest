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

    //��ʽ1: ��Э����,������Ϊ����,�����˿ں�
    bool ret;
    string text = "http://www.cppblog.com/qinqing1984";
    boost::cmatch what;
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "http");
    assert(what[2].str() == "www.cppblog.com");
    assert(what[3].str() == "");
    assert(what[4].str() == "/qinqing1984");

    //��ʽ2: ����Э����,������Ϊ����,���˿ں�
    text = "www.cppblog.com:80/qinqing1984";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "");
    assert(what[2].str() == "www.cppblog.com");
    assert(what[3].str() == "80");
    assert(what[4].str() == "/qinqing1984");

    //��ʽ3: ����Э����,������Ϊ����,����·��
    text = "www.cppblog.com:80";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "");
    assert(what[2].str() == "www.cppblog.com");
    assert(what[3].str() == "80");
    assert(what[4].str() == "");

    //��ʽ4: Э��Ϊhttps,������ΪIP,���˿ں�
    text = "https://192.168.1.1:443/index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(ret);
    assert(what[1].str() == "https");
    assert(what[2].str() == "192.168.1.1");
    assert(what[3].str() == "443");
    assert(what[4].str() == "/index.html");

    //��ʽ5: �˿ڳ���5λ��
    text = "ftp://192.168.1.1:888888";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    //��ʽ6: û��Э����
    text = "//192.168.1.1/index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    //��ʽ7: û�з�����
    text = "http:///index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    //��ʽ8: ���Ϸ��ķ�����
    text = "cppblog/index.html";
    ret = boost_match(pattern.c_str(), text.c_str(), regex::icase | regex::perl, &what);
    assert(!ret);

    return 0;
}
#endif