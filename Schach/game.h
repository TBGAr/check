#ifndef GAME_H
#define GAME_H

#include <QWidget>

class game : public QWidget
{
    Q_OBJECT
public:
    explicit game(QWidget *parent = nullptr);

    void show();
    void createGame();
    void click(std::vector<quint8> Pos);
signals:

public slots:

private:
    class board
    {
    public:
        board(std::vector<std::vector<std::vector<quint8>>> start);

        std::vector<std::vector<quint8>> validMoves(std::vector<quint8> reqPos);
        bool changePos(std::vector<quint8> start, std::vector<quint8> dest);
        void showBoard();


    private:
        std::vector<std::vector<std::vector<quint8>>> _boardWPos;
    };

    board* _boardWFunc;
    bool _isSelected;
    std::vector<quint8> _selPos;
    quint8 _currPlayer;
};

#endif // GAME_H
