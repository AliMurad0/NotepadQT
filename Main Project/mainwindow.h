#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>

#include "Notepad.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void insertText();
    void deleteText();
    void undoAction();

private:
    QTextEdit *editor;
    QLineEdit *input;

    QAction *insertAct;
    QAction *deleteAct;
    QAction *undoAct;

    Notepad notepad;

    void setupUI();
    void refreshUI();
};

#endif
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>

#include "Notepad.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void insertText();
    void deleteText();
    void undoAction();

private:
    QTextEdit *editor;
    QLineEdit *input;

    QAction *insertAct;
    QAction *deleteAct;
    QAction *undoAct;

    Notepad notepad;

    void setupUI();
    void refreshUI();
};

#endif
