#include "figure.h"

// EMPTY CONSTRUCTOR
Figure::Figure()
{
    this->figureType = 0;
    this->y = -4;
    this->x = 0;
    this->dx = 0;

    this->height = 4;
    this->width = 4;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->form[i][j] = 1;
        }
    }

    this->heightShadow = 4;
    this->widthShadow = 4;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->formShadow[i][j] = 1;
        }
    }
}

// COPY CONSTRUCTOR
Figure::Figure(const Figure &f)
{
    this->figureType = f.figureType;
    this->y = f.y;
    this->x = f.x;
    this->dx = f.dx;

    this->height = f.height;
    this->width = f.width;

    this->heightShadow = f.heightShadow;
    this->widthShadow = f.widthShadow;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->form[i][j] = f.form[i][j];
            this->formShadow[i][j] = f.formShadow[i][j];
        }
    }
}

// CONSTRUCTOR
Figure::Figure(int figureType)
{
    this->figureType = 0;
    this->y = -4;
    this->x = 0;
    this->dx = 0;

    this->height = 4;
    this->width = 4;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->form[i][j] = 1;
        }
    }

    this->heightShadow = 4;
    this->widthShadow = 4;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->formShadow[i][j] = 1;
        }
    }
}

// CONSTRUCTOR
Figure::Figure(int figureType, int y, int x, int dx, int height, int width, int form[4][4], int heightShadow, int widthShadow, int formShadow[4][4])
{
    this->figureType = figureType;
    this->y = y;
    this->x = x;
    this->dx = dx;

    this->height = height;
    this->width = width;

    this->heightShadow = heightShadow;
    this->widthShadow = widthShadow;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            this->form[i][j] = form[i][j];
            this->formShadow[i][j] = formShadow[i][j];
        }
    }
}

Figure::~Figure(){};


// EMPTY FORMS
void Figure::refreshForm()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->form[i][j] = 0;
        }
    }
}

void Figure::refreshFormShadow()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->formShadow[i][j] = 0;
        }
    }
}

// UPDATE FORM
void Figure::updateForm(int height, int width, int form[4][4])
{
    this->height = height;
    this->width = width;

    this->heightShadow = height;
    this->widthShadow = width;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            this->form[i][j] = form[i][j];
            this->formShadow[i][j] = form[i][j];
        }
    }
}

// SET VALUES
void Figure::setYPosition(int y)
{
    this->y = y;
}

void Figure::setXPosition(int x)
{
    this->x = x;
}

void Figure::setDxAngle(int dx)
{
    this->dx = dx;
}


// ROTATE
void Figure::rotateRight()
{
    int _dx = this->dx;
    _dx++;
    if(_dx == 4)
    {
        _dx = 0;
    }
    this->setDxAngle(_dx);
    this->refreshFormShadow();

    if(this->dx == 0 || this->dx == 2)
    {
        this->heightShadow = this->height;
        this->widthShadow = this->width;
        if(this->dx == 0)
        {
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    this->formShadow[i][j] = this->form[i][j];
                }
            }
        }
        if(this->dx == 2)
        {
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(i-4+this->heightShadow>= 0 && i-4+this->heightShadow < 4 && j-4+this->widthShadow >=0 && j-4+this->widthShadow <4)
                    {
                        this->formShadow[i-4+this->heightShadow][j-4+this->widthShadow] = this->form[3 - i][3 - j];
                    }
                }
            }
        }
    }

    if(this->dx == 1 || this->dx == 3)
    {
        this->heightShadow = this->width;
        this->widthShadow = this->height;
        if(this->dx == 1)
        {
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(j-4+this->widthShadow >=0 && j-4+this->widthShadow <4)
                    {
                        this->formShadow[i][j-4+this->widthShadow] = this->form[3 - j][i];
                    }
                }
            }
        }
        if(this->dx == 3)
        {
            for(int i = 0; i < 4; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(i-4+this->heightShadow>= 0 && i-4+this->heightShadow < 4)
                    {
                        this->formShadow[i-4+this->heightShadow][j] = this->form[j][3 - i];
                    }
                }
            }
        }
    }

}

// GO DOWN
void Figure::goDown()
{
    int _y = this->y;
    _y++;
    this->setYPosition(_y);
}

// GO RIGHT
void Figure::goRight()
{
    int _x = this->x;
    _x++;
    this->setXPosition(_x);
}

// GO LEFT
void Figure::goLeft()
{
    int _x = this->x;
    _x--;
    this->setXPosition(_x);
}


// GET VALUES
int Figure::getY()
{
    return this->y;
}

int Figure::getX()
{
    return this->x;
}

int Figure::getDx()
{
    return this->dx;
}

int Figure::getHeight()
{
    return this->height;
}

int Figure::getWidth()
{
    return this->width;
}

int Figure::getFormValue(int i, int j)
{
    return this->form[i][j];
}


int Figure::getHeightShadow()
{
    return this->heightShadow;
}

int Figure::getWidthShadow()
{
    return this->widthShadow;
}

int Figure::getFormShadowValue(int i, int j)
{
    return this->formShadow[i][j];
}
