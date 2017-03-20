# TetrisTerm
Little ncurses tetris game.

## Make and play

```
$ make
$ ./tetristerm --help
Usage: ./tetristerm [options]
Options:
   --help               Display this help
   -l --level={num}     Start Tetris at level num (def: 1)
   -kl --key-left={K}   Move the tetrimino LEFT using the K key (def: left arrow)
   -kr --key-right={K}  Move the tetrimino RIGHT using the K key (def: right arrow)
   -kt --key-turn={K}   TURN the tetrimino clockwise 90d using the K key  (def: top arrow)
   -kd --key-drop={K}   DROP the tetrimino using the K key (def: down arrow)
   -kq --key-quit={K}   QUIT the using the K key (def: 'Q' key)
   -kp --key-pause={K}  PAUSE/RESTART the game using the K key (def: space bar)
   --map-size={row,col} Set the numbers of rows and columns of the map (def: 20,10)
   -w --without-next    Hide next tetrimino (def: false)
   -d --debug           Debug mode (def: false)
```

## Create your own tetriminos

You can craft your own tetriminos ! The binary will look for `.tetrimino` files located in the `tetriminos/` folder.

The format is the following:
```
cols rows color
[shape]
```
Here is a sample file:
```
3 2 3
***
 *
```
Your tetrimino doesn't seem to appear in-game ? It may be badly formatted, activate the debug mode with the `-d` option.

## Known issues

The game may blink annoyingly, due to a big mapsize or of your terminal. This is our first ncurses project, so don't blame us :)
