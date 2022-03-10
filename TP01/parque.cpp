#include "parque.h"
#include <vector>

using namespace std;

// a)
ParqueEstacionamento::ParqueEstacionamento(unsigned lot, unsigned nMaxCli)
    : lotacao(lot), numMaximoClientes(nMaxCli) {
    clientes = {};
    vagas = lot;
}

unsigned ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

// b)
int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (int i = 0; i < clientes.size(); i++)
        if (clientes.at(i).nome == nome)
            return i;

    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size() >= numMaximoClientes)
        return false;

    InfoCartao cliente = {};
    cliente.nome = nome;

    clientes.push_back(cliente);
    return true;
}

// c)
bool ParqueEstacionamento::entrar(const string &nome) {
    if (vagas <= 0)
        return false;

    for (auto &cliente : clientes)
        if (cliente.nome == nome)
            if (cliente.presente) {
                return false;
            } else {
                --vagas;
                cliente.presente = true;
                return true;
            }

    return false;
}

// d)
bool ParqueEstacionamento::retiraCliente(const string &nome) {
    for (auto cliente = clientes.begin(); cliente < clientes.end(); ++cliente)
        if ((*cliente).nome == nome)
            if ((*cliente).presente) {
                return false;
            } else {
                clientes.erase(cliente);
                return true;
            }

    return false;
}

// e)
bool ParqueEstacionamento::sair(const string &nome) {
    for (auto &cliente : clientes)
        if (cliente.nome == nome && cliente.presente) {
            ++vagas;
            cliente.presente = false;
            return true;
        }

    return false;
}

// f)
unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    unsigned acc{0};

    for (auto &cliente : clientes)
        acc += cliente.presente;

    return acc;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}
