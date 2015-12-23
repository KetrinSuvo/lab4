#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// хранит значение PATH_MAX - максимальное значение пути / имени файла
#include <linux/limits.h>
// функция программы envxкотоаря считывает переменные окружения процесса в переданный ей буфер.
int get_env(char const * PID, int sizeof_PID, char *buff, int sizeof_buff)
{
	
	char fname[sizeof_PID];
	
  	strcpy( fname, "/proc/" ); 
  	strcat( fname, PID );
  	strcat( fname, "/environ" ); 

  	//открыли файл
  	FILE *file; 
	file = fopen(fname,"r");
	//проверили что он открылся
	if(file == NULL){
		printf("can't open '%s'. May be you will try with sudo?",fname);
		return 0;
	}

	//начали читать файл
	//читаем пока не дойдем до конца файла
	char ch;
	int bcount=0;
 	while((ch=fgetc(file)) !=EOF) 
 	{
 		
 		if (ch == '\0')
 			ch = '\n';
 	
 			
 		if (bcount >= sizeof_buff)
 		{
 			printf("Buffer overflow\n");
 			return 1;
 		}
 		
 		buff[bcount] = ch;
 		
 		bcount++;
		
	}
	//закрываем файл по окончанию всех операций
	fclose(file);

	return 0;
}

// основная функция программы pwdx. на входе ждет указатель на буфер со строкой-PID-ом процесса, раземром этой строки и указатель на буфер куда
// сохранить потом результат работы. Размер буфера buff определяется  системным значением PATH_MAX
int get_pwd(char const * PID,int sizeof_PID, char *buff)
{
	
	char sLink[sizeof_PID];
	
  	strcpy( sLink, "/proc/" ); 
  	strcat( sLink, PID );
  	strcat( sLink, "/cwd" ); 

  	
 	int size = readlink(sLink, buff, PATH_MAX);

 	
	buff[size] = '\0';

 	
	if (size == -1)
	{
		printf("No Such process\n" );
		return 1;
	}

	return 0;

}
