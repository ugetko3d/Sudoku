#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QMessageBox>

#include "ui_Sudoku.h"

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget* parent = Q_NULLPTR);

private:
    bool solve(int y, int x);
    bool validNumber(int y, int x, int val);
    bool isValidBoard();
    void updateNumberBox(int x, int y, int val);
    void updateBoard();

    Ui::SudokuClass ui;

    const int NEW = 0;
    int** board;

private slots:
    void onButtonSolveClicked();
    void onButtonResetClicked();
};
