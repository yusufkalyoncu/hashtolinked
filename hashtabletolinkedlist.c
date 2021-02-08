#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cell {
    char *anahtar;
    struct cell *next;
};
int lookup(char *anahtar, struct cell *l){
    if(l==NULL) return 0;
    else if(!strcmp(anahtar,l->anahtar)) return 1;
    else return lookup(anahtar,l->next);
}

int insert(char *anahtar, struct cell **l){
    if(*l==NULL){
        *l=(struct cell*)malloc(sizeof(struct cell));
        (*l)->anahtar=(char*)malloc((strlen(anahtar)+1)*sizeof(char));
        strcpy((*l)->anahtar,anahtar);
        (*l)->next=NULL;
        return 1;
    }
    else if(strcmp(anahtar,(*l)->anahtar)) 
        return insert(anahtar, &((*l)->next));
    else return 0;
}

void print_list(struct cell *l){
    if(l!=NULL){
        printf("%s ", l->anahtar);
        print_list(l->next);
    }
    
}


struct table_node{
    int count;
    struct cell *header;
};

struct hash_tablosu{
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

unsigned hash(char *anahtar, int multiplier, int table_size){
    int i=0;
    unsigned int value=0;
    while(anahtar[i]){
        value = (anahtar[i]+multiplier*value)% table_size;
        i++;
    }
    return value;
}

void initialize_hash_table(struct hash_tablosu **hash_table, 
        int multiplier, int table_size){
    int i;
    *hash_table=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
   if(*hash_table==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
   }    
    (*hash_table)->tablo_basi=
       (struct table_node *)malloc(table_size*sizeof(struct table_node));
    if((*hash_table)->tablo_basi==NULL){
       printf(" Hash tablosu icin yer ayrilamnadi... Hata!!!");
       exit(1);
    }
    (*hash_table)->tablo_uzunlugu= table_size;
    (*hash_table)->multiplier= multiplier;
    
    for(i=0; i<table_size; i++){
        ((*hash_table)->tablo_basi+i)->count = 0;
        ((*hash_table)->tablo_basi+i)->header = NULL;
    }
}

void insert_hash_table(struct hash_tablosu *hash_table,
        char *anahtar){
    int hash_index = hash(anahtar, hash_table->multiplier,
            hash_table->tablo_uzunlugu);
    if(insert(anahtar,&((hash_table->tablo_basi +hash_index)->header)))
     (hash_table->tablo_basi +hash_index)->count++;
}

void print_hash_table(struct hash_tablosu *hash_table){
    if(hash_table){
        int index;
        printf("----- HASH TABLOSU -----\n");
        for(index=0; index<hash_table->tablo_uzunlugu; index++){
            printf("%5d : (%2d) ",index,(hash_table->tablo_basi +index)->count);
          //  printf("%5d : (%2d) ",index,hash_table->tablo_basi[index].counter);
            print_list((hash_table->tablo_basi+index)->header);
            printf("\n");
        }
    }
    else printf("Hash Tablosu Bos ...\n"); 
    
}

void listeye_donusturme(struct hash_tablosu *htable, struct cell **liste_basi){
	int i;
	for(i=0;i<(htable->tablo_uzunlugu);i++){
		if(((htable->tablo_basi)+i)->header!=NULL){
			if(*liste_basi==NULL){
				*liste_basi = ((htable->tablo_basi)+i)->header;
				((htable->tablo_basi)+i)->header = NULL;
				((htable->tablo_basi)+i)->count = 0;
			}
			else{
				struct cell *tmp = *liste_basi;
				while(tmp->next!=NULL){
					tmp=tmp->next;
				}
				tmp->next = ((htable->tablo_basi)+i)->header;
				((htable->tablo_basi)+i)->header = NULL;
				((htable->tablo_basi)+i)->count = 0;		
			}
		}
	}
}


void liste_yaz(struct cell *liste_basi){
    while(liste_basi!=NULL){
        printf(liste_basi->anahtar);
        printf(" -> ");
        liste_basi=liste_basi->next;
    }
    printf("NULL");
    printf("\n");
}


int main(int argc, char** argv) {
    struct hash_tablosu *htable=NULL;
    
    initialize_hash_table(&htable,3,5);
    insert_hash_table(htable,"MRX");
    insert_hash_table(htable,"Erzincan");
    insert_hash_table(htable,"Canakkale");
    insert_hash_table(htable,"Istanbul");
    insert_hash_table(htable,"Sakarya");
    insert_hash_table(htable,"Rize");
    insert_hash_table(htable,"Bursa");
    insert_hash_table(htable,"Bilecik");
    insert_hash_table(htable,"Edirne");
    insert_hash_table(htable,"Kastamonu");
    print_hash_table(htable);
    printf("\n");
	struct cell *hashtolist = NULL;
	printf("%s",hashtolist);
	printf("\n");
	listeye_donusturme(htable,&hashtolist);
	printf("\n");
	print_hash_table(htable);
	printf("\n");
	liste_yaz(hashtolist);
	
    return (EXIT_SUCCESS);
}


