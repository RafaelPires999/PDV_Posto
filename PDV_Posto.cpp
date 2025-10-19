#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <cstdio>
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

// Tratamento de Dados
void VerificarSim_Nao(char& confirmar);
int lerInteiroValido(const string& mensagem);
double lerFlutuanteValido(const string& mensagem);
string lerStringNaoVazio(const string& mensagem);

// Funções de Combustível
void GerenciarCombustivel(vector<Combustivel>& combustiveis);
void CarregarCombustiveis(vector<Combustivel>& combustiveis);
void SalvarCombustiveis(const vector<Combustivel>& combustiveis);
void CadastrarCombustivel(vector<Combustivel>& combustiveis);
void AtualizarPreco(vector<Combustivel>& combustiveis);
void AddEstoqueCombustivel(vector<Combustivel> &combustiveis);
void ExcluirCombustivel(vector<Combustivel>& combustiveis);
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
void ExcluirProduto(vector<ProdutoLoja>& produto);

// Funções de Clientes
void GerenciamentoCliente(vector<Clientes>& cliente);
void CarregarCliente(vector<Clientes>& cliente);
void SalvarCliente(vector<Clientes>& cliente);
void CadastrarCliente(vector<Clientes>& cliente);
void ListarCliente(const vector<Clientes>& cliente);
int BuscaClienteNome(const vector<Clientes>& cliente, string nomeCliente);
void consultarSaldo(vector<Clientes>& cliente);
void RegistrarPagamentoCliente(vector<Clientes>& cliente);
void ExcluirCliente(vector<Clientes>& cliente);

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


// ===================== TRATAMENTO DE DADOS ======================

// Verificação de sim ou não
void VerificarSim_Nao(char &confirmar) {
    while (toupper(confirmar) != 'S' && toupper(confirmar) != 'N') {
        system("cls");
        cout << "Dígito Inválido\n\n";
        cout << "Dígite Novamente (S/N): ";
        cin >> confirmar;
        system("cls");
    }
}

