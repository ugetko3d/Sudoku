#include "Sudoku.h"

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    board = new int*[9];
    for(int i = 0; i < 9; i++)
        board[i] = new int[9];

    for (int i = 0; i < 9; i++)
    {   
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = NEW;

            QSpinBox* numberBox = new QSpinBox;

            QFont font = numberBox->font();
            font.setPointSize(20);
            numberBox->setFont(font);

            numberBox->setMinimum(NEW);
            numberBox->setMaximum(9);
            numberBox->setValue(NEW);
            numberBox->setFixedHeight(50);
            numberBox->setFixedWidth(50);

            ui.gridLayout->addWidget(numberBox, i, j);
        }
    }

    connect(ui.buttonSolve, &QPushButton::released, this, &Sudoku::onButtonSolveClicked);
    connect(ui.buttonReset, &QPushButton::released, this, &Sudoku::onButtonResetClicked);
}

bool Sudoku::solve(int y, int x)
{
    if (y > 8) {
        return true;
    }

    if (board[y][x] != NEW) {

        if (x < 8) {
            return solve(y, (x + 1));
        }

        else {
            return solve((y + 1), 0);
        }

    }

    else {

        for (int val = 1; val < 10; val++) {

            if (validNumber(y, x, val)) {
                board[y][x] = val;
                updateNumberBox(y, x, val);

                if (x < 8) {

                    if (solve(y, (x + 1))) {
                        return true;
                    }

                    else {
                        board[y][x] = NEW;
                        updateNumberBox(y, x, NEW);
                    }

                }

                else {

                    if (solve((y + 1), 0)) {
                        return true;
                    }

                    else {
                        board[y][x] = NEW;
                        updateNumberBox(y, x, NEW);
                    }

                }

            }

        }

        return false;

    }
}

bool Sudoku::validNumber(int y, int x, int val)
{
    for (int i = 0; i < 9; i++) {

        if (i != y) {
            if (board[i][x] == val) {
                return false;
            }
        }

        if (i != x) {
            if (board[y][i] == val) {
                return false;
            }
        }

    }

    int startRow = y / 3 * 3;
    int startCol = x / 3 * 3;

    for (int j = startRow; j < (startRow + 3); j++) {

        for (int k = startCol; k < (startCol + 3); k++) {

            if (!(j == y && k == x)) {

                if (board[j][k] == val) {
                    return false;
                }

            }

        }

    }

    return true;
}

bool Sudoku::isValidBoard()
{
    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            if (board[i][j] != NEW) {

                for (int val = 1; val < 10; val++) {

                    if (!(validNumber(i, j, val)) && board[i][j] == val) {
                        return false;
                    }

                }

            }

        }

    }
    return true;
}

void Sudoku::onButtonSolveClicked()
{
    updateBoard();

    QMessageBox* message = new QMessageBox;

    if (!isValidBoard())
    {
        
        message->setText("Sudoku board is invalid, please learn the rules of Sudoku...");
        message->exec();
    }
    else {
        if (solve(0, 0))
        {
            message->setText("Sudoku board was successfully solved!");
            message->exec();
        }
        else
        {
            message->setText("There was no solution to this Sudoku board...");
            message->exec();
        }
    }
}

void Sudoku::onButtonResetClicked()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            updateNumberBox(i, j, 0);
}

void Sudoku::updateNumberBox(int x, int y, int val)
{
    QLayoutItem* item = ui.gridLayout->itemAtPosition(x, y);
    QWidget* widget = item->widget();
    QSpinBox* numberBox = dynamic_cast<QSpinBox*>(widget);
    numberBox->setValue(val);
    numberBox->repaint();
}

void Sudoku::updateBoard()
{
    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {
            QLayoutItem* item = ui.gridLayout->itemAtPosition(i, j);
            QWidget* widget = item->widget();
            QSpinBox* numberBox = dynamic_cast<QSpinBox*>(widget);
            board[i][j] = numberBox->value();
        }

    }
}
