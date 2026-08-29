#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
//PARA COMPILAR UTILIZE CTRL+SHIFT+B

// Objetivo: Inserir 4 alunos na lista duplamente encadeada e fazer uma função listar onde ele lista do primeiro para o ultimo e do ultimo para o primeiro


struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *prox;
    Aluno *ante;
};


struct Alunos{
    Aluno *inicio;
    Aluno *fim;
    int tamanho;
};


Alunos a;

void inicializar(){
    a.inicio = NULL;
    a.fim = NULL;
    a.tamanho = 0;
}


void adicionarAluno(Aluno *novo){ 


    if (a.inicio == NULL) { // Verifica se existe algum aluno
        a.inicio = novo;
        a.fim = novo;
        return;
    }

    Aluno *temp = a.inicio;

    while(temp != NULL){


        if(strcmp(temp->nome, novo->nome) > 0){

            if (a.inicio == temp){
                novo->prox = temp;
                temp->ante = novo;
                a.inicio = novo;
                a.tamanho++;
                return;
                }   

            novo->prox = temp;
            novo->ante = temp->ante;
            novo->ante->prox = novo;
            temp->ante = novo;
            a.tamanho++;
            return;
            }

        temp = temp->prox;
    }

    novo->ante = a.fim;
    novo->prox = NULL;
    a.fim->prox = novo;
    a.fim = novo;
    a.tamanho++;

}
   
void criarAluno(){

    Aluno *temp = a.inicio;
    Aluno *novo;

    if((novo = new Aluno) != NULL){

        printf("Digite a matricula do aluno 'Ex.:A0000000': ");
        cin.getline(novo->matricula, 9);
        while(temp != NULL){
            if(strcmp(temp->matricula, novo->matricula) == 0){
                printf("Ja existe aluno com esta matricula.");
                delete(novo);
                return;
            }
            temp = temp->prox;
        }

        temp = a.inicio;

        printf("Digite o CPF do aluno 'Ex.:111.222.333-44': ");
        cin.getline(novo->cpf, 15);
        while(temp != NULL){
            if(strcmp(temp->cpf, novo->cpf) == 0){
                printf("Ja existe aluno com este CPF.");
                delete(novo);
                return;
            }
            temp = temp->prox;
        }

        printf("Digite o nome do aluno 'Joao Carlos': ");
        cin.getline(novo->nome, 40);

        printf("Digite a nota do aluno 'Ex.:55.7': ");
        cin >> novo->nota;

        printf("Digite a idade do aluno 'Ex.:25': ");
        cin >> novo->idade;

        cin.ignore(10000, '\n');

        printf("Digite o curso do aluno 'Ex.:Sistema de informacao': ");
        cin.getline(novo->curso, 40); 

        printf("Digite a cidade do aluno 'Ex.:Colatina': ");
        cin.getline(novo->cidade, 40);  
        
    }

    novo->ante = NULL;
    novo->prox = NULL;

    adicionarAluno(novo);

}

void lerArquivo(const char *nome_arquivo){

    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        cout << "Arquivo inexistente.\n";
        return;
    }

    char linha[300];

    if (fgets(linha, sizeof(linha), arquivo) == NULL){
        cout << "Arquivo vazio\n";
        return;
    }

    Aluno *novo;

    while ((novo = new Aluno) != NULL) {

        if (fscanf(arquivo, "%8[^,], %14[^,], %39[^,], %lf, %d, %39[^,], %39[^\n]",
            novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
                
                // Inicializar cada aluno
                novo->prox = NULL;
                novo->ante = NULL;

                adicionarAluno(novo);

                cout << "Aluno adicionado " << novo->matricula << " - " << novo->nome << "\n"; 
                fgetc(arquivo); // Pula 1 caractere no arquivo, neste caso vai pular o \n do final da linha e o ponteiro vai estar pronto para ler a proxima no outro fscanf
        }

        else{ // Se ele não conseguir pegar todos os elementos ele deleta o aluno novo criado e sai do loop
            delete novo;
            break;
        }
    }

    fclose(arquivo);
    printf("Leitura concluida. Total de alunos %d\n", a.tamanho);

}

