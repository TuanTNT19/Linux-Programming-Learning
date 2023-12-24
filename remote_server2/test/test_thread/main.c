#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

typedef struct{
    char hoten[20];
    int namsinh;
    char quequan[50];
} sinh_vien;

pthread_t thread_id1;
pthread_t thread_id2;
pthread_t thread_id3;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condition_id1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t condition_id2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t condition_id3 = PTHREAD_COND_INITIALIZER;

int input_ = 0;
int write_ = 0;
int read_ = 1;

char *file_name = "thongtinsinhvien.txt";

static void *input_thread(void *info);
static void *write_thread(void *info);
static void *read_thread(void *info);

int main() {
    int ret = 0;
    sinh_vien khai;

    int fd = open(file_name, O_CREAT | O_APPEND, 0667);
    if(-1 == fd) {
        printf("create file error \n\n");
    }
    close(fd);

    if(ret = pthread_create(&thread_id1, NULL, &input_thread, &khai)) {
        printf("pthread create thread id1 error, status = %d \n", ret);
    }
    if(ret = pthread_create(&thread_id2, NULL, &write_thread, &khai)) {
        printf("pthread create thread id1 error, status = %d", ret);
    }

    if(ret = pthread_create(&thread_id3, NULL, &read_thread, &khai)) {
        printf("pthread create thread id1 error, status = %d", ret);
    }
    while(1);
    printf("the end \n");
    return 0;
//    }
   
}

static void *input_thread(void *agsv) {
    sinh_vien *info = (sinh_vien*) agsv;
    char buf [10] = {0};

    while (1)
    {
        /*khoa thread*/
        pthread_mutex_lock(&lock);
        /*doi tin hieu tu thread3*/
        while(read_ !=1 ){
            pthread_cond_wait(&condition_id3, &lock);
            //printf("receiver singal to thread3 \n");
        }
        
        printf("nhap thong tin sinh vien: \n");
        printf("- Name: \n");
        /* nhap ten sinh vien tu ban phim*/
        fgets(info->hoten, sizeof(info->hoten),stdin);
        printf("- Que quan \n");
        /* nhap que quan sinh vien tu ban phim*/
        fgets(info->quequan, sizeof(info->quequan),stdin);
        printf("- Nam sinh \n");
        /* nhap nam sinh tu ban phim*/
        fgets(buf, sizeof(buf),stdin);
        /* chuyen doi nam sinh tu chuoi thanh so nguyen*/
        info->namsinh = atoi(buf);
        
        /* gui tin hieu toi thread2*/
        input_ = 1;
        read_ = 0;
        pthread_cond_signal(&condition_id1);
        /* mo khoa thread*/
        pthread_mutex_unlock(&lock);
        /* gan gia tri de thuc hien dieu kien doi thread3 */
        
    }
}

static void *write_thread(void *info) {
    char buff[100] = {0};
    sinh_vien *a = (sinh_vien*) info;

    while (1)
    {
        pthread_mutex_lock(&lock);
        
//        if(1 == write_)  
        /*wait singal* to input_thread*/
        while(input_ != 1)
        {
            pthread_cond_wait(&condition_id1, &lock);
        }
        printf("write thead operation \n\n");
        /* open file thongtinsinhvien*/
        int fd = open(file_name, O_WRONLY | O_APPEND, 0667);
        if(fd == -1)
            printf("open write error\r\n");
        
        /*ep thong tin sinh vien vao buff*/
        sprintf(buff,"%s%s%d\n", a->hoten, a->quequan, a->namsinh);
        /* ghi thong tin sinh vien vao dau file*/
        lseek(fd, 1, SEEK_SET);
        /* ghi thong tin sinh vien vao file*/
        int w = write(fd, buff, strlen(buff));
        if(w == -1) {
            printf("write error \r\n");
        }
        /* dong file*/
        close(fd);
        /* transmit signal to thread3*/
        input_ = 0;
        write_ = 1;
        pthread_cond_signal(&condition_id2);
 
        
        pthread_mutex_unlock(&lock);
        
    }
    

}

static void *read_thread(void *info) {
    sinh_vien *a = (sinh_vien*) info;
    char buff[50] = {0};

    while(1) {
        pthread_mutex_lock(&lock);
        
       // if(1 == read_) {
            /* wait singal to thread2*/
            while(write_ != 1)
            {
            pthread_cond_wait(&condition_id2, &lock);
            }
            /* open file thongtinsinhvien.txt*/
            int fd = open(file_name, O_RDONLY);
            if(-1 == fd) {
                printf("open file error \n");
            }
            /*read data file thongtinsinhvien.txt*/
            int r = read(fd, &buff, sizeof(buff));
            /* close file thongtinsinhvien.txt*/
            close(fd);

            printf("thong tin sinh vien Khai: \n %s \n\n", buff);
            /*transmit signal to thread1*/
          
        //}
        write_ = 0;
        read_ = 1;
        pthread_cond_signal(&condition_id3);
        pthread_mutex_unlock(&lock);
    }
}