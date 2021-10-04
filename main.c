#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define HashSize 10     //Размер таблицы

typedef struct HashNode {   //Хеш-таблица
    long int key;
    long int number;
    struct HashNode * next;
} * HashNode;

long int HashIndex(long int key, long int size){
    return (key % size);    //Генерируем индекс, берем остаток от деления на размер таблицы
}

HashNode AddNode(HashNode * hash, long int key, long int num){ //Добавление элемента в хеш таблицу
    long int index = HashIndex(key, HashSize);  //Берем индекс

    HashNode * temp = hash;
    HashNode new;
    HashNode node = (HashNode * ) malloc (sizeof(HashNode));

    node->key = key;
    node->number = num;
    node->next = NULL;

    if(hash[index] == NULL)
        hash[index] = node; //Если место не занято
    else {
        new = temp[index];  //Если место уже занято - произошла коллизия
        while (new->next != NULL)
            new = new->next;    //Доходим до конца текущего списка, и добавляем туда элемент
        new->next = node;
    }

    return hash;
}

HashNode HashFound(HashNode * hash, long int key){

    long int index = HashIndex(key, HashSize);  //Берем индекс
    HashNode node = hash[index];

    while (node != NULL){   //Проходим по списку элементов с полученным индексом и ищем наш
        if(node->key == key){
            return node;
            break;
        }
        node = node->next;
    }
    return (NULL);  //Возвращаем ноль, если элемент не найден
}

void DellHash(HashNode * hash, long int key){   //Удаление элемента из таблицы

    long int index = HashIndex(key, HashSize);  //Генерируем индекс
    HashNode temp;
    HashNode new = NULL;

    temp = hash[index];
    while(temp != NULL){
        if(temp->key == key){
            if(new == NULL)
                hash[index] = temp->next;
            else
                new->next = temp->next; //Находем элемент в списке с полученным индексом, и удаляем.
            free(temp);
            return;
        }
        new = temp;
        temp = temp->next;
    }
}

void PrintHash(HashNode * hash){
    //Вывод элементов таблицы на экран - проходимся по всем спискам и выводим в строку все элементы один за другим
    HashNode * node = hash;
    HashNode temp = (HashNode * ) malloc (sizeof(HashNode));

    for(long int index = 0; index < HashSize; index++){
        printf("%li", index);

        if(node[index] == NULL) //Если ключа нет
            printf("    NULL\n");

        if(node[index] != NULL){
            printf("    %li", node[index]->key);    //Если ключ есть, то выводим

            if(node[index]->next != NULL){
                temp = node[index];

                while(temp->next != NULL){
                    node[index] = node[index]->next;
                    printf("    %li", node[index]->key);

                    if(node[index]->next == NULL)
                        break;
                }

                printf("\n");
                node[index] = temp;
            }

            if(node[index]->next == NULL)
                printf("\n");

        }

    }
}

void ResultsPrint(long int *hash, long int * qua, int number){    //Вывод полученных результатов по времени
    printf("\n\tQuantityies");
    for(int i = 0; i < number - 1; i++)
        printf("    %7li", *(1 + qua + i));

    printf("\n\n\tHashTable:");

    printf("\n\tAdding     ");
    for(int i = 0; i < number - 1; i++)
        printf("    %7li", *(3 + hash + i * 3));

    printf("\n\tFound      ");
    for(int i = 0; i < number - 1; i++)
        printf("    %7li", *(3 + hash + i * 3 + 1));

    printf("\n\tDelete     ");
    for(int i = 0; i < number - 1; i++)
        printf("    %7li", *(3  + hash + i * 3 + 2));
    printf("\n");
}

long perf_time() {  //Функция, используемая для подсчета времени работы
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time.QuadPart;
}

int main() {

    HashNode HashTable[HashSize];   //Создаем таблицу

    for(int i = 0; i < HashSize; i++)   //Обнуляем таблицу
        *(HashTable + i) = NULL;

    long int quantity[] = { 100, 500, 1000, 2500, 5000, 7500, 10000}; //Количество числе в каждом тесте

    long int timing[7][3] = {0};  //Массив для подсчета времени работы всех операций
    long int count[5] = {0};    //Берем элементы со случайными индексами, для их поиска
    long int num_f[5] = {0};

    long int * mass = NULL;

    srand(time(NULL));

    for(int i = 0; i < 7; i++){

        mass = (long int * ) malloc (sizeof(long int) * quantity[i]);   //Выделяем память в массиве для хранения элементов
        long int t = perf_time();   //Считываем время до начала добавления элементов

        for(int u = 0; u < 5; u++)
            count[u] = rand() % quantity[i];

        for(int j = 0; j < quantity[0]; j++){
            mass[j] = rand() % 10000;

            for(int u = 0; u < 5; u++)
                if(j == count[u])
                    num_f[u] = mass[j];

            AddNode(HashTable, mass[j], mass[j]);
        }

        timing[i][0] = (perf_time() - t) / quantity[i];

        //PrintHash(HashTable);

        t = perf_time();    //Считываем время до поиска элементов

        for(int u = 0; u < 5; u++)
            HashFound(HashTable, num_f);

        timing[i][1] = (perf_time() - t) / 5;   //Высчитываем среднее время поиска

        t = perf_time();    //Считываем время до удаления элементов

        for(int u = 0; u < quantity[i]; u++)    //Очищаем таблицу
            DellHash(HashTable, mass[i]);

        timing[i][2] = (perf_time() - t) / quantity[i];   //Среднее время удаления

        free(mass); //Очищаем массив с элементами
        mass = NULL;

    }

    ResultsPrint(timing, quantity, 7);
    return 0;
}
