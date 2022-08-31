#include <iostream>
#include <semaphore.h>
#include <thread>
#include <unistd.h>
#include <stdlib.h>
#define n 1
/*------------Declaracion de los monitores-----------------*/
class productor;
class consumidor;   
using namespace std;    
class buffer{
    private:
    /*Variables*/
    sem_t libres,mutex;
    int cola[n],elemento,final=0,a=0;
    public:
    void insertar(int,int&);
    int retirar(int,int&);
};
void buffer::insertar(int elemento,int &pos)
{
    
    sleep(1);
    while(cola[a]!=NULL&&a!=n)//busca la cola de espacios vacios
    {
        a++;
    }

    sem_wait(&libres);
    if(cola[a]==NULL)
    {
        sem_wait(&libres);
        final=a;
        cola[final]=elemento;//Guardamos elemento a la cola en un espacio    
        int i=final;
    }
    sleep(1);//esperar
    sem_post(&mutex);//libera la sc   
}
int buffer::retirar(int elemento,int &pos){
    sem_wait(&mutex);
    int frente=0;
    int a=0;
    while(cola[a]!=elemento&& a!=n){
        a++;    
    }
    sleep(1);
    if(cola[a]==elemento)
    {
        frente=a;
        elemento=cola[frente];
        return elemento;
        int i=frente;   
        sleep(1);
    }
    sem_post(&mutex);
}
void productoA()
{   
    int i=1;
    int elemento;
    buffer bufer;
    bufer.insertar(1,i);
    printf("\n\t Productor A genera elemnto de tipo 1 y pone en la posicion  :%i  \n",i);
}
void productoB()
{
    int i=2;
    int elemento;
    buffer bufer;
    bufer.insertar(2,i);
    printf("\n\t Productor B genera elemnto de tipo 1 y pone en la posicion  :%i  \n",i);
}
void consumidorA(){

}
void consumidorB(){

}
void consumidorByA(){

}