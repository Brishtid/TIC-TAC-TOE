#include<bits/stdc++.h>
using namespace std;


int win=1;
int lose=-1;
int ties=0;


vector<vector<char>> arr= {
{' ', ' ', ' '},
{' ', ' ', ' '},
{' ', ' ', ' '}
};


void print() {
    cout<< "  0 1 2\n";
    for (int i=0;i<3;i++) {
        cout<<i<<" ";
        for (int j=0;j<3;j++) {
            if(arr[i][j]==' ')
            cout<< "."<<" ";
            else
             cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}


string Winner() {
    for (int i=0;i<3;i++) {
        if (arr[i][0]==arr[i][1] && arr[i][1]==arr[i][2] && arr[i][0]!=' ')
            return string(1,arr[i][0]);
        if (arr[0][i]==arr[1][i] && arr[1][i]==arr[2][i] && arr[0][i]!=' ')
            return string(1, arr[0][i]);
    }
    if (arr[0][0]==arr[1][1] && arr[1][1]==arr[2][2] && arr[0][0]!=' ')
        return string(1, arr[0][0]);
    if (arr[0][2]==arr[1][1] && arr[1][1]==arr[2][0] && arr[0][2]!=' ')
        return string(1, arr[0][2]);


    for (auto row:arr) {
        for (char box:row) {
            if (box==' ')
                return "";
        }
    }


    return "tie";
}


int minimax(int depth,bool maxi,char comp,char me) {
    string result=Winner();
    if (result==string(1,comp)) return win;
    else if (result==string(1,me)) return lose;
    else if (result=="tie") return ties;


    if(maxi){
        int bestScore=INT_MIN;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (arr[i][j]==' ') {
                    arr[i][j]=comp;
                    int score=minimax(depth + 1,false,comp,me);
                    arr[i][j]=' ';
                    bestScore=max(score,bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore=INT_MAX;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (arr[i][j]==' ') {
                    arr[i][j]=me;
                    int score=minimax(depth + 1,true,comp,me);
                    arr[i][j]=' ';
                    bestScore=min(score,bestScore);
                }
            }
        }
        return bestScore;
    }
}


void opp(char comp,char me) {
    int bestScore=INT_MIN;
    int row;
    int col;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (arr[i][j]==' ') {
                arr[i][j]=comp;
                int score=minimax(0,false,comp,me);
                arr[i][j]=' ';
                if (score>bestScore) {
                    bestScore=score;
                    row=i;
                    col=j;
                }
            }
        }
    }
    arr[row][col]=comp;
}


void my(char me) {
    int row, col;
    cout << "Enter your move (row and column): ";
    cin>>row>>col;
    while(row<0 || row>2 || col<0 || col>2 || arr[row][col]!=' ') {
        cout<<"Invalid.Try again:";
        cin>>row>>col;
    }
    arr[row][col]=me;
}


int main() {
    char comp,me;
    cout<<"Enter the symbol of your choice (X or O): ";
    cin>>me;
    while(me!='X' && me!='O'){
        cout<<"Invalid.Enter valid choice (X or O): ";
        cin>>me;
    }
    comp=(me=='X')?'O':'X';
    string res="";
    print();


    while (res=="") {
       
        my(me);
        print();
        res=Winner();
        if (res!="") break;


        opp(comp,me);
        print();
        res=Winner();
        if(res!="") break;
    }
    if (res=="tie") {
        cout<<"It's a tie!"<<endl;
    } else {
        cout<<"Winner:"<<res<<endl;
    }


    return 0;
}



