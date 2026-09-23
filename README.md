# ⛽ PDV Posto

Sistema de **Ponto de Venda (PDV)** para posto de combustível com loja de conveniência, desenvolvido em **C++** e executado no console. Controla venda de combustíveis e produtos, estoque dos tanques, clientes com fiado e fechamento de caixa.

## ✨ Funcionalidades

**Vendas (PDV)**
- Venda de combustível (por litro) e de produtos da conveniência
- Formas de pagamento: Dinheiro, Cartão de Débito, Cartão de Crédito, PIX e Fiado

**Combustíveis**
- Cadastro de combustível com preço por litro e capacidade do tanque
- Atualização de preço
- Entrada de estoque (litros)
- Listagem, exclusão e consulta do nível dos tanques

**Loja de conveniência**
- Cadastro de produtos, atualização de preço, entrada de estoque, listagem e exclusão

**Clientes**
- Cadastro (nome, CPF e contato), listagem e exclusão
- Consulta de saldo devedor e registro de pagamentos

**Relatórios e caixa**
- Total vendido por forma de pagamento
- Fechamento de caixa com data e hora
- Histórico de fechamentos
- Relatório de clientes devedores

**Validação de entradas**
- Tratamento de números inteiros, números decimais e textos vazios, evitando que o programa trave com entradas inválidas

## 🛠️ Tecnologias

- C++ (STL: `vector`, `string`, `map`)
- Visual Studio (projeto `.sln` / `.vcxproj`)
- Persistência em arquivos binários (`.dat`)

## 📁 Arquivos de dados

| Arquivo | Conteúdo |
|---|---|
| `combustiveis.dat` | Combustíveis, preços e estoque |
| `Produtos.dat` | Produtos da conveniência |
| `Clientes.dat` | Clientes e saldo devedor |
| `vendas.dat` | Vendas realizadas |
| `historico.dat` | Histórico de fechamentos de caixa |

## ▶️ Como executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/RafaelPires999/PDV_Posto.git
   ```
2. Abra o arquivo `PDV_Posto.sln` no **Visual Studio**.
3. Compile e execute (`Ctrl + F5`).

> O sistema foi feito para **Windows** (usa `fopen_s`, função do compilador da Microsoft).

## 👨‍💻 Autor

**Rafael Aguiar Pires** — estudante de Análise e Desenvolvimento de Sistemas na FAI (Adamantina-SP)
[GitHub](https://github.com/RafaelPires999)
