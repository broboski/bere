///INCLUS�O DAS BIBLIOTECAS:

#include <stdio.h> //Bilbioteca padr�o de entrada e sa�da (printf e sanf)
#include <stdlib.h>// Comandos de controle de fluxo (system pause, system cls, system exit)
#include <string.h> //Auxilia na manipu�a��o de strings
#include <locale.h> //Permite a inclus�o e a leitura de car�cteres da l�ngua portuguesa

#define tam 100
//fun��o "define" define uma constante no c�digo.

//Declara��o das fun��es:
void menuPrincipal(), cadastros(), menuVendas(), relatorios(), ConferirCodigoProduto(), invalido(), estoqueMinimo(), informarQntProduto(), estoqueNegativo(), sangria(), cadastroClientes(), exibirClientes(), cadastroProdutos(), novaVenda();
/////////////////////////////
typedef struct {
    int numero;
    char nome[100];
    char rua[100];
    char bairro[100];
    char cpf[20];
    char celular[20];
    //float saldoCliente;
} Cliente;
Cliente *listaClientes = NULL;

typedef struct {
    int codigo;
    char descricao[100];
    char categoria[50];
    float precoCompra;
    float precoVenda;
    float margemLucro;
    int qntEstoque;
    int minEstoque;
} Produto;
Produto novoProduto;
Produto *listaProdutos = NULL;

typedef struct {
    char login[13];
    char password[9];
    int tipo; // 1 - Administrador | 2 - Usu�rio comum
} Usuario;

void cadastrarUsuario(Usuario *usuarios, int *numUsuarios);
int validarLogin(char *login);
int validarSenha(char *senha);
////////////////////////////////
/*
typedef struct{
    int codigo;
    float valor_total;
    float valor_pago;
    float valor_a_pagar;
    float valor_descontado;
    float taxa_desconto;
    char status_venda;} CAD_VENDAS;
CAD_VENDAS Vendas;
*/

///Declara��o de vari�veis globais

int quantidadeProdutos = 0, quantidadeClientes = 0, OpSelecionada, posicaoVenda, conferirValor = 0, i, produtoSelecionado, caixaAberto = 0, op, opCadastro;

float valor_em_caixa, faturamento;

char simounao;

///Declara��o dos ponteiros

 int *pos_venda = &posicaoVenda;

//------------------------------------------------------------
int main(){
    setlocale(LC_ALL,"portuguese");
    cadastrarUsuario(Usuario *usuarios, int *numUsuarios);
    system("cls");
    relatorios();
    menuPrincipal();
    /*free(listaClientes);
    free(listaProdutos);
    return 0;*/
}

//////////
void menuPrincipal(){
    printf("   --== Menu Principal ==--\n");
    printf("\n    1. Cadrastros");
    printf("\n    2. Vendas");
    printf("\n    3. Abertura de Caixa");
    printf("\n    4. Fechamento de Caixa");
    printf("\n    5. Relatorios");
    printf("\n    6. Sangria\n\n");
    printf("Digite a operacao desejada: ");
    scanf("%d", &op);

    system("clear || cls");

    switch(op){
    case 1:
        cadastros(&listaClientes, &quantidadeClientes, &listaProdutos, &quantidadeProdutos);
        break;
    case 2:
        menuVendas();
        break;
    case 3:
        //abreCaixa();
        break;
    case 4:
        //fechaCaixa();
        break;
    case 5:
        break;
    case 6:
        sangria();
        break;
}
}
void cadastros(Cliente **clientes, int *quantidadeClientes, Produto **produtos, int *quantidadeProdutos) {

    system("cls");

    do {
        printf("--== CADASTROS ==--\n");
        printf("\n 1. Cadastro de Clientes\n");
        printf(" 2. Exibir Clientes Cadastrados\n");
        printf(" 3. Cadastro de Produtos\n");
        printf(" 0. Retornar ao Menu Principal\n\n");
        printf("Digite a operacao desejada: ");
        scanf(" %d", &opCadastro);
        getchar();
        system("cls");

        switch (opCadastro) {
            case 1:
                cadastroClientes(clientes, quantidadeClientes);
                break;
            case 2:
                exibirClientes(*clientes, *quantidadeClientes);
                break;
            case 3:
                cadastroProdutos(produtos, quantidadeProdutos);
                break;
            case 0:
                return;
            default:
                printf("\n\nOpcao invalida! Tente novamente.\n\n");
                system("pause");
                system("cls");
        }
    } while (opCadastro != 0);
}

