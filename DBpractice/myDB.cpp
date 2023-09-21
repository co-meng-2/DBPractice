#include <iostream>
#include <mysqlx/xdevapi.h>


#ifndef _DEBUG
#pragma comment(lib, "mysqlcppconn8.lib")
#else
#pragma comment(lib, "mysqlcppconn8d.lib")
#endif

int main()
{
    std::locale::global(std::locale("ko_KR.utf8"));

    try
    {
        mysqlx::Session session(mysqlx::SessionOption::HOST, "localhost",
            mysqlx::SessionOption::PORT, 33060,
            mysqlx::SessionOption::USER, "root",
            mysqlx::SessionOption::PWD, "0000");

        mysqlx::Schema myDb = session.getSchema("mydb");
        mysqlx::Table myTable = myDb.getTable("lol_ranking1");


        // 데이터 추가 (Insert)
        // myTable.insert("nick_name", "rank_point").values("TwelveTank", 1802).execute();
        // myTable.insert("nick_name").values("일반유저").execute();

        //// 데이터 조회 (Select)
        mysqlx::RowResult result = myTable.select("nick_name", "rank_point").execute();

        for (mysqlx::Row row : result)
        {
            std::cout << row[0].get<std::string>() << " ";
            if (!row[1].isNull())
                std::cout << row[1].get<int>();
            std::cout << "\n";
        }


        session.close();
    }
    catch(const mysqlx::Error& err)
    {
        std::cout << "An error occurred: " << err.what() << std::endl;
    }
	
    

    return 0;
}
