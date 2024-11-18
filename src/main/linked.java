import java.io.*;

class No {
    int valor;
    No proximo;

    No(int valor) {
        this.valor = valor;
        this.proximo = null;
    }
}

class Lista {
    private No inicio;

    Lista() {
        this.inicio = null;
    }

    public void adicionar(int valor, int posicao) {
        if (posicao < 0 || posicao > tamanho()) {
            System.out.println("Posição " + posicao + " inválida. Valor " + valor + " não foi adicionado.");
            return;
        }

        No novoNo = new No(valor);

        if (posicao == 0) {
            novoNo.proximo = inicio;
            inicio = novoNo;
        } else {
            No atual = inicio;
            for (int i = 0; i < posicao - 1; i++) {
                if (atual.proximo == null) break;
                atual = atual.proximo;
            }
            novoNo.proximo = atual.proximo;
            atual.proximo = novoNo;
        }
    }

    public int tamanho() {
        int contador = 0;
        No atual = inicio;
        while (atual != null) {
            contador++;
            atual = atual.proximo;
        }
        return contador;
    }

    public void remover(int valor) {
        if (inicio == null) {
            System.out.println("A lista está vazia.");
            return;
        }

        if (inicio.valor == valor) {
            inicio = inicio.proximo;
            System.out.println("Valor " + valor + " removido da lista.");
            return;
        }

        No atual = inicio;
        while (atual.proximo != null && atual.proximo.valor != valor) {
            atual = atual.proximo;
        }

        if (atual.proximo != null) {
            atual.proximo = atual.proximo.proximo;
            System.out.println("Valor " + valor + " removido da lista.");
        } else {
            System.out.println("Valor " + valor + " não encontrado na lista.");
        }
    }

    public void imprimir() {
        if (inicio == null) {
            System.out.println("A lista está vazia.");
        } else {
            System.out.print("Lista atual: ");
            No atual = inicio;
            while (atual != null) {
                System.out.print(atual.valor + " ");
                atual = atual.proximo;
            }
            System.out.println();
        }
    }

    public void processarArquivo(String arquivo) {
        try (BufferedReader br = new BufferedReader(new FileReader(arquivo))) {
            String[] valoresIniciais = br.readLine().split(" ");
            for (String valor : valoresIniciais) {
                adicionar(Integer.parseInt(valor), tamanho());
            }

            int numeroAcoes = Integer.parseInt(br.readLine());

            for (int i = 0; i < numeroAcoes; i++) {
                String linha = br.readLine();
                if (linha == null || linha.trim().isEmpty()) continue;

                String[] acao = linha.split(" ");
                String tipoAcao = acao[0];
                int valor = acao.length > 1 ? Integer.parseInt(acao[1]) : 0;
                int posicao = acao.length > 2 ? Integer.parseInt(acao[2]) : 0;

                switch (tipoAcao) {
                    case "A":
                        adicionar(valor, posicao);
                        System.out.println("Valor " + valor + " adicionado na posição " + posicao);
                        break;
                    case "R":
                        remover(valor);
                        break;
                    case "P":
                        imprimir();
                        break;
                    default:
                        System.out.println("Ação desconhecida: " + linha);
                        break;
                }
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Erro no formato do número: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        Lista gerenciador = new Lista();
        gerenciador.processarArquivo("C:\\Users\\adria\\Desktop\\Nanda\\arq.txt");
    }
}