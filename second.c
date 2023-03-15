// 04-fifo-reader.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
   int     another_fd;
   size_t  another_size;
   int buf_size = 20;
   char    str_buf[buf_size];
   char    another_name[] = "bbb.fifo";

   // Только читает из созданного канала
   if((another_fd = open(another_name, O_RDONLY)) < 0){
      printf("Can\'t open FIFO for reading\n");
      exit(-1);
   }
   another_size = read(another_fd, str_buf, buf_size);
   if(another_size < 0){
      printf("Can\'t read string from FIFO\n");
      exit(-1);
   }
   printf("Reader exit, str_buf: %s\n", str_buf);
   if(close(another_fd) < 0){
      printf("Reader: Can\'t close FIFO\n"); exit(-1);
   }


   ////



   int     fd, result;
   size_t  size;
   char msg[] = "Hello, number1";
   int msg_size = sizeof(msg);
   char    name[] = "aaa.fifo";

   (void)umask(0);

   // Вариант с проверкой требует удаления именованного канала
   // if(mknod(name, S_IFIFO | 0666, 0) < 0){
   //   printf("Can\'t create FIFO\n");
   //   exit(-1);
   // }

   // Вариант без проверки позволяет использовать уже созданный FIFO
   mknod(name, S_IFIFO | 0666, 0);

   if((fd = open(name, O_WRONLY)) < 0){
      printf("Can\'t open FIFO for writting\n");
      exit(-1);
   }
   size = write(fd, msg, msg_size);
   if(size != msg_size){
      printf("Can\'t write all string to FIFO\n");
      exit(-1);
   }
   if(close(fd) < 0){
      printf("Writer: Can\'t close FIFO\n"); exit(-1);
   }





   return 0;
}
