#include <json/json.h>
#include <sstream>
#include <iostream>
#include <fstream>


bool readFromStream()
{
	Json::Value root;
	std::ifstream ifs;
	ifs.open("test.json");

	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;//是否读取注释
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << root << std::endl;
	return EXIT_SUCCESS;
}

bool readFromString()
{
	const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
	const auto rawJsonLength = static_cast<int>(rawJson.length());

	JSONCPP_STRING err;
	Json::Value root;

	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) //解析
	{
		std::cout << "error" << std::endl;
		return false;
	}

	const std::string name = root["Name"].asString();
	const int age = root["Age"].asInt();

	std::cout << name << std::endl;
	std::cout << age << std::endl;
	return true;
}

bool writeToStream()
{
	Json::Value root, array1, array2, value1, value2;
	Json::StreamWriterBuilder builder;
	const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	value1["str"] = "100";
	value1["int"] = 20;
	value2["name"] = "zhou";
	value2["age"] = 18;
	array1.append(value1);//json数组使用append
	array1.append(value2);
	array2.append(3);
	array2.append(1);
	array2.append(2);
	root["array1"] = array1;
	root["array2"] = array2;
	root["test"] = "jsoncpp";

	writer->write(root, &std::cout);
	std::cout<<"\n----数组访问测试----"<<std::endl;
	writer->write(root["array1"][0], &std::cout);

	return true;
}

bool writeToString()
{
	Json::Value root;
	Json::Value data;

	root["action"] = "run";
	data["number"] = 1;
	root["data"] = data;

	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";//设置缩进格式，""为去格式化
	const std::string json_file = Json::writeString(builder, root);
	std::cout << json_file << std::endl;

	return true;
}

void test(Json::Value& obj)
{
	Json::Value array, value;
	int a = 0;
	std::string str = "aa";
	value["test1"] = a;
	value["test2"] = str;
	array.append(value);
	array.append(value);
	obj["array"] = array;
}

int _main() {
	std::cout << "--------------------readFromStream--------------------" << std::endl;
	readFromStream();
	std::cout << "--------------------readFromString--------------------" << std::endl;
	readFromString();
	std::cout << "\n--------------------writeToStream--------------------" << std::endl;
	writeToStream();
	std::cout << "\n--------------------writeToString--------------------" << std::endl;
	writeToString();

	std::cout << "\n--------------------生命周期测试--------------------" << std::endl;
	Json::StreamWriterBuilder builder;
	const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	Json::Value val;
	test(val);
	writer->write(val, &std::cout);
	return 0;
}



Json::Value ReadFromString(std::string& strJson)
{
	try {
		const auto rawJsonLength = static_cast<int>(strJson.length());

		JSONCPP_STRING err;
		Json::Value root;

		Json::CharReaderBuilder builder;
		const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
		if (!reader->parse(strJson.c_str(), strJson.c_str() + rawJsonLength, &root, &err))
		{
			std::cout << "error" << std::endl;
			return false;
		}

		return root;
	}
	catch (std::exception& ec)
	{
		return false;
	}
}

std::string WriteToString(Json::Value jsRoot)
{
	std::string ret;
	try {
		Json::StreamWriterBuilder builder;
		builder["indentation"] = "";
		ret = Json::writeString(builder, jsRoot);
		return ret;
	}
	catch (std::exception& ec)
	{
		return ret;
	}
}
int main()
{
	try {
		Json::Value root,test;

		root["dsasd"].append(test);
		root["a"].resize(0);
		std::string str = "dasd+dasdas+ds";
		std::cout << str.find("+") << std::endl;
		std::cout << str.find("+",4+1) << std::endl;;
		std::cout << WriteToString(root) << std::endl;

	}
	catch (std::exception& ec)
	{
		std::cout << ec.what() << std::endl;
	}
}