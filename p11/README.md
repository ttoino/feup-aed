# 11ª aula prática – Caminhos mais curtos e apoio ao 2º trabalho prático

Nesta aula iremos usar como base a classe **Graph** introduzida nas aula prática anteriores.
A classe **FunWithGraphs** contém alguns grafos não dirigidos e pesados "prontos a usar" e que são usados nos testes unitários desta aula.
Para facilitar a sua tarefa nesta aula pode ver aqui as suas ilustrações:

> Alguns grafos não dirigidos e pesados

```
graph1
      ₇
   2-----3
₁₂/|\₁ ₉/|\₆
 / | \ / | \
1  |⁸ 5  |³ 7
 \ | / \ | /
 ³\|/⁵ ²\|/¹
   4-----6
      ⁵
```

```
graph2
   ₁₆   ₁₂
 1----2----3
 |\   |\   |
³| \₈ | \₁ |¹⁰
 |  \ |₁₅\ |
 | ₉ \| ₆ \|
 4----5----6
 |   /| ₁₄/|
 | ₅/ |  / |
⁷| / ²| /  |⁴
 |/   |/   |
 7----8----9
   ¹³   ¹¹
```

> Alguns grafos dirigidos e pesados

```
graph3
               ₁
             -----
     ₄   ₄  ↙     \
   2←--3←--4←--5   6
 ²↙ \ ⁸↑ ₂↗  ³ ↑ ₃↗↑
 1 ¹⁵\ | /    ²| / |⁵
 ₁↘ ₅ ↘|/ ₁ ₇  |/₅ |
   7--→7--→9-→10←-11
    \  ₂  ↗ ↖  ₃  /
     -----   -----
```

```
graph4
    ₃
   ←--
  1--→2
 ↑|\⁵ ↑↖
₈||₂\₉| \
 |↓  ↘|⁻⁶|₄₂
  3←--4  |
   \⁻⁸  /
    ----
```

## 1. Algoritmo de Dijkstra e caminhos mais curtos

Uma componente fundamental do 2º trabalho é o cálculo de caminhos mais curtos.
Quando o grafo não é pesado pode simplesmente ser usada uma pesquisa em largura (ex: exercício 4 da 9ª aula prática).
Se o grafo for pesado (e não existirem pesos negativos) pode usar o algoritmo de Dijkstra.
Pode ver uma explicação na aula teórica nº 21 (slides 7 a 14), que inclui pseudo-código.

O objetivo deste exercício é dar-lhe a oportunidade de testar uma implementação do algoritmo de Dijkstra e verificar se ela está a devolver os resultados esperados.
Pode fazer uma única implementação do algoritmo e depois cada um dos métodos devolve uma parte diferente dos resultados obtidos (sugestão: acrescentar na `struct Node` de `Graph` dois atributos inteiros - *dist* e *pred* – e um booleano - *visited*).

Pode usar a *MinHeap* dada (nós como chave e distância como valor) para implementar a fila de prioridade *Q* do pseudo-código (não esquecendo de fazer *decreaseKey* ao atualizar uma distância).
O slide 14 indica outras alternativas para implementar o algoritmo de Dijkstra usando apenas estruturas de dados da STL (ex: usar *set* e implementar atualização como remoção + reinserção).

### a) Distância entre dois nós.

Função a implementar:

```cpp
int Graph::dijkstra_distance(int a, int b)
```

**Complexidade temporal esperada:** O(|E| log |V|)\
(onde *|V|* é o número de nós e *|E|* o número de ligações)

Esta função deve calcular a distância do nó *a* para o nó *b*, ou seja, qual o menor custo (soma dos pesos) de um caminho entre *a* e *b*.
Se não existir nenhum caminho a função deve devolver -1.

*Exemplo de chamada e output esperado:*

```cpp
Graph g1 = FunWithGraphs::graph1();
cout << g1.dijkstra_distance(1, 2) << endl;
cout << g1.dijkstra_distance(4, 3) << endl;
Graph g3 = FunWithGraphs::graph3();
cout << g3.dijkstra_distance(8, 11) << endl;
cout << g3.dijkstra_distance(11, 8) << endl;
```

```
9
8
-1
22
```

*Explicação:*

- *graph1:* distância entre nós 1 e 2 é 9 (caminho: 1 → 4 → 5 → 2, com custo 9 = 3 + 5 + 1)
- *graph1:* distância entre nós 4 e 3 é 8 (caminho: 4 → 6 → 3, com custo 8 = 5 + 3)
- *graph3:* não existe nenhum caminho entre 8 e 11
- *graph3:* distância entre nós 11 e 8 é 22 (caminho: 11 → 6 → 4 → 3 → 2 → 1 → 7 → 8, com custo 22)

### b) Caminho mais curto entre dois nós.

Função a implementar:

```cpp
list<int> Graph::dijkstra_path(int a, int b)
```

**Complexidade temporal esperada:** O(|E| log |V|)\
(onde *|V|* é o número de nós e *|E|* o número de ligações)

Esta função deve devolver o caminho mais curto entre o nó *a* e nó *b* , ou seja, o de menor custo entre *a* e *b*.
A lista devolvida deve ter um tamanho igual ao número de nós do caminho e nela devem vir sequencialmente os nós do caminho (o primeiro nó deve ser *a* e o último nó deve ser *b* ).
Se existir mais do que um caminho, qualquer um é aceite.
Se não existir nenhum caminho a função deve devolver uma lista vazia (de tamanho zero).

*Exemplo de chamada e output esperado:*

```cpp
Graph g1 = FunWithGraphs::graph1();
list<int> v1 = g1.dijkstra_path(1, 2);
cout << "size = " << v1.size() << ":";
for (int i : v1) cout << " " << i;
cout << endl;
list<int> v2 = g1.dijkstra_path(4, 3);
cout << "size = " << v2.size() << ":";
for (int i : v2) cout << " " << i;
cout << endl;
Graph g3 = FunWithGraphs::graph3();
list<int> v3 = g3.dijkstra_path(8, 11);
cout << "size = " << v3.size() << endl;
```

```
size = 4: 1 4 5 2
size = 3: 4 6 3
size = 0
```

*Explicação:*

- *graph1:* caminho mais curto entre nós 1 e 2 é 1 → 4 → 5 → 2, com custo 9 = 3 + 5 + 1
- *graph1:* caminho mais curto entre nós 4 e 3 é 4 → 6 → 3, com custo 8 = 5 + 3
- *graph3:* não existe nenhum caminho entre 8 e 11

### *(exercícios extra)* Mais ideias para exploração:

A prioridade deve ser nesta fase o trabalho, mas se quiser depois explorar esta parte de caminhos mais
curtos deixamos ficar uma sugestão:

### Implementar o algoritmo de Bellman-Ford.

E se existissem pesos negativos como em *graph4*?
Nesse grafo, qual é o caminho mais curto entre os nós 1 e 2?
O que devolveria (erradamente) o algoritmo de Dijkstra?
Implemente o algoritmo de Bellman-Ford como explicado nas aulas (ver slides 17 a 19 da aula teórica nº 21) e use *graph4* para poder verificar se o algoritmo funciona.

### Existência de ciclos negativos.

Use a extensão do algoritmo de Bellman-Ford dada nas aulas (slide 21 da aula teórica nº 21) para verificar se existe algum ciclo negativo num dado grafo (que implicaria, por exemplo, que a distância entre qualquer par de nós do ciclo pode ser tão baixo quanto quisermos, se percorrermos várias vezes o ciclo para ir reduzindo a distância).
Crie grafos com e sem ciclos negativos para verificar empiricamente a sua implementação.
