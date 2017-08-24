#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
int main ()
{
      MYSQL *mysql = NULL;
      mysql = mysql_init(mysql);
      mysql =mysql_real_connect(mysql,"127.0.0.1","root","test123","xiao",3306,NULL,0);
      if(NULL== mysql)
      {
          printf("connect error\n");
          return -1;
      }
      char *sql ="set names utf8";
           int ret= mysql_query(mysql,sql);
           if(ret)
           {
            printf("set code error\n");
            return -1;
           }
           mysql_query(mysql,"start transaction");
          int ret1= mysql_query(mysql,"insert into abc values(19,'xiao','wuli',85)");
        // int ret2= mysql_query(mysql,"insert into abc values(19)");
         // if(ret1||ret2)
            if(ret1)
          {
              mysql_query(mysql,"rollback");
              return -2;
          }
          int num = mysql_affected_rows(mysql);
          printf("affected %d\n",num);
          mysql_close(mysql);
          return 0;
}
