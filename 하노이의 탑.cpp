#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define WIN_WIDTH 70 

#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 5

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
 
int towers[3][DISKS];
int towerTop[3] = {DISKS-1,-1,-1};

int tries = 0; 
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Tries: "<<tries<<endl;
}
void instructions(){
	
	system("cls");
	cout<<"게임 방법";
	cout<<"\n----------------";
	cout<<"\n 디스크를 타워 1에서 타워 3으로 이동. ";
	cout<<"\n 작은 디스크에는 큰 디스크를 배치할 수 없습니다";
	cout<<"\n 타워 번호는 1, 2, 3입니다";
	cout<<"\n\n아무 키나 누르면 메뉴로 돌아갑니다";
	getch();
}
void drawTile(int tower, int tileNo, int y){
	int x;
	if( tower == 1 ) x = T1POS;
	else if( tower == 2 ) x = T2POS;
	else if( tower == 3 ) x = T3POS;
	
	x -= tileNo;
	
	for(int j=0; j<((tileNo)*2)-1; j++){
		gotoxy(x,y);
		cout<<"±";
		x++;
	}
}
void drawTower(int tower){
	int x;
	int y = 9;
	
	gotoxy(10, 10); cout<<"==========";
	gotoxy(25, 10); cout<<"==========";
	gotoxy(40, 10); cout<<"==========";
	
	gotoxy(15, 11); cout<<"1";
	gotoxy(30, 11); cout<<"2";
	gotoxy(45, 11); cout<<"3";
	
	for(int i=0; i<5; i++){
		drawTile(tower, towers[tower-1][i], y);
		y--;
	}
}
int isEmpty(int towerNo){
	for(int i=0; i<DISKS; i++)
		if( towers[towerNo][i] != 0 )
			return 0;
	return 1;
}
int validate(int from, int to){
	if( !isEmpty(to) ){
		  
		if( towers[from][towerTop[from]] < towers[to][towerTop[to]] )
			return 1;
		else 
			return 0;
	}
	return 1;
}
int move(int from, int to){
	if( isEmpty(from) ) return 0; 
	if( validate(from, to) ){ 
		if( towers[from][towerTop[from]] != 0 ){
			towerTop[to]++;
			towers[to][towerTop[to]] = towers[from][towerTop[from]];
			towers[from][towerTop[from]] = 0;
			towerTop[from]--;
			return 1;
		}
	}
	return 0;
}
int win(){ 
	for(int i=0; i<DISKS; i++)
		if( towers[2][i] != DISKS-i )
			return 0;
	return 1;
}

void play(){
	int from, to;
	for(int i=0; i<DISKS; i++)
		towers[0][i] = DISKS-i;
	for(int i=0; i<DISKS; i++)
		towers[1][i] = 0;
	for(int i=0; i<DISKS; i++)
		towers[2][i] = 0;
	 
	do{
		system("cls"); 		  
		
		cout<<"============================================================"<<endl;
		cout<<"                         하노이의 탑                        "<<endl;
		cout<<"============================================================"<<endl<<endl;
		
		drawTower(1);
		drawTower(2);
		drawTower(3);
		
		if( win() ){
			system("cls");
			cout<<"============================================================"<<endl;
			cout<<"                           게임 종료                        "<<endl;
			cout<<"============================================================"<<endl;
			cout<<endl<<endl<<endl;
			cout<<"아무 키나 누르면 메뉴로 돌아갑니다.";
			getch();
			break;
		}
		
		gotoxy(10,15);
		cout<<"옮길 디스크 (디스크: 1,2,3): ";
		cin>>from;
		gotoxy(10,16);
		cout<<"옮길 위치 (위치: 1,2,3): ";
		cin>>to;
		
		if( to < 1 || to > 3 ) continue;
		if( from < 1 || from > 3 ) continue;
		if( from == to ) continue;
		
		from--;
		to--;
		
		move(from, to);
		 
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){ 
			}
			if( ch=='d' || ch=='D' ){ 
			} 
			if(ch==27){
				break;
			}
		} 
		  
	}while(1);
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |       하노이의 탑      | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. 게임 시작";
		gotoxy(10,10); cout<<"2. 게임 방법";	 
		gotoxy(10,11); cout<<"3. 나가기";
		gotoxy(10,13); cout<<"옵션 선택: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