// Verificação Somente números inteiros
int lerInteiroValido(const string& mensagem) {
    int numero;
    while (true) {
        cout << mensagem;
        cin >> numero;

        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
        else {
            system("cls");
            cout << "Entrada inválida. Por favor, digite apenas um número inteiro.\n\n";
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Verificação de Números Flutuante
double lerFlutuanteValido(const string& mensagem) {
    double numero;
    while (true) {
        cout << mensagem;
        cin >> numero;

        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
        else {
            system("cls");
            cout << "Endrada Inválida. Digite Somente Números.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Verificar Campo Vazio em String
string lerStringNaoVazio(const string& mensagem) {
    string texto;
    while (true) {
        cout << mensagem;
        if (!getline(cin, texto)) {
            cin.clear();
            texto.clear();
        }

        size_t inicio = texto.find_first_not_of(" \t\r\n");
        if (inicio == string::npos) {
            system("cls");
            cout << "Entrada inválida. Campo não pode ser vazio\n\n";
            continue;
        }
        size_t fim = texto.find_last_not_of(" \t\r\n");
        return texto.substr(inicio, fim - inicio + 1);
    }
}

// ==================== Funções de Combustível ====================

// Salva os dados dos combustíveis no arquivo binário
void SalvarCombustiveis(const vector<Combustivel>& combustiveis) {
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Combustiveis.dat", "wb") != 0 || arquivo == nullptr) {
        cout << "Não foi possível abrir arquivo\n\n";
        system("pause");
        return;
    }

    size_t tamanho = combustiveis.size();
    fwrite(&tamanho, sizeof(size_t), 1, arquivo);
    for (const auto& c : combustiveis) {
        size_t nomeLen = c.nome.size();
        fwrite(&nomeLen, sizeof(size_t), 1, arquivo);
        fwrite(c.nome.c_str(), sizeof(char), nomeLen, arquivo);
        fwrite(&c.precoPorLitro, sizeof(double), 1, arquivo);
        fwrite(&c.capacidadeTanque, sizeof(double), 1, arquivo);
        fwrite(&c.estoqueLitros, sizeof(double), 1, arquivo);
    }
    fclose(arquivo);
}

// Carrega os dados dos combustíveis do arquivo binário
void CarregarCombustiveis(vector<Combustivel>& combustiveis) {
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Combustiveis.dat", "rb") != 0 || arquivo == nullptr) {
        return;
    }

    size_t tamanho = 0;
    fread(&tamanho, sizeof(size_t), 1, arquivo);
    for (size_t i = 0; i < tamanho; i++) {
        Combustivel c;
        size_t nomeLen = 0;
        fread(&nomeLen, sizeof(size_t), 1, arquivo);
        c.nome.resize(nomeLen);
        fread(&c.nome[0], sizeof(char), nomeLen, arquivo);
        fread(&c.precoPorLitro, sizeof(double), 1, arquivo);
        fread(&c.capacidadeTanque, sizeof(double), 1, arquivo);
        fread(&c.estoqueLitros, sizeof(double), 1, arquivo);
        combustiveis.push_back(c);
    }
    fclose(arquivo);
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
        cout << "4 - Excluir Combustível\n";
        cout << "5 - Listar Combustíveis\n\n";
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
            ExcluirCombustivel(combustiveis);
            break;
        case 5:
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
    char confirma, op;

    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "======== CADASTRAR NOVO COMBUSTÍVEL ========\n\n";
        cadastro.nome = lerStringNaoVazio("Digite o nome do Combustível (Ex. Etanol): ");
        transform(cadastro.nome.begin(), cadastro.nome.end(), cadastro.nome.begin(), ::toupper);

        int indice = BuscaCombustivel(combustiveis, cadastro.nome);
        if (indice != -1){
            system("cls");
            cout << "Combustível Já Cadastrado. \n\nDesejar Tentar Outro Combustível ? (S/N): ";
            cin >> op;
            VerificarSim_Nao(op);
            if (toupper(op) == 'S') continue;
            else return;
        }

        cadastro.precoPorLitro = lerFlutuanteValido("Digite o preço por Litro: R$ ");
        cadastro.capacidadeTanque = lerFlutuanteValido("Capacidade Tanque: ");
        cadastro.estoqueLitros = lerFlutuanteValido("Digite a quantidade inicial em estoque (Litros): ");

        if (cadastro.estoqueLitros > cadastro.capacidadeTanque) {
            system("cls");
            cout << "Estoque Acima da Capacidade do Tanque\n\n";
            cadastro.estoqueLitros = lerFlutuanteValido("Digite a quantidade inicial em estoque (Litros): ");
        }

        cout << "\n\nDeseja confirmar o cadastro? (S/N): ";
        cin >> confirma;

        VerificarSim_Nao(confirma);

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

        VerificarSim_Nao(op);

    } while (toupper(op) == 'S');
}

// Atualiza o preço de um combustível
void AtualizarPreco(vector<Combustivel>& combustiveis) {
    string nome;
    char confirmar;
    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "===================== ATUALIZAR PREÇO =====================\n\n";
        nome = lerStringNaoVazio("Qual combustível deseja atualizar? (Ex. Etanol): ");
        transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

        int indice = BuscaCombustivel(combustiveis, nome);

        if (indice != -1) {
            cout << "\nPreço atual do " << combustiveis[indice].nome
                << ": R$ " << fixed << setprecision(2) << combustiveis[indice].precoPorLitro << "\n";

            double novoPreco;
            novoPreco = lerFlutuanteValido("Digite o novo preço por litro: R$ ");

            combustiveis[indice].precoPorLitro = novoPreco;
            SalvarCombustiveis(combustiveis);

            cout << "\nPreço atualizado com sucesso!\n\n";
        }
        else {
            cout << "\nCombustível não encontrado!\n\n";
        }

        cout << "Deseja Atualizar Outro Preço ? (S/N): ";
        cin >> confirmar;

        VerificarSim_Nao(confirmar);
    } while (toupper(confirmar) == 'S');
}

// Adiciona estoque a um combustível
void AddEstoqueCombustivel(vector<Combustivel> &combustiveis) {
    string nome;
    char confirmar;
    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "================== ENTRADA DE ESTOQUE ===================\n\n";
        nome = lerStringNaoVazio("Qual Combustível Deseja Inserir Estoque ? (Ex. Etanol): ");
        transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

        int indice = BuscaCombustivel(combustiveis, nome);
        if (indice != -1) {
            cout << "\nEstoque Atual do " << combustiveis[indice].nome
                << ": " << fixed << setprecision(2) << combustiveis[indice].estoqueLitros;

            double addEstoque;
            addEstoque = lerFlutuanteValido("\nDigite Quantidade Para Estoque: ");

            combustiveis[indice].estoqueLitros += addEstoque;
            SalvarCombustiveis(combustiveis);
            cout << "\nEstoque Atualizado com Sucesso\n\n";
        }
        else {
            cout << "\nCombustível não Encontrado\n\n";
        }

        cout << "Deseja Inserir Outro Estoque ? (S/N): ";
        cin >> confirmar;

        VerificarSim_Nao(confirmar);
    } while (toupper(confirmar) == 'S');
}

// Excluir Combustível
void ExcluirCombustivel(vector<Combustivel>& combustiveis) {
    string nome;
    char confirmar, op;
    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "==================== EXCLUIR COMBUSTÍVEL =======================\n\n";
        nome = lerStringNaoVazio("Qual combustível Deseja Excluir ? (Ex. Etanol): ");
        transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

        int indice = BuscaCombustivel(combustiveis, nome);
        cout << endl;

        if (indice != -1) {
            cout << "Combustível: " << setw(15) << combustiveis[indice].nome << "\n";
            cout << "Preço:" << setw(18) << "R$ " << fixed << setprecision(2) << combustiveis[indice].precoPorLitro << "\n";
            cout << "Estoque:" << setw(20) << fixed << setprecision(2) << combustiveis[indice].estoqueLitros << " Litros\n";
            cout << "--------------------------------------------------------------\n\n";

            cout << "Deseja Excluir ? (S/N): ";
            cin >> confirmar;

            VerificarSim_Nao(confirmar);

            if (toupper(confirmar) == 'S') {
                if (combustiveis[indice].estoqueLitros == 0) {
                    combustiveis.erase(combustiveis.begin() + indice);
                    SalvarCombustiveis(combustiveis);
                    cout << "\nCombustível Excluido com Sucesso\n\n";
                }
                else {
                    system("cls");
                    cout << "Combustível com Estoque\n\n";
                    cout << "Combustivel: " << combustiveis[indice].nome;
                    cout << "\nEstoque:     " << fixed << setprecision(2) << combustiveis[indice].estoqueLitros << " Litros";
                    cout << "\n\nExclusão Cancelado\n\n";
                }
            }
            else {
                cout << "\nExclusão Cancelado\n\n";
            }
        }
        else {
            cout << "\nCombustível Não Encontrado\n\n";
        }

        cout << "Deseja Excluir Outro Combustível ? (S/N): ";
        cin >> op;
        
        VerificarSim_Nao(op);
    } while (toupper(op) == 'S');
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
        cout << "\n4 - Excluir Produto";
        cout << "\n5 - Listar Produto\n\n";
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
            ExcluirProduto(produto);
            break;
        case 5:
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
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Produtos.dat", "rb") != 0 || arquivo == nullptr) {
        return;
    }

    size_t tamanho = 0;
    fread(&tamanho, sizeof(size_t), 1, arquivo);
    for (size_t i = 0; i < tamanho; i++) {
        ProdutoLoja p;
        fread(&p.id, sizeof(int), 1, arquivo);
        size_t nomeLen = 0;
        fread(&nomeLen, sizeof(size_t), 1, arquivo);
        p.nome.resize(nomeLen);
        fread(&p.nome[0], sizeof(char), nomeLen, arquivo);
        fread(&p.precoUnitario, sizeof(double), 1, arquivo);
        fread(&p.quantEstoque, sizeof(int), 1, arquivo);
        produto.push_back(p);
    }
    fclose(arquivo);
}

