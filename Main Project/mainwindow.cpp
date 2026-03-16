#include "mainwindow.h"
#include <QVBoxLayout>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    refreshUI();
}

void MainWindow::setupUI()
{
    setWindowTitle("Notepad Pro (Stack Based)");
    resize(800, 500);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    input = new QLineEdit();
    input->setPlaceholderText("Type text and press Enter");

    editor = new QTextEdit();
    editor->setReadOnly(true);

    layout->addWidget(input);
    layout->addWidget(editor);
    setCentralWidget(central);

    QToolBar *toolbar = addToolBar("Tools");
    insertAct = toolbar->addAction("Insert");
    deleteAct = toolbar->addAction("Delete");
    undoAct   = toolbar->addAction("Undo");

    connect(insertAct, &QAction::triggered, this, &MainWindow::insertText);
    connect(deleteAct, &QAction::triggered, this, &MainWindow::deleteText);
    connect(undoAct,   &QAction::triggered, this, &MainWindow::undoAction);
    connect(input, &QLineEdit::returnPressed, this, &MainWindow::insertText);

    statusBar()->showMessage("Cursor: 0");

    // Dark theme
    setStyleSheet(
        "QMainWindow{background:#1e1e1e;}"
        "QTextEdit{background:#252526;color:white;font:13px Consolas;}"
        "QLineEdit{background:#333;color:white;padding:6px;}"
        );
}

void MainWindow::insertText()
{
    QString txt = input->text();
    if (txt.isEmpty()) return;

    notepad.insertText(txt.toStdString());
    input->clear();
    refreshUI();
}

void MainWindow::deleteText()
{
    bool ok;
    int len = QInputDialog::getInt(this, "Delete", "Characters:", 1, 1, 1000, 1, &ok);
    if (ok) {
        notepad.deleteText(len);
        refreshUI();
    }
}

void MainWindow::undoAction()
{
    notepad.undo();
    refreshUI();
}

void MainWindow::refreshUI()
{
    editor->setText(QString::fromStdString(notepad.getContent()));
    statusBar()->showMessage(
        "Cursor: " + QString::number(notepad.getCursorPosition()) +
        " | Length: " + QString::number(notepad.getContent().length())
        );
}
