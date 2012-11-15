#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Header.h"
//#include "Queue.h"

const int tableSize = 301;
//#define tableSize 301;
const int step = 1;

struct HashItem
{
    char direct[128];
    //Queue *responseQueue;/////////////////
    int id;
    int empty;
    int visit;
};

struct HashTable
{
    int size;
    struct HashItem* arrayHash;
};

int HashKey(int id)
{
    return id % tableSize;
}

int InsertToHashTable(struct HashTable *table, char* info, int clientid)
{
    if (table->size == tableSize - 1)
    {
        return -1; //таблица переполнена
    }
    else
    {
        int i = HashKey(clientid);
        if (table->arrayHash[i].empty)
        {
            table->arrayHash[i].empty = 0;//false
            table->arrayHash[i].visit = 1;//true
            strcpy(table->arrayHash[i].direct, info);
            //table->arrayHash[i].direct = info;
            //InitializeQueue(table->arrayHash[i].responseQueue);//////////
            table->arrayHash[i].id = clientid;
            table->size++;
            return i;
        }
        else
        {
            i = (i + step) % tableSize;
            while (table->arrayHash[i].empty == 0)
                i = (i + step) % tableSize;

            table->arrayHash[i].empty = 0;
            table->arrayHash[i].visit = 1;
            strcpy(table->arrayHash[i].direct, info);
            //table->arrayHash[i].direct = info;
            //InitializeQueue(table->arrayHash[i].responseQueue);////////////
            printf("In Col %d :  %s", i, table->arrayHash[i].direct);
            table->arrayHash[i].id = clientid;
            table->size++;
            return i;
        }

    }
}

int FindIndex(struct HashTable* table, int clientid)
{
    int i = HashKey(clientid);

    if (table->arrayHash[i].empty == 0 && table->arrayHash[i].id == clientid)
    {
        return i;
    }
    else // коллизия
    {
        i = (i + step) % tableSize;
        int flag = 0;

        while (flag == 0 && table->arrayHash[i].visit)
        {
            if (table->arrayHash[i].empty == 0 && table->arrayHash[i].id == clientid)
                flag = 1;
            else
                i = (i + step) % tableSize;

            if (flag)
                return i;
            else
                return -1;
        }
    }
}

char* GetDirect(struct HashTable table, int index)
{
    return table.arrayHash[index].direct;
}

int DelFromHashTable(struct HashTable* table, int clientid)
{
    if(table->size == 0)
        return -1;
    else
    {
        int i = HashKey(clientid)    ;

        if(table->arrayHash[i].id == clientid)
        {
            table->arrayHash[i].empty = 1;
            table->size--;
            return 0;
        }
        else //коллизия
        {
            i = FindIndex(table, clientid);
            if (i == -1)
                return -1;
            else
            {
                table->arrayHash[i].empty = 1;
                table->size--;
                return 0;
            }
        }
    }
}

int ChangeHashTable(struct HashTable *table, int index, char *newDir)
{
    strcpy(table->arrayHash[index].direct, newDir);
    //table->arrayHash[index].direct = newDir;

    return 0;
}

struct HashTable HashInit()
{
    struct HashTable table;
    table.arrayHash = (struct HashItem *)malloc(sizeof(struct HashItem) * tableSize);
    table.size = 0;
    int i;
    for(i = 0; i < tableSize; i++)
    {
        table.arrayHash[i].empty = 1;
        table.arrayHash[i].visit = 0;
    }

    return table;
}

int DistructHash(struct HashTable *table)
{
    table->size = 0;
    free(table->arrayHash);

    return 0;
}

/*int main(int argc, char** argv)
{
    struct HashTable table = HashInit();
    printf("Adding\n");

    char* a = "/home/alina/\0";
    InsertToHashTable(&table, a, 7);
    InsertToHashTable(&table, a, 8);

    int index = FindIndex(&table, 7);
    printf("index = %d\n", index);
    char *dirc = GetDirect(table, index);
    printf("dirc = %s\n", dirc);

    index = FindIndex(&table, 8);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("dirc = %s\n", dirc);

    index = FindIndex(&table, 7);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("old dirc = %s\n", dirc);
    dirc = "/home/alina/Изображения/\0";
    ChangeHashTable(&table, index, dirc);
    printf("new dirc = %s\n", GetDirect(table, index));

    index = FindIndex(&table, 8);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("old dirc = %s\n", dirc);
    dirc = "/home/alina/Изображения/\0";
    ChangeHashTable(&table, index, dirc);
    printf("new dirc = %s\n", GetDirect(table, index));


    index = FindIndex(&table, 8);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("old dirc = %s\n", dirc);
    dirc = "/home/alina/Изображения/111/\0";
    ChangeHashTable(&table, index, dirc);
    printf("new dirc = %s\n", GetDirect(table, index));

    index = FindIndex(&table, 7);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("old dirc = %s\n", dirc);
    dirc = "/home/alina/Изображения/111/\0";
    ChangeHashTable(&table, index, dirc);
    printf("new dirc = %s\n", GetDirect(table, index));

    printf("LS1=======================================================\n");

    index = FindIndex(&table, 8);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("dirc = %s\n", dirc);

    index = FindIndex(&table, 7);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("dirc = %s\n", dirc);

    printf("LS2=======================================================\n");

    index = FindIndex(&table, 8);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("dirc = %s\n", dirc);

    index = FindIndex(&table, 7);
    printf("index = %d\n", index);
    dirc = GetDirect(table, index);
    printf("dirc = %s\n", dirc);

    return 0;

}*/
