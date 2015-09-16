RPG
===


Introdução
----------

Este projeto (descontinuado) é uma batalha simples, num estilo RPG de texto, feito em linguagem C.
Até o momento, só é possível distribuir pontos para diferentes atributos do personagem criado pelo usuário. Feito isso, ocorre a batalha contra um Goblin controlado pelo computador.


Uso
---

Para compilar, basta digitar no root do código:

    $ make

O programa é executado pelo terminal (Linux ou Windows) da seguinte forma:

    $ ./bin/Rpg


Instruções
----------

Os atributos existentes são:

| Atributo   | Sigla | Descrição                                                                            |
| ---------- | ----- | ------------------------------------------------------------------------------------ |
| Vida       | HP    | Quando chegar a 0 (zero), o personagem é nocauteado                                  |
| Ataque     | ATK   | Aumenta o dano dos ataques da unidade                                                |
| Defesa     | DEF   | Reduz o dano recebido pela unidade                                                   |
| Agilidade  | AGI   | Determina a chance de acerto de um golpe, além da chance de se esquivar de um ataque |
| Velocidade | SPD   | Frequência com que a unidade pode agir (ou seja, escolher ações) na batalha          |
| Sorte      | LUCK  | Aumenta a chance de dar um golpe crítico                                             |

Na batalha, as ações possíveis são:

- **Atacar:** Tenta acertar um ataque no inimigo.
- **Carregar o golpe:** Aumenta o dano do próximo ataque dado. Equivale a multiplicar o dano causado pelo número de vezes que o comando carregar foi escolhido. Cuidado: há um limite para o número de cargas!
- **Defender:** Reduz o dano recebido até o próximo turno da unidade.


Observações
----------

  - A música usada é [*Decisive Battle*](http://finalfantasy.wikia.com/wiki/The_Decisive_Battle_%28Final_Fantasy_VI%29 "Mais sobre a música"), do jogo [**Final Fantasy VI**](http://finalfantasy.wikia.com/wiki/Final_Fantasy_VI "Mais sobre Final Fantasy VI") (SNES). Não é de nossa autoria; foi usada como teste simplesmente pela beleza dessa trilha sonora.
