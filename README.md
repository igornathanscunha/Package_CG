# Package_CG

Pacote experimental de ferramentas em C para computação gráfica. O projeto reúne operações matemáticas 2D e funções para leitura, processamento e escrita de imagens RGB no formato PPM.

## Funcionalidades

- Representação de cores RGB e imagens.
- Operações de rotação de pontos 2D, incluindo rotação inversa e cisalhamento.
- Filtro de blur por média em uma vizinhança 3x3, com replicação das bordas.
- Leitura e escrita de imagens PPM nos tipos P3 (texto) e P6 (binário).
- Programas de exemplo para blur e rotação de imagens.

## Requisitos

- GCC ou outro compilador compatível com C.
- GNU Make.
- Biblioteca matemática padrão (`libm`), linkada com `-lm` pelo Makefile.

No Linux, instale o compilador e o Make pelo gerenciador de pacotes da sua distribuição, caso ainda não estejam disponíveis.

## Compilar

Execute os comandos na raiz do projeto, onde está o `Makefile`:

```sh
make
```

Isso compila os dois exemplos e cria os executáveis em `build/`. Para compilar somente um deles:

```sh
make blur_image
make rotate_image
```

Para remover os executáveis gerados:

```sh
make clean
```

## Usar o exemplo de blur

O programa recebe o caminho da imagem PPM e o número de passagens do filtro:

```sh
./build/blur_image img/gato_preto.ppm 10
```

O resultado é gravado como `blur.ppm` no diretório de onde o programa foi executado. Se o arquivo já existir, será sobrescrito. Cada passagem aplica novamente o filtro 3x3; o segundo argumento não altera o tamanho da vizinhança.

## Exemplo de rotação

A interface do programa recebe os caminhos de entrada e saída:

```sh
./build/rotate_image img/gato_preto.ppm img/gato_preto_rotacionada.ppm
```

O ângulo está definido como 30 graus no código e a imagem de saída é alocada com o dobro da largura e da altura da original.

**Limitação conhecida:** o exemplo compila, mas atualmente pode abortar durante a execução por uma liberação duplicada de memória após a gravação. Essa rotina precisa ser corrigida antes de usar o exemplo de rotação; o README não altera o comportamento do código.

## Estrutura do projeto

```text
include/cg/   Headers públicos: tipos e declarações das funções
src/          Implementações organizadas por área
examples/     Programas executáveis de demonstração
img/          Imagens PPM usadas como entrada e referência
build/        Executáveis gerados pelo Makefile
Makefile      Regras de compilação dos exemplos
```

Os headers podem ser incluídos pelos programas com caminhos como `#include "cg/image/blur.h"`. O Makefile configura `include/` como caminho de busca dos headers.

## Adicionar um exemplo

Crie o novo arquivo em `examples/`, por exemplo `examples/meu_programa.c`, com sua própria função `main`. Depois, adicione um alvo correspondente no `Makefile`, informando o arquivo do exemplo e os módulos de `src/` que ele utiliza. O Makefile atual não descobre exemplos novos automaticamente.

## Estado do projeto

Este projeto está em desenvolvimento e tem finalidade acadêmica. A rotação matemática e o processamento de imagens são implementações próprias para estudo; não há ainda uma suíte de testes automatizados.