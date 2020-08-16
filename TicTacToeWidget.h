#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QPushButton;
class Widget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Player)
    Q_PROPERTY(Player currentPlayer READ currentPlayer
                   WRITE setCurrentPlayer
                       NOTIFY currentPlayerChanged)

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initNewGame();
    enum Player{
        Invalid, Player1, Player2, Draw
    };
    Player currentPlayer() const;
    void setCurrentPlayer(Player p);
    Player checkWinConditions() const;

private:
    QList<QPushButton*> board;
    void setupBoard();
    Player m_currentPlayer;

signals:
    void currentPlayerChanged(Player);
    void gameOver(Widget::Player);

public slots:
    void handleButtonClick(int);
};
#endif // WIDGET_H
