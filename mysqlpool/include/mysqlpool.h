#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H

#include<iostream>
#include<mysql/mysql.h>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include<string>


// mysql connection pool
class MysqlPool {
  public:
    MysqlPool(const char*   _mysqlhost,
              const char*   _mysqluser,
              const char*   _mysqlpwd,
              const char*   _databasename,
              unsigned int  _port = 0,
              const char*   _socket = NULL,
              unsigned long _client_flag = 0 );        //constuctor completes the initialization of mysql parameter
    std::map<const std::string,std::vector<const char* > > executeSql(const char* sql); //execute mysql query,return a map,eg:map['field'][i]
    ~MysqlPool();//close all connections
  private:
    MYSQL* createOneConnect();                    //when pool is empty,we need create a new connection
    MYSQL* getOneConnect();                       //get a connection from connection pool
    void close(MYSQL* conn);                      //push connection into queue
  private:
    std::queue<MYSQL*> mysqlpool;                 //connection pool
    const char*   _mysqlhost;                     //mysql host
    const char*   _mysqluser;                     //mysql username
    const char*   _mysqlpwd;                      //mysql password
    const char*   _databasename;                   //mysql dbname
    unsigned int  _port;                          //mysql portnumber
    const char*   _socket;                        //whether it uses Socket or Pipeline,it usually sets at NULL
    unsigned long _client_flag;                   //0 is ok
};

#endif
