#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <clocale>
#include <locale>
#include <map>
#include <limits>
#include <cmath>
#include <time.h>
#include <sstream>
using namespace std;

// Representa um tipo de combustível disponível no posto
struct Combustivel {
    string nome;
    double precoPorLitro = 0.0;
    double estoqueLitros = 0.0;
    double capacidadeTanque = 0.0;
};

// Representa um produto vendido na loja de conveniência
struct ProdutoLoja {
    int id = 0;
    string nome;
    double precoUnitario = 0.0;
    int quantEstoque = 0;
};

// Representa Gerenciamento de Clientes
struct Clientes {
    int id = 0;
    string nome, cpf, contato;
    double saldoDevedor = 0;
};

// Representa uma venda realizada (combustível ou produto)
struct Venda {
    enum tipoVenda { COMBUSTIVEL, PRODUTO } tipo;
    string nomeItem;
    double quantVendido = 0.0;
    double valorTotal = 0.0;
    int formaPagamento = 0;
};

// representa Data e Hora
struct DataHora {
    int dia = 1;
    int mes = 1;
    int ano = 2000;
    int hora = 0;
    int minuto = 0;
    int segundo = 0;
};

// Representa Histórico de Fechamento de Caixa
struct fechamentoCaixa {
    DataHora dataHoraFechamento;
    double valorTotalVendido = 0;
};

// ==================== Declaração de Funções ====================
void MenuPrincipal(vector<Combustivel>& combustiveis, vector<ProdutoLoja>& produto, vector<Venda>& vendas, vector<Clientes>& cliente, vector<fechamentoCaixa>& historico);
void OpcaoMenu(int op_menu, vector<Combustivel>& combustiveis, vector<ProdutoLoja>& produto, vector<Venda>& vendas, vector<Clientes>& cliente, vector<fechamentoCaixa>& historico);

// Data e Hora
DataHora obterDataHoraAtual();
void ImprimirDataHoraAtual();

// Funções de Combustível
void GerenciarCombustivel(vector<Combustivel>& combustiveis);
void CarregarCombustiveis(vector<Combustivel>& combustiveis);
void SalvarCombustiveis(const vector<Combustivel>& combustiveis);
void CadastrarCombustivel(vector<Combustivel>& combustiveis);
void AtualizarPreco(vector<Combustivel>& combustiveis);
void AddEstoqueCombustivel(vector<Combustivel> &combustiveis);
void ListarCombustivel(const vector<Combustivel>& combustiveis);
int BuscaCombustivel(const vector<Combustivel>& combustiveis, const string& nome);
void QuantidadeTanque(const vector<Combustivel>& combustiveis);

// Funções de Produto da Loja
void GerenciamentoConveniencia(vector<ProdutoLoja>& produto);
void CarregarProduto(vector<ProdutoLoja>& produto);
void SalvarProduto(vector<ProdutoLoja>& produto);
int BuscaProduto(const vector<ProdutoLoja> produto, int cod);
void CadastrarProduto(vector<ProdutoLoja>& produto);
void AtualizarPrecoProduto(vector<ProdutoLoja>& produto);
void AddEstoqueProduto(vector<ProdutoLoja> &produto);
void ListarProduto(const vector<ProdutoLoja>& produto);

// Funções de Clientes
void GerenciamentoCliente(vector<Clientes>& cliente);
void CarregarCliente(vector<Clientes>& cliente);
void SalvarCliente(vector<Clientes>& cliente);
void CadastrarCliente(vector<Clientes>& cliente);
void ListarCliente(const vector<Clientes>& cliente);
int BuscaClienteNome(const vector<Clientes>& cliente, string nomeCliente);
void consultarSaldo(vector<Clientes>& cliente);
void RegistrarPagamentoCliente(vector<Clientes>& cliente);

// Funções de Venda e Relatórios e Caixa 
void RelatoriosCaixa(vector<Venda>& vendas, vector<Combustivel>& combustiveis, vector<Clientes>& cliente, vector<fechamentoCaixa>& historico);
void CarregarVendas(vector<Venda>& vendas);
void SalvarVendas(vector<Venda>& vendas);
void NovaVenda(vector<Combustivel>& combustivel, vector<ProdutoLoja>& produto, vector<Clientes>& cliente, vector<Venda>& vendas);
void imprimirValorTotalTiposPagamento(const vector<Venda>& vendas);
void FecharCaixa(vector<Venda>& vendas, vector<Combustivel>& combustiveis, vector<fechamentoCaixa>& historico);
void RelatorioClienteDevedores(const vector<Clientes>& cliente);

// Funções Fechamento de Caixa
void CarregarHistoricoFechamento(vector<fechamentoCaixa>& historico);
void SalvarHistoricoFechamento(const vector<fechamentoCaixa>& historico);
void ExibirHistoricoFechamento(const vector<fechamentoCaixa>& historico);


// ==================== Função Principal ====================
int main()
{
    vector<Combustivel> combustiveis;
    vector<ProdutoLoja> produto;
    vector<Clientes> cliente;
    vector<Venda> vendas;
    vector<fechamentoCaixa> historico;
    locale::global(locale("pt_BR.UTF-8"));

    // Arquivos
    CarregarCombustiveis(combustiveis);
    CarregarProduto(produto);
    CarregarVendas(vendas);
    CarregarCliente(cliente);
    CarregarHistoricoFechamento(historico);

    MenuPrincipal(combustiveis, produto, vendas, cliente, historico);

    return 0;
}

// Menu principal do sistema
void MenuPrincipal(vector<Combustivel>& combustiveis, vector<ProdutoLoja>& produto, vector<Venda>& vendas, vector<Clientes>& cliente, vector<fechamentoCaixa> &historico) {
    string escolha;
    int op_menu;

    while (true) {
        system("cls");
        cout << "=========== PDV POSTO RÁPIDO ============\n\n";
        cout << "1 - Iniciar Nova Venda (PDV)\n";
        cout << "2 - Gerenciar Combustíveis\n";
        cout << "3 - Gerenciar Loja de Conveniência\n";
        cout << "4 - Gerenciar Cliente\n";
        cout << "5 - Relatórios e Caixa\n\n";
        cout << "0 - Sair do Sistema\n\n";
        cout << "Digite a Opção: ";
        cin >> escolha;

        if (escolha.size() == 1 && isdigit(escolha[0])) {
            op_menu = stoi(escolha);
            if (op_menu >= 0 && op_menu <= 5) {
                if (op_menu == 0) {
                    break;
                }
                OpcaoMenu(op_menu, combustiveis, produto, vendas, cliente, historico);
            }
            else {
                cout << "\nOpção Inválida!\n";
                system("pause");
            }
        }
        else {
            cout << "\nEntrada Inválida! Digite apenas o número da opção.\n";
            system("pause");
        }
    }
}

