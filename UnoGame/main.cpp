#include "game/uno_game.h"
#include "utils/logger.h"
#include "utils/stats.h"
#include "SmartPlayer.hpp"
#include "StupidPlayer.hpp"

void statisticTest();
int main()
{

    UnoGame game;
    Logger logger;
    SmartPlayer player1("Vasya");
    StupidPlayer player2("Kolya");
    game.addPlayer(&player1);
    game.addPlayer(&player2);
    game.addObserver(&logger);
    game.runGame();
    statisticTest();
}

void statisticTest()
{
    UnoGame game;
    SmartPlayer player1("Vasya");
    StupidPlayer player2("Kolya");
    game.addPlayer(&player1);
    game.addPlayer(&player2);
    StatsObserver result = runGames(game, 1000);
    StatsObserver::MV winMV = result.getWinsMV();
    std::cout << "Vasya won in " << winMV.mean[0] * 100 << "% of games" << std::endl;
}
