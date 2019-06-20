#include <stdio.h>
#include <stdlib.h>

/*
    Dinamik array dengan menggunakan konsep pointer.
    soal:
        menyusun buku yang memiliki jumlah halaman tertentu pada rak buku.
        kode cara menyusun:
            1 x y : masukkan buku dengan jumlah halaman y pada rak ke x.
            2 x y : tampilkan jumlah halaman pada buku y di rak ke x.
            3 x   : tampilkan jumlah buku yang ada pada rak ke x.
*/

int* total_number_of_books; //This stores the total number of total_number_of_bookss in each total_number_of_shelves.

int** total_number_of_pages;// This stores the total number of total_number_of_pagess in each total_number_of_books of each total_number_of_shelves. The rows represent the shelves and the columns represent the total_number_of_bookss.

int main()
{
    int total_number_of_shelves;
    scanf("%d", &total_number_of_shelves);

    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);

    //alokasi memori untuk tiap variabel
    total_number_of_books = (int*)malloc(sizeof(int)*total_number_of_shelves);
    total_number_of_pages = (int**)malloc(sizeof(int*)*total_number_of_shelves);

    int i;
    for(i = 0; i < total_number_of_shelves; i++)
    {
        total_number_of_books[i] = 0;
        total_number_of_pages[i] = (int*)malloc(sizeof(int));
    }

    while (total_number_of_queries--)
    {
        int type_of_query;
        scanf("%d", &type_of_query);

        if (type_of_query == 1)
        {
            /*
             * Process the query of first type here.
             */
            int x, y;
            scanf("%d %d", &x, &y);
            
            total_number_of_books[x] += 1;
            total_number_of_pages[x] = realloc(total_number_of_pages[x], total_number_of_books[x]*sizeof(int));
            total_number_of_pages[x][total_number_of_books[x] - 1] = y;

        }
        else if (type_of_query == 2)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", total_number_of_pages[x][y]);
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", total_number_of_books[x]);
        }
    }

    if (total_number_of_books)
        free(total_number_of_books);
        
    for (i = 0; i < total_number_of_shelves; i++)
        if (total_number_of_pages[i])
            free(total_number_of_pages[i]);
            
    if (total_number_of_pages)
        free(total_number_of_pages);

    return 0;
}
