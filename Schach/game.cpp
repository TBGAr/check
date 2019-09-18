#include "game.h"
#include <iostream>
#include <QDebug>

game::game(QWidget *parent) :
  QWidget(parent),_isSelected(false),_currPlayer(1)
{
    createGame();
}

void game::show(){
    _boardWFunc->showBoard();
}

void game::createGame(){
    std::vector<std::vector<std::vector<quint8>>> hardcode = {
                                                                    {{0,1,2},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,2}},
                                                                    {{0,1,3},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,3}},
                                                                    {{0,1,4},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,4}},
                                                                    {{0,1,5},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,5}},
                                                                    {{0,1,6},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,6}},
                                                                    {{0,1,4},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,4}},
                                                                    {{0,1,3},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,3}},
                                                                    {{0,1,2},{0,1,1},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,2,1},{0,2,2}},
                                                                    };
    _boardWFunc = new board(hardcode);
}

void game::click(std::vector<quint8> Pos){
    if(!_isSelected){
        _selPos=Pos;
        _isSelected=true;
    }else{
        if(_boardWFunc->changePos(_selPos,Pos)){
            if(_currPlayer==1){
                _currPlayer=2;
            }else{
                _currPlayer=1;
            }
        }
        _selPos.clear();
        _isSelected=false;
    }
}


//board

game::board::board(std::vector<std::vector<std::vector<quint8>>> start):
    _boardWPos(start)
{}

void game::board::showBoard(){
    int fill;
    for(int i=7;i>=0;i--){
        for(int j=0;j<8;j++){
            fill=_boardWPos[j][i][1];
            std::cout<<fill<<',';
            fill=_boardWPos[j][i][2];
            std::cout<<fill<<' ';
        }
        std::cout<<std::endl;
    }
}

std::vector<std::vector<quint8>> game::board::validMoves(std::vector<quint8> reqPos){
    std::vector<std::vector<quint8>> result;


    switch(_boardWPos[reqPos[0]][reqPos[1]][2]){
    case 0: break;
    //bauer
    case 1:
        if(_boardWPos[reqPos[0]][reqPos[1]][0]){
            //already moved rook
            result.push_back({reqPos[0],reqPos[1]+1});
        } else {
            //if rook was not moved so far
            result.push_back({reqPos[0],reqPos[1]+1});
            result.push_back({reqPos[0],reqPos[1]+2});
        }
        break;
    //turm
    case 2:
        //nach rechts
        for(quint8 i=reqPos[0]+1;i<8;i++){
            if(!_boardWPos[i][reqPos[1]][1]){
                //wenn sich keine figur auf einem der nächsten felder befindet
                result.push_back({i,reqPos[1]});
            }else{
                break;
            }
        }
        //nach unten
        for(quint8 i = reqPos[1]-1;i>=0&&i!=255;i--){
            if(!_boardWPos[reqPos[0]][i][1]){
                //wenn sich keine figur auf einem der nächsten felder befindet
                result.push_back({reqPos[0],i});
            }else{
                break;
            }
        }
        //nach links
        for(quint8 i = reqPos[0]-1;i>=0 && i!=255;i--){
            if(!_boardWPos[i][reqPos[1]][1]){
                //wenn sich keine figur auf einem der nächsten felder befindet
                result.push_back({i,reqPos[1]});
            }else{
                break;
            }
        }
        //nach oben
        for(quint8 i = reqPos[1]+1;i<8;i++){
            if(!_boardWPos[reqPos[0]][i][1]){
                //wenn sich keine figur auf einem der nächsten felder befindet
                result.push_back({reqPos[0],i});
            }else{
                break;
            }
        }
        break;
    case 3: //Springer
        //oben Rechts
        if(reqPos[0]+1<8 && reqPos[1]+2<8){
            if(!_boardWPos[reqPos[0]+1][reqPos[1]+2][1]){
                result.push_back({reqPos[0]+1,reqPos[1]+2});
            }
        }
        //oben links
        if(reqPos[0]-1<8 && reqPos[0]-1>=0 && reqPos[1]+2<8){
            if(!_boardWPos[reqPos[0]-1][reqPos[1]+2][1]){
                result.push_back({reqPos[0]-1,reqPos[1]+2});
            }
        }
        //links oben
        if(reqPos[0]-2<8 && reqPos[0]-2>=0 && reqPos[1]+1<8){
            if(!_boardWPos[reqPos[0]-2][reqPos[1]+1][1]){
                result.push_back({reqPos[0]-2,reqPos[1]+1});
            }
        }
        //links unten
        if(reqPos[0]-2<8 && reqPos[0]-2>=0 && reqPos[1]-1<8 && reqPos[1]-1>=0){
            if(!_boardWPos[reqPos[0]-2][reqPos[1]-1][1]){
                result.push_back({reqPos[0]-2,reqPos[1]-1});
            }
        }
        //unten links
        if(reqPos[0]-1<8 && reqPos[0]-1>=0 && reqPos[1]-2<8 && reqPos[1]-2>=0){
            if(!_boardWPos[reqPos[0]-1][reqPos[1]-2][1]){
                result.push_back({reqPos[0]-1,reqPos[1]-2});
            }
        }
        //unten rechts
        if(reqPos[0]+1<8 && reqPos[1]-2<8 && reqPos[1]-2 >=0){
            if(!_boardWPos[reqPos[0]+1][reqPos[1]-2][1]){
                result.push_back({reqPos[0]+1,reqPos[1]-2});
            }
        }
        //rechts unten
        if(reqPos[0]+2<8 && reqPos[1]-1<8 && reqPos[1]-1>=0){
            if(!_boardWPos[reqPos[0]+2][reqPos[1]-1][1]){
                result.push_back({reqPos[0]+2,reqPos[1]-1});
            }
        }
        //rechts oben
        if(reqPos[0]+2<8 && reqPos[1]+1<8){
            if(!_boardWPos[reqPos[0]+2][reqPos[1]+1][1]){
                result.push_back({reqPos[0]+2,reqPos[1]+1});
            }
        }

    }
    return result;
}

bool game::board::changePos(std::vector<quint8> start, std::vector<quint8> dest){
    std::vector<std::vector<quint8>> valMov= validMoves(start);
    for(quint8 i=0;i<valMov.size();i++){
        if(valMov[i]==dest){
            _boardWPos[dest[0]][dest[1]] = _boardWPos[start[0]][start[1]];
            _boardWPos[dest[0]][dest[1]][0]=1;
            _boardWPos[start[0]][start[1]]={0,0,0};
            return true;
        }
    }

    return false;
}
