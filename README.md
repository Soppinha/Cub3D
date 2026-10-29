*Este projeto foi criado como parte do currículo da 42 por svaladar, LOGIN_DA_DUPLA.*

# cub3D

## Descrição

O cub3D é um raycaster em C inspirado em Wolfenstein 3D (id Software, 1992). O programa lê um arquivo de cena `.cub` e desenha, em primeira pessoa, o interior de um labirinto em uma janela da [MiniLibX](https://github.com/42Paris/minilibx-linux).

O objetivo do projeto é aplicar matemática básica (vetores, trigonometria) para transformar um mapa 2D em uma imagem 3D, e praticar janelas, eventos, imagens e o parsing rigoroso de um arquivo de configuração.

**Parte obrigatória**

- Parsing do `.cub`: as quatro texturas (`NO`, `SO`, `WE`, `EA`), as cores de chão (`F`) e de teto (`C`) e o mapa. Qualquer erro de configuração gera `Error` seguido de uma mensagem explícita.
- Validação do mapa: caracteres permitidos, exatamente um jogador e mapa fechado por paredes (flood fill a partir de fora do mapa, mais a verificação de que nenhum chão encosta em um espaço).
- Raycasting com o algoritmo DDA, uma textura diferente para cada face (norte, sul, leste e oeste) e cores sólidas de chão e teto.
- Movimento com `W` `A` `S` `D`, rotação com `←` `→` e saída limpa com `ESC` ou com o X da janela.
- Velocidade medida por segundo (delta time), igual em qualquer máquina.

**Bônus**

- Colisão com as paredes: o jogador desliza ao bater de raspão.
- Rotação da câmera com o mouse.

## Instruções

### Requisitos

Linux com `cc`, `make` e as bibliotecas de desenvolvimento do X11 usadas pela MiniLibX:

```bash
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

### Compilação

```bash
make          # parte obrigatória -> ./cub3D
make bonus    # bônus            -> ./cub3D_bonus
make clean    # remove os objetos
make fclean   # remove os objetos e os executáveis
make re       # recompila do zero
```

A `libft` e a MiniLibX são compiladas automaticamente pelo `Makefile`.

### Execução

```bash
./cub3D maps/valid/medium.cub
./cub3D_bonus maps/bonus/collision.cub
```

| Tecla | Ação |
|---|---|
| `W` / `S` | andar para frente / para trás |
| `A` / `D` | andar para a esquerda / para a direita |
| `←` / `→` | girar a câmera |
| mouse | girar a câmera (somente no bônus) |
| `ESC` ou o X da janela | sair |

### Formato do arquivo `.cub`

```
NO ./tex/north.xpm
SO ./tex/south.xpm
WE ./tex/west.xpm
EA ./tex/east.xpm

F 100,60,20
C 30,30,80

111111
100101
101001
1100N1
111111
```

- Os seis elementos podem vir em qualquer ordem, separados por linhas vazias e com espaços extras entre o identificador e o valor.
- As cores são `R,G,B`, cada componente no intervalo `[0,255]`.
- O mapa vem sempre por último e usa apenas `0` (chão), `1` (parede), espaço (vazio) e `N`/`S`/`E`/`W` (posição e direção inicial do jogador).
- O mapa precisa ser fechado por paredes: nenhum chão pode encostar em um espaço ou na borda.

### Testes

A pasta `maps/` tem mapas para cada item da avaliação:

- `maps/valid/`: cenas válidas (exemplo do subject, nascimento em cada direção, ordem embaralhada, cores extremas, texturas trocadas, mapa irregular, mapa grande).
- `maps/invalid/`: um arquivo para cada tipo de erro (extensão, identificador faltando, duplicado ou desconhecido, textura inválida, cores inválidas, mapa aberto, jogador ausente ou repetido, caractere inválido...). Todos devem imprimir `Error` seguido de uma mensagem e sair com código 1.
- `maps/bonus/`: mapas para testar o bônus.

```bash
./cub3D maps/valid/spawn_east.cub
./cub3D maps/invalid/open_left.cub
```

## Escolhas técnicas

- **DDA:** cada coluna da tela lança um raio que avança de célula em célula do grid até encontrar uma parede. A distância perpendicular evita o efeito "olho de peixe".
- **Delta time:** o passo e o giro são multiplicados pelo tempo desde o frame anterior (`gettimeofday`), com um teto de 0,05 s para que um travamento não vire um teletransporte.
- **Bônus por substituição de arquivo:** o código comum chama funções como `can_stand` e `init_mouse`. A regra `all` liga as versões obrigatórias (`collision.c`, `mouse.c`) e a regra `bonus` liga as versões `_bonus.c`. Nenhum código de bônus entra no executável obrigatório.
- **Mouse:** o cursor é recentralizado ao chegar perto da borda da janela. Se o sistema ignorar o reposicionamento (como no Wayland), o programa detecta isso e passa a girar apenas pelo deslocamento do mouse, sem saltos.

## Recursos

- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html): base do algoritmo DDA e do mapeamento de texturas.
- [F. Permadi: Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/): fundamentos geométricos do raycasting.
- [42 Docs: MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx): imagens, eventos e hooks da MiniLibX.
- [minilibx-linux](https://github.com/42Paris/minilibx-linux): código-fonte e páginas de manual da biblioteca.
- [PrismarineJS/minecraft-assets](https://github.com/PrismarineJS/minecraft-assets): origem das texturas das paredes (blocos de pedra do Minecraft 1.21.4, convertidos de PNG para XPM). Minecraft é marca e propriedade da Mojang Studios.

### Uso de IA

Usamos o Claude (Anthropic) como assistente durante o desenvolvimento. Todo o código gerado foi revisado, testado e discutido por nós antes de entrar no projeto. A IA foi usada para:

- **Testes:** gerar os mapas de teste de `maps/`.
- **Texturas:** converter as texturas do Minecraft de PNG para XPM.
