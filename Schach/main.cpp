#include "mainwindow.h"
#include <QApplication>
#include "game.h"
#include <iostream>

void asciiBoard(){
    game* test = new game();
    test->show();
}

void moveTest(){
    game* test = new game();
    test->click({0,1});
    test->click({0,3});
    test->click({0,0});
    test->click({0,2});
    test->click({0,2});
    test->click({7,2});
    test->click({7,2});
    test->click({7,5});
    test->click({7,5});
    test->click({0,5});
    test->click({6,0});
    test->click({7,2});


    std::cout<<std::endl;
    test->show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    asciiBoard();
    moveTest();

    return a.exec();
}
