#include "field.h"

// EMPTY CONSTRUCTOR
Field::Field()
{
    this->y = 2;
    this->x = 5;

    this->height = 20;
    this->width = 15;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            this->matrix[i][j] = 0;
            this->oldFigureMatrix[i][j] = 0;
            this->newFigureMatrix[i][j] = 0;
        }
    }

    this->ongoingBlock = '@';
    this->block = '#';
    this->field = ' ';

    this->gameStatus = true;
}

// COPY CONSTRUCTOR
Field::Field(const Field &f)
{
    this->y = f.y;
    this->x = f.x;

    this->height = f.height;
    this->width = f.width;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            this->matrix[i][j] = f.matrix[i][j];
            this->oldFigureMatrix[i][j] = f.oldFigureMatrix[i][j];
            this->newFigureMatrix[i][j] = f.newFigureMatrix[i][j];
        }
    }

    this->ongoingBlock = f.ongoingBlock;
    this->block = f.block;
    this->field = f.field;

    this->gameStatus = f.gameStatus;
}

// CONSTRUCTOR
Field::Field(int x, int y, int height, int width, int matrix[100][100], int oldFigureMatrix[100][100], int newFigureMatrix[100][100], char ongoingBlock, char block, char field, bool gameStatus)
{
    this->y = y;
    this->x = x;

    this->height = height;
    this->width = width;

    this->block = block;
    this->field = field;

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            this->matrix[i][j] = matrix[i][j];
            this->oldFigureMatrix[i][j] = oldFigureMatrix[i][j];
            this->newFigureMatrix[i][j] = newFigureMatrix[i][j];
        }
    }

    this->ongoingBlock = ongoingBlock;
    this->block = block;
    this->field = field;

    this->gameStatus = gameStatus;
}

// DESTRUCTOR
Field::~Field(){}


// EMPTY MATRIX
void Field::refreshFieldMatrix()
{
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->width; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void Field::refreshOldFigureMatrix()
{
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->width; j++)
        {
            oldFigureMatrix[i][j] = 0;
        }
    }
}

void Field::refreshNewFigureMatrix()
{
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->width; j++)
        {
            newFigureMatrix[i][j] = 0;
        }
    }
}



// FETCH MATRIX FIELD VALUES TO SCREEN
void Field::fetchField()
{
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->width; j++)
        {
            if(matrix[i][j] == 1)
            {
                fetch(this->x + j, this->y + i, this->block);
            } else {
                fetch(this->x + j, this->y + i, this->field);
            }
        }
    }

    this->refreshOldFigureMatrix();
    this->refreshNewFigureMatrix();
}

// CLEAN PREVIOUS FIGURE TRACK. THIS IS A MUST. COULD USE fetchField, BUT IT WILL LOOK LIKE IT'S FLASHING
void Field::clean()
{
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->width; j++)
        {
            if(this->oldFigureMatrix[i][j] != this->newFigureMatrix[i][j])
            {
                if(matrix[i][j] == 1)
                {
                    fetch(this->x + j, this->y + i, this->block);
                } else {
                    fetch(this->x + j, this->y + i, this->field);
                }
            }
        }
    }
}

