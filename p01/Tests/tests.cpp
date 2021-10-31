#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "parque.h"
#include <string>

using testing::Eq;

TEST(test_1, abrirParque)
{
    ParqueEstacionamento p1(4, 6);
    // Testa se o parque foi aberto com a lotacao indicada
    ASSERT_EQ(4, p1.getNumLugares());
    // Testa se o parque foi aberto com o numero maximo de clientes indicado
    ASSERT_EQ(6, p1.getNumMaximoClientes());
}

TEST(test_1, adicionarCliente)
{
    ParqueEstacionamento p1(3, 5);
    // Testa se deixa adicionar um novo cliente
    ASSERT_EQ(true, p1.adicionaCliente("Joao"));
    p1.adicionaCliente("Antonio");
    p1.adicionaCliente("Rui");
    p1.adicionaCliente("Maria");
    p1.adicionaCliente("Clara");
    // Testa se recusa novo cliente quando numero maximo de clientes foi atingido
    ASSERT_EQ(false, p1.adicionaCliente("Paula"));
    // Testa se retorna a posicaoo correcta do cliente
    ASSERT_EQ(1, p1.posicaoCliente("Antonio"));
    // Testa se retorna -1 caso o cliente nao exista
    ASSERT_EQ(-1, p1.posicaoCliente("Joana"));
}

TEST(test_1, entrarParque)
{
    ParqueEstacionamento p1(3, 5);
    p1.adicionaCliente("Joao");
    p1.adicionaCliente("Maria");
    p1.adicionaCliente("Antonio");
    p1.adicionaCliente("Rui");
    // Testa se deixa entrar no parque um cliente existente
    ASSERT_EQ(true, p1.entrar("Maria"));
    // Testa se nao deixa entrar no parque um cliente que nao existe
    ASSERT_EQ(false, p1.entrar("Paula"));
    // Testa se nao dexia entrar em cliente que ja la esta
    ASSERT_EQ(false, p1.entrar("Maria"));
    p1.entrar("Joao");
    p1.entrar("Antonio");
    // Testa se nao deixa entrar quando a lotacao esta completa
    ASSERT_EQ(false, p1.entrar("Rui"));
}

TEST(test_1, retirarCliente)
{
    ParqueEstacionamento p1(3, 5);
    p1.adicionaCliente("Joao");
    p1.adicionaCliente("Maria");
    p1.adicionaCliente("Antonio");
    p1.entrar("Maria");
    // Testa se nao deixa remover cliente que esta dentro do parque
    ASSERT_EQ(false, p1.retiraCliente("Maria"));
    // Testa se deixa remover cliente que esta fora do parque
    ASSERT_EQ(true, p1.retiraCliente("Antonio"));
    // Testa se nao deixa remover cliente que nao existe
    ASSERT_EQ(false, p1.retiraCliente("Ana"));
}

TEST(test_1, sairParque)
{
    ParqueEstacionamento p1(3, 5);
    p1.adicionaCliente("Joao");
    p1.adicionaCliente("Maria");
    p1.adicionaCliente("Rui");
    p1.entrar("Maria");
    p1.entrar("Joao");
    p1.entrar("Rui");
    // Testa se um cliente estacionado no parque, sai.
    ASSERT_EQ(true, p1.sair("Maria"));
    // Testa se nao deixa sair um cliente que nao esta estacionado.
    ASSERT_EQ(false, p1.sair("Maria"));
    // Testa se nao deixa sair um cliente que nao existe.
    ASSERT_EQ(false, p1.sair("Antonio"));
}

TEST(test_1, lugaresLotacaoParque)
{
    ParqueEstacionamento p1(3, 5);
    p1.adicionaCliente("Joao");
    p1.adicionaCliente("Maria");
    p1.adicionaCliente("Antonio");
    p1.entrar("Maria");
    p1.entrar("Antonio");
    // Testa se Lotacao do parque esta correcta
    ASSERT_EQ(3, p1.getNumLugares());
    // Testa se o numero de viaturas presentes no parque esta correcto
    ASSERT_EQ(2, p1.getNumLugaresOcupados());
    // Testa se o o numero de clientes registados no parque esta correcto
    ASSERT_EQ(3, p1.getNumClientesAtuais());
}
