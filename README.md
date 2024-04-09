# cub3D

1. *Leitura do Mapa e Configurações Iniciais:*
   - *Entrada de Dados:* Carrega o mapa do jogo e configurações iniciais (como posição do jogador, direção da visão, e configurações de luz e texturas) de um arquivo de configuração.
   - *Processamento:* Parse e validação do mapa e configurações.
   - *Saída:* Estrutura de dados representando o mapa, configurações do jogador, e outros elementos necessários para iniciar o jogo.

2. *Motor de Raycasting:*
   - *Entrada de Dados:* Posição atual do jogador, direção da visão, e o mapa do jogo.
   - *Processamento:*
     - Cálculo dos raios projetados da posição do jogador em direção ao mapa para determinar visibilidade, distâncias e colisões.
     - Determinação das texturas e sombras com base na intersecção dos raios com os elementos do mapa.
   - *Saída:* Dados de renderização (distâncias, ângulos, texturas) para serem usados na geração da visão 3D.

3. *Renderização da Visão 3D:*
   - *Entrada de Dados:* Dados de renderização do motor de raycasting.
   - *Processamento:* Geração da visão 3D usando os dados de renderização, aplicando texturas, ajustando perspectiva e sombras conforme necessário.
   - *Saída:* Imagem 3D a ser exibida na tela.

4. *Controle do Jogador e Interação:*
   - *Entrada de Dados:* Comandos do usuário (movimento, olhar ao redor).
   - *Processamento:* Atualização da posição e direção do jogador com base nos comandos.
   - *Saída:* Novas posições e direções enviadas ao motor de raycasting.

5. *Loop de Jogo:*
   - Integração dos componentes acima em um loop contínuo de jogo, onde a entrada do usuário é processada, o estado do jogo é atualizado, e a nova visão 3D é renderizada e exibida ao usuário.
  
5. *Fluxograma do Projeto:*
   
![Cub3D](https://github.com/alessandracruz/Imagens/blob/main/Cub3Dv1.png)

