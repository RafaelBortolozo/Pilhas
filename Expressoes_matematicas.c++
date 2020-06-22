#include <stdlib.h>
#include <stdio.h>

typedef struct sElemento{ 
    struct sElemento *next;
    struct sElemento *prev;
    char escopo; 
} Elemento;

typedef struct sPilha{ 
    struct sElemento *head;
    struct sElemento *tail; 
    int size;
} Pilha;

Pilha *criaPilha();
void insereTexto(Pilha *pilha, char *texto);
int numCaracteres(char *texto);
void push(Pilha *pilha, char caracter);
char stacktop(Pilha *pilha);
void pop(Pilha *pilha);
void empty(Pilha *pilha);
void mostraPilha(Pilha *pilha);
void destroiPilha(Pilha *pilha);

main(){
    Pilha *pilha = criaPilha();
	
    char texto[]= "7+ {7846} +- (789{895}8) {([8498]8)4} ([{";
    insereTexto(pilha, texto);
    
    mostraPilha(pilha);
    destroiPilha(pilha);
}

Pilha *criaPilha(){
    Pilha *pilha= (Pilha*)malloc(sizeof(Pilha));
    pilha->head= NULL;
    pilha->tail= NULL;
    pilha->size= 0;
    return pilha;
}

int numCaracteres(char *texto){
    int cont;
    while(texto[cont] != '\0'){
        ++cont;
    }
    return cont;
}

void insereTexto(Pilha *pilha,char *texto){
    char aux;
    
    //verifica quantos caracteres tem a string
    int numCaracter= numCaracteres(texto);
    
    for(int i=0; i<numCaracter ; i++){ 
        switch (texto[i]){
            
            //escopos abertos eh adicionado na pilha
            case '(':
            push(pilha,'(');
            break;

            case '[':
            push(pilha,'[');
            break;

            case '{':
            push(pilha,'{');
            break;

            //escopos fechados sao analisados, eles devem ter um escopo de 
            //abertura do mesmo tipo na pilha->tail , caso contrario, encerra o algoritmo
            //informando que a expressao matematica é invalida.

            //Quando aparece a mensagem "Caracter ? excluido!" 
            //quer dizer que o pilha->tail correspondeu com o escopo fechado
            case ')':
            aux= stacktop(pilha);
            if(aux=='('){
                pop(pilha);
            }
            break;

            case ']':
            aux= stacktop(pilha);
            if(aux=='['){
                pop(pilha);
            }
            break;

            case '}':
            aux= stacktop(pilha);
            if(aux=='{'){
                pop(pilha);
            }
            break;
        }
    }
    if(pilha->size==0){
        printf("\nExpressao matematica VALIDA\n");
    } else{
        printf("\nExpressao matematica INVALIDA\n");
    }

}

void push(Pilha *pilha, char caracter){
    Elemento *novo_elemento= (Elemento*)malloc(sizeof(Elemento));
    novo_elemento->escopo= caracter;

    //se a pilha esta vazia, adiciona o primeiro escopo como head e tail da pilha
    if(pilha->size==0){    
        pilha->head=novo_elemento;
        pilha->head->prev=NULL;
        pilha->head->next=NULL;
        pilha->tail=novo_elemento;
    }else{
        Elemento *aux= pilha->tail;
        novo_elemento->next = aux->next;
	    novo_elemento->prev = aux;
        pilha->tail = novo_elemento;
        aux->next = novo_elemento;

    }
    pilha->size++;
    printf("Caracter %c adicionado!\n", novo_elemento->escopo);
}

char stacktop(Pilha *pilha){
    if((pilha->head!=NULL)and(pilha->size!=0)){
        char aux= pilha->tail->escopo;
        return aux;
    }else{
        printf("Expressao invalida, erro de Underflow!\n");
        exit(0);
    }
    
}

void pop(Pilha *pilha){
    if((pilha->head!=NULL)and(pilha->size!=0)){
        Elemento *auxDelete= pilha->tail;
        if(auxDelete== pilha->head){
            pilha->head = auxDelete->next;
            if(pilha->head==NULL){
                pilha->tail=NULL;
            }else{
                auxDelete->next->prev=NULL;
            }
        }else{
            auxDelete->prev->next = auxDelete->next;
            if(auxDelete->next==NULL){
                pilha->tail=auxDelete->prev;
            }else{
                auxDelete->next->prev = auxDelete->prev;
            }
        }

        printf("Caracter %c excluido!\n", auxDelete->escopo);
        free(auxDelete);
        pilha->size--;

    }else{
        printf("Expressao invalida, erro de Underflow!\n");
        exit(0);
    }
}

void empty(Pilha *pilha){
    bool empty;
    if(pilha->size==0){
        empty=true;
    }else{
        empty=false;
    }
    printf("\nEmpty: %s\n", empty ? "true" : "false");
}

void mostraPilha(Pilha *pilha){
    Elemento *aux2= pilha->head;

    printf("\n\nPilha: %i elementos\n", pilha->size);
    printf("Head ------------ Tail \n");

    for(int i=0; i < pilha->size; i++){
        printf("%c ",aux2->escopo);
        aux2=aux2->next;
    }
    printf("\n\n");
}

void destroiPilha(Pilha *pilha){
    //O certo seria destruir os elementos pelo tail por se tratar de uma 
    //pilha, porem, como o objetivo eh apenas liberar a memoria, utilizei 
    //o mesmo algoritmo das outras atividades que exclui pelo head.
    Elemento *auxDestroiElemento;
    if(pilha->size>0){
        while(pilha->size>0){
            auxDestroiElemento= pilha->head;
            pilha->head = auxDestroiElemento->next;
            if(pilha->head==NULL){
                pilha->tail=NULL;
            }else{
                auxDestroiElemento->next->prev=NULL;
            }
    
            printf("Caracter %c destruido!\n", auxDestroiElemento->escopo);
            free(auxDestroiElemento);
            pilha->size--;
        }
        mostraPilha(pilha);
    }
    free(pilha);
}
