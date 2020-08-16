#include "TicTacToeWidget.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSignalMapper>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setupBoard();
}

Widget::~Widget()
{
}

void Widget::initNewGame()
{
    for (int i = 0; i < 9; ++i) {
        board.at(i)->setText(" ");
    }
}

Widget::Player Widget::currentPlayer() const
{
    return m_currentPlayer;
}

void Widget::setCurrentPlayer(Player p)
{
    if(m_currentPlayer = p) {
        return;
    }
    m_currentPlayer = p;
    emit currentPlayerChanged(p);
}

void Widget::setupBoard()
{
    QGridLayout *gridLayout = new QGridLayout;
    QSignalMapper *mapper = new QSignalMapper;
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            QPushButton *button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            button->setText(" ");
            gridLayout->addWidget(button, row, column);
            board.append(button);
            mapper->setMapping(button, board.count() - 1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleButtonClick(int)));
    setLayout(gridLayout);
}



Widget::Player Widget::checkWinConditions() const{
    std::vector<std::vector<int>> winIndexes {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // cols
        {0, 4, 8}, {2, 4, 6}             // diags
    };

    // Collecting the texts once
    std::vector<QString> texts;
    for (int i = 0; i < 9; ++i) {
        texts.push_back(board.at(i)->text());
    }

    // Checking win conditions
    for (auto const& indexes: winIndexes) {
        QString text;

        for (auto const& i: indexes) {
            text.append(texts[i]);
        }

        if (text == "XXX") {
            return Player1;
        } else if (text == "OOO") {
            return Player2;
        }
    }

    // Check draw
    bool emptyButtonsExists = false;
    for (auto const& text : texts) {
        if (text == " ") {
            emptyButtonsExists = true;
        }
    }

    if (!emptyButtonsExists) {
        return Draw;
    }

    return Invalid;
}

void Widget::handleButtonClick(int index)
{
    if(index < 0 || index >= board.size()) return;
    QPushButton *button = board.at(index);
    if(button->text() != " ") return;
    button->setText(currentPlayer() == Player1 ? "X" : "O");
    Player winner = checkWinConditions();
    if(winner == Invalid) {
        setCurrentPlayer(currentPlayer() == Player1 ? Player2 : Player1);
        return;
    } else {
        emit gameOver(winner);
    }


}
