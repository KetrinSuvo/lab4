#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
// функция программы envxкотоаря считывает переменные окружения процесса в переданный ей буфер.
int get_env(char const * PID, int sizeof_PID, char *buff, int sizeof_buff)
{
	//выделили буфер под будущее значение т.н. ссылки
	char fname[sizeof_PID];
	//составили эту ссылку с использованием PID по известному шаблону
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
 		//если встречаем символ терминации, заменяем его символом переноса строки
 		if (ch == '\0')
 			ch = '\n';
 	
 		//прежде чем писать в возвращаемый буфер, проверяем-не выйдем ли мы за его границы	
 		if (bcount >= sizeof_buff)
 		{
 			printf("Buffer overflow\n");
 			return 1;
 		}
 		//если все ок, в очередную ячейку буфера запихиваем свежесчитанный символ
 		buff[bcount] = ch;
 		//сдвигаем счетчик заполненности буфера на 1.
 		bcount++;
		
	}
	//закрываем файл по окончанию всех операций
	fclose(file);

	return 0;
}
// функция выводящая на экран хелп сообщение
void usage()
{
	printf("Usage:\n pwdx [options] pid...\n\n Options:\n -h display this help and exit\n -V  output version information and exit\n\n");

}

int main(int argc, char const *argv[])
{

	char buff[81924]; //буфер на 8 кб
	// проверили на наличие аргументов. если их нет то вызвали usage()
	if (argc <=1 )
	{
		usage();
		return 0;
	}
	// если их слишком много напихали то сказали об этом
	if (argc > 3 )
	{
		printf("Too many arguments\n");
		return 0;
	}
	// если в роли аргумента выпал -h тогда опять вызываем usage()
	if (strncmp(argv[1], "-h", 2) == 0)
	{
		usage();
		return 0;
	}
	// если -V - тогда выводим версию
	if (strncmp(argv[1], "-V", 2) == 0)
	{
		printf("envx v0.01 SuvorovaEA\n");
		return 0;
	}
	
	// и наконец если нам все же скормили PID передаем его нашей функции и пусть она его обрабатывает
	int result = get_env(argv[1], strlen(argv[1]), buff, sizeof(buff));

	//по результату работы функция должна заполнить нам буфер и вернуть 0 или что-то другое в случае ошибки.
	if (result != 0)
		return 1;

	// если все ок- выводим содержимое буфера
	printf("%s\n",buff);


	return 0;
}
