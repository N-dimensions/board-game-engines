# Tic-Tac-Toe-engine
Consists of MCTS implementation on Tic-Tac-Toe, 
the engine has various commands which allows you to
play against it from given position, analyse different positions and also specify details.
It uses MCTS (Monte Carlo Tree Search) where it conducts random playouts in a systematic manner.
commands work as follows
help()                 -> will give list of all commands (only 7 including help()...)
play_start().ON        -> to play against the engine from start (toggle to OFF if you don't want engine analysis)
play_from().ON         -> to play against the engine from specified position (same thing for toggling)
                          after passing the command you have to specify the position.
analyse()              -> to get engine analysis for a particular move.
set playouts_primary   -> setting primary playouts (see analyse function's working) default 10
set playouts_secondary -> setting secondary playouts (see analyse function's working) default 10
terminate()            -> exit the main function
(All header files (.h files) and cpp files have been written by the author (i.e. N-dimensions))
