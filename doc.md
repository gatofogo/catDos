# Documentacao Tecnica - CatDos

Documento voltado para desenvolvedores que querem entender a estrutura do projeto antes de modificar ou criar novos nós.

## Estrutura Geral do Codigo

O projeto usa uma estrutura em arvore inspirada em sistemas de UI baseados em Nos (Nodes).

* `main.cpp`: Ponto de entrada. Configura o terminal no Windows (suporte a ANSI e codificacao UTF-8), inicializa os buffers, carrega o arquivo e roda o loop principal.

* `Node.h` / `Root.cpp`: Define a classe base `Node` e a classe `Root`. A `Root` gerencia a arvore de componentes, repassando chamadas de `update()` e `render()` para os filhos.

* `screen.cpp`: Gerencia a tela do terminal e faz a renderizacao via double buffer.

* `terminal.cpp`: Captura o tamanho atual do terminal para redimensionar a interface.

* `input.cpp`: Abstracao para leitura de teclas no Windows.

* `TextEditor.cpp`: Implementacao do no do editor de texto (herda de `Node`).

## Logica do Loop Principal

O ciclo do programa roda dentro do `while(true)` no `main.cpp` e segue três etapas basicas:

1. **Checagem de Redimensionamento:** Compara o tamanho do terminal com o frame anterior. Se mudou, limpa a tela e ajusta as dimensoes dos nos.

2. **Atualizacao (`update`):** A `Root` chama o `update()` de todos os nos filhos para processar entradas e atualizar estado (como a posicao do cursor).

3. **Renderizacao (`render` + `redraw`):** Os nos escrevem seu conteudo no buffer de tela. Depois, o `screen::redraw` envia as diferencas para o terminal.

4. **Pausa:** `Sleep(16)` no Windows para segurar o loop em torno de \~60 FPS.

## Como Funciona a Entrada (Input)

A classe `WinInput` (`input.cpp`) abstrai o input no Windows sem bloquear a execucao:

* `has_key()`: Usa `_kbhit()` da biblioteca `<conio.h>` para saber se ha alguma tecla pressionada.

* `get_key()`: Usa `_getch()` para ler o código da tecla sem precisar esperar pelo Enter.

No `TextEditor.cpp`, as teclas sao tratadas da seguinte forma:

* Teclas especiais (setas): Retornam código `0` ou `224` primeiro, exigindo uma segunda leitura de `_getch()` para identificar a seta pressionada (75=Esquerda, 72=Cima, 77=Direita, 80=Baixo).

* Backspace (`8`): Remove caracteres ou junta a linha atual com a anterior.

* Enter (`13`): Divide a linha atual na posicao do cursor e insere uma nova.

* Ctrl + S (`19`): Escreve o vetor `file` de volta no arquivo de destino.

## Double Buffer (`screen.cpp`)

Para evitar que a tela pisque ao redesenhar o terminal, a classe `screen` mantem dois buffers na memoria:

* `back_screen`: Onde os nos desenham o frame atual durante a etapa de `render()`.

* `front_screen`: O estado exato do que esta impresso na tela do terminal.

### Processo de Redraw:

1. O método `redraw()` percorre cada caractere do `back_screen`.

2. Ele compara o caractere e a cor do `back_screen` com o `front_screen`.

3. Se forem iguais, ele pula.

4. Se forem diferentes, ele move o cursor do terminal para aquela posicao usando sequencias ANSI (`\033[linha;colunaH`), imprime o novo caractere com a cor correta e atualiza o `front_screen`.

5. No final do frame, reseta as cores do terminal com `\033[0m`.

## Estrutura do Texto e Limite do Buffer

O texto e armazenado como um vetor de strings (`std::vector<std::string> file`), onde cada indice representa uma linha.

* O cursor mantem as posicoes `x` e `y` no texto.

* A funcao `clamp` (`utils.cpp`) impede que o cursor saia dos limites do vetor ou das linhas.

* Na renderizacao, o editor desenha a borda vermelha e adiciona os numeros de linha antes do texto (`0. `, `1. `...).