// Salva os produtos da loja no arquivo binário
void SalvarProduto(vector<ProdutoLoja> &produto) {
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Produtos.dat", "wb") != 0 || arquivo == nullptr) {
        cout << "Não foi possível abrir o arquivo\n\n";
        system("pause");
        return;
    }

    size_t tamanho = produto.size();
    fwrite(&tamanho, sizeof(size_t), 1, arquivo);
    for (const auto& p : produto) {
        fwrite(&p.id, sizeof(int), 1, arquivo);
        size_t nomeLen = p.nome.size();
        fwrite(&nomeLen, sizeof(size_t), 1, arquivo);
        fwrite(p.nome.c_str(), sizeof(char), nomeLen, arquivo);
        fwrite(&p.precoUnitario, sizeof(double), 1, arquivo);
        fwrite(&p.quantEstoque, sizeof(int), 1, arquivo);
    }
    fclose(arquivo);
}

// Cadastra um novo produto na loja
void CadastrarProduto(vector<ProdutoLoja>& produto) {
    ProdutoLoja cadastro;
    char confirmar, op;

    do {
        system("cls");
        cout << "=========== CADASTRAR NOVO PRODUTO ===========\n\n";
        cadastro.id = lerInteiroValido("Código do Produto: ");

        int indice = BuscaProduto(produto, cadastro.id);
        if (indice != -1) {
            system("cls");
            cout << "Código Já Cadastrado. \n\nDeseja tentar outro código? (S/N): ";
            cin >> op;
            VerificarSim_Nao(op);
            if (toupper(op) == 'S') continue;
            else return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cadastro.nome = lerStringNaoVazio("Nome do Produto (Ex. Água): ");
        transform(cadastro.nome.begin(), cadastro.nome.end(), cadastro.nome.begin(), ::toupper);

        cadastro.precoUnitario = lerFlutuanteValido("Preço Unitário: ");
        cadastro.quantEstoque = lerInteiroValido("Estoque Inicial: ");

        cout << "\n\nDeseja Confirmar Cadastro ? (S/N): ";
        cin >> confirmar;

        VerificarSim_Nao(confirmar);

        if (toupper(confirmar) == 'S') {
            produto.push_back(cadastro);
            SalvarProduto(produto);
            cout << "\n\nCadastro Confirmado com Sucesso\n\n";
        }

        cout << "Deseja Cadastrar Outro Produto ? (S/N): ";
        cin >> op;

        VerificarSim_Nao(op);
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
    char confirmar;
    do {
        system("cls");
        cout << "================ ATUALIZAR PREÇO DO PRODUTO ================\n\n";
        id = lerInteiroValido("Qual Produto Deseja Aualizar o Preço: ");

        int indice = BuscaProduto(produto, id);
        if (indice != -1) {
            cout << "\nProduto: " << produto[indice].nome;
            cout << "\nPreço Atual: R$ " << fixed << setprecision(2) << produto[indice].precoUnitario;

            double novopreco;
            novopreco = lerFlutuanteValido("\n\nDigite o Preço Atual: ");

            produto[indice].precoUnitario = novopreco;
            SalvarProduto(produto);

            cout << "\nPreço Atualizado com Sucesso\n\n";
        }
        else {
            cout << "\nCódigo Não Encontrado\n\n";
        }

        cout << "Deseja Alterar Outro Preço ? (S/N): ";
        cin >> confirmar;

        VerificarSim_Nao(confirmar);
    } while (toupper(confirmar) == 'S');
}

// Exluir Produto
void ExcluirProduto(vector<ProdutoLoja>& produto) {
    int cod;
    char confirmar, op;
    do {
        system("cls");
        cout << "====================== EXCLUIR PRODUTO ======================\n\n";
        cod = lerInteiroValido("Digite o Código do Produto Que Deseja Excluir: ");

        int indice = BuscaProduto(produto, cod);
        cout << endl;

        if (indice != -1) {
            cout << right;
            cout << setw(7) << produto[indice].id
                << setw(20) << produto[indice].nome
                << setw(15) << "R$ " << fixed << setprecision(2) << produto[indice].precoUnitario
                << setw(11) << produto[indice].quantEstoque;
            cout << "\n-------------------------------------------------------------\n";

            cout << "\nDeseja Excluir ? (S/N): ";
            cin >> confirmar;

            VerificarSim_Nao(confirmar);

            if (toupper(confirmar) == 'S') {
                produto.erase(produto.begin() + indice);
                SalvarProduto(produto);
                cout << "\nProduto Excluido com Sucesso\n\n";
            }
            else {
                cout << "\nExclusão Cancelado\n\n";
            }
        }
        else {
            cout << "\Produto Não Encontrado\n\n";
        }

        cout << "Deseja Excluir Outro Produto ? (S/N): ";
        cin >> op;

        VerificarSim_Nao(op);
    } while (toupper(op) == 'S');
}

// Adiciona estoque a um produto
void AddEstoqueProduto(vector<ProdutoLoja> &produto) {
    int id;
    char confirmar;
    do {
        system("cls");
        cout << "============== ADICIONAR ESTOQUE PRODUTO ===============\n\n";
        id = lerInteiroValido("Digite o Código do Produto: ");

        int indice = BuscaProduto(produto, id);
        if (indice != -1) {
            cout << "\nProduto: " << produto[indice].nome;
            cout << "\nEstoque Atual: " << produto[indice].quantEstoque;

            int estoqueNovo;
            estoqueNovo = lerInteiroValido("\n\nInsira Quantidade: ");

            produto[indice].quantEstoque += estoqueNovo;
            SalvarProduto(produto);

            cout << "\nEstoque Atualizado com Sucesso\n\n";
        }

        cout << "Deseja Adicionar Outro Estoque ? (S/N): ";
        cin >> confirmar;

        VerificarSim_Nao(confirmar);
    } while (toupper(confirmar) == 'S');
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
        cout << "4 - Registrar Pagamento de Dívida\n";
        cout << "5 - Exluir Cliente\n\n";
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
        case 5:
            ExcluirCliente(cliente);
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
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Clientes.dat", "rb") != 0 || arquivo == nullptr) {
        return;
    }

    size_t tamanho = 0;
    fread(&tamanho, sizeof(size_t), 1, arquivo);
    for (size_t i = 0; i < tamanho; i++) {
        Clientes c;
        fread(&c.id, sizeof(int), 1, arquivo);

        size_t nomeLen;
        fread(&nomeLen, sizeof(size_t), 1, arquivo);
        c.nome.resize(nomeLen);
        fread(&c.nome[0], sizeof(char), nomeLen, arquivo);

        size_t cpfLen;
        fread(&cpfLen, sizeof(size_t), 1, arquivo);
        c.cpf.resize(cpfLen);
        fread(&c.cpf[0], sizeof(char), cpfLen, arquivo);

        size_t contatoLen;
        fread(&contatoLen, sizeof(size_t), 1, arquivo);
        c.contato.resize(contatoLen);
        fread(&c.contato[0], sizeof(char), contatoLen, arquivo);

        fread(&c.saldoDevedor, sizeof(double), 1, arquivo);
        cliente.push_back(c);
    }
    fclose(arquivo);
}

// Salvar os Clientes do Arquivo Binário
void SalvarCliente(vector<Clientes>& cliente) {
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Clientes.dat", "wb") != 0 || arquivo == nullptr) {
        cout << "Não foi possível abrir o arquivo\n\n";
        system("pause");
        return;
    }

    size_t tamanho = cliente.size();
    fwrite(&tamanho, sizeof(size_t), 1, arquivo);
    for (const auto& c : cliente) {
        fwrite(&c.id, sizeof(int), 1, arquivo);
        
        size_t nomeLen = c.nome.size();
        fwrite(&nomeLen, sizeof(size_t), 1, arquivo);
        fwrite(c.nome.c_str(), sizeof(char), nomeLen, arquivo);

        size_t cpfLen = c.cpf.size();
        fwrite(&cpfLen, sizeof(size_t), 1, arquivo);
        fwrite(c.cpf.c_str(), sizeof(char), cpfLen, arquivo);

        size_t contatoLen = c.contato.size();
        fwrite(&contatoLen, sizeof(size_t), 1, arquivo);
        fwrite(c.contato.c_str(), sizeof(char), contatoLen, arquivo);

        fwrite(&c.saldoDevedor, sizeof(double), 1, arquivo);
    }
    fclose(arquivo);
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

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cadastro.nome = lerStringNaoVazio("\nNome: ");
        transform(cadastro.nome.begin(), cadastro.nome.end(), cadastro.nome.begin(), ::toupper);

        cadastro.cpf = lerStringNaoVazio("CPF: ");
        cadastro.contato = lerStringNaoVazio("Contato: ");
        cadastro.saldoDevedor = lerFlutuanteValido("Saldo Inicial: R$ ");

        cout << "\nDeseja Confirmar Cadastro ? (S/N): ";
        cin >> confirmar;
        VerificarSim_Nao(confirmar);

        if (toupper(confirmar) == 'S') {
            cliente.push_back(cadastro);
            SalvarCliente(cliente);
            cout << "\n\nCadastro Realizado com Sucesso\n\n";
            id++;
        }
        cout << "Deseja Cadastrar Outro Cliente ? (S/N): ";
        cin >> opcao;

        VerificarSim_Nao(opcao);
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

// Excluir Cliente
void ExcluirCliente(vector<Clientes>& cliente) {
    string nome;
    char confirmar, op;
    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "===================================== EXCLUIR CLIENTES ======================================\n\n";
        nome = lerStringNaoVazio("Qual Cliente Deseja Excluir ?: ");
        transform(nome.begin(), nome.end(), nome.begin(), ::toupper);

        int indice = BuscaClienteNome(cliente, nome);
        cout << endl;

        if (indice != -1) {
            cout << left;
            cout << setw(5) << "ID"
                << setw(30) << "NOME"
                << setw(18) << "CPF"
                << setw(20) << "CONTATO"
                << "SALDO DEVEDOR" << endl;
            cout << "---------------------------------------------------------------------------------------------\n\n";
            cout << setw(5) << cliente[indice].id
                << setw(30) << cliente[indice].nome
                << setw(18) << cliente[indice].cpf
                << setw(20) << cliente[indice].contato
                << "R$ "
                << fixed << setprecision(2) << cliente[indice].saldoDevedor << endl;
            cout << "---------------------------------------------------------------------------------------------\n";

            cout << "\nDeseja Excluir ?(S/N): ";
            cin >> confirmar;

            VerificarSim_Nao(confirmar);

            if (toupper(confirmar) == 'S') {
                if (cliente[indice].saldoDevedor == 0) {
                    cliente.erase(cliente.begin() + indice);
                    SalvarCliente(cliente);
                    cout << "\nCliente Excluido com Sucesso\n\n";
                }
                else {
                    cout << "\nCliente Não Pode Ser Excluido\n\n";
                    cout << "Saldo Dívida: R$ " << fixed << setprecision(2) << cliente[indice].saldoDevedor << "\n\n";
                }
            }
            else {
                cout << "\nExclusão Cancelado\n\n";
            }
        }
        else {
            cout << "\Cliente Não Encontrado\n\n";
        }

        cout << "Deseja Excluir Outro Cliente ? (S/N): ";
        cin >> op;

        VerificarSim_Nao(op);
    } while (toupper(op) == 'S');
}

