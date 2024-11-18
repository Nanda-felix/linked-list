#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class No {
public:
    int valor;
    No* proximo;

    No(int v) : valor(v), proximo(nullptr) {}
};

class Lista {
private:
    No* inicio;

public:
    Lista() : inicio(nullptr) {}

    void adicionar(int valor, int posicao) {
        if (posicao < 0 || posicao > tamanho()) {
            std::cout << "Posição " << posicao << " inválida. Valor " << valor << " não foi adicionado.\n";
            return;
        }

        No* novoNo = new No(valor);

        if (posicao == 0) {
            novoNo->proximo = inicio;
            inicio = novoNo;
        } else {
            No* atual = inicio;
            for (int i = 0; i < posicao - 1; ++i) {
                if (atual->proximo == nullptr) break;
                atual = atual->proximo;
            }
            novoNo->proximo = atual->proximo;
            atual->proximo = novoNo;
        }
    }

    int tamanho() {
        int contador = 0;
        No* atual = inicio;
        while (atual) {
            ++contador;
            atual = atual->proximo;
        }
        return contador;
    }

    void remover(int valor) {
        if (inicio == nullptr) {
            std::cout << "A lista está vazia.\n";
            return;
        }

        if (inicio->valor == valor) {
            No* temp = inicio;
            inicio = inicio->proximo;
            delete temp;
            std::cout << "Valor " << valor << " removido da lista.\n";
            return;
        }

        No* atual = inicio;
        while (atual->proximo && atual->proximo->valor != valor) {
            atual = atual->proximo;
        }

        if (atual->proximo) {
            No* temp = atual->proximo;
            atual->proximo = atual->proximo->proximo;
            delete temp;
            std::cout << "Valor " << valor << " removido da lista.\n";
        } else {
            std::cout << "Valor " << valor << " não encontrado na lista.\n";
        }
    }

    void imprimir() {
        if (inicio == nullptr) {
            std::cout << "A lista está vazia.\n";
            return;
        }

        std::cout << "Lista atual: ";
        No* atual = inicio;
        while (atual) {
            std::cout << atual->valor << " ";
            atual = atual->proximo;
        }
        std::cout << "\n";
    }

    void processarArquivo(const std::string& caminho) {
        std::ifstream arquivo(caminho);

        if (!arquivo.is_open()) {
            std::cerr << "Erro ao abrir o arquivo: " << caminho << "\n";
            return;
        }

        std::string linha;

        // Primeira linha: valores iniciais
        if (std::getline(arquivo, linha)) {
            std::istringstream iss(linha);
            int valor;
            while (iss >> valor) {
                adicionar(valor, tamanho());
            }
        }

        // Segunda linha: número de ações
        int numeroAcoes = 0;
        if (std::getline(arquivo, linha)) {
            numeroAcoes = std::stoi(linha);
        }

        // Processar ações
        for (int i = 0; i < numeroAcoes; ++i) {
            if (std::getline(arquivo, linha)) {
                std::istringstream iss(linha);
                std::string tipoAcao;
                int valor = 0, posicao = 0;

                iss >> tipoAcao;
                if (tipoAcao == "A") {
                    iss >> valor >> posicao;
                    adicionar(valor, posicao);
                    std::cout << "Valor " << valor << " adicionado na posição " << posicao << "\n";
                } else if (tipoAcao == "R") {
                    iss >> valor;
                    remover(valor);
                } else if (tipoAcao == "P") {
                    imprimir();
                } else {
                    std::cout << "Ação desconhecida: " << linha << "\n";
                }
            }
        }

        arquivo.close();
    }
};

int main() {
    Lista lista;
    lista.processarArquivo("C:\\Users\\adria\\Desktop\\Nanda\\arq.txt");
    return 0;
}


// Execução principal
const lista = new Lista();
lista.processarArquivo('C:\\Users\\adria\\Desktop\\Nanda\\arqg.txt');