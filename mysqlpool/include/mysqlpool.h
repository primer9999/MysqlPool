#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H

#include<iostream>
#include<mysql/mysql.h>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include<string>
#include<mutex>
#include<thread>



class MysqlPool {
  public:
    ~MysqlPool();
    std::map<const std::string,std::vector<const char* > > executeSql(const char* sql);//sql语句的执行函数
    static MysqlPool* getMysqlPoolObject();              //单列模式获取本类的对象
    void setParameter( const char*   _mysqlhost,
                       const char*   _mysqluser,
                       const char*   _mysqlpwd,
                       const char*   _databasename,
                       unsigned int  _port = 0,
                       const char*   _socket = NULL,
                       unsigned long _client_flag = 0,
                       unsigned int  MAX_CONNECT = 50 );              //设置数据库参数
  private:
    MysqlPool();
    MYSQL* createOneConnect();                    //创建一个新的连接对象
    MYSQL* getOneConnect();                       //获取一个连接对象
    void close(MYSQL* conn);                      //关闭连接对象
    bool isEmpty();                               //连接池队列池是否为空
    MYSQL* poolFront();                           //连接池队列的队头
    unsigned int poolSize();                      //获取连接池的大小
    void poolPop();                               //弹出连接池队列的队头
  private:
    std::queue<MYSQL*> mysqlpool;                 //连接池队列
    const char*   _mysqlhost;                     //mysql主机地址
    const char*   _mysqluser;                     //mysql用户名
    const char*   _mysqlpwd;                      //mysql密码
    const char*   _databasename;                  //要使用的mysql数据库名字
    unsigned int  _port;                          //mysql端口
    const char*   _socket;                        //可以设置成Socket or Pipeline，通常设置为NULL
    unsigned long _client_flag;                   //设置为0
    unsigned int  MAX_CONNECT;                    //同时允许最大连接对象数量
    unsigned int  connect_count;                  //目前连接池的连接对象数量
    static std::mutex objectlock;                 //对象锁
    static std::mutex poollock;                   //连接池锁
    static MysqlPool* mysqlpool_object;           //类的对象
};

#endif