// Consultar Saldo do Cliente
void consultarSaldo(vector<Clientes>& cliente) {
    string nome;
    char confirmar;
    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "==================== CONSULTAR SALDO =====================\n\n";
        nome = lerStringNaoVazio("Digite o Nome do Cliente: ");
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

        cout << "Deseja Consultar Saldo de Outro Cliente ? (S/N): ";
        cin >> confirmar;

        VerificarSim_Nao(confirmar);
    } while (toupper(confirmar) == 'S');
}

// Registrar Pagamento Cliente
void RegistrarPagamentoCliente(vector<Clientes>& cliente) {
    string nome;
    char confirmar, op;
    double valorPagamento = 0.0;
    do {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "============= REGISTRAR PAGAMENTO DE DÍVIDA ===============\n\n";
        nome = lerStringNaoVazio("Digite o Nome do Cliente: ");
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

            valorPagamento = lerFlutuanteValido("\nDigite o Valor do Pagamento: R$ ");

            while (valorPagamento < 0 || round(valorPagamento * 100.0) > round(cliente[indice].saldoDevedor * 100.0)) {
                system("cls");
                cout << "============= REGISTRAR PAGAMENTO DE DÍVIDA ===============\n\n";
                cout << "Erro, valor inválido, negativo ou maior que o saldo devedor!\n\n";
                cout << "Saldo Devedor Atual: R$ " << fixed << setprecision(2) << cliente[indice].saldoDevedor << endl;
                valorPagamento = lerFlutuanteValido("\nDigite o Valor do Pagamento: R$ ");
            }

            cout << "\n\nDeseja Confirmar ? (S/N): ";
            cin >> confirmar;

            VerificarSim_Nao(confirmar);

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

        cout << "Deseja Registrar Outro Pagamento ? (S/N): ";
        cin >> op;

        VerificarSim_Nao(op);
    } while (toupper(op) == 'S');
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
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Vendas.dat", "rb") != 0 || arquivo == nullptr) {
        return;
    }

    size_t tamanho = 0;
    fread(&tamanho, sizeof(size_t), 1, arquivo);
    for (size_t i = 0; i < tamanho; i++) {
        Venda v;
        int tipoInt;
        fread(&tipoInt, sizeof(int), 1, arquivo);
        v.tipo = (tipoInt == 0) ? Venda::COMBUSTIVEL : Venda::PRODUTO;

        size_t nomeLen = 0;
        fread(&nomeLen, sizeof(size_t), 1, arquivo);
        v.nomeItem.resize(nomeLen);
        fread(&v.nomeItem[0], sizeof(char), nomeLen, arquivo);

        fread(&v.quantVendido, sizeof(double), 1, arquivo);
        fread(&v.valorTotal, sizeof(double), 1, arquivo);
        fread(&v.formaPagamento, sizeof(int), 1, arquivo);
        vendas.push_back(v);
    }
    fclose(arquivo);
}

