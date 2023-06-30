# School-database-IT003
Database-final
1. Run `CreateSchema1.sql` file in mySQL to create database `TRUONGHOC1`.
2. Run `generate-db.cpp` to create SQL file containing insert queries in folder `insert_query`, then run all SQL files in that folder to insert data into database `TRUONGHOC1`
    ``` bash
    g++ ggenerate-db.cpp -o gen-db
    ./gen-db
    ``` 
3. Run `CreateSchema2.sql` file in mySQL to create database `TRUONGHOC2`, then insert data into it.
4. Run `query-db.py` to execute query, the output on the screen includes a table of query result and execution time, it also creates XML file containing query result in XML folder.
5. Run `query-xml.py` to perform query on XML files using Xpath. The output includes the tables of query result.
