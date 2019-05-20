#include "stats.h"

// EMPTY CONSTRUCTOR
Stats::Stats()
{
    this->y = 2;
    this->x = 30;
    this->height = 20;
    this->width = 20;
}

// COPY CONSTRUCTOR
Stats::Stats(const Stats &s)
{
    this->y = s.y;
    this->x = s.x;
    this->height = s.height;
    this->width = s.width;
}

// CONSTUCTOR
Stats::Stats(int y, int x, int height, int width)
{
    this->y = y;
    this->x = x;
    this->height = height;
    this->width = width;
}

// DESTRUCTOR
Stats::~Stats(){}


// GET VALUES
int Stats::getY()
{
    return this->y;
}

int Stats::getX()
{
    return this->x;
}

int Stats::getWidth()
{
    return this->width;
}

int Stats::getHeight()
{
    return this->height;
}





// EMPTY CONSTRUCTOR
Stats1::Stats1():Stats(2, 60, 20, 20)
{
    this->gameStatus = true;
    this->paused = true;
}

// COPY CONSTRUCTOR
Stats1::Stats1(const Stats1 &s):Stats(s.y, s.x, s.height, s.width)
{
    this->gameStatus = s.gameStatus;
    this->paused = s.paused;
}

// CONSTRUCTOR
Stats1::Stats1(bool gameStatus, bool paused, int y, int x, int height, int width):Stats(y, x, height, width)
{
    this->gameStatus = gameStatus;
    this->paused = paused;
}

// DESTRUCTOR
Stats1::~Stats1(){};

// GET
bool Stats1::getGameStatus()
{
    return this->gameStatus;
}

bool Stats1::getPaused()
{
    return this->paused;
}

int Stats1::getY()
{
    return this->y;
}

int Stats1::getX()
{
    return this->x;
}

int Stats1::getWidth()
{
    return this->width;
}

int Stats1::getHeight()
{
    return this->height;
}

// SET
void Stats1::setGameStatus(bool gameStatus)
{
    this->gameStatus = gameStatus;
}

void Stats1::setPaused(bool paused)
{
    this->paused = paused;
}

// FETCH
void Stats1::fetchGameStatus()
{
    fetch(this->x, this->y, "Game Status:");
    fetch(this->x, this->y+1, this->gameStatus);
}

void Stats1::fetchPaused()
{
    fetch(this->x, this->y+2, "Paused:");
    fetch(this->x, this->y+3, this->paused);
}

void Stats1::fetchMessages()
{
    fetch(this->x, this->y+5, "Start: 'ENTER'");
    fetch(this->x, this->y+6, "Unpause: 'ENTER'");
    fetch(this->x, this->y+7, "Pause: 'p/P'");
}



// EMPTY CONSTRUCTOR
Stats2::Stats2():Stats(2, 30, 20, 20)
{
    this->level = 1;
    this->score = 0;
    this->speed = 0;
    this->responsiveSpeed = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->nextFigureForm[i][j] = 1;
        }
    }
}

// COPY CONSTRUCTOR
Stats2::Stats2(const Stats2 &s):Stats(s.y, s.x, s.height, s.width)
{
    this->level = s.level;
    this->score = s.score;
    this->speed = s.speed;
    this->responsiveSpeed = s.responsiveSpeed;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->nextFigureForm[i][j] = s.nextFigureForm[i][j];
        }
    }
}

// CONSTRUCTOR
Stats2::Stats2(int level, int score, float speed, float responsiveSpeed, int nextFigureForm[4][4], int y, int x, int height, int width):Stats(y, x, height, width)
{
    this->level = level;
    this->score = score;
    this->speed = speed;
    this->responsiveSpeed = responsiveSpeed;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->nextFigureForm[i][j] = nextFigureForm[i][j];
        }
    }
}

// DESTRUCTOR
Stats2::~Stats2(){};



// GET
int Stats2::getLevel()
{
    return this->level;
}

