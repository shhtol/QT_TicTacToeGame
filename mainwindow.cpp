#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "configurationdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionNewGame, &QAction::triggered, this, &MainWindow::startNewGame);
    QObject::connect(ui->actionQuit, &QAction::triggered, qApp, &QApplication::quit);
    QObject::connect(ui->gameBoard, &Widget::currentPlayerChanged, this, &MainWindow::updateNameLabels);
    QObject::connect(ui->gameBoard, &Widget::gameOver, this, &MainWindow::handleGameOver);
    ui->gameBoard->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame() {
    ConfigurationDialog dlg(this);
    if (dlg.exec() == QDialog::Rejected) {
        return;
    }

    ui->player1->setText(dlg.player1Name());
    ui->player2->setText(dlg.player2Name());
    ui->gameBoard->initNewGame();
    ui->gameBoard->setEnabled(true);

    updateNameLabels();
}

void MainWindow::updateNameLabels() {
    QFont f = ui->player1->font();

    f.setBold(ui->gameBoard->currentPlayer() == Widget::Player1);
    ui->player1->setFont(f);
    f.setBold(ui->gameBoard->currentPlayer() == Widget::Player2);
    ui->player2->setFont(f);
}

void MainWindow::handleGameOver(Widget::Player winner) {
    ui->gameBoard->setEnabled(false);
    QString message;

    if (winner == Widget::Draw) {
        message = "Game ended with a draw.";
    } else {
        message = QString("%1 wins").arg(winner == Widget::Player1 ? ui->player1->text() : ui->player2->text());
    }

    QMessageBox::information(this, "Info", message);
}