// Executa a opção escolhida no menu principal
void OpcaoMenu(int op_menu, vector<Combustivel>& combustiveis, vector<ProdutoLoja>& produto, vector<Venda>& vendas, vector<Clientes>& cliente, vector<fechamentoCaixa> &historico) {
    switch (op_menu) {
    case 1:
        NovaVenda(combustiveis, produto, cliente, vendas);
        break;
    case 2:
        GerenciarCombustivel(combustiveis);
        break;
    case 3:
        GerenciamentoConveniencia(produto);
        break;
    case 4:
        GerenciamentoCliente(cliente);
        break;
    case 5:
        RelatoriosCaixa(vendas, combustiveis, cliente, historico);
        break;
    }
}


// ================ DATA E HORA ==================

// Função para obter a data e hora atual do sistema
DataHora obterDataHoraAtual() {
    DataHora dh;
    time_t agora = time(nullptr);
    struct tm info; 
    localtime_s(&info, &agora);
    dh.dia = info.tm_mday;
    dh.mes = info.tm_mon + 1;
    dh.ano = info.tm_year + 1900;
    dh.hora = info.tm_hour;
    dh.minuto = info.tm_min;
    dh.segundo = info.tm_sec;
    return dh;
}

// Imprimir Data e horário Atual
void ImprimirDataHoraAtual() {
    DataHora dh = obterDataHoraAtual();
    cout << "Data: " << setw(2) << setfill('0') << dh.dia << "/"
        << setw(2) << setfill('0') << dh.mes << "/"
        << dh.ano << " - "
        << setw(2) << setfill('0') << dh.hora << ":"
        << setw(2) << setfill('0') << dh.minuto << ":"
        << setw(2) << setfill('0') << dh.segundo << endl;
}


// ==================== Funções de Combustível ====================

// Salva os dados dos combustíveis no arquivo binário
void SalvarCombustiveis(const vector<Combustivel>& combustiveis) {
    ofstream arquivo("combustiveis.dat", ios::binary | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro crítico: Não foi possível abrir o arquivo para salvar os dados.\n";
        system("pause");
        return;
    }
    size_t tamanho = combustiveis.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    for (const auto& c : combustiveis) {
        size_t nomeLen = c.nome.size();
        arquivo.write(reinterpret_cast<const char*>(&nomeLen), sizeof(nomeLen));
        arquivo.write(c.nome.c_str(), nomeLen);
        arquivo.write(reinterpret_cast<const char*>(&c.precoPorLitro), sizeof(c.precoPorLitro));
        arquivo.write(reinterpret_cast<const char*>(&c.estoqueLitros), sizeof(c.estoqueLitros));
        arquivo.write(reinterpret_cast<const char*>(&c.capacidadeTanque), sizeof(c.capacidadeTanque));
    }
    arquivo.close();
}

// Carrega os dados dos combustíveis do arquivo binário
void CarregarCombustiveis(vector<Combustivel>& combustiveis) {
    ifstream arquivo("combustiveis.dat", ios::binary);
    if (!arquivo.is_open()) {
        return;
    }
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; ++i) {
        Combustivel c;
        size_t nomeLen = 0;
        arquivo.read(reinterpret_cast<char*>(&nomeLen), sizeof(nomeLen));
        c.nome.resize(nomeLen);
        arquivo.read(&c.nome[0], nomeLen);
        arquivo.read(reinterpret_cast<char*>(&c.precoPorLitro), sizeof(c.precoPorLitro));
        arquivo.read(reinterpret_cast<char*>(&c.estoqueLitros), sizeof(c.estoqueLitros));
        arquivo.read(reinterpret_cast<char*>(&c.capacidadeTanque), sizeof(c.capacidadeTanque));
        combustiveis.push_back(c);
    }
    arquivo.close();
}

// Menu de gerenciamento de combustíveis
void GerenciarCombustivel(vector<Combustivel>& combustiveis) {
    int opcao;
    string escolha;
    do {
        system("cls");
        cout << "========== GERENCIAR COMBUSTÍVEIS ==========\n\n";
        cout << "1 - Cadastrar Novo Combustível\n";
        cout << "2 - Atualizar Preço por Litro\n";
        cout << "3 - Registrar Entrada de Estoque\n";
        cout << "4 - Listar Combustíveis\n\n";
        cout << "0 - Voltar ao Menu Principal\n\n";
        cout << "Digite sua Opção: ";
        cin >> escolha;

        if (escolha.size() == 1 && isdigit(escolha[0])) {
            opcao = stoi(escolha);
        }
        else {
            opcao = -1;
        }

        switch (opcao) {
        case 1:
            CadastrarCombustivel(combustiveis);
            break;
        case 2:
            AtualizarPreco(combustiveis);
            break;
        case 3:
            AddEstoqueCombustivel(combustiveis);
            break;
        case 4:
            ListarCombustivel(combustiveis);
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "\nOpção Inválida!\n";
            system("pause");
            break;
        }
    } while (opcao != 0);
}