int Stats2::getScore()
{
    return this->score;
}

float Stats2::getSpeed()
{
    return this->speed;
}

float Stats2::getResponsiveSpeed()
{
    return this->responsiveSpeed;
}

int Stats2::getY()
{
    return this->y;
}

int Stats2::getX()
{
    return this->x;
}

int Stats2::getWidth()
{
    return this->width;
}

int Stats2::getHeight()
{
    return this->height;
}


// SET
void Stats2::setLevel(int level)
{
    this->level = level;
}

void Stats2::setScore(int score)
{
    this->score = score;
}

void Stats2::setSpeed(float speed)
{
    this->speed = speed;
}

void Stats2::setResponsiveSpeed(float responsiveSpeed)
{
    this->responsiveSpeed = responsiveSpeed;
}

void Stats2::setNextFigureForm(int i, int j, int value)
{
    this->nextFigureForm[i][j] = value;
}


// FETCH
void Stats2::fetchLevel()
{
    fetch(this->x,this->y, "Level:");
    fetch(this->x,this->y+1, this->level);
}

void Stats2::fetchScore()
{
    fetch(this->x, this->y+2, "Score:");
    fetch(this->x, this->y+3, this->score);
}

void Stats2::fetchSpeed()
{
    fetch(this->x, this->y+4, "Speed:");
    fetch(this->x, this->y+5, this->speed);
}

void Stats2::fetchResponsiveSpeed()
{
    fetch(this->x, this->y+6, "Responsive Speed:");
    fetch(this->x, this->y+7, this->responsiveSpeed);
}

void Stats2::fetchNextFigureForm()
{
    fetch(this->x, this->y+8, "Next figure:");

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(this->nextFigureForm[i][j])
            {
                fetch(this->x + j, this->y + 9 + i, '@');
            } else {
                fetch(this->x + j, this->y + 9 + i, ' ');
            }
        }
    }
}

// EMPTY CONSTRUCTOR
Stats3::Stats3():Stats(2, 90, 20, 20)
{

}

// COPY CONSTRUCTOR
Stats3::Stats3(const Stats3 &s):Stats(s.y, s.x, s.height, s.width)
{
    this->scores = s.scores;
}

// CONSTRUCTOR
Stats3::Stats3(list<int>scores):Stats()
{
    this->scores = scores;
}

// DESTRUCTOR
Stats3::~Stats3(){};

// READ SCORES FROM scores.txt
void Stats3::readScores()
{

    int k;
    this->scores.clear();

    std::ifstream myfile1("scores.txt");

    if(!myfile1.fail())
    {
        while(!myfile1.eof())
        {
            myfile1>>k;
            this->scores.push_back(k);
        }
    }
    myfile1.close();
}

// APPEND SCORES
void Stats3::appendScores(int score)
{
    this->scores.push_back(score);
}

// UPDATE SCORES
void Stats3::updateScores()
{
    this->scores.sort();
    this->scores.reverse();

    list<int>::iterator it;

    ofstream myfile2("scores.txt");

    for(it = this->scores.begin(); it != this->scores.end(); it++)
    {
        myfile2 << *it;
        if(it != --this->scores.end())
        {
            myfile2 << " ";
        }
    }
    myfile2.close();
}

// FETCH TOP 5 SCORES
void Stats3::fetchTop5()
{
    int _i = 0;
    list<int>::iterator it;
    fetch(this->x, this->y, "TOP 5 SCORES:");

    for(it = this->scores.begin(); it != this->scores.end(); it++)
    {
        if(_i < 5)
        {
            fetch(this->x, this->y + 1 + _i, *it);
        }
        _i++;
    }
}


//GET
int Stats3::getY()
{
    return this->y;
}

int Stats3::getX()
{
    return this->x;
}

int Stats3::getWidth()
{
    return this->width;
}

int Stats3::getHeight()
{
    return this->height;
}
