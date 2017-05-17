#include"include/mysqlpool.h"

int main() {
  MysqlPool *mysql = MysqlPool::getMysqlPoolObject();
  mysql->setParameter("localhost","root","root","mysqltest",0,NULL,0,2);
  std::map<const std::string,std::vector<const char*> > m = mysql->executeSql("select * from test");
  for (std::map<const std::string,std::vector<const char*> >::iterator it = m.begin() ; it != m.end(); ++it) {
    std::cout << it->first << std::endl;
    const std::string field = it->first;
    for (size_t i = 0;i < m[field].size();i++) {
      std::cout <<  m[field][i]  << std::endl;
    }
  }
  delete mysql;
  return 0;
}