void cadastroClientes(Cliente **clientes, int *quantidadeClientes) {

    printf("   ...::: Cadastro de Clientes :::...\n\n");

    if (*quantidadeClientes % tam == 0) {

        *clientes = realloc(*clientes, (*quantidadeClientes + tam) * sizeof(Cliente));
        if (*clientes == NULL) {
            printf("\n\nErro ao alocar mem�ria.\n");
            system("pause");
            system("cls");
            exit(1);
        }
    }

    Cliente novoCliente;

    printf("Digite o nome do cliente: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    printf("Digite o CPF do cliente (somente numeros): ");
    fgets(novoCliente.cpf, sizeof(novoCliente.cpf), stdin);
    novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = '\0';

    printf("Digite a rua do cliente: ");
    fgets(novoCliente.rua, sizeof(novoCliente.rua), stdin);
    novoCliente.rua[strcspn(novoCliente.rua, "\n")] = '\0';

    printf("Digite o numero da casa do cliente: ");
    scanf("%d", &novoCliente.numero);
    getchar();

    printf("Digite o bairro do cliente: ");
    fgets(novoCliente.bairro, sizeof(novoCliente.bairro), stdin);
    novoCliente.bairro[strcspn(novoCliente.bairro, "\n")] = '\0';

    printf("Digite o celular do cliente (somente numeros): ");
    fgets(novoCliente.celular, sizeof(novoCliente.celular), stdin);
    novoCliente.celular[strcspn(novoCliente.celular, "\n")] = '\0';

    (*clientes)[*quantidadeClientes] = novoCliente;
    (*quantidadeClientes)++;
}

void exibirClientes(Cliente *clientes, int quantidadeClientes) {
    if (quantidadeClientes == 0) {
        printf("\n\nNenhum cliente cadastrado.\n\n");
        system("pause");
        system("cls");
            } else {
        printf("...::: Clientes Cadastrados :::...\n");
        for (int i = 0; i < quantidadeClientes; i++) {
            printf("\nCliente %d\n", i + 1);
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Rua: %s\n", clientes[i].rua);
            printf("Numero: %d\n", clientes[i].numero);
            printf("Bairro: %s\n", clientes[i].bairro);
            printf("Celular: %s\n", clientes[i].celular);
            //printf("Saldo na conta: %f", clientes[i].saldoCliente);
            printf("----------------------------------\n\n");
        }
        system("pause");
        system("cls");
    }
}

void cadastroProdutos(Produto **produtos, int *quantidadeProdutos){

    printf("   ...::: Cadastro de Produtos :::...\n\n");

    if (*quantidadeProdutos % tam == 0) {

        *produtos = realloc(*produtos, (*quantidadeProdutos + tam) * sizeof(Produto));
        if (*produtos == NULL) {
            printf("\n\nErro ao alocar mem�ria.\n\n");
            system("pause");
            system("cls");
            exit(1);
        }
    }

    Produto novoProduto;

    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigo);
    getchar();

    printf("Digite a descricao do produto: ");
    fgets(novoProduto.descricao, sizeof(novoProduto.descricao), stdin);
    novoProduto.descricao[strcspn(novoProduto.descricao, "\n")] = '\0';

    printf("Digite a categoria do produto: ");
    fgets(novoProduto.categoria, sizeof(novoProduto.categoria), stdin);
    novoProduto.categoria[strcspn(novoProduto.categoria, "\n")] = '\0';

    printf("Digite o preco de Venda: ");
    scanf("%f", &novoProduto.precoVenda);
    getchar();

    printf("Digite a quantidade em Estoque do produto: ");
    scanf("%d", &novoProduto.qntEstoque);
    getchar();

    printf("\nCodigo do Produto: %d\n", novoProduto.codigo);
    printf("Nome do Produto: %s\n", novoProduto.descricao);
    printf("Categoria do Produto: %s\n", novoProduto.categoria);
    printf("Preco do Produto: R$%f\n", novoProduto.precoVenda);
    printf("Quantidade em Estoque do Produto: %d\n", novoProduto.qntEstoque);

    system("pause");

    (*produtos)[*quantidadeProdutos] = novoProduto;
    (*quantidadeProdutos)++;

}
////////////

void menuVendas(){

    if(caixaAberto == 0){
        printf("N�o � poss�vel registrar uma nova venda com o caixa fechado. \n");
        printf("V� para o menu principal --> abrir caixa , em seguida, efetue a abertura do caixa e registre sua nova venda.");
        main();
    }relatorios();
    printf("1 Nova venda\n2 Retirada de Caixa (Sangria)\n3 Pagamento\n4 Retornar ao Menu Principal\n");
    scanf("%d", &op);
    switch(op){
        case 1:
        novaVenda();
        break;
        case 2:
        sangria();
        break;
        case 3:
        menuPagamento();
        break;
        case 4:
        menuPrincipal();
        break;
    }
}

