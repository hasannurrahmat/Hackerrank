#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Sorting Array of Strings (Hard)
URL: https://www.hackerrank.com/challenges/sorting-array-of-strings/problem

mengurutkan array of string berdasarkan lexicographic (sesuai abjad)
urutan ke 1 : menghasilkan array of string yang diurut berdasarkan abjad a-z
       ke 2 : menghasilkan array of string yang diurut berdasarkan abjad z-a
       ke 3 : menghasilkan array of string yang diurut berdasarkan jumlah perbedaan karakter yang paling sedikit
       ke 4 : menghasilkan array of string yang diurut berdasarkan panjang string terkecil
*/

int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b); // return compare string a dan b untuk asc
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return strcmp(b, a); //return compare string b dan a untuk desc
}

int distinct_chars(const char *a)
{
    //mencari banyaknya karakter yang berbeda dalam string
    int diff = 0;
   
    while (*a != '\0') {
        if (!strchr(a + 1, *a))
            diff++;
        a++;
    }
    return diff; //return banyaknya karakter yang berbeda
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    //mengurutkan jumlah karakter berbeda dari string dari yang paling sedikit
    int sort = distinct_chars(a) - distinct_chars(b); //memanggil fungsi distinct_chars untuk string a dan b
    return (sort) ? sort : lexicographic_sort(a, b);  //jika sort lebih dari 0, return sort, else panggil fungsi lexicographic_sort
}

int sort_by_length(const char* a, const char* b) {
    //mengurutkan array string berdasarkan panjang tiap string
    int sort = strlen(a) - strlen(b);
    return (sort) ? sort : lexicographic_sort(a, b); //jika sort lebih dari 0, return sort, else panggil fungsi lexicographic_sort
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    // menggunakan sorting buble sort
    int sorted = 0;
    int i = 0;
    while (!sorted) {
        sorted = 1;
        for (i = 0; i < len - 1; i++) {
            if (cmp_func(arr[i], arr[i + 1]) > 0) {
                char *tmp = arr[i];  // string ke i ditampung ke dalam temp
                arr[i] = arr[i + 1]; // isi string ke i dengan string selanjutnya
                arr[i + 1] = tmp;    // isi string selanjutnya denga temp
                sorted = 0;
            }
        }
    }
}

int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    int i;
    for(i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    return 0;
}