// Salva as vendas no arquivo binário
void SalvarVendas(vector<Venda>& vendas) {
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Vendas.dat", "wb") != 0 || arquivo == nullptr) {
        cout << "Não foi possível abrir o arquivo\n\n";
        system("pause");
        return;
    }

    size_t tamanho = vendas.size();
    fwrite(&tamanho, sizeof(size_t), 1, arquivo);

    for (const auto& v : vendas) {
        int tipoInt = (v.tipo == Venda::COMBUSTIVEL ? 0 : 1);
        fwrite(&tipoInt, sizeof(int), 1, arquivo);

        size_t nomeLen = v.nomeItem.size();
        fwrite(&nomeLen, sizeof(size_t), 1, arquivo);
        fwrite(v.nomeItem.c_str(), sizeof(char), nomeLen, arquivo);

        fwrite(&v.quantVendido, sizeof(double), 1, arquivo);
        fwrite(&v.valorTotal, sizeof(double), 1, arquivo);
        fwrite(&v.formaPagamento, sizeof(int), 1, arquivo);
    }
    fclose(arquivo);
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
            char confirmar;
            do {
                system("cls");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "=================== COMBUSTÍVEL ====================\n\n";
                nomeCombustivel = lerStringNaoVazio("Digite Tipo Combustível (Ex. Etanol): ");
                transform(nomeCombustivel.begin(), nomeCombustivel.end(), nomeCombustivel.begin(), ::toupper);

                int indice = BuscaCombustivel(combustivel, nomeCombustivel);
                if (indice != -1) {
                    double litros;
                    litros = lerFlutuanteValido("Digite a Quatidade em Litros: ");

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

                cout << "Deseja Adicionar Outro Combustível ? (S/N): ";
                cin >> confirmar;

                VerificarSim_Nao(confirmar);
            } while (toupper(confirmar) == 'S');
        }
        else if (op == 2) {
            int idProduto;
            char confirmar;
            do {
                system("cls");
                cout << "=============== PRODUTOS DA LOJA =================\n\n";
                idProduto = lerInteiroValido("Digite o código do Produto: ");

                int indice = BuscaProduto(produto, idProduto);
                if (indice != -1) {
                    cout << "\nProduto: " << produto[indice].nome;
                    int quantidade;
                    quantidade = lerInteiroValido("\nDigite Quantidade: ");

                    if (quantidade > 0 && produto[indice].quantEstoque >= quantidade) {
                        Venda novaVenda;
                        novaVenda.tipo = Venda::PRODUTO;
                        novaVenda.nomeItem = produto[indice].nome;
                        novaVenda.quantVendido = quantidade;
                        novaVenda.valorTotal = quantidade * produto[indice].precoUnitario;

                        itemVenda.push_back(novaVenda);
                        totalVenda += novaVenda.valorTotal;
                        produto[indice].quantEstoque -= quantidade;
                        cout << "\nItem Adicionado\n\n";
                    }
                    else {
                        cout << "Estoque Insuficiente ou Quantidade Inválida\n\n";
                    }
                }
                else {
                    cout << "Produto Não Encontrado\n\n";
                }

                cout << "Deseja Adicionar Outro Produto ? (S/N): ";
                cin >> confirmar;

                VerificarSim_Nao(confirmar);
            } while (toupper(confirmar) == 'S');
        }
        else if (op != 0) {
            cout << "\nOpção Inválida\n";
        }

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

                VerificarSim_Nao(confirmar);

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

    VerificarSim_Nao(confirmar);
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
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Historico.dat", "rb") != 0 || arquivo == nullptr) {
        return;
    }

    size_t tamanho = 0;
    if (fread(&tamanho, sizeof(size_t), 1, arquivo) != 1) {
        fclose(arquivo);
        return;
    }

    for (size_t i = 0; i < tamanho; i++) {
        fechamentoCaixa f;
        fread(&f.dataHoraFechamento.dia, sizeof(int), 1, arquivo);
        fread(&f.dataHoraFechamento.mes, sizeof(int), 1, arquivo);
        fread(&f.dataHoraFechamento.ano, sizeof(int), 1, arquivo);
        fread(&f.dataHoraFechamento.hora, sizeof(int), 1, arquivo);
        fread(&f.dataHoraFechamento.minuto, sizeof(int), 1, arquivo);
        fread(&f.dataHoraFechamento.segundo, sizeof(int), 1, arquivo);
        fread(&f.valorTotalVendido, sizeof(double), 1, arquivo);

        historico.push_back(f);
    }
    fclose(arquivo);
}