void novaVenda(){
       printf("C�DIGO \t NOME \t CATEGORIA \t PRE�O \t ESTOQUE");

       for(i=0; i<quantidadeProdutos; i++){//estrutura de repeti��o imprimide todos os produtos cadastrados

            printf("%d \t %s \t %s \t R$%.2f \t %d \n", novoProduto[i].codigo, novoProduto[i].descricao, novoProduto[i].categoria, novoProduto[i].precoVenda, novoProduto[i].qntEstoque);
            }

        printf("\n\nDigite o c�digo do produto desejado:  ");
        scanf("%d", &OpSelecionada);

        ConferirCodigoProduto(); //fun��o confere se o valor informado pelo usu�rio corresponde ao c�digo de algum produto


        if(conferirValor==0){invalido(); menuVendas();}

        if(novoProduto[produtoSelecionado].estoque <= novoProduto[produtoSelecionado].estoque_minimo){estoqueMinimo();}
        //se o estoque atual do produto for menor ou igual ao estoque m�nimo, � chamada uma nova fun��o para confirmar a venda do produto
        else{informarQntProduto();}
}
void estoqueMinimo(){

    printf("O produto selecionado foi: %s. O estoque minimo do produto foi atingido.\n", novoProduto[produtoSelecionado].nome);

    printf("Estoque atual: %d\n", novoProduto[produtoSelecionado].estoque);
    printf("Estoque minimo:%d\n", novoProduto[produtoSelecionado].estoque_minimo);

    printf("\nDeseja vender esse produto?\n Digite 's' para sim ou 'n' para n�o:  ");
    scanf("%c", &simounao);
    fflush(stdin);

    if(simounao != 's' && simounao != 'S' && simounao != 'n' && simounao != 'N'){ //caso o valor informado pelo usu�rio n�o seja 'n' nem 's',
    invalido();                                                                   //o sistema informa valor inv�lido e pergunta ao usu�rio novamente.
    estoqueMinimo();}

    if(simounao == 'N' || simounao == 'n'){
    printf("Venda deste produto cancelada. Retornando ao menu de compras...\n\n");
    system("pause");
    menuVendas();}

    if(simounao == 's' || simounao == 'S'){informarQntProduto();}}

void informarQntProduto(){

 int qtd;

    system("cls");
    relatorios();

    printf("Produto selecionado: %s\n Pre�o: R$%.2f\n", novoProduto[produtoSelecionado].nome, novoProduto[produtoSelecionado].preco_venda);
    printf("\nQuantas unidades deste produto deseja vender?");
    scanf("%d", &qtd);
    fflush(stdin);

    if(qtd<0){invalido(); informarQntProduto();}
    if(qtd>novoProduto[produtoSelecionado].estoque){estoqueNegativo();}//caso a quantidade de unidades do produto a ser vendida seja maior
                                                                   //do que o estoque atual do produto, ser� chamada uma nova fun��o.

    //imprimir_carrinho();
    system("pause");












}

void cadastrarUsuario(Usuario *usuarios, int *numUsuarios) {
    printf("\n=== Cadastro de Usu�rios ===\n");

    if (*numUsuarios >= 100) {
        printf("N�mero m�ximo de usu�rios cadastrados atingido.\n");
        return;
    }

    printf("Digite o login do usu�rio (entre 8 e 12 caracteres): ");
    char login[13];
    scanf("%s", login);

    // Validar tamanho do login
    if (!validarLogin(login)) {
        printf("Login inv�lido. O login deve ter entre 8 e 12 caracteres.\n");
        return;
    }

    printf("Digite a senha do usu�rio (entre 6 e 8 caracteres): ");
    char senha[9];
    scanf("%s", senha);

    // Validar tamanho da senha
    if (!validarSenha(senha)) {
        printf("Senha inv�lida. A senha deve ter entre 6 e 8 caracteres.\n");
        return;
    }

    // Cadastro do tipo de usu�rio
    int tipo;
    printf("Digite o tipo do usu�rio (1 - Administrador, 2 - Usu�rio comum): ");
    scanf("%d", &tipo);
    if (tipo != 1 && tipo != 2) {
        printf("Tipo de usu�rio inv�lido.\n");
        return;
    }

    // Adicionar usu�rio ao array de usu�rios
    strcpy(usuarios[*numUsuarios].login, login);
    strcpy(usuarios[*numUsuarios].password, senha);
    usuarios[*numUsuarios].tipo = tipo;

    (*numUsuarios)++; // Incrementa o contador de usu�rios cadastrados

    int validarLogin(char *login) {
        int len = strlen(login);
        return (len >= 8 && len <= 12);
    }

    int validarSenha(char *senha) {
        int len = strlen(senha);
        return (len >= 6 && len <= 8);
    }

    printf("Usu�rio cadastrado com sucesso.\n");
}



































void ConferirCodigoProduto(){ //fun��o compara o valor informado pelo usu�rio com o c�digo de todos os produtos cadastrados.

    conferirValor = 0;
    for(i=0; i<quantidadeProdutos; i++){
        if(OpSelecionada == novoProduto[i].codigo){conferirValor = 1; produtoSelecionado = i;}
    }

    //Desse modo, caso o n�mero digitado pelo usu�rio n�o corresponder ao c�digo de nenhum dos produtos,
    // a vari�vel "conferirValor" permanecer� 0. Do contr�rio, ela passar� a ter o valor 1

   //Al�m disso, a vari�vel "produtoSelecionado" ir� guardar a posi��o da struct que corresponde ao c�digo do produto que o usu�rio selecionou.
}






void relatorios(){printf("     MERCEARIA DA DONA BER�\n_____________________________________\n\n");}

void invalido(){
    printf("\n O VALOR INSERIDO � INV�LIDO! TENTE NOVAMENTE");
    system("pause");
}


void sangria(){

    system("cls");
    relatorios();
    printf("Sangria\n_____________________________________\n\n");

    printf("Valor em caixa: R$");




}


