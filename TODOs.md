## General

- [ ] Menù principale che permette
  - [ ] Single Player
  - [ ] Local (or Network se sono pazzo abbastanza) Multiplayer

- [X] rappresentare i singoli tetramini
- [X] metodo per inserire i tetramini nel campo ad una posizione e rotazione specifica controllando gli estremi
- [X] decidere i 20 (o più) tetramini iniziali
- [X] far cadere i tetramini
- [X] riconoscere ed eliminare le linee complete + dare punti per esse 
  - [X] punti = 2^(righe eliminate - 1) * 1.5f arrotondato per difetto
- [ ] capire quando il gioco finisce
  - [ ] non ci sono più tetramini
  - [ ] non c'è più posto per i tetramini


## Multi-player

- [ ] Gestire due giocatori quindi:
  - [ ] un set condiviso di tetramini con il doppio dei pezzi
  - [ ] due schermi 
  - [ ] due contatori per il punteggio
  - [ ] turni alterni
- [ ] invertire (1 -> 0, 0 -> 1) le righe del giocatore opposto in caso di 2-3 linee eliminate con un solo tetramino
- [ ] se i pezzi finiscono, il giocatore con il punteggio più alto vince
- [ ] implementare una IA da giocare contro


## Turno

- [X] Ogni turno bisongna:
  - [X] mostrare il campo con i tetramini posizionati
  - [X] chiedere al giocatore cosa vuole fare
  - [X] inserire il tetramino
  - [X] aggiornare il punteggio
  - [X] aggiornare i tetramini rimasti