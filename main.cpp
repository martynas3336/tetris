#include <iostream>
#include <list>
#include <fstream>

#include <time.h>
#include <windows.h>

#include "functions.cpp"

#include "figure.cpp"
#include "field.cpp"
#include "stats.cpp"

void game();
void updateFigureForm(Figure *figure, int figureType);

int main()
{
    try {
        game();
    } catch(const std::exception& err){
        std::cout << "ERROR" << std::endl;
    }

}

void game()
{
    float startingDelay = 100;
    float minDelay = 25;

    float timer = 0;
    float delay = startingDelay;
    float responsiveDelay = startingDelay;

    bool paused = true;
    bool gameStatus = true;

    bool figureSpawned = false;
    Field field;
    field.refreshFieldMatrix();
    field.fetchField();

    generateBorders(field.getY(), field.getX(), field.getHeight(), field.getWidth());

    Stats1 stats1;

    generateBorders(stats1.getY(), stats1.getX(), stats1.getHeight(), stats1.getWidth());

    stats1.setPaused(paused);
    stats1.fetchPaused();

    stats1.setGameStatus(gameStatus);
    stats1.fetchGameStatus();

    stats1.fetchMessages();

    Stats2 stats2;

    generateBorders(stats2.getY(), stats2.getX(), stats2.getHeight(), stats2.getWidth());

    stats2.setLevel(1);
    stats2.fetchLevel();

    stats2.setScore(0);
    stats2.fetchScore();

    stats2.setSpeed(100/delay);
    stats2.setResponsiveSpeed(0);
    stats2.fetchSpeed();
    stats2.fetchResponsiveSpeed();

    Stats3 stats3;

    generateBorders(stats3.getY(), stats3.getX(), stats3.getHeight(), stats3.getWidth());

    stats3.readScores();
    stats3.fetchTop5();

    Figure figure(0);

    Figure nextFigure(0);

    updateFigureForm(&nextFigure, random(1, 7));
    field+(field, &nextFigure);
//    field.spawnFigure(&nextFigure);

    while(1)
    {
        if(!field.getGameStatus())
        {
            if(gameStatus != field.getGameStatus())
            {
                stats3.appendScores(stats2.getScore());
                stats3.updateScores();
                stats3.readScores();
                stats3.fetchTop5();
            }
            gameStatus = field.getGameStatus();
            if(!gameStatus)
            {
                stats1.setGameStatus(gameStatus);
                stats1.fetchGameStatus();
            }
            if(GetAsyncKeyState(VK_RETURN)&1)
            {
                delay = startingDelay;
                responsiveDelay = startingDelay;

                paused = true;
                gameStatus = true;
                figureSpawned = false;

                field.refreshFieldMatrix();
                field.refreshOldFigureMatrix();
                field.refreshNewFigureMatrix();
                field.setGameStatus(gameStatus);
                field.fetchField();

                stats2.clearLevel();
                stats2.setLevel(1);
                stats2.fetchLevel();

                stats2.clearScore();
                stats2.setScore(0);
                stats2.fetchScore();

                stats2.clearSpeed();
                stats2.setSpeed(100/delay);
                stats2.fetchSpeed();

                stats2.clearResponsiveSpeed();
                stats2.setResponsiveSpeed(0);
                stats2.fetchResponsiveSpeed();

                stats3.readScores();
                stats3.fetchTop5();
            }
        } else {
            if(!paused)
            {
                timer++;
            }
            if(figureSpawned)
            {
                if(timer >= responsiveDelay)
                {
                    if(field.checkFigureGoDown(&figure))
                    {
                        figure.goDown();

                        field = field << &figure;
//                        field.fetchFigure(&figure);
                    } else {
                        field^(&figure);

                        // UPDATE SCORE
                        int lines = field.checkLines();
                        if(lines)
                        {
                            stats2.setScore(stats2.getScore() + lines * 10);
                            stats2.fetchScore();
                        }

                        // CHECK AND UPDATE LEVEL
                        if(stats2.getLevel() != stats2.getScore() / 100 + 1)
                        {
                            stats2.setLevel(stats2.getScore() / 100 + 1);
                            stats2.fetchLevel();
                        }

                        // CHECK AND UPDATE SPEED

                        float _delay = -0.75 * stats2.getScore() + 100;
                        if(_delay > 100)
                        {
                            _delay = 100;
                        }
                        if(_delay < 25)
                        {
                            _delay = 25;
                        }
                        if(_delay != delay)
                        {
                            delay = _delay;
                            stats2.setSpeed(100/_delay);
                            stats2.setResponsiveSpeed(100/_delay);
                            stats2.fetchSpeed();
                            stats2.fetchResponsiveSpeed();
                        }

                        field.fetchField();
                        figureSpawned = false;
                        field.checkGameStatus();
                    }
                    timer = 0;
                } else {

                    if(GetAsyncKeyState(VK_RETURN)&1)
                    {
                        if(paused)
                        {
                            paused = false;
                            stats1.setPaused(paused);
                            stats1.fetchPaused();
                        }

                        if(!gameStatus)
                        {
                            gameStatus = true;
                            stats1.setGameStatus(gameStatus);
                            stats1.fetchGameStatus();
                        }
                    }

                    if(GetAsyncKeyState('P')&1 || GetAsyncKeyState('p'))
                    {
                        if(!paused)
                        {
                            paused = true;
                            stats1.setPaused(paused);
                            stats1.fetchPaused();
                        }
                    }

                    if(!paused && gameStatus)
                    {
                        if(GetAsyncKeyState(VK_UP)&1)
                        {
                            if(field.checkFigureRotateRight(&figure))
                            {
                                figure.rotateRight();
                                field = field << &figure;
//                                field.fetchFigure(&figure);
                            }
                        }


                        if(GetAsyncKeyState(VK_LEFT)&1)
                        {
                            if(field.checkFigureGoLeft(&figure))
                            {
                                figure.goLeft();
                                field = field << &figure;
//                                field.fetchFigure(&figure);
                            }
                        }


                        if(GetAsyncKeyState(VK_RIGHT)&1)
                        {
                            if(field.checkFigureGoRight(&figure))
                            {
                                figure.goRight();
                                field = field << &figure;
//                                field.fetchFigure(&figure);
                            }
                        }

                        if(GetAsyncKeyState(VK_DOWN))
                        {
                            responsiveDelay = delay * 0.25;
                            stats2.setResponsiveSpeed(100 / responsiveDelay);
                            stats2.fetchResponsiveSpeed();
                        } else {
                            responsiveDelay = delay;
                            stats2.setResponsiveSpeed(100 / responsiveDelay);
                            stats2.fetchResponsiveSpeed();
                        }
                    }

                }




            } else {
                figure = nextFigure;

                updateFigureForm(&nextFigure, random(1, 7));

                field+(field, &nextFigure);
//                field.spawnFigure(&nextFigure);
                figureSpawned = true;

                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        stats2.setNextFigureForm(i, j, nextFigure.getFormShadowValue(i, j));
                    }
                }
                stats2.fetchNextFigureForm();
            }
            Sleep(1);
        }
    }
}


void updateFigureForm(Figure *figure, int figureType)
{
    switch(figureType)
    {
        case 1:// I
        {
            int form[4][4] = {
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0}};
            figure->updateForm(4, 1, form);
            break;
        }
        case 2:// Z
        {
            int form[4][4] = {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}};
            figure->updateForm(2, 3, form);
            break;
        }
        case 3:// S
        {
            int form[4][4] = {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}};
            figure->updateForm(2, 3, form);
            break;
        }
        case 4:// T
        {
            int form[4][4] = {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}};
            figure->updateForm(2, 3, form);
            break;
        }
        case 5:// L
        {
            int form[4][4] = {
            {1,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,0,0,0}};
            figure->updateForm(3, 2, form);
            break;
        }
        case 6:// J
        {
            int form[4][4] = {
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}};
            figure->updateForm(3, 2, form);
            break;
        }
        case 7:// O
        {
            int form[4][4] = {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}};
            figure->updateForm(2, 2, form);
            break;
        }
        default:
        {
            int form[4][4] = {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}};
            figure->updateForm(4, 4, form);
        }
    }
}
