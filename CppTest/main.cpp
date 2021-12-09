#include<iostream>
#include<string>
#include<map>
#include<chrono>

struct ci_less //: std::binary_function<std::string, std::string, bool>
{
	// case-independent (ci) compare_less binary function
	struct nocase_compare //: public std::binary_function<unsigned char, unsigned char, bool>
	{
		bool operator()(const unsigned char& c1, const unsigned char& c2) const
		{
			return tolower(c1) < tolower(c2);
		}
	};
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		return std::lexicographical_compare(s1.begin(), s1.end(), // source range
			s2.begin(), s2.end(), // dest range
			nocase_compare());    // comparison
	}
};

int main()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> timePoint =
		std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint.time_since_epoch());
	size_t nTime = timeNow.count();//获取时间戳精确到微秒

	double a = 1638845727.6457758;
	size_t t = a * 1000-3000;
	std::cout << t << std::endl;
	std::cout << nTime << std::endl;
	return 0;
}
