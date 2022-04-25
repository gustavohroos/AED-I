# Autor: Gustavo Henrique Roos
# Matrícula: 20101184
# Algoritmos e Estruturas de Dados II
# Professor: Guilherme Netto

from queue import PriorityQueue
import numpy as np

class Grafo:
    def __init__(self, vertices):
        self.vertices = vertices
        self.grafo = np.zeros((self.vertices, self.vertices), dtype=int)
        self.width = 2
        self.visitado = []
    
    def adiciona_aresta(self, u, v, peso):
        self.grafo[u][v] = self.grafo[v][u] = peso

    def mostra_matriz(self):
        print('a matriz de adjacências é:')

        if self.vertices > 9:
            self.width += 1

        print(4*' ' + ' '*(self.width) + '0', end='')

        for i in range(self.vertices - 1):
            if i < 8:
                print(' '*(self.width) + str(i+1), end='')
            else:
                print(' '*(self.width - 1) + str(i+1), end='')
        print()

        for i in range(self.vertices):
            if i < 9:
                print(str(i), ' | ', end='')
            else:
                print(str(i), '| ', end='')
            for j in range(self.vertices):
                print(str(self.grafo[i][j]).rjust(self.width, " "), end = ' ')
            print()
        
        if self.vertices > 9:
            self.width -= 1

    def adiciona_arestas(self, quantidade):
        for i in range(quantidade):
            origem = input(f'digite o vértice origem da aresta {i}: ')
            destino = input(f'digite o vértice destino da aresta {i}: ')
            peso = input(f'digite o peso da aresta {i}: ')
            self.adiciona_aresta(int(origem), int(destino), int(peso))
            self.width = max(self.width, len(str(peso)))
            self.mostra_matriz()
    
    def dijkstra(self, vertice):
        N = {v: np.inf for v in range(self.vertices)}
        N[vertice] = 0

        self.visitado.clear()

        fila = PriorityQueue()
        fila.put((0, vertice))

        while not fila.empty():
            (distancia, vertice_atual) = fila.get()
            self.visitado.append(vertice_atual)

            for adjacente in range(self.vertices):
                if self.grafo[vertice_atual][adjacente] != 0:
                    distancia = self.grafo[vertice_atual][adjacente]
                    if adjacente not in self.visitado:
                        custo_antigo = N[adjacente]
                        custo_novo = N[vertice_atual] + distancia
                        if custo_novo < custo_antigo:
                            fila.put((custo_novo, adjacente))
                            N[adjacente] = custo_novo
        return N
    
    def dijk(self):
        for vertice_origem in range(self.vertices):
            distancias = grafo.dijkstra(int(vertice_origem))
            for vertice in range(len(distancias)):
                if distancias[vertice] != np.inf:
                    print(f'A distância mínima do vértice {vertice_origem} para o vértice {vertice} é {distancias[vertice]}')
                else:
                    print(f'Não existe um caminho possível do vértice {vertice_origem} para o vértice {vertice}')
        self.mostra_matriz()

if __name__ == '__main__':
    vertices = -1
    while(vertices <= 0 or vertices > 20):
        vertices = int(input('digite a quantidade de vértices (maximo 20): '))
    grafo = Grafo(vertices)
    arestas = int(input('digite a quantidade de arestas: '))
    grafo.adiciona_arestas(arestas)
    grafo.dijk()
