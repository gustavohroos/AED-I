class Grafo:
    def __init__(self, vertices):
        self.vertices = vertices
        self.grafo = [[0]*self.vertices for i in range(self.vertices)]
        self.width = 2
    
    def adiciona_aresta(self, u, v, peso):
        self.grafo[u-1][v-1] = self.grafo[v-1][u-1] = peso

    def mostra_matriz(self):
        print('a matriz de adjacências é:')

        if self.vertices > 9:
            self.width += 1

        print(4*' ' + ' '*(self.width) + '1', end='')

        for i in range(self.vertices - 1):
            if i < 8:
                print(' '*(self.width) + str(i+2), end='')
            else:
                print(' '*(self.width - 1) + str(i+2), end='')
        print()

        for i in range(self.vertices):
            if i < 9:
                print(str(i+1), ' | ', end='')
            else:
                print(str(i+1), '| ', end='')
            for j in range(self.vertices):
                print(str(self.grafo[i][j]).rjust(self.width, " "), end = ' ')
            print()
        
        if self.vertices > 9:
            self.width -= 1

    def adiciona_arestas(self, quantidade):
        for i in range(quantidade):
            origem = input(f'digite a origem do aresta {i+1}: ')
            destino = input(f'digite o destino do aresta {i+1}: ')
            peso = input(f'digite o peso do aresta {i+1}: ')
            self.adiciona_aresta(int(origem), int(destino), int(peso))
            self.width = max(self.width, len(str(peso)))
            self.mostra_matriz()
            

if __name__ == '__main__':
    vertices = -1
    while(vertices <= 0 or vertices > 20):
        vertices = int(input('digite a quantidade de vértices (maximo 20): '))
    grafo = Grafo(vertices)
    arestas = int(input('digite a quantidade de arestas: '))
    grafo.adiciona_arestas(arestas)

