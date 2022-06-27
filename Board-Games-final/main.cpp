// Board-Games-final.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*  all_positions_yet --> A map containing all positions
	the first element in this vector would be one with FEN "_________".
	which will also be the 1st element of *history array
	then fd_child_nodes(history[0], all_positions_yet) shall be called. which adds "child nodes to our vector".
	then expl=explore_aor_best_continuation(mvpld=0, true) shall be called which will find the best node for us (and explore the unexplored).
	Add this child node to *history[1] (i.e. history[1]=history[0]->child[expl]) 
	and call fd_child_nodes(history[1]),explore_aor_best_continuation(mvpld=1, false).
	RULE: If you find child nodes and explore them, you are obliged to search from start (except the first time).
	go expl=explore_aor_best_continuation(mvpld=0, true), history[1]=history[0]->child[expl] 
	if(!(history[1]->chd_fd)), 
		go for fd_chd_nodes(history[1], all_positions_yet), explore_aor_best_continuation(mvpld=1, false);
		and then go back to "red/line 10"
	else (good news the node already has children),
		go for  expl = best_continuation_explore(mvpld=1, true), history[2]=history[1]->child[expl] 
		if(!(history[2]->chd_fd))
			go for fd_chd_nodes(history[2], all_positions_yet), explore_aor_best_continuation(mvpld=2, false);
			and then go back to "red/line 10"
		else(you get it)

*/
#include"Header.h"
int main()
{
//	analyse("X____O___");
	srand(time(0));
	Position testboard[3];
	Position *historytmp[10];
	int expl, depth, count=0, best;
	historytmp[0] = &testboard[0];
	std::unordered_map<std::string, Position> all_positions_yet;
	all_positions_yet[testboard[0].FEN] = testboard[0];
	fd_child_nodes(historytmp[0], all_positions_yet);
	for (int mvpld = 0; mvpld < 9; mvpld++)
	{
		depth = mvpld;
		while (depth < 9 && count <1000)
		{
			//std::cout << "depth ->" << depth << std::endl;
			count++;
			//std::cout << "Present depth " << depth << std::endl;
			expl = explore_aor_best_continuation(historytmp, depth, 10, true);
			//std::cout << "Best continuation: " << history[depth]->child[expl]->FEN << std::endl;
			depth++;
			historytmp[depth] = historytmp[depth - 1]->child[expl];
			if (win(historytmp[depth]->FEN) != 2)
			{
				depth = mvpld;
				continue;
			}
			if (historytmp[depth - 1]->child[expl]->chd_fd)
			{
				continue;
			}
			fd_child_nodes(historytmp[depth], all_positions_yet);
			explore_aor_best_continuation(historytmp, depth, 10, false);
			depth = mvpld;
		}
		std::cout << "present move: " << historytmp[mvpld]->FEN << std::endl;
		//std::cout << historytmp[mvpld]->child[0]->explored << std::endl;
		best = fd_best_play(historytmp, mvpld, 100);
		std::cout << "Best continuation: " << historytmp[mvpld]->child[best]->FEN << std::endl;
		historytmp[mvpld + 1] = historytmp[mvpld]->child[best];
		count = 0;
	}
	//std::cout << win(historytmp[9]->FEN) << std::endl;
	return 0;

}
