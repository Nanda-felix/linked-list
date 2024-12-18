class no:
    def __init__(self, valor):
        self.valor = valor
        self.proximo = None

class Lista:
    def __init__(self):
        self.inicio = None

    def adicionar(self, valor, posicao):
        if posicao < 0 or posicao > self.tamanho():
            print(f"Posição {posicao} inválida. Valor {valor} não foi adicionado.")
            return

        novo_no = no(valor)

        if posicao == 0:  
            novo_no.proximo = self.inicio
            self.inicio = novo_no
        else:
            atual = self.inicio
            for _ in range(posicao - 1):
                if atual.proximo is None:
                    break
                atual = atual.proximo
            novo_no.proximo = atual.proximo
            atual.proximo = novo_no

    def tamanho(self):
        contador = 0
        atual = self.inicio
        while atual:
            contador += 1
            atual = atual.proximo
        return contador

    def remover(self, valor):
        if self.inicio is None:
            print("A lista está vazia.")
            return

        if self.inicio.valor == valor: 
            self.inicio = self.inicio.proximo
            print(f"Valor {valor} removido da lista.")
            return

        atual = self.inicio
        while atual.proximo and atual.proximo.valor != valor:
            atual = atual.proximo

        if atual.proximo:
            atual.proximo = atual.proximo.proximo
            print(f"Valor {valor} removido da lista.")
        else:
            print(f"Valor {valor} não encontrado na lista.")

    def imprimir(self):
        if self.inicio is None:
            print("A lista está vazia.")
        else:
            print("Lista atual:", end=" ")
            atual = self.inicio
            while atual:
                print(atual.valor, end=" ")
                atual = atual.proximo
            print()  

    def processar_arquivo(self, arquivo):
        try:
            with open(arquivo, 'r') as arquivo:
                
                valores_iniciais = arquivo.readline().split()
                for valor in valores_iniciais:
                    self.adicionar(int(valor), self.tamanho())  

                
                numero_acoes = int(arquivo.readline())

                for _ in range(numero_acoes):
                    linha = arquivo.readline().strip()
                    if not linha:
                        continue

                    acao = linha.split()

                    if len(acao) < 2:
                        if acao[0] == 'P':
                            tipo_acao = acao[0]
                            valor = None
                            posicao = None
                        else:
                            print(f"Ação inválida (falta valor ou comando): {linha}")
                            continue
                    else:
                        tipo_acao = acao[0]
                        valor = int(acao[1])

                
                        if len(acao) > 2:
                                posicao = int(acao[2])
            

                    if tipo_acao == "A":
                        self.adicionar(valor, posicao)
                        print(f"Valor {valor} adicionado na posição {posicao}")
                    elif tipo_acao == "R":
                        self.remover(valor)
                    elif tipo_acao == "P":
                        self.imprimir()
                    else:
                        print(f"Ação desconhecida: {linha}")
        except IOError as e:
            print(f"Erro ao ler o arquivo: {e}")
        except ValueError as e:
            print(f"Erro no formato do número: {e}")


if __name__ == "__main__":
    gerenciador = Lista()
    gerenciador.processar_arquivo("C:\\Users\\Ferna\\OneDrive\\Projetos\\Lista_ligada-1\\arq.txt")
