#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include<string.h>

int main(int argc,char *argv[])
{
    MYSQL *mysql =mysql_init(NULL);
    mysql =mysql_real_connect(mysql,"127.0.0.1",argv[1],argv[2],"xiao",3306,NULL,0);
    if(mysql==NULL)
    {
        printf("connect error\n");
    }
    mysql_query(mysql,"set names utf8");

    while(1)
    {

    printf("mysql >");
    char  buf[1024];
    fgets(buf,sizeof(buf),stdin);
    int ret =0;
    int i;
    if(strncmp(buf,"insert",6)==0||strncmp(buf,"update",6)==0||strncmp(buf,"delete",6)==0)
    {
        ret= mysql_query(mysql,buf);
        if(ret)
        {
            printf("error\n");
            return -1;
        }
        int num =mysql_affected_rows(mysql);
        printf("affected %d rows",num);
    }
    else if( strncmp(buf,"select",6)==0)
    {
        ret = mysql_query(mysql,buf);
        if(ret)
        {
            printf("error\n");
            return -1;
        }
        int count =mysql_field_count(mysql);
        MYSQL_RES *result=mysql_store_result(mysql);
        MYSQL_FIELD *fields = mysql_fetch_fields(result);

        for(i=0;i<count;i++)
        {
            printf("%s\t",fields[i].name);
        }
        printf("\n");
        MYSQL_ROW row;
        while(row =mysql_fetch_row(result))
        {
            for(i=0;i<count;++i)
            {
                printf("%s\t",row[i]);
            }
            printf("\n");
        }
        mysql_free_result(result);
    }
    else if(strncmp(buf,"exit",4)== 0)
    {
        mysql_close(mysql);
        return 0;
    }
    else {
        printf("参数错误\n");

    	}

}
return 0;
}
