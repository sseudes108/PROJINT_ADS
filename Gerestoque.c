/*
GerarRelatório(){Apontar maior e menor quantidades em estoque. Mostrar últimas movimentações dos produtos};
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DesenharLinha();
void InitProdutos();

void MainMenu();
void TrocarMenu(int);
void MenuEspera(int);

void CadastrarProduto();
void AtualizarEstoque();
void LocalizarProduto();
void GerarRelatório();
void AtualizarHistorico();
void UltimasMovimentacoes();
void MenorMaiorQuantidade();

void MostrarTodos();
void InfoProduto(int);

struct Local{
    int Linha;
    int Coluna;
    int Andar;
};
struct Produto{
    int ID;
    char Nome[27];
    int Categoria;
    int QuantidadeEstoque;
    float Preco;
    struct Local Localizacao;
};
struct Historico{
    int IDMovimentado;
    int quantidadeAlterada;
};

#define MaxProdutos 108
struct Produto Produtos[MaxProdutos];
struct Historico History[MaxProdutos];
int IDMovimentacao;

int main(){
    InitProdutos();

    MostrarTodos();
    MainMenu();
    
    return 0;
}

//Helper
void DesenharLinha(){
    for(int i = 0; i < 54; i++){
        printf("*");
        if(i == 53) printf("\n");
    };
}

void InitProdutos(){
    IDMovimentacao = 0;
    for(int i = 0; i < MaxProdutos/4; i++){
        History[i].IDMovimentado = 0;
        History[i].quantidadeAlterada = 0;

        char nome[27];

        int magicNumber = i%2;
        int randNum = rand() % 3;
        int randQuant = rand() % 72;

        int randLinha = rand() % 11;
        int randColuna = rand() % 9;
        int randAndar = rand() % 10;
        
        Produtos[i].ID = i+1;

        sprintf(nome, "produto%d", Produtos[i].ID);
        strcpy(Produtos[i].Nome, nome);

        Produtos[i].Categoria = (magicNumber + 1); //1 or 2

        Produtos[i].QuantidadeEstoque = randQuant;
        
        Produtos[i].Preco = i + ( 27 * 0.09 );

        Produtos[i].Localizacao.Linha = (randLinha);
        Produtos[i].Localizacao.Coluna = (randColuna);
        Produtos[i].Localizacao.Andar = (randAndar);

        AtualizarHistorico(Produtos[i].ID, Produtos[i].QuantidadeEstoque);
    }
}

void MostrarTodos(){
    for(int i = 0; i < MaxProdutos; i++){
        if(Produtos[i].ID == 0){
            break;
        }else{
            InfoProduto(i + 1);
        }
    }
}

void InfoProduto(int id){
    id -= 1;
    printf("ID : %d\n", Produtos[id].ID);
    printf("Nome : %s\n", Produtos[id].Nome);
    printf("Categoria : %d\n", Produtos[id].Categoria);
    printf("QuantidadeEstoque : %d\n", Produtos[id].QuantidadeEstoque);
    printf("Preco : %f\n", Produtos[id].Preco);
    printf("Linha %d, Coluna %d, Andar %d\n", Produtos[id].Localizacao.Linha, Produtos[id].Localizacao.Coluna, Produtos[id].Localizacao.Andar);
    printf("\n");
}


//Menus
void MainMenu(){
    int escolha;
    DesenharLinha();
    printf("* ***** Gerestoque ****** *\n");
    printf("\n");
    printf("*  1 - Cadastrar Produto  *\n");
    printf("*  2 - Atualizar Estoque  *\n");
    printf("*  3 - Localizar Produto  *\n");
    printf("*  4 - Gerar Relatorios   *\n");
    printf("*  Ctrl + C - Sair        *\n");
    DesenharLinha();

    printf("\n");
    printf("Digite a opção desejada\n");
    scanf("%d", &escolha);

    TrocarMenu(escolha);
}

void TrocarMenu(int menuID){
    switch (menuID){
        case 0:
            MainMenu();
        break;

        case 1:
            CadastrarProduto();
        break;

        case 2:
            AtualizarEstoque();
        break;

        case 3:
            LocalizarProduto();
        break;

        case 4:
            GerarRelatório();
        break;
    }
}

void MenuEspera(int menuID){
    int escolha;
    
    switch (menuID){
        case 1:
            printf("* 1 para Cadastrar um novo produto  *\n");
        break;

        case 2:
            printf("* 2 para atualizar mais um produto  *\n");
        break;

        case 3:
            printf("* 3 para buscar novamente *\n");
        break;

        default:
        break;
    }

    printf("* 0 - para retornar ao menu principal *\n");
    printf("* Ctrl+C para sair                    *\n");
    scanf("%d", &escolha);

    if(escolha == menuID) { TrocarMenu(menuID); }
    if(escolha == 0){ TrocarMenu(0); }
}


//Metodos funcionais
void CadastrarProduto(){
    int prodID;
    DesenharLinha();

    for(int i = 0; i < MaxProdutos; i++){
        if(Produtos[i].ID != 0){
           continue;
        }else{
            prodID = i;
            Produtos[i].ID = prodID +1;
            break;
        }
    }

    //Nome
    char prodNome[28];
    printf("\n");
    printf("Qual o nome?\n");
    scanf("%27s", prodNome);
    strcpy(Produtos[prodID].Nome, prodNome);

    //Categoria
    int prodCat;
    printf("\n");
    printf("Qual a categoria?\n");
    printf("Categoria 1\n");
    printf("Categoria 2\n");
    printf("Categoria 3\n");
    printf("\n");
    scanf("%d", &prodCat);

    Produtos[prodID].Categoria = prodCat;

    //Quantidade
    int prodQuant;
    printf("\n");
    printf("Qual a quantidade\n");
    scanf("%d", &prodQuant);

    Produtos[prodID].QuantidadeEstoque = prodQuant;

    //Preco
    float prodPreco;
    printf("\n");
    printf("Qual o Preco?\n");
    scanf("%f", &prodPreco);

    Produtos[prodID].Preco = prodPreco;

    //Local
    int randLinha = rand() % 11;
    int randColuna = rand() % 9;
    int randAndar = rand() % 10;

    Produtos[prodID].Localizacao.Linha = randLinha;
    Produtos[prodID].Localizacao.Coluna = randColuna;
    Produtos[prodID].Localizacao.Andar = randAndar;

    AtualizarEstoque(Produtos[prodID].ID, Produtos[prodID].QuantidadeEstoque);

    printf("\n");
    printf("Produto Cadastrado com sucesso\n");
    printf("ID: %d\n", Produtos[prodID - 1].ID);
    printf("Categoria: %d\n", Produtos[prodID - 1].Categoria);
    printf("Quantidade em Estoque: %d\n", Produtos[prodID - 1].QuantidadeEstoque);
    printf("Preco: %.2f\n", Produtos[prodID - 1].Preco);
    printf("Localizacao: Linha: %d, Coluna: %d, Andar: %d\n", Produtos[prodID - 1].Localizacao.Linha, Produtos[prodID - 1].Localizacao.Coluna, Produtos[prodID - 1].Localizacao.Andar);

    printf("\n");
    MostrarTodos();

    MenuEspera(1);
}

void LocalizarProduto(){
    int id;

    DesenharLinha();
    printf("Qual o ID do produto?");

    printf("\n\n");

    printf("* 0 - para retonrar\n\n");
    DesenharLinha();
    scanf("%d", &id);

    if(id != 0){
        for(int i = 0; i < 99; i++){
            printf("ID: %d, Quantidade: %d\n", i, Produtos[i].QuantidadeEstoque);
            if(Produtos[i].ID == id){

                int escolha;
                printf("\n");
                InfoProduto(i);

                printf("\n");
                DesenharLinha();

                MenuEspera(3);

                break;
            }
        }
    }else{
        TrocarMenu(0);
    }
}

void AtualizarEstoque(){
    int id;
    printf("\nQual o ID do produto?");
    scanf("%d", &id);

    int quant;
    printf("\nQual a quantidade a ser adicionada?");
    scanf("%d", &quant);

    Produtos[id - 1].QuantidadeEstoque += quant;

    AtualizarHistorico(Produtos[id - 1].ID, quant);

    printf("\nNova quantidade em estoque: %d\n", Produtos[id - 1].QuantidadeEstoque);
    InfoProduto(id);

    MenuEspera(2);
}

void GerarRelatório(){
    MenorMaiorQuantidade();
    UltimasMovimentacoes();
    
    MenuEspera(4);
}

void MenorMaiorQuantidade(){
    int menorQuant = -1;
    int menorQuantID = -1;

    int maiorQuant = -1;
    int maiorQuantID = -1;

    for(int i = 0; i < MaxProdutos; i++){
        if(Produtos[i].ID != 0){
            if(menorQuant == -1 || maiorQuant == -1){
                menorQuant = Produtos[i].QuantidadeEstoque;
                maiorQuant = Produtos[i].QuantidadeEstoque;
                menorQuantID = Produtos[i].ID;
                maiorQuantID = Produtos[i].ID;
            }

            if(Produtos[i].QuantidadeEstoque < menorQuant){
                menorQuant = Produtos[i].QuantidadeEstoque;
                menorQuantID = Produtos[i].ID;
            }

            if(Produtos[i].QuantidadeEstoque > maiorQuant){
                maiorQuant = Produtos[i].QuantidadeEstoque;
                maiorQuantID = Produtos[i].ID;
            }
        }
    }

    printf("\n*** Menor Quantidade ***\n");
    InfoProduto(menorQuantID);

    printf("\n*** Maior Quantidade ***\n");
    InfoProduto(maiorQuantID);
}

void UltimasMovimentacoes(){
    DesenharLinha();
    printf("***** Ultimas Movimentacoes *****\n");
    DesenharLinha();

    for (int i = 0; i < MaxProdutos; i++){
        if(History[i].IDMovimentado != 0){
            InfoProduto(History[i].IDMovimentado);
            printf("Quantidade Alterada %d", History[i].quantidadeAlterada);

            printf("\n");
            DesenharLinha();
        }
    }
}

void AtualizarHistorico(int idMovimentado, int qtdAlterada){
    History[IDMovimentacao].IDMovimentado = idMovimentado;
    History[IDMovimentacao].quantidadeAlterada = qtdAlterada;
    IDMovimentacao++;
}