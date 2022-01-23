## General

- [X] Menu' principale che permette
  - [X] Single Player
  - [X] Local Multiplayer

- [X] rappresentare i singoli tetramini
- [X] metodo per inserire i tetramini nel campo ad una posizione e rotazione specifica controllando gli estremi
- [X] decidere i 20 (o piu') tetramini iniziali
- [X] far cadere i tetramini
- [X] riconoscere ed eliminare le linee complete + dare punti per esse 
  - [X] punti = 2^(righe eliminate - 1) * 1.5f arrotondato per difetto
- [X] capire quando il gioco finisce
  - [X] non ci sono piu' tetramini
  - [X] non c'e' piu' posto per i tetramini


## Multi-player

- [X] Gestire due giocatori quindi:
  - [X] un set condiviso di tetramini con il doppio dei pezzi
  - [X] due schermi 
  - [X] due contatori per il punteggio
  - [X] turni alterni
- [X] invertire (1 -> 0, 0 -> 1) le righe del giocatore opposto in caso di 2-3 linee eliminate con un solo tetramino
- [X] se i pezzi finiscono, il giocatore con il punteggio piu' alto vince
- [X] implementare una IA da giocare contro


## Turno

- [X] Ogni turno bisongna:
  - [X] mostrare il campo con i tetramini posizionati
  - [X] chiedere al giocatore cosa vuole fare
  - [X] inserire il tetramino
  - [X] aggiornare il punteggio
  - [X] aggiornare i tetramini rimasti