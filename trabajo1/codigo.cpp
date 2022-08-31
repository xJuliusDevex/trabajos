#include <iostream>
#include <semaphore.h>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
using namespace std;    
/*------------------Inicializacion de las variables---------------------*/
//semaphoro 
sem_t mutex,coche,salida;
//integer
int n,nespera;
//hilos
thread *pr_Llegada=new thread[4];
thread pr_Salida;
/*------------------declaracion de procesos------------------------------*/
static void Psalida();
static void Pllegada(int);
/*------------------------------Los  procesos----------------------------*/
static void Psalida()
{
    while(true)
    {
        while(nespera!=0)//espera  a que exista un coche en espera 
        {
            sem_wait(&coche);//bloquea  los coches  que llegan
            sem_wait(&mutex);//bloque de barrera
            nespera++;
            sem_post(&salida);//desbloquea la salida
            sem_post(&mutex);//desbloquea la barrera
            cout<<endl<<"El coche esta saliendo";
        }
    }
}
static void Pllegada(int i)
{
    while (true)
    {
        sem_wait(&mutex);// bloquea la barrera 
        if(nespera<n) //verifica si la espera esta llena 
        {
            nespera--;
            cout<<endl<<"carril abierto Nº"<<i+1;
            cout<<endl<<"El coche esta llegando carril Nº "<<i+1;
            cout<<endl<<"El coche esta esperando carril Nº "<<i+1;
            sem_post(&coche);//desbloquea  los coches
            sem_post(&mutex);//desbloquea la barrera
            sem_post(&salida);//desbloquea la salida
        }
        else
        {
            sem_post(&mutex);//desbloquea la barrera
        }
    }
}
/*------------------------main--------------------*/
int main()
{
    /*-------inicializacion------*/
    sem_init(&mutex,0,1);
    sem_init(&coche,0,0);
    sem_init(&salida,0,0);
    nespera=0;
    n=4;
    for(int i=0;i<n;i++)
    {
        pr_Llegada[i]=thread(Pllegada,i);
    }
    pr_Salida=thread(Psalida);

    for(int i=0;i<n;i++)
    {
        if(pr_Llegada[i].joinable())
        {
            pr_Llegada[i].join();
        }
    }
    if (pr_Salida.joinable())
    {
        pr_Salida.join();
    }
}