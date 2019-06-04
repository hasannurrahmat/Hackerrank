#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5


/*
    Problem:
    memberikan output berupa kata, kalimat, atau paragraf berdasarkan input dokumen.
*/

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

typedef struct word word; //definisikan struct yang telah dibuat
typedef struct sentence sentence; //definisikan struct yang telah dibuat
typedef struct paragraph paragraph; //definisikan struct yang telah dibuat
typedef struct document document; //definisikan struct yang telah dibuat

void add_char(word* _word, char character) //buat prosedur baru yang menyimpan huruf
{
    static int size;

    if (_word->data == NULL)
    {
        _word->data = (char*)malloc(0);
        size = 2;
    }

    _word->data = (char*)realloc(_word->data, size * sizeof(char));
    _word->data[size - 2] = character;
    _word->data[size - 1] = 0;

    size++;
}

void add_word(sentence* _sentence, word* _word) //buat prosedur baru yang menyimpan kata
{
    if (_sentence->data == NULL)
    {
        _sentence->data = (word*)malloc(0);
        _sentence->word_count = 0;
    }

    _sentence->word_count++;
    _sentence->data = (word*)realloc(_sentence->data, _sentence->word_count * sizeof(word));
    _sentence->data[_sentence->word_count - 1] = *_word;
    _word->data = NULL;
}

void add_sentence(paragraph* _paragraph, sentence* _sentence) //buat prosedur baru yang menyimpan kalimat
{
    if (_paragraph->data == NULL)
    {
        _paragraph->data = (sentence*)malloc(0);
        _paragraph->sentence_count = 0;
    }

    _paragraph->sentence_count++;
    _paragraph->data = (sentence*)realloc(_paragraph->data, _paragraph->sentence_count * sizeof(sentence));
    _paragraph->data[_paragraph->sentence_count - 1] = *_sentence;
    _sentence->data = NULL;
}

void add_paragraph(document* _document, paragraph* _paragraph) //buat prosedur baru yang menyimpan paragraf
{
    if (_document->data == NULL)
    {
        _document->data = (paragraph*)malloc(0);
        _document->paragraph_count = 0;
    }

    _document->paragraph_count++;
    _document->data = (paragraph*)realloc(_document->data, _document->paragraph_count * sizeof(paragraph));
    _document->data[_document->paragraph_count - 1] = *_paragraph;
    _paragraph->data = NULL;
}

struct document get_document(char* text) {
    document _document;
    paragraph _paragraph;
    sentence _sentence;
    word _word;

    _document.data = NULL;
    _paragraph.data = NULL;
    _sentence.data = NULL;
    _word.data = NULL;

    int i;
    for (i = 0; i <= strlen(text); i++)
    {
        switch (text[i])
        {
        case ' ':
            add_word(&_sentence, &_word); //jika kata dipisah dengan spasi panggil add_word
            break;

        case '.':
            add_word(&_sentence, &_word); //jika kata dipisah dengan spasi panggil add_word
            add_sentence(&_paragraph, &_sentence); //jika kata dipisah dengan titik panggil add_sentence
            break;

        case '\n':
        case '\0':
            add_paragraph(&_document, &_paragraph); //jika kata dipisah dengan \n atau \0 panggil add_paragraph
            break;

        default:
            add_char(&_word, text[i]);
            break;
        }
    }

    return _document;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1]; //return dokumen berdasarkan huruf ke k pada kalimat ke m di paragraf ke n
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m - 1].data[k - 1]; //return dokumen berdasarkan kalimat ke k di paragraf ke m
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1]; //return dokumen berdasarkan paragraf ke k
}


void print_word(struct word w) {
    printf("%s", w.data); //print kata
}

void print_sentence(struct sentence sen) {
    int i;
    for(i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    int i;
    for(i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    int i;
    for(i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count, i;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}