// Busca combustível pelo nome
int BuscaCombustivel(const vector<Combustivel>& combustiveis, const string& nome) {
    string nomeMaiusculo = nome;
    transform(nomeMaiusculo.begin(), nomeMaiusculo.end(), nomeMaiusculo.begin(), ::toupper);
    for (size_t i = 0; i < combustiveis.size(); i++) {
        if (combustiveis[i].nome == nomeMaiusculo) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Cadastra um novo combustível
void CadastrarCombustivel(vector<Combustivel>& combustiveis) {
    Combustivel cadastro;
    char confirma;
    char op;

    do {
        system("cls");
        cin.ignore();
        cout << "======== CADASTRAR NOVO COMBUSTÍVEL ========\n\n";
        cout << "Digite o nome do Combustível (Ex. Etanol): ";
        getline(cin, cadastro.nome);
        transform(cadastro.nome.begin(), cadastro.nome.end(), cadastro.nome.begin(), ::toupper);

        if (BuscaCombustivel(combustiveis, cadastro.nome) != -1) {
            cout << "\nEste combustível já está cadastrado!\n\n";
            system("pause");
            return;
        }

        cout << "Digite o preço por Litro: R$ ";
        cin >> cadastro.precoPorLitro;
        cout << "Digite a quantidade inicial em estoque (Litros): ";
        cin >> cadastro.estoqueLitros;
        cout << "Capacidade Tanque: ";
        cin >> cadastro.capacidadeTanque;

        cout << "\n\nDeseja confirmar o cadastro? (S/N): ";
        cin >> confirma;

        if (toupper(confirma) == 'S') {
            combustiveis.push_back(cadastro);
            SalvarCombustiveis(combustiveis);
            cout << "\nCombustível cadastrado com sucesso!\n\n";
        }
        else {
            cout << "\nCadastro cancelado.\n\n";
        }
        cout << "Deseja Cadastrar Outro Combustível ? (S/N): ";
        cin >> op;
    } while (toupper(op) == 'S');
}

// Atualiza o preço de um combustível
void AtualizarPreco(vector<Combustivel>& combustiveis) {
    string nome;
    system("cls");
    cout << "===================== ATUALIZAR PREÇO =====================\n\n";
    cout << "Qual combustível deseja atualizar? (Ex. Etanol): ";
    cin.ignore();
    getline(cin, nome);

    int indice = BuscaCombustivel(combustiveis, nome);

    if (indice != -1) {
        cout << "\nPreço atual do " << combustiveis[indice].nome
            << ": R$ " << fixed << setprecision(2) << combustiveis[indice].precoPorLitro << "\n";

        double novoPreco;
        cout << "Digite o novo preço por litro: R$ ";
        cin >> novoPreco;

        combustiveis[indice].precoPorLitro = novoPreco; 
        SalvarCombustiveis(combustiveis);              

        cout << "\nPreço atualizado com sucesso!\n\n";
    }
    else {
        cout << "\nCombustível não encontrado!\n\n";
    }
    system("pause");
}

// Adiciona estoque a um combustível
void AddEstoqueCombustivel(vector<Combustivel> &combustiveis) {
    string nome;
    system("cls");
    cout << "================== ENTRADA DE ESTOQUE ===================\n\n";
    cout << "Qual Combustível Deseja Inserir Estoque ? (Ex. Etanol): ";
    cin.ignore();
    getline(cin, nome);

    int indice = BuscaCombustivel(combustiveis, nome);
    if (indice != -1) {
        cout << "\nEstoque Atual do " << combustiveis[indice].nome
            << ": " << fixed << setprecision(2) << combustiveis[indice].estoqueLitros;

        double addEstoque;
        cout << "\nDigite Quantidade Para Estoque: ";
        cin >> addEstoque;

        combustiveis[indice].estoqueLitros += addEstoque;
        SalvarCombustiveis(combustiveis);
        cout << "\nEstoque Atualizado com Sucesso\n\n";
    }
    else {
        cout << "\nCombustível não Encontrado\n\n";
    }
    system("pause");
}

// Lista todos os combustíveis cadastrados
void ListarCombustivel(const vector<Combustivel>& combustiveis) {
    system("cls");
    cout << "================= LISTA DE COMBUSTÍVEIS ================\n\n";

    if (combustiveis.empty()) {
        cout << "Nenhum combustível cadastrado.\n\n";
        return;
    }

    cout << right;
    for (int i = 0;i< combustiveis.size();i++) {
        cout << "Combustível: " << setw(15) << combustiveis[i].nome << "\n";
        cout << "Preço:" << setw(18) << "R$ " << fixed << setprecision(2) << combustiveis[i].precoPorLitro << "\n";
        cout << "Estoque:" <<setw(20)<< fixed << setprecision(2) << combustiveis[i].estoqueLitros << " Litros\n";
        cout << "--------------------------------------------------\n\n";
    }
}

// Quantidade de Estoque Combustível
void QuantidadeTanque(const vector<Combustivel>& combustiveis) {
    cout << "\n----------------------------- ESTOQUE TANQUE ----------------------------\n\n";
    cout << left << setw(21) << "Combustível" 
        << setw(15) << "Estoque"
        << setw(15) << "Cap. Tanque";
    cout << "\n\n";
    for (size_t i = 0; i < combustiveis.size(); i++) {
        cout << left << setw(20) << combustiveis[i].nome
            << setw(15) << combustiveis[i].estoqueLitros 
            << setw(7) << fixed << setprecision(2) 
            << (combustiveis[i].estoqueLitros / combustiveis[i].capacidadeTanque) * 100
            << "%" << endl;
    }
    cout << "\n-------------------------------------------------------------------------\n\n";
}


// ==================== Funções de Produto da Loja ====================

// Menu de gerenciamento da loja de conveniência
void GerenciamentoConveniencia(vector<ProdutoLoja> &produto) {
    int opcao;
    string escolha;
    do {
        system("cls");
        cout << "====== GERENCIAR LOJA DE CONVENIÊNCIA ======\n\n";
        cout << "1 - Cadastrar Novo Produto";
        cout << "\n2 - Atualizar Preço do Produto";
        cout << "\n3 - Adicionar Estoque";
        cout << "\n4 - Listar Produto\n\n";
        cout << "0 - Voltar ao Menu Principal\n\n";
        cout << "Digite Opção: ";
        cin >> escolha;

        if (escolha.size() == 1 && isdigit(escolha[0])) {
            opcao = stoi(escolha);
        }
        else {
            opcao = -1;
        }

        switch (opcao) {
        case 1:
            CadastrarProduto(produto);
            break;
        case 2:
            AtualizarPrecoProduto(produto);
            break;
        case 3:
            AddEstoqueProduto(produto);
            break;
        case 4:
            ListarProduto(produto);
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "\nOpção Inválida\n\n";
            system("pause");
            break;
        }
    } while (opcao != 0);
}

// Carrega os produtos da loja do arquivo binário
void CarregarProduto(vector<ProdutoLoja>& produto) {
    ifstream arquivo("Produtos.dat", ios::binary);
    if (!arquivo.is_open()) {
        return;
    }
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; i++) {
        ProdutoLoja p;
        arquivo.read(reinterpret_cast<char*>(&p.id), sizeof(p.id));
        size_t nomeLen = 0;
        arquivo.read(reinterpret_cast<char*>(&nomeLen), sizeof(nomeLen));
        p.nome.resize(nomeLen);
        arquivo.read(&p.nome[0], nomeLen);
        arquivo.read(reinterpret_cast<char*>(&p.precoUnitario), sizeof(p.precoUnitario));
        arquivo.read(reinterpret_cast<char*>(&p.quantEstoque), sizeof(p.quantEstoque));
        produto.push_back(p);
    }
    arquivo.close();
}

// Salva os produtos da loja no arquivo binário
void SalvarProduto(vector<ProdutoLoja> &produto) {
    ofstream arquivo("Produtos.dat", ios::binary | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro: não foi possível abrir o arquivo 'Produtos.dat' para escrita" << endl;
        system("pause");
        return;
    }
    size_t tamanho = produto.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    for (const auto& p : produto) {
        arquivo.write(reinterpret_cast<const char*>(&p.id), sizeof(p.id));
        size_t nomeLen = p.nome.size();
        arquivo.write(reinterpret_cast<const char*>(&nomeLen), sizeof(nomeLen));
        arquivo.write(p.nome.c_str(), nomeLen);
        arquivo.write(reinterpret_cast<const char*>(&p.precoUnitario), sizeof(p.precoUnitario));
        arquivo.write(reinterpret_cast<const char*>(&p.quantEstoque), sizeof(p.quantEstoque));
    }
    arquivo.close();
}

// Cadastra um novo produto na loja
void CadastrarProduto(vector<ProdutoLoja>& produto) {
    ProdutoLoja cadastro;
    char confirmar, op;

    do {
        system("cls");
        cout << "=========== CADASTRAR NOVO PRODUTO ===========\n\n";
        cout << "Código do Produto: ";
        cin >> cadastro.id;
        if (BuscaProduto(produto, cadastro.id) != -1) {
            cout << "\nCódigo Já Cadastrado\n\n";
            system("pause");
            return;
        }
        cout << "Nome do Produto (Ex. Água): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, cadastro.nome);
        transform(cadastro.nome.begin(), cadastro.nome.end(), cadastro.nome.begin(), ::toupper);
        cout << "Preço Unitário: ";
        cin >> cadastro.precoUnitario;
        cout << "Estoque Inicial: ";
        cin >> cadastro.quantEstoque;

        cout << "\n\nDeseja Confirmar Cadastro ? (S/N): ";
        cin >> confirmar;

        if (toupper(confirmar) == 'S') {
            produto.push_back(cadastro);
            SalvarProduto(produto);
            cout << "\n\nCadastro Confirmado com Sucesso\n\n";
        }

        cout << "Deseja Cadastrar Outro Produto ? (S/N): ";
        cin >> op;
    } while (toupper(op) == 'S');
}

// Busca produto pelo código
int BuscaProduto(const vector<ProdutoLoja> produto, int cod) {
    int id = cod;
    for (size_t i = 0; i < produto.size(); i++) {
        if (id == produto[i].id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Lista todos os produtos cadastrados
void ListarProduto(const vector<ProdutoLoja>& produto) {
    system("cls");
    cout << "===================== LISTA DE PRODUTOS =====================\n\n";
    cout << setw(7)<< "ID" << setw(20) << "PRODUTO" << setw(20) << "PREÇO" << setw(15) << "ESTOQUE\n\n";
    if (produto.empty()) {
        cout << "Nenhum Produto Cadastrado\n\n";
        return;
    }

    cout << right;
    for (int i = 0; i < produto.size(); i++) {
        cout << setw(7) << produto[i].id
            << setw(20) << produto[i].nome
            << setw(15) << "R$ " << fixed << setprecision(2) << produto[i].precoUnitario
            << setw(11) << produto[i].quantEstoque;
        cout << "\n-------------------------------------------------------------\n";
    }
    cout << endl;
}

// Atualiza o preço de um produto
void AtualizarPrecoProduto(vector<ProdutoLoja>& produto) {
    int id;
    system("cls");
    cout << "================ ATUALIZAR PREÇO DO PRODUTO ================\n\n";
    cout << "Qual Produto Deseja Aualizar o Preço: ";
    cin >> id;

    int indice = BuscaProduto(produto, id);
    if (indice != -1) {
        cout << "\nProduto: " << produto[indice].nome;
        cout << "\nPreço Atual: R$ " << fixed << setprecision(2) << produto[indice].precoUnitario;

        double novopreco;
        cout << "\n\nDigite o Preço Atual: ";
        cin >> novopreco;

        produto[indice].precoUnitario = novopreco;
        SalvarProduto(produto);

        cout << "\nPreço Atualizado com Sucesso\n\n";
    }
    else {
        cout << "\nCódigo Não Encontrado\n\n";
    }
    system("pause");
}

// Adiciona estoque a um produto
void AddEstoqueProduto(vector<ProdutoLoja> &produto) {
    int id;
    system("cls");
    cout << "============== ADICIONAR ESTOQUE PRODUTO ===============\n\n";
    cout << "Digite o Código do Produto: ";
    cin >> id;

    int indice = BuscaProduto(produto, id);
    if (indice != -1) {
        cout << "\nProduto: " << produto[indice].nome;
        cout << "\nEstoque Atual: " << produto[indice].quantEstoque;

        int estoqueNovo;
        cout << "\n\nInsira Quantidade: ";
        cin >> estoqueNovo;

        produto[indice].quantEstoque += estoqueNovo;
        SalvarProduto(produto);

        cout << "\nEstoque Atualizado com Sucesso\n\n";
    }
    system("pause");
}


// ==================== Funções de Clientes =======================

// Menu de Gerenciamento de Clientes
void GerenciamentoCliente(vector<Clientes>& cliente) {
    string escolha;
    int opcao;
    do {
        system("cls");
        cout << "================= GERENCIAMENTO DE CLIENTES ==================\n\n";
        cout << "1 - Cadastrar Novo Cliente\n";
        cout << "2 - Listar Todos os Clientes\n";
        cout << "3 - Consultar Saldo de Cliente\n";
        cout << "4 - Registrar Pagamento de Dívida\n\n";
        cout << "0 - Voltar ao Menu Principal\n\n";
        cout << "Digite sua Opção: ";
        cin >> escolha;

        if (escolha.size() == 1 && isdigit(escolha[0])) {
            opcao = stoi(escolha);
        }
        else {
            opcao = -1;
        }

        switch (opcao) {
        case 1:
            CadastrarCliente(cliente);
            break;
        case 2:
            ListarCliente(cliente);
            break;
        case 3:
            consultarSaldo(cliente);
            break;
        case 4:
            RegistrarPagamentoCliente(cliente);
            break;
        case 0:
            break;
        default:
            cout << "\nDigito Inválido\n\n";
            system("pause");
            break;
        }
    } while (opcao != 0);
}

// Carregar os Clientes do Arquivo Binário
void CarregarCliente(vector<Clientes>& cliente) {
    ifstream arquivo("Cliente.dat", ios::binary);
    if (!arquivo.is_open()) {
        return;
    }
    
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; i++) {
        Clientes c;
        arquivo.read(reinterpret_cast<char*>(&c.id), sizeof(c.id));
        size_t nomelen;
        arquivo.read(reinterpret_cast<char*>(&nomelen), sizeof(nomelen));
        c.nome.resize(nomelen);
        arquivo.read(&c.nome[0], nomelen);
        size_t cpflen;
        arquivo.read(reinterpret_cast<char*>(&cpflen), sizeof(cpflen));
        c.cpf.resize(cpflen);
        arquivo.read(&c.cpf[0], cpflen);
        size_t contatolen;
        arquivo.read(reinterpret_cast<char*>(&contatolen), sizeof(contatolen));
        c.contato.resize(contatolen);
        arquivo.read(&c.contato[0], contatolen);
        arquivo.read(reinterpret_cast<char*>(&c.saldoDevedor), sizeof(c.saldoDevedor));
        cliente.push_back(c);
    }
    arquivo.close();
}

// Salvar os Clientes do Arquivo Binário
void SalvarCliente(vector<Clientes>& cliente) {
    ofstream arquivo("Cliente.dat", ios::binary | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro: não foi possível abrir o arquivo Cliente.dat\n\n";
        system("pause");
        return;
    }
    size_t tamanho = cliente.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    for (const auto& c : cliente) {
        arquivo.write(reinterpret_cast<const char*>(&c.id), sizeof(c.id));
        size_t nomelen = c.nome.size();
        arquivo.write(reinterpret_cast<const char*>(&nomelen), sizeof(nomelen));
        arquivo.write(c.nome.c_str(), nomelen);
        size_t cpflen = c.cpf.size();
        arquivo.write(reinterpret_cast<const char*>(&cpflen), sizeof(cpflen));
        arquivo.write(c.cpf.c_str(), cpflen);
        size_t contatolen = c.contato.size();
        arquivo.write(reinterpret_cast<const char*>(&contatolen), sizeof(contatolen));
        arquivo.write(c.contato.c_str(), contatolen);
        arquivo.write(reinterpret_cast<const char*>(&c.saldoDevedor), sizeof(c.saldoDevedor));
    }
    arquivo.close();
}

// Cadastrar Cliente
void CadastrarCliente(vector<Clientes>& cliente) {
    Clientes cadastro;
    char confirmar, opcao;
    int id;

    if (cliente.empty()) {
        id = 1;
    }
    else {
        id = cliente.back().id + 1;
    }

    do {
        system("cls");
        cout << "=================== CADASTRAR CLIENTE ====================\n\n";
        cout << "ID Cliente: " << id;
        cadastro.id = id;
        cout << "\nNome: ";
        cin.ignore();
        getline(cin, cadastro.nome);
        transform(cadastro.nome.begin(), cadastro.nome.end(), cadastro.nome.begin(), ::toupper);
        cout << "CPF: ";
        getline(cin, cadastro.cpf);
        cout << "Contato: ";
        getline(cin, cadastro.contato);
        cout << "Saldo Inicial: R$ ";
        cin >> cadastro.saldoDevedor;

        cout << "\nDeseja Confirmar Cadastro ? (S/N): ";
        cin >> confirmar;
        if (toupper(confirmar) == 'S') {
            cliente.push_back(cadastro);
            SalvarCliente(cliente);
            cout << "\n\nCadastro Realizado com Sucesso\n\n";
            id++;
        }
        cout << "Deseja Cadastrar Outro Cliente ? (S/N): ";
        cin >> opcao;
    } while (toupper(opcao) == 'S');
}

// Listar Cliente
void ListarCliente(const vector<Clientes>& cliente) {
    system("cls");
    cout << "===================================== LISTA DE CLIENTES =====================================\n\n";

    if (cliente.empty()) {
        cout << "Nenhum Cliente Cadastrado\n\n";
        system("pause");
        return;
    }

    cout << left;
    cout << setw(5) << "ID"
        << setw(30) << "NOME"
        << setw(18) << "CPF"
        << setw(20) << "CONTATO"
        << "SALDO DEVEDOR" << endl;

    cout << "---------------------------------------------------------------------------------------------\n\n";
    for (int i = 0; i < cliente.size(); i++) {
        cout << setw(5) << cliente[i].id
            << setw(30) << cliente[i].nome
            << setw(18) << cliente[i].cpf
            << setw(20) << cliente[i].contato
            << "R$ "
            << fixed << setprecision(2) << cliente[i].saldoDevedor << endl;
        cout << "---------------------------------------------------------------------------------------------\n";
    }
    cout << endl;
    system("pause");
}

// Busca Cliente pelo código
int BuscaClienteNome(const vector<Clientes>& cliente, string nomeCliente) {
    string nome = nomeCliente;
    for (size_t i = 0; i < cliente.size(); i++) {
        if (nome == cliente[i].nome) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Consultar Saldo do Cliente
void consultarSaldo(vector<Clientes>& cliente) {
    string nome;
    system("cls");
    cout << "==================== CONSULTAR SALDO =====================\n\n";
    cout << "Digite o Nome do Cliente: ";
    cin.ignore();
    getline(cin, nome);
    transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

    cout << "\n\n";
    int indice = BuscaClienteNome(cliente, nome);
    if (indice != -1) {
        cout << left;
        cout << setw(5) << "ID"
            << setw(30) << "NOME"
            << "SALDO DEVEDOR" << endl;
        cout << "----------------------------------------------------------\n\n";
        cout << setw(5) << cliente[indice].id
            << setw(30) << cliente[indice].nome
            << "R$ "
            << fixed << setprecision(2) << cliente[indice].saldoDevedor << endl;
        cout << "----------------------------------------------------------\n";
    }
    else {
        cout << "Cliente Não Encontrado\n\n";
    }
    system("pause");
}

// Registrar Pagamento Cliente
void RegistrarPagamentoCliente(vector<Clientes>& cliente) {
    string nome;
    char confirmar;
    double valorPagamento = 0.0;
    system("cls");
    cout << "============= REGISTRAR PAGAMENTO DE DÍVIDA ===============\n\n";
    cout << "Digite o Nome do Cliente: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nome);
    transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

    cout << "\n\n";
    int indice = BuscaClienteNome(cliente, nome);
    if (indice != -1) {
        cout << left;
        cout << setw(5) << "ID"
            << setw(30) << "NOME"
            << "SALDO DEVEDOR" << endl;
        cout << "----------------------------------------------------------\n\n";
        cout << setw(5) << cliente[indice].id
            << setw(30) << cliente[indice].nome
            << "R$ "
            << fixed << setprecision(2) << cliente[indice].saldoDevedor << endl;
        cout << "----------------------------------------------------------\n";

        cout << "\nDigite o Valor do Pagamento: R$ ";
        cin >> valorPagamento;

        while (valorPagamento < 0 || round(valorPagamento * 100.0) > round(cliente[indice].saldoDevedor * 100.0)) {
            system("cls");
            cout << "============= REGISTRAR PAGAMENTO DE DÍVIDA ===============\n\n";
            cout << "Erro, valor inválido, negativo ou maior que o saldo devedor!\n\n";
            cout << "Saldo Devedor Atual: R$ " << fixed << setprecision(2) << cliente[indice].saldoDevedor << endl;
            cout << "\nDigite o Valor do Pagamento: R$ ";
            cin >> valorPagamento;
        }

        cout << "\n\nDeseja Confirmar ? (S/N): ";
        cin >> confirmar;

        if (toupper(confirmar) == 'S') {
            long long saldoDevedorCentavos = round(cliente[indice].saldoDevedor * 100.0);
            long long valorPagamentoCentavos = round(valorPagamento * 100.0);

            saldoDevedorCentavos -= valorPagamentoCentavos;

            cliente[indice].saldoDevedor = saldoDevedorCentavos / 100.0;

            SalvarCliente(cliente);
            cout << "\nPagamento Efetuado Com Sucesso\n";

            cout << "Novo Saldo Devedor: R$ " << cliente[indice].saldoDevedor;
            cout << "\n\n";
        }
        else {
            cout << "\nPagamento Cancelado\n\n";
        }
    }
    else {
        cout << "Nenhum Cliente Encontrado\n\n";
    }
    system("pause");
}


// ============= Funções de Venda e Relatórios e Caixa ==============

// Menu Relatórios e Caixa
void RelatoriosCaixa(vector<Venda>& vendas, vector<Combustivel> &combustiveis, vector<Clientes> &cliente, vector<fechamentoCaixa> &historico) {
    string escolha;
    int opcao;
    do {
        system("cls");
        cout << "=============== RELATÓRIOS E CAIXA ================\n\n";
        cout << "1 - Fechar Caixa do Dia\n";
        cout << "2 - Ver Relatório de Clientes Devedores\n";
        cout << "3 - Ver Histórico de Fechamentos de Caixa\n\n";
        cout << "0 - Voltar ao Menu Principal\n\n";
        cout << "Digite Sua Opção: ";
        cin >> escolha;

        if (escolha.size() == 1 && isdigit(escolha[0])) {
            opcao = stoi(escolha);
        }
        else {
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                FecharCaixa(vendas, combustiveis, historico);
                break;
            case 2:
                RelatorioClienteDevedores(cliente);
                break;
            case 3:
                ExibirHistoricoFechamento(historico);
                break;
            case 0:
                break;
            default:
                cout << "\nDígito Inválido\n\n";
                system("pause");
                break;
        }

    } while (opcao != 0);
}

// Carrega as vendas do arquivo binário
void CarregarVendas(vector<Venda>& vendas) {
    ifstream arquivo("vendas.dat", ios::binary);
    if (!arquivo.is_open()) {
        return;
    }
    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; ++i) {
        Venda v;
        int tipoInt;
        arquivo.read(reinterpret_cast<char*>(&tipoInt), sizeof(tipoInt));
        v.tipo = (tipoInt == 0) ? Venda::COMBUSTIVEL : Venda::PRODUTO;
        size_t nomeLen = 0;
        arquivo.read(reinterpret_cast<char*>(&nomeLen), sizeof(nomeLen));
        v.nomeItem.resize(nomeLen);
        arquivo.read(&v.nomeItem[0], nomeLen);
        arquivo.read(reinterpret_cast<char*>(&v.quantVendido), sizeof(v.quantVendido));
        arquivo.read(reinterpret_cast<char*>(&v.valorTotal), sizeof(v.valorTotal));
        arquivo.read(reinterpret_cast<char*>(&v.formaPagamento), sizeof(v.formaPagamento));
        vendas.push_back(v);
    }
    arquivo.close();
}

// Salva as vendas no arquivo binário
void SalvarVendas(vector<Venda>& vendas) {
    ofstream arquivo("vendas.dat", ios::binary | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro: não foi possível abrir o arquivo de vendas.\n";
        return;
    }
    size_t tamanho = vendas.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    for (const auto& v : vendas) {
        int tipoInt = (v.tipo == Venda::COMBUSTIVEL ? 0 : 1);
        arquivo.write(reinterpret_cast<const char*>(&tipoInt), sizeof(tipoInt));
        size_t nomeLen = v.nomeItem.size();
        arquivo.write(reinterpret_cast<const char*>(&nomeLen), sizeof(nomeLen));
        arquivo.write(v.nomeItem.c_str(), nomeLen);
        arquivo.write(reinterpret_cast<const char*>(&v.quantVendido), sizeof(v.quantVendido));
        arquivo.write(reinterpret_cast<const char*>(&v.valorTotal), sizeof(v.valorTotal));
        arquivo.write(reinterpret_cast<const char*>(&v.formaPagamento), sizeof(v.formaPagamento));
    }
    arquivo.close();
}

// Registra uma nova venda (combustível ou produto)
void NovaVenda(vector<Combustivel>& combustivel, vector<ProdutoLoja>& produto, vector<Clientes> &cliente, vector<Venda>& vendas) {
    vector<Venda> itemVenda;
    int op;
    double totalVenda = 0.0;

    do {
        system("cls");
        cout << "============ REGISTRAR NOVA VENDA ==============\n\n";
        cout << "1 - Vender Combustível";
        cout << "\n2 - Vender Produto da Loja";
        cout << "\n0 - Finalizar Venda\n\n";
        cout << "Opção: ";
        cin >> op;

        if (op == 1) {
            string nomeCombustivel;
            system("cls");
            cout << "=================== COMBUSTÍVEL ====================\n\n";
            cout << "Digite Tipo Combustível (Ex. Etanol): ";
            cin.ignore();
            getline(cin, nomeCombustivel);
            transform(nomeCombustivel.begin(), nomeCombustivel.end(), nomeCombustivel.begin(), ::toupper);

            int indice = BuscaCombustivel(combustivel, nomeCombustivel);
            if (indice != -1) {
                double litros;
                cout << "Digite a Quatidade em Litros: ";
                cin >> litros;

                if (litros > 0 && combustivel[indice].estoqueLitros >= litros) {
                    Venda novaVenda;
                    novaVenda.tipo = Venda::COMBUSTIVEL;
                    novaVenda.nomeItem = combustivel[indice].nome;
                    novaVenda.quantVendido = litros;
                    novaVenda.valorTotal = litros * combustivel[indice].precoPorLitro;

                    itemVenda.push_back(novaVenda);
                    totalVenda += novaVenda.valorTotal;
                    combustivel[indice].estoqueLitros -= litros;
                    cout << "\nItem Adicionado\n\n";
                }
                else {
                    cout << "\nEstoque Insuficiente ou Quantidade Inválida\n\n";
                }
            }
            else {
                cout << "\nCombustível Não Encontrado\n\n";
            }
        }
        else if (op == 2) {
            int idProduto;
            system("cls");
            cout << "=============== PRODUTOS DA LOJA =================\n\n";
            cout << "Digite o código do Produto: ";
            cin >> idProduto;

            int indice = BuscaProduto(produto, idProduto);
            if (indice != -1) {
                int quantidade;
                cout << "Digite Quantidade: ";
                cin >> quantidade;

                if (quantidade > 0 && produto[indice].quantEstoque >= quantidade) {
                    Venda novaVenda;
                    novaVenda.tipo = Venda::PRODUTO;
                    novaVenda.nomeItem = produto[indice].nome;
                    novaVenda.quantVendido = quantidade;
                    novaVenda.valorTotal = quantidade * produto[indice].precoUnitario;

                    itemVenda.push_back(novaVenda);
                    totalVenda += novaVenda.valorTotal;
                    produto[indice].quantEstoque -= quantidade;
                    cout << "\nItem Adicionado\n";
                }
                else {
                    cout << "\nEstoque Insuficiente ou Quantidade Inválida\n";
                }
            }
            else {
                cout << "\nProduto Não Encontrado\n";
            }
        }
        else if (op != 0) {
            cout << "\nOpção Inválida\n";
        }
        if (op == 1 || op == 2 || op != 0)
            system("pause");

    } while (op != 0);

    if (!itemVenda.empty()) {
        system("cls");
        cout << "=============== FINALIZAR VENDA ===============\n\n";
        cout << "Total Venda: R$ " << fixed << setprecision(2) << totalVenda;
        cout << "\n\nFORMA DE PAGAMENTO\n";
        cout << "1 - Dinheiro";
        cout << "\n2 - Cartão Débito";
        cout << "\n3 - Cartão Crédito";
        cout << "\n4 - PIX";
        cout << "\n5 - Fiado";
        cout << "\n\nOpção: ";
        int formaPag;
        cin >> formaPag;

        if (formaPag == 5) {
            string nome;
            char confirmar;
            do {
                system("cls");
                cout << "=============== FINALIZAR VENDA ===============\n\n";
                cout << "Digite o nome do Cliente: ";
                cin.ignore();
                getline(cin, nome);
                transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

                cout << "\n\n";
                int indice = BuscaClienteNome(cliente, nome);
                if (indice != -1) {
                    cout << left;
                    cout << setw(5) << "ID"
                        << setw(30) << "NOME";
                    cout << "\n-----------------------------------------\n\n";
                    cout << setw(5) << cliente[indice].id
                        << setw(30) << cliente[indice].nome;
                    cout << "\n-----------------------------------------\n";
                }
                else {
                    cout << "Cliente Não Encontrado\n\n";
                }
                
                cout << "Deseja Confirmar ?(S/N): ";
                cin >> confirmar;

                if (toupper(confirmar) == 'S') {
                    cliente[indice].saldoDevedor += totalVenda;
                }

            } while (toupper(confirmar) != 'S');
        }

        for (auto& item : itemVenda) {
            item.formaPagamento = formaPag;
            vendas.push_back(item);
        }
        SalvarVendas(vendas);
        SalvarCombustiveis(combustivel);
        SalvarProduto(produto);
        SalvarCliente(cliente);

        cout << "\n\nVenda Registrada Com Sucesso\n\n";
    }
    else {
        cout << "\n\nNenhum Item na Venda. Venda Cancelada\n\n";
    }
    system("pause");
}

// Tipo de Pagamentos
void imprimirValorTotalTiposPagamento(const vector<Venda>& vendas) {
    double dinheiro = 0, debito = 0, credito = 0, pix = 0, fiado = 0;
    for (size_t i = 0; i < vendas.size(); i++) {
        switch (vendas[i].formaPagamento) {
        case 1: dinheiro += vendas[i].valorTotal; break;
        case 2: debito += vendas[i].valorTotal; break;
        case 3: credito += vendas[i].valorTotal; break;
        case 4: pix += vendas[i].valorTotal; break;
        case 5: fiado += vendas[i].valorTotal; break;
        }
    }

    cout << "\n--------------------- TOTAL DE TIPOS DE PAGAMENTOS ----------------------\n\n";
    cout << "Dinheiro:..........R$ " << fixed << setprecision(2) << dinheiro << endl;
    cout << "Débito:............R$ " << fixed << setprecision(2) << debito << endl;
    cout << "Crédito:...........R$ " << fixed << setprecision(2) << credito << endl;
    cout << "PIX:...............R$ " << fixed << setprecision(2) << pix << endl;
    cout << "Fiado:.............R$ " << fixed << setprecision(2) << fiado << endl;
}

// Realiza o fechamento do caixa, mostrando o resumo das vendas
void FecharCaixa(vector<Venda>& vendas, vector<Combustivel>& combustiveis, vector<fechamentoCaixa> &historico) {
    system("cls");
    cout << "========================== FECHAMENTO DE CAIXA ==========================\n\n";

    if (vendas.empty()) {
        cout << "Nenhuma venda registrada no período.\n\n";
        system("pause");
        return;
    }

    double totalGeral = 0.0;
    map<string, double> totalLitrosCombustivel;
    map<string, double> totalValorCombustivel;
    map<string, int> totalQuantProduto;
    map<string, double> totalValorProduto;

    for (const auto& v : vendas) {
        totalGeral += v.valorTotal;
        if (v.tipo == Venda::COMBUSTIVEL) {
            totalLitrosCombustivel[v.nomeItem] += v.quantVendido;
            totalValorCombustivel[v.nomeItem] += v.valorTotal;
        }
        else {
            totalQuantProduto[v.nomeItem] += static_cast<int>(v.quantVendido);
            totalValorProduto[v.nomeItem] += v.valorTotal;
        }
    }

    cout << "------------------------- VENDAS DE COMBUSTÍVEIS ------------------------\n\n";
    if (totalValorCombustivel.empty()) {
        cout << "Nenhuma venda de combustível registrada.\n";
    }
    else {
        for (const auto& par : totalValorCombustivel) {
            cout << "Combustível: " << left << setw(20) << par.first
                << "Litros: " << setw(10) << fixed << setprecision(2) << totalLitrosCombustivel[par.first]
                << "Total: R$ " << fixed << setprecision(2) << par.second << endl;
        }
    }

    cout << "\n-------------------------- VENDAS DE PRODUTOS ---------------------------\n\n";
    if (totalValorProduto.empty()) {
        cout << "Nenhuma venda de produto registrada.\n";
    }
    else {
        for (const auto& par : totalValorProduto) {
            cout << "Produto: " << left << setw(25) << par.first
                << "Unidades: " << setw(8) << totalQuantProduto[par.first]
                << "Total: R$ " << fixed << setprecision(2) << par.second << endl;
        }
    }

    cout << "\n-------------------------------------------------------------------------\n";
    cout << "VALOR TOTAL DAS VENDAS: R$ " << fixed << setprecision(2) << totalGeral << endl;
    cout << "-------------------------------------------------------------------------\n\n";

    imprimirValorTotalTiposPagamento(vendas);
    QuantidadeTanque(combustiveis);

    char confirmar;
    cout << "Deseja Realmente Fechar o Caixar ? (S/N): ";
    cin >> confirmar;

    if (toupper(confirmar) == 'S') {
        cout << "\nFechamento com Sucesso\n\n";
        fechamentoCaixa novoFechamento;
        novoFechamento.dataHoraFechamento = obterDataHoraAtual();
        novoFechamento.valorTotalVendido = totalGeral;
        historico.push_back(novoFechamento);

        vendas.clear();
        SalvarVendas(vendas);
        SalvarHistoricoFechamento(historico);
    }
    else {
        cout << "\nOperação Cancelada Pelo Usúario\n\n";
    }
    system("pause");
}

// Relatório de Clientes Devedores
void RelatorioClienteDevedores(const vector<Clientes>& cliente) {
    system("cls");
    cout << "============ RELATÓRIO DE CLIENTES DEVEDORORES ============\n\n";
    cout << left;
    cout << setw(5) << "ID"
        << setw(30) << "NOME"
        << "SALDO DEVEDOR" << endl;
    cout << "-----------------------------------------------------------\n\n";

    for (size_t i = 0; i < cliente.size(); i++) {
        if (cliente[i].saldoDevedor > 0.0) {
            cout << setw(5) << cliente[i].id
                << setw(30) << cliente[i].nome
                << "R$ "
                << fixed << setprecision(2) << cliente[i].saldoDevedor << endl;
            cout << "-----------------------------------------------------------\n";
        }
    }
    cout << endl;
    system("pause");
}


// ============= Funções de Histórico de Fechamento =============

// Carregar o Histórico de Fechamento do Arquivo Binário
void CarregarHistoricoFechamento(vector<fechamentoCaixa>& historico) {
    ifstream arquivo("historico.dat", ios::binary);
    if (!arquivo.is_open()) {
        return;
    }

    size_t tamanho = 0;
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; i++) {
        fechamentoCaixa f;
        arquivo.read(reinterpret_cast<char*>(&f), sizeof(fechamentoCaixa));
        historico.push_back(f);
    }
    arquivo.close();
}

// Savar Histórico de Fechamentos no Arquivo Binário
void SalvarHistoricoFechamento(const vector<fechamentoCaixa>& historico) {
    ofstream arquivo("historico.dat", ios::binary | ios::trunc);
    if (!arquivo.is_open()) {
        cout << "Erro: não foi possível abrir o arquivo de histórico\n\n";
        system("pause");
        return;
    }

    size_t tamanho = historico.size();
    arquivo.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    for (const auto& fechamento : historico) {
        arquivo.write(reinterpret_cast<const char*>(&fechamento), sizeof(fechamentoCaixa));
    }
    arquivo.close();
}

// Exibir o Histórico de Fechamento de Caixa
void ExibirHistoricoFechamento(const vector<fechamentoCaixa>& historico) {
    system("cls");
    cout << "================== HISTÓRICO DE FECHAMENTO DE CAIXA ==================\n\n";

    if (historico.empty()) {
        cout << "Nenhum Fechamento de Caixa Registrado\n\n";
        system("pause");
        return;
    }

    cout << left;
    cout << setw(15) << "DATA"
        << setw(12) << "HORA"
        << "VALOR TOTAL VENDIDO" << endl;
    cout << "---------------------------------------------------------------------\n\n";

    for (const auto& f : historico) {
        cout << setw(2) << setfill('0') << f.dataHoraFechamento.dia << "/"
            << setw(2) << setfill('0') << f.dataHoraFechamento.mes << "/"
            << setw(6) << setfill(' ') << f.dataHoraFechamento.ano;

        cout << setw(3) << setfill(' ') << " "
            << setw(2) << setfill('0') << f.dataHoraFechamento.hora << ":"
            << setw(2) << setfill('0') << f.dataHoraFechamento.minuto << ":"
            << setw(10) << setfill(' ') << f.dataHoraFechamento.segundo;

        cout << setfill(' ') << setw(2) << "R$ "
            << fixed << setprecision(2) << f.valorTotalVendido << endl;
    }
    cout << "---------------------------------------------------------------------\n\n";
    system("pause");
}