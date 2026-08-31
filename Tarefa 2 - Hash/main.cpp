#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;
#define MAX 100

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
Alunos AlunosCPF[MAX];
clock_t inicio, fim;

void inicializar(){

    // a.fim = NULL;
    // a.inicio = NULL;
    // a.tamanho = 0;

    for (int i = 0; i < MAX; i++)
    {
        AlunosCPF[i].inicio = NULL;
        AlunosCPF[i].fim = NULL;
        AlunosCPF[i].tamanho = 0;
    }
    
}


void adicionarAluno(Aluno *novo){ 

    char digitoVerificador[3];

    digitoVerificador[0] = novo->cpf[12];
    digitoVerificador[1] = novo->cpf[13];
    digitoVerificador[2] = '\0';

    int indice = atoi(digitoVerificador); //Pega algarismo e diminui por '0' e tranforma em inteiro e depois multiplica por 10 e soma com o proximo algarismo e assim por diante, no final ele vai ter o numero inteiro do CPF

    printf("Indice do aluno %s - %s: %d\n", novo->cpf, novo->nome, indice);

    if (AlunosCPF[indice].inicio == NULL){ // Verifica se existe algum aluno
        AlunosCPF[indice].inicio = novo;
        AlunosCPF[indice].fim = novo;
        AlunosCPF[indice].tamanho++;
        printf("%d\n", AlunosCPF[indice].tamanho);
        return;
    }

    Aluno *temp = AlunosCPF[indice].inicio;

    while(temp != NULL){


        if(strcmp(temp->nome, novo->nome) > 0){

            if (AlunosCPF[indice].inicio == temp){
                novo->prox = temp;
                temp->ante = novo;
                a.inicio = novo;
                a.tamanho++;
                printf("%d\n", AlunosCPF[indice].tamanho);
                return;
                }   

            novo->prox = temp;
            novo->ante = temp->ante;
            novo->ante->prox = novo;
            temp->ante = novo;
            AlunosCPF[indice].tamanho++;
            printf("%d\n", AlunosCPF[indice].tamanho);
            return;
            }

        temp = temp->prox;
    }

    novo->ante = a.fim;
    novo->prox = NULL;
    AlunosCPF[indice].fim->prox = novo;
    AlunosCPF[indice].fim = novo;
    AlunosCPF[indice].tamanho++;

    printf("%d\n", AlunosCPF[indice].tamanho);

}
   
void criarAluno(){

    Aluno *temp = a.inicio;
    Aluno *novo;

    if((novo = new Aluno) != NULL){

        cin.ignore();

        printf("Digite a matricula do aluno 'Ex.:A0000000': ");
        cin.getline(novo->matricula, 9);

        printf("Digite o CPF do aluno 'Ex.:111.222.333-44': ");
        cin.getline(novo->cpf, 15);

        while(temp != NULL){

            if(strcmp(temp->cpf, novo->cpf) == 0){
                printf("Ja existe aluno com este CPF.");
                delete(novo);
                return;
            }

            if(strcmp(temp->matricula, novo->matricula) == 0){
                printf("Ja existe aluno com esta matricula.");
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
    int contador = 0;

    while ((novo = new Aluno) != NULL) {

        if (fscanf(arquivo, "%8[^,], %14[^,], %39[^,], %lf, %d, %39[^,], %39[^\n]",
            novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
                
                // Inicializar cada aluno
                novo->prox = NULL;
                novo->ante = NULL;

                adicionarAluno(novo);
                contador++;
                

                // cout << "Aluno adicionado " << novo->matricula << " - " << novo->nome << "\n"; 
                fgetc(arquivo); // Pula 1 caractere no arquivo, neste caso vai pular o \n do final da linha e o ponteiro vai estar pronto para ler a proxima no outro fscanf
        }

        else{ // Se ele não conseguir pegar todos os elementos ele deleta o aluno novo criado e sai do loop
            delete novo;
            break;
        }
    }

    fclose(arquivo);
    printf("\nTotal de alunos adicionados %d", contador);
}

void exibirAlunos(){ // A partir de agora ele vai exibir em ordem alfabetica mas de cada lista da hash

    printf("\t==ALUNOS==\n");

    Aluno *atual = AlunosCPF[0].inicio;

    for (int i = 0; i < MAX; i++) {

    

        while (atual != NULL) {

            printf("Matricula - %s\n", atual->matricula);
            printf("Nome - %s\n", atual->nome);
            printf("CPF - %s\n", atual->cpf);
            printf("Nota - %lf\n", atual->nota);
            printf("Idade - %d\n", atual->idade);
            printf("Curso - %s\n", atual->curso);
            printf("Cidade - %s\n\n", atual->cidade);

            atual = atual->prox;
        }

    printf("Total de alunos %d\n\n", a.tamanho);
    }
    
    
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

    
    inicio = time(NULL);
     
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

            fim = time(NULL);
            double tempo = difftime(fim, inicio);
            printf("\nTempo gasto para busca do aluno %.02f\n", tempo);

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

void limparLista(){ //Limpar os espaços de memória após o usuario finalizar o programa.

    Aluno *atual = a.inicio;

    while (atual != NULL){

        Aluno *proximo = atual->prox;
        delete atual;
        atual = proximo;
    }
}


int main(){

    inicializar(); // Inicializar a lista do zero
    inicio = time(NULL);

    printf("\t==SISTEMA LEITURA DE ALUNOS==\n");
    lerArquivo("alunos_incompletosV2.csv"); // ler o arquivo csv e adiciona a lista duplamente encadeada
    fim = time(NULL);

    double tempo = difftime(fim, inicio);
    printf("\nTempo gasto para leitura de arquivos %.02f\n", tempo);

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
        buscarAlunos(); // Busca dos alunos na lista encadeada 
        break;
    
    case '3':
        criarAluno(); // Cria novo aluno a partir dos dados que usuario digitar 
        break;
    case '4':
        printf("Programa finalizado."); // Finaliza programa 
        limparLista();
        break;

    default:
        printf("Nenhuma opcao selecionada.");
        break;
    }

    }


    return 0;
    
}