// CHECK IF FIGURE IS ALLOWED IN CURRENT POSITION
bool Field::check(Figure *figure)
{
    //COMPLETELY TOP OF THE FIELD
    bool ok = false;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i + figure->getY() >= 0 && figure->getFormShadowValue(i, j))
            {
                ok = true;
            }
        }
    }

    if(!ok)
    {
        return false;
    }


    // BELOW THE FIELD
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i + figure->getY() >= this->height && figure->getFormShadowValue(i, j))
            {
                return false;
            }
        }
    }
    // RIGHT OF THE FIELD
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(j + figure->getX() >= this->width && figure->getFormShadowValue(i, j))
            {
                return false;
            }
        }
    }
    // LEFT OF THE FIELD
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(j + figure->getX() < 0 && figure->getFormShadowValue(i, j))
            {
                return false;
            }
        }
    }
    // DOESNT GO ON TOP OF THE OTHER FIGURE
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i + figure->getY() >= 0)
            {
                if(this->matrix[i + figure->getY()][j + figure->getX()] && figure->getFormShadowValue(i, j))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// SET POTISION OF CURRENT FIGURE TO BE JUST ON THE TOP OF THE FIELD AND IN THE MIDDLE
//void Field::spawnFigure(Figure *figure)
Field operator+(Field field, Figure *figure)
{
    // SET FIGURE X POSITION TO BE IN THE MIDDLE
    figure->setXPosition((field.getWidth() - figure->getWidth())/2);

    // SET FIGURE Y POSITION TO BE JUST AT THE TOP OF THE FIELD
    figure->setYPosition(-(figure->getHeight()));
}

// FETCH FIGURE TO SCREEN REMOVING TRACKS AT THE SAME TIME
Field operator<<(Field field, Figure *figure)
{

    field.refreshNewFigureMatrix();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i+figure->getY() >= 0 && j+figure->getX() >= 0)
            {
                field.setNewFigureMatrix(i+figure->getY(),j+figure->getX(), figure->getFormShadowValue(i, j));
            }
        }
    }


    field.clean();

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(figure->getFormShadowValue(i, j) && i+(figure->getY()) >= 0)
            {
                fetch(j+(figure->getX()) + field.getX(), i+(figure->getY()) + field.getY(), field.getOngoingBlock());
            }
        }
    }

    field.refreshOldFigureMatrix();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i+figure->getY() >= 0 && j+figure->getX() >= 0)
            {
                field.setOldFigureMatrix(i+figure->getY(),j+figure->getX(), figure->getFormShadowValue(i, j));
            }
        }
    }

    return field;
}

// STICK THIS FIGURE THE THE MATRIX
void Field::operator^(Figure *figure)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(figure->getFormShadowValue(i, j))
            {
                if(i+(figure->getY()) >= 0)
                {
                    this->matrix[i+(figure->getY())][j+(figure->getX())] = figure->getFormShadowValue(i,j);
                }
            }
        }
    }
}

// CHECK LINES IF THERE IS FULL LINE
int Field::checkLines()
{
    int lines = 0;
    for(int i = 0; i < height; i++)
    {
        bool line = true;
        for(int j = 0; j < width; j++)
        {
            line = line && matrix[i][j];
        }
        if(line)
        {
            lines++;
            removeLine(i);
        }
    }
    return lines;
}

// REMOVE LINE FROM MATRIX
void Field::removeLine(int line)
{
    for(int i = line; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            if(i)
            {
                matrix[i][j] = matrix[i-1][j];
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

// CHECK IF FIGURE CAN ROTATE RIGHT
bool Field::checkFigureRotateRight(Figure *figure)
{
    Figure _figure = *figure;
    _figure.rotateRight();
    if(check(&_figure))
    {
        return true;
    }
    return false;
}

// CHECK IF FUGURE CAN GO DOWN
bool Field::checkFigureGoDown(Figure *figure)
{
    Figure _figure = *figure;
    _figure.goDown();
    if(check(&_figure))
    {
        return true;
    }
    return false;
}

// CHECK IF FIGURE CAN GO LEFT
bool Field::checkFigureGoLeft(Figure *figure)
{
    Figure _figure = *figure;
    _figure.goLeft();
    if(check(&_figure))
    {
        return true;
    }
    return false;
}

// CHECK IF FIGURE CAN GO RIGHT
bool Field::checkFigureGoRight(Figure *figure)
{
    Figure _figure = *figure;
    _figure.goRight();
    if(check(&_figure))
    {
        return true;
    }
    return false;
}

// CHECK IF ANY OF MIDDLE 3 BLOCKS OF MATRIX TOP ARE TAKEN
void Field::checkGameStatus()
{
    int deadSpot = this->width/2;

    if(this->matrix[0][deadSpot-1] || this->matrix[0][deadSpot] || this->matrix[0][deadSpot+1])
    {
        this->gameStatus = false;
    } else {
        this->gameStatus = true;
    }
}


// GET VALUES
int Field::getY()
{
    return this->y;
}

int Field::getX()
{
    return this->x;
}

int Field::getHeight()
{
    return this->height;
}

int Field::getWidth()
{
    return this->width;
}

char Field::getOngoingBlock()
{
    return this->ongoingBlock;
}

bool Field::getGameStatus()
{
    return this->gameStatus;
}
void Field::setGameStatus(bool status)
{
    this->gameStatus = status;
}

void Field::setNewFigureMatrix(int i, int j, int value)
{
    this->newFigureMatrix[i][j] = value;
}

void Field::setOldFigureMatrix(int i, int j, int value)
{
    this->oldFigureMatrix[i][j] = value;
}
