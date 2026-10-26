# GUIA DA MECÂNICA

Esse é o corpo do jogo que a gente combinou na sexta: **os key
inputs e a mecânica**. A parte DA VISTA (raycasting) continua sua.
Aqui explica cada peça pro teu raio encaixar sem mistério.

\---

## 1\. O que veio de novo (e onde mora cada coisa)

|Arquivo|O que é|
|-|-|
|`src/hooks/keys.c`|AS BANDEIRAS: tecla aperta/solta vira estado|
|`src/hooks/move.c`|O JOGADOR VIVO: nascer, andar, girar, colisão|
|`includes/cub3d.h`|Teclas, velocidades e a `t\_player`|
|`Makefile`|Os dois arquivos novos na lista + `-lm` (math)|

E **três enxertos pequenos** nos teus arquivos (com comentário de
explicação no lugar): `window.c` (os hooks de press/release), `hooks.c`
(o render chama o update) e `main.c` (o init\_player antes da janela).

## 2\. A ideia central: SININHO virou BANDEIRA

O `mlx\_key\_hook` antigo avisava **uma vez** quando a tecla descia —
pra andar segurando, o movimento ficava refém do auto-repeat do
teclado (que muda de máquina pra máquina).

O modelo novo:

```
tecla desce  -> key\_press   -> keys\[IDX\_W] = 1  (bandeira SOBE)
tecla sobe   -> key\_release -> keys\[IDX\_W] = 0  (bandeira DESCE)
                     |
                     v
render\_hook (60x/seg) -> update\_player() LE as bandeiras
                     -> anda um passinho por frame
```

Não são muitos eventos: são **dois** (apertou, soltou) e um **estado**
que fica entre eles. O movimento suave nasce do *loop*, não do teclado.

## 3\. Por que `keys\[KEY\_COUNT]` e não `keys\[256]`?

O keycode das setas (65361...) passa de 256 — não caberia no array.
Então `key\_index()` **traduz** o keycode da X11 pra um índice pequeno
(0 a 5). Bônus de avaliação: array pequeno, zero desperdício, e você
explica a tradução em uma frase.

## 4\. O CONTRATO com o teu raycasting (guarde estes 6 números)

```c
p->x, p->y        // posição do jogador (double, centro da célula +0.5)
p->dir\_x, p->dir\_y    // vetor pra onde a câmera olha (cos/sin do ângulo)
p->plane\_x, p->plane\_y // vetor "tela de lado": o FOV (\~66 graus)
```

O teu raycasting clássico (estilo lodev) usa exatamente esses seis.
O `update\_dir()` recalcula dir e plane **sempre que o ângulo muda** —
você nunca precisa mexer neles.

## 5\. ONDE o teu raycast pluga

No `render\_hook`, o buraco tá marcadinho:

```c
int	render\_hook(void \*param)
{
	...
	update\_player(scene);   // 1. o corpo anda
	/\* AQUI: o teu render raycast pintando a img (scene->mlx.img) \*/
	mlx\_put\_image\_to\_window(...); // 2. joga o frame na tela
	return (0);
}
```

Pinta direto no `img.addr` (os bytes da imagem que já existe) — o
`put\_image` depois já mostra. Enquanto não tiver raycast, a tela fica
preta: **o jogador tá andando no escuro, sua parte acende a luz.**

## 6\. Colisão: por que testar X e Y SEPARADO

`try\_move()` pergunta pro SEU `is\_walkable()` se o destino é chão.
Mas testa x e y um por vez: bater de frente **para**, bater de
raspão **desliza** na parede. É o padrão dos jogos de verdade — e é
uma resposta pronta pra avaliação.

## 7\. O mouse: a porta tá aberta (bônus depois do prazo!)

Já existe `p->mouse\_dx` e o consumo no `update\_player`. Pra ativar:
um `mlx\_hook` com MotionNotify (evento 6), guarde o delta X em
`scene->player.mouse\_dx` — pronto, câmera segue o mouse. Unas 15
linhas. Mas **isso é bônus**: o prazo primeiro!

## 8\. Como testar HOJE (sem texturas de verdade)

O parser pede texturas que ainda não existem. Pra testar o movimento
enquanto isso, dá pra fazer o que a gente fez aqui: 4 `.xpm` de 1
pixel (é texto!) e um mapa apontando pra eles. A tela fica preta,
mas o jogo roda — e o heartbeat no terminal mostra o mapa e o player.

## 9\. Perguntas que podem te fazer na avaliação (respostas prontas)

* **Por que dois mlx\_hook em vez de mlx\_key\_hook?** → O
key\_hook avisa UMA vez por pressão; o par press/release dá
ESTADO — o movimento contínuo vem do loop lendo a bandeira,
não do teclado repetindo.
* **Por que `+0.5` no init\_player?** → A célula é inteira; nascer
no centro evita ficar em cima da quina da parede.
* **Por que ângulo único + update\_dir?** → Uma fonte de verdade:
dir e plane são SEMPRE derivados do ângulo — impossível
dessincronizar.
* **Por que `-lm` no Makefile?** → `cos/sin` moram na libm do
sistema; sem a flag o link falha.

\---

Qualquer dúvida, me chama.

