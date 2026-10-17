# Editor de Texto CatDos

Editor de texto simples para terminal do Windows, feito em C++.

## Como rodar

1. Compile o projeto:
   g++ src/*.cpp -Iinclude -std=c++17 -Wall -g -o CatDos.exe

2. Execute o `CatDos.exe`.

3. Digite o caminho do arquivo para abrir/salvar (ex: `nota.txt`). Pressione Enter em branco para abrir sem salvar.

## Controles

- Setas: navegação
- Backspace: apaga texto
- Enter: quebra linha
- Ctrl + S: salva o arquivo

## Limitações atuais

- **Apenas caracteres ASCII simples:** Não use acentos (`á`, `ã`, `ç`) nem caracteres especiais (`ʣ`, emojis). O editor ainda não lida com UTF-8 multibyte, o que quebra o alinhamento do cursor e da tela.
- Projeto em fase inicial de testes.

## Roadmap (Futuro)

O objetivo é transformar o CatDos em uma mini IDE para terminal, incluindo:
- Explorador de arquivos
- Terminal embutido
- Suporte a múltiplos arquivos