void exibirAlunos(){

    printf("\t==ALUNOS==\n");
    Aluno *atual = a.inicio;;
    int contador = 0;

    while (atual != NULL) {

        printf("Matricula - %s\n", atual->matricula);
        printf("Nome - %s\n", atual->nome);
        printf("CPF - %s\n", atual->cpf);
        printf("Nota - %lf\n", atual->nota);
        printf("Idade - %d\n", atual->idade);
        printf("Curso - %s\n", atual->curso);
        printf("Cidade - %s\n\n", atual->cidade);

        atual = atual->prox;
        contador ++;
    }

    printf("Total de alunos %d\n\n", contador);
}

void removerAluno(Aluno *alunoRemover){

    if(a.inicio == alunoRemover && a.fim == alunoRemover){
        a.inicio = NULL;
        a.fim = NULL;
    }
    else if (a.inicio == alunoRemover){
        alunoRemover->prox->ante = NULL;
        a.inicio = alunoRemover->prox;
    }
    else if(a.fim == alunoRemover){
        alunoRemover->ante->prox = NULL;
        a.fim = alunoRemover->ante;
    }
    else{
        alunoRemover->ante->prox = alunoRemover->prox;
        alunoRemover->prox->ante = alunoRemover->ante;
    }

    delete(alunoRemover);
    a.tamanho--;
    printf("\n\nAluno removido.\n\n");
} 



void buscarAlunos(){
    
    Aluno *atual = a.inicio;
    char op;
    char atualCPF[15];
    char atualMatricula[9];
    int encontrado = 0;
    

    printf("\nBuscar por\n 1 - Matricula\n 2 - CPF\n");
    cin >> op;

    if (op == '1'){
        printf("Digite a matricula 'Ex.:A0000000'\n");
        cin >> atualMatricula;
    }

    else if (op == '2'){
        printf("Digite o CPF 'Ex.:111.222.333-44'\n");
        cin >> atualCPF;
    }

    else{
        printf("Opcao inválida.");
        return;
    }
     
    while(atual != NULL){

        if (op == '1' && (strcmp(atual->matricula, atualMatricula) == 0)){
            encontrado = 1;
        }

        if (op == '2' && (strcmp(atual->cpf, atualCPF) == 0)){
            encontrado = 1;
        }

        if (encontrado == 1){

            printf("\n\nALUNO ENCONTRADO\n\n");

            printf("Matricula - %s\n", atual->matricula);
            printf("Nome - %s\n", atual->nome);
            printf("CPF - %s\n", atual->cpf);
            printf("Nota - %lf\n", atual->nota);
            printf("Idade - %d\n", atual->idade);
            printf("Curso - %s\n", atual->curso);
            printf("Cidade - %s\n\n\n", atual->cidade);
            printf("Deseja remover este aluno? (S/N)\n");
            cin >> op;
            

            if (tolower(op) == 's'){
                removerAluno(atual);
            }

            return;
        }

        atual = atual->prox;  

    }
    printf("Aluno nao encontrado.");

}


int main(){

    inicializar(); // Inicializar a lista do zero
    printf("\t==SISTEMA LEITURA DE ALUNOS==\n");
    lerArquivo("C:/Users/Leandro/Desktop/TPA/exemplo0807/alunos_completosV2.csv"); // ler o arquivo csv e adiciona a lista duplamente encadeada
    
    char op = ' ';

    while(op != '4'){
        
    printf("\nDigite uma opcao\n1 - Exibir Alunos\n2 - Buscar Aluno\n3 - Inserir novo aluno\n4 - Sair\n");
    cin >> op;

    switch (op)
    {
    case '1':
        exibirAlunos(); // Exibe todos os alunos 
        break;
    
    case '2':
        buscarAlunos(); // Exibe todos os alunos 
        break;
    
    case '3':
        criarAluno(); // Exibe todos os alunos 
        break;
    case '4':
        printf("Programa finalizado."); // Exibe todos os alunos 
        break;

    default:
        printf("Nenhuma opcao selecionada.");
        break;
    }

    }


    return 0;
    
}