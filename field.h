#ifndef FIELD_H
#define FIELD_H

class Field {

    private:
        int y;
        int x;
        int width;
        int height;

        int matrix[100][100];
        int oldFigureMatrix[100][100];
        int newFigureMatrix[100][100];

        char ongoingBlock;
        char block;
        char field;

        bool gameStatus = true;

    public:
        Field();
        Field(const Field &f);
        Field(int x, int y, int height, int width, int matrix[100][100], int oldFigureMatrix[100][100], int newFigureMatrix[100][100], char ongoingBlock, char block, char field, bool gameStatus);
        ~Field();

        void refreshFieldMatrix();
        void refreshOldFigureMatrix();
        void refreshNewFigureMatrix();

        void fetchField();
        void clean();

        bool check(Figure *figure);

        // SPAWN FIGURE OPERATOR
        friend Field operator+(Field field, Figure *figure);

        void fetchFigure(Figure *figure);
        // STICK FIGURE OPERATOR
        void operator^(Figure *figure);

        int checkLines();
        void removeLine(int line);

        bool checkFigureRotateRight(Figure *figure);
        bool checkFigureGoDown(Figure *figure);
        bool checkFigureGoLeft(Figure *figure);
        bool checkFigureGoRight(Figure *figure);
        void checkGameStatus();

        int getY();
        int getX();

        int getHeight();
        int getWidth();

        bool getGameStatus();

};
#endif
