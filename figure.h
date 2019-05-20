#ifndef FIGURE_H
#define FIGURE_H

class Figure
{

    private:
        int figureType;
        int y;
        int x;
        int dx;
        int height;
        int width;
        int form[4][4];

        int heightShadow;
        int widthShadow;
        int formShadow[4][4];

    public:
        Figure();
        Figure(const Figure &f);
        Figure(int figureType);
        Figure(int figureType, int y, int x, int dx, int height, int width, int form[4][4], int heightShadow, int widthShadow, int formShadow[4][4]);
        ~Figure();

        void refreshForm();
        void refreshFormShadow();
        void updateForm(int height, int width, int form[4][4]);

        void setYPosition(int y);
        void setXPosition(int x);
        void setDxAngle(int dx);

        void rotateRight();
        void goDown();
        void goRight();
        void goLeft();

        int getY();
        int getX();
        int getDx();

        int getHeight();
        int getWidth();
        int getFormValue(int i, int j);

        int getHeightShadow();
        int getWidthShadow();
        int getFormShadowValue(int i, int j);

};

#endif
