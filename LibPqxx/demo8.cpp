#if 0
#include <iostream>
#include <pqxx/pqxx>
#include <pqxx/except>

int main(int argc, char* argv[])
{
    try
    {
        //Do something
    }
    catch (pqxx::sql_error const& e)//sql�쳣����
    {
        std::cerr
            << "Database error: " << e.what() << std::endl
            << "Query was     : " << e.query() << std::endl
            << "sqlstate      : " << e.sqlstate() << std::endl;
        return 3;
    }
    catch (pqxx::broken_connection const& e)//�����쳣����
    {
        std::cout << "broken_connection : " << e.what() << std::endl;
        return 2;
    }
    catch (std::exception const& e)//�����쳣
    {
        std::cerr << "std::exception: " << e.what() << std::endl;

        return 1;
    }
}
#endif