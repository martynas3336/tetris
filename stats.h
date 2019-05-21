#ifndef STATS_H
#define STATS_H

using namespace std;

class Stats {

    protected:
        int y;
        int x;
        int height;
        int width;

    public:
        Stats();
        Stats(const Stats &s);
        Stats(int y, int x, int height, int width);
        ~Stats();

        virtual int getY();
        virtual int getX();
        virtual int getHeight();
        virtual int getWidth();
};

class Stats1 : public Stats
{

    private:
        bool gameStatus;
        bool paused;

    public:
        Stats1();
        Stats1(const Stats1 &s);
        Stats1(bool gameStatus, bool paused, int y, int x, int height, int width);
        ~Stats1();

        bool getGameStatus();
        bool getPaused();

        void setGameStatus(bool gameStatus);
        void setPaused(bool paused);

        void fetchGameStatus();
        void fetchPaused();

        void fetchMessages();

        int getY();
        int getX();
        int getHeight();
        int getWidth();
};

class Stats2 : public Stats
{
    private:
        int level;
        int score;
        float speed;
        float responsiveSpeed;
        int nextFigureForm[4][4];

    public:
        Stats2();
        Stats2(const Stats2 &s);
        Stats2(int level, int score, float speed, float responsiveSpeed, int nextFigureForm[4][4], int y, int x, int height, int width);
        ~Stats2();

        int getLevel();
        int getScore();
        float getSpeed();
        float getResponsiveSpeed();

        void setLevel(int level);
        void setScore(int score);
        void setSpeed(float speed);
        void setResponsiveSpeed(float responsiveSpeed);
        void setNextFigureForm(int i, int j, int value);

        void clearLevel();
        void fetchLevel();

        void clearScore();
        void fetchScore();

        void clearSpeed();
        void fetchSpeed();

        void clearResponsiveSpeed();
        void fetchResponsiveSpeed();

        void fetchNextFigureForm();

        int getY();
        int getX();
        int getHeight();
        int getWidth();

};

class Stats3:Stats
{
    private:
        list<int>scores;

    public:
        Stats3();
        Stats3(const Stats3 &s);
        Stats3(list<int>scores);
        ~Stats3();

        void readScores();
        void appendScores(int score);
        void updateScores();
        void fetchTop5();

        int getY();
        int getX();
        int getHeight();
        int getWidth();

};
#endif