// Savar Histórico de Fechamentos no Arquivo Binário
void SalvarHistoricoFechamento(const vector<fechamentoCaixa>& historico) {
    FILE* arquivo = nullptr;
    if (fopen_s(&arquivo, "Historico.dat", "wb") != 0 || arquivo == nullptr) {
        cout << "Não foi possível abrir o arquivo\n\n";
        system("pause");
        return;
    }

    size_t tamanho = historico.size();
    fwrite(&tamanho, sizeof(size_t), 1, arquivo);

    for (const auto& f : historico) {
        fwrite(&f.dataHoraFechamento.dia, sizeof(int), 1, arquivo);
        fwrite(&f.dataHoraFechamento.mes, sizeof(int), 1, arquivo);
        fwrite(&f.dataHoraFechamento.ano, sizeof(int), 1, arquivo);
        fwrite(&f.dataHoraFechamento.hora, sizeof(int), 1, arquivo);
        fwrite(&f.dataHoraFechamento.minuto, sizeof(int), 1, arquivo);
        fwrite(&f.dataHoraFechamento.segundo, sizeof(int), 1, arquivo);
        fwrite(&f.valorTotalVendido, sizeof(double), 1, arquivo);
    }
    fclose(arquivo);
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
        ostringstream ssData;
        ostringstream ssHora;

        ssData.imbue(locale::classic());
        ssHora.imbue(locale::classic());

        ssData << setfill('0') << setw(2) << f.dataHoraFechamento.dia << "/"
            << setw(2) << f.dataHoraFechamento.mes << "/"
            << setw(4) << f.dataHoraFechamento.ano;

        ssHora << setfill('0') << setw(2) << f.dataHoraFechamento.hora << ":"
            << setw(2) << f.dataHoraFechamento.minuto << ":"
            << setw(2) << f.dataHoraFechamento.segundo;

        cout << left
            << setw(15) << ssData.str()
            << setw(15) << ssHora.str()
            << "R$ " << fixed << setprecision(2) << f.valorTotalVendido
            << endl;
    }
    cout << "---------------------------------------------------------------------\n\n";
    system("pause");
}