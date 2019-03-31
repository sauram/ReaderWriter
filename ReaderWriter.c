//31.03.2019
//Saurabh Singh Gautam
//Sauram
/*

Following is the Starve-free solution of Reader Writer Problem

*/
#include<stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include<pthread.h>
#include<semaphore.h>

sem_t mutual_wala_execution,block_ko_writekaro;
int data = 0,reader_ka_count = 0;

void *reader(void *arg){
  int f;
  f = ((int)arg);
  sem_wait(&mutual_wala_execution);
  reader_ka_count = reader_ka_count + 1;
  if(reader_ka_count==1)
   sem_wait(&block_ko_writekaro);
  sem_post(&mutual_wala_execution);
  printf("Data read by the reader %d is %d\n",f,data);
  sleep(1);
  sem_wait(&mutual_wala_execution);
  reader_ka_count = reader_ka_count - 1;
  if(reader_ka_count==0)
   sem_post(&block_ko_writekaro);
  sem_post(&mutual_wala_execution);
}

void *writer(void *arg){
  int f;
  f = ((int) arg);
  sem_wait(&block_ko_writekaro);
  data++;
  printf("Data written by the writer %d is %d\n",f,data);
  sleep(1);
  sem_post(&block_ko_writekaro);
}

int main(){
  int i,b; 
  pthread_t reader_tid[5],writer_tid[5];
  sem_init(&mutual_wala_execution,0,1);
  sem_init(&block_ko_writekaro,0,1);
  for(i=0;i<=3;i++)
  {
    pthread_create(&writer_tid[i],NULL,writer,(void *)i);
    pthread_create(&reader_tid[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=3;i++)
  {
    pthread_join(writer_tid[i],NULL);
    pthread_join(reader_tid[i],NULL);
  }
  return 0;
}
