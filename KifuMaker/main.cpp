//
//  main.cpp
//  KifuMaker
//
//  Created by students on 2017/05/18.
//  Copyright © 2017年 noname. All rights reserved.
//


/////////////////////////////////////////////////////////////////////////////////////////////////////
//PCを買ったので新しくXcodeプロジェクトを作り直しました
/////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

//盤のサイズ
#define SIZE 9

//駒の列挙型-------------------------------------------------------------------------------------------
enum PIECE{
    FU=1,KY,KE,GI,KI,KA,HI,OU,TO,NY,NK,NG,UM,RY
};

//指し手のクラス-----------------------------------------------------------------------------------------
class Phase {
public:
    int before;
    int after;
    int time;
    PIECE piece;
};

//情報のタイプを示す列挙型--------------------------------------------------------------------------------
enum PROP{
    PLACE=0,SENTE,GOTE
};


//数字を駒の文字列にする関数------------------------------------------------------------------------------
//n:駒名　手番込みでも可
//hasPhase:手番込みであるか　trueの場合＋ーが文字列の先頭につきます
string getPiece(int n,bool hasPhase=false){
    string Pieces[] = {"","FU","KY","KE","GI","KI","KA","HI","OU","TO","NY","NK","NG","UM","RY"};
    string s("");
    if(hasPhase)
        s += (n<0)?("-"):((n>0)?("+"):(" * ")) ;
    s += Pieces[abs(n)];
    return s;
}

//整数の２次元配列から盤面を表示する関数--------------------------------------------------------------------
void showBoard(int (*board)[SIZE]){
    for(int i=0;i<SIZE;i++){
        cout << "P" << i+1;
        for(int j=0;j<SIZE;j++){
            cout << getPiece(board[i][j],true);
        }
        cout << endl;
    }
}

//棋譜の情報などを入力する関数----------------------------------------------------------------------------
void printProp(PROP type,string s){
    switch(type){
        case PLACE:
            s="$SITE:"+s;
            break;
        case SENTE:
            s="N+"+s;
            break;
        case GOTE:
            s="N-"+s;
            break;
    }
    cout << s << endl;
}

//指し手を計算する関数-----------------------------------------------------------------------------------
//b:移動前の駒の位置
//a:移動後の駒の位置
//p:移動した駒の種類
void printPhase(int b,int a,int p,int t=-1){
    static int tb,tn=(int)time(NULL);
    static bool turn=true;//先手か後手か、true=先手
    int td;
    string s=(turn)?("+"):("-");
    turn ^= true;//先手と後手の切り替え
    //前回関数を呼び出した時と今回呼び出した時の時刻の差を計算
    tb=tn;
    tn=(int)time(NULL);
    td=tn-tb;
    
    //書き込む
    //時間の書き込み
    cout << "T" << td << endl;
    //指し手の書き込み
    cout << s << b << a << getPiece(p) << endl;
    
}
//指し手を入力する関数-----------------------------------------------------------------------------------
void inputPhase(vector<Phase> &v){
    
}

//メイン関数-------------------------------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    //初期の盤面
    int board[SIZE][SIZE]={
        {-2,-3,-4,-5,-8,-5,-4,-3,-2},
        { 0,-7, 0, 0, 0, 0, 0,-6, 0},
        {-1,-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 0, 6, 0, 0, 0, 0, 0, 7, 0},
        { 2, 3, 4, 5, 8, 5, 4, 3, 2},
    };
    string fn,sente,gote,place;
    vector<Phase> tern;
    
    //初期設定
    
    cout << "ファイル名を入力してください" << endl;
    cin >> fn;
    fn = fn+".csa";
    cout << "先手の名前を入力してください" << endl;
    cin >> sente;
    cout << "後手の名前を入力してください" << endl;
    cin >> gote;
    
    inputPhase(tern);
    
    
    //file
    ofstream wf;
    wf.open(fn, ios::out);
    
    cout << "writing " << fn << "..." << endl;
    streambuf* last = cout.rdbuf();
    
    //出力先を標準出力にするにはこの関数をコメントアウトする
    cout.rdbuf(wf.rdbuf());
    
    
    //
    
    showBoard(board);
    
    //test
    printPhase(77, 76, FU);
    printPhase(33, 34, FU);
    printPhase(67, 66, FU);
    printPhase(83, 84, FU);
    
    
    
    wf.close();
    cout.rdbuf(last);
    cout << "wrote " << fn << "!" << endl;
    
    
    return 0;
}
