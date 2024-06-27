///INCLUSÃO DAS BIBLIOTECAS:

#include <stdio.h> //Bilbioteca padrão de entrada e saída (printf e sanf)
#include <stdlib.h>// Comandos de controle de fluxo (system pause, system cls, system exit)
#include <string.h> //Auxilia na manipuçação de strings
#include <locale.h> //Permite a inclusão e a leitura de carácteres da língua portuguesa

#define tam 100
//função "define" define uma constante no código.

//Declaração das funções:
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
    int tipo; // 1 - Administrador | 2 - Usuário comum
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

///Declaração de variáveis globais

int quantidadeProdutos = 0, quantidadeClientes = 0, OpSelecionada, posicaoVenda, conferirValor = 0, i, produtoSelecionado, caixaAberto = 0, op, opCadastro;

float valor_em_caixa, faturamento;

char simounao;

///Declaração dos ponteiros

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
            printf("\n\nErro ao alocar memória.\n");
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
            printf("\n\nErro ao alocar memória.\n\n");
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
        printf("Não é possível registrar uma nova venda com o caixa fechado. \n");
        printf("Vá para o menu principal --> abrir caixa , em seguida, efetue a abertura do caixa e registre sua nova venda.");
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
       printf("CÓDIGO \t NOME \t CATEGORIA \t PREÇO \t ESTOQUE");

       for(i=0; i<quantidadeProdutos; i++){//estrutura de repetição imprimide todos os produtos cadastrados

            printf("%d \t %s \t %s \t R$%.2f \t %d \n", novoProduto[i].codigo, novoProduto[i].descricao, novoProduto[i].categoria, novoProduto[i].precoVenda, novoProduto[i].qntEstoque);
            }

        printf("\n\nDigite o código do produto desejado:  ");
        scanf("%d", &OpSelecionada);

        ConferirCodigoProduto(); //função confere se o valor informado pelo usuário corresponde ao código de algum produto


        if(conferirValor==0){invalido(); menuVendas();}

        if(novoProduto[produtoSelecionado].estoque <= novoProduto[produtoSelecionado].estoque_minimo){estoqueMinimo();}
        //se o estoque atual do produto for menor ou igual ao estoque mínimo, é chamada uma nova função para confirmar a venda do produto
        else{informarQntProduto();}
}
void estoqueMinimo(){

    printf("O produto selecionado foi: %s. O estoque minimo do produto foi atingido.\n", novoProduto[produtoSelecionado].nome);

    printf("Estoque atual: %d\n", novoProduto[produtoSelecionado].estoque);
    printf("Estoque minimo:%d\n", novoProduto[produtoSelecionado].estoque_minimo);

    printf("\nDeseja vender esse produto?\n Digite 's' para sim ou 'n' para não:  ");
    scanf("%c", &simounao);
    fflush(stdin);

    if(simounao != 's' && simounao != 'S' && simounao != 'n' && simounao != 'N'){ //caso o valor informado pelo usuário não seja 'n' nem 's',
    invalido();                                                                   //o sistema informa valor inválido e pergunta ao usuário novamente.
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

    printf("Produto selecionado: %s\n Preço: R$%.2f\n", novoProduto[produtoSelecionado].nome, novoProduto[produtoSelecionado].preco_venda);
    printf("\nQuantas unidades deste produto deseja vender?");
    scanf("%d", &qtd);
    fflush(stdin);

    if(qtd<0){invalido(); informarQntProduto();}
    if(qtd>novoProduto[produtoSelecionado].estoque){estoqueNegativo();}//caso a quantidade de unidades do produto a ser vendida seja maior
                                                                   //do que o estoque atual do produto, será chamada uma nova função.

    //imprimir_carrinho();
    system("pause");












}

void cadastrarUsuario(Usuario *usuarios, int *numUsuarios) {
    printf("\n=== Cadastro de Usuários ===\n");

    if (*numUsuarios >= 100) {
        printf("Número máximo de usuários cadastrados atingido.\n");
        return;
    }

    printf("Digite o login do usuário (entre 8 e 12 caracteres): ");
    char login[13];
    scanf("%s", login);

    // Validar tamanho do login
    if (!validarLogin(login)) {
        printf("Login inválido. O login deve ter entre 8 e 12 caracteres.\n");
        return;
    }

    printf("Digite a senha do usuário (entre 6 e 8 caracteres): ");
    char senha[9];
    scanf("%s", senha);

    // Validar tamanho da senha
    if (!validarSenha(senha)) {
        printf("Senha inválida. A senha deve ter entre 6 e 8 caracteres.\n");
        return;
    }

    // Cadastro do tipo de usuário
    int tipo;
    printf("Digite o tipo do usuário (1 - Administrador, 2 - Usuário comum): ");
    scanf("%d", &tipo);
    if (tipo != 1 && tipo != 2) {
        printf("Tipo de usuário inválido.\n");
        return;
    }

    // Adicionar usuário ao array de usuários
    strcpy(usuarios[*numUsuarios].login, login);
    strcpy(usuarios[*numUsuarios].password, senha);
    usuarios[*numUsuarios].tipo = tipo;

    (*numUsuarios)++; // Incrementa o contador de usuários cadastrados

    int validarLogin(char *login) {
        int len = strlen(login);
        return (len >= 8 && len <= 12);
    }

    int validarSenha(char *senha) {
        int len = strlen(senha);
        return (len >= 6 && len <= 8);
    }

    printf("Usuário cadastrado com sucesso.\n");
}



































void ConferirCodigoProduto(){ //função compara o valor informado pelo usuário com o código de todos os produtos cadastrados.

    conferirValor = 0;
    for(i=0; i<quantidadeProdutos; i++){
        if(OpSelecionada == novoProduto[i].codigo){conferirValor = 1; produtoSelecionado = i;}
    }

    //Desse modo, caso o número digitado pelo usuário não corresponder ao código de nenhum dos produtos,
    // a variável "conferirValor" permanecerá 0. Do contrário, ela passará a ter o valor 1

   //Além disso, a variável "produtoSelecionado" irá guardar a posição da struct que corresponde ao código do produto que o usuário selecionou.
}






void relatorios(){printf("     MERCEARIA DA DONA BERÊ\n_____________________________________\n\n");}

void invalido(){
    printf("\n O VALOR INSERIDO É INVÁLIDO! TENTE NOVAMENTE");
    system("pause");
}


void sangria(){

    system("cls");
    relatorios();
    printf("Sangria\n_____________________________________\n\n");

    printf("Valor em caixa: R$");




}


