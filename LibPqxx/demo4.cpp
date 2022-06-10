#if 0
#include <iostream>
#include <pqxx/pqxx>

int main()
{
	try
	{
		pqxx::connection C("postgresql://ami:ami@10.32.233.138:5432/ami_empower");
		pqxx::work W{ C };
		pqxx::stream_to tStream = pqxx::stream_to::raw_table(W, "test", "id,ns_name,ns_server,task_cached");//Use table() or raw_table() factory create
		//pqxx::stream_to tStream = pqxx::stream_to::raw_table(W, "test");
		//pqxx::stream_to tStream{ W, "test" };

		std::vector<std::tuple<int,std::string, std::string,std::string>> datas;
		for (int i = 0; i < 100; i++)
		{
			datas.push_back(std::make_tuple(i, "Test", "127.0.0.1", "2"));
		}
		for(auto const& row: datas)
			tStream << row;
		tStream.complete();
		W.commit();
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}

#endif