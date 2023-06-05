#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>
//코드의 처음에 필요한 헤더 파일이 포함되어 있다.

#define WIN_WIDTH 70 

#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 5
//상수를 정의하여 창의 너비 및 기둥 및 디스크의 위치를 설정한다.

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
 
int towers[3][DISKS];
int towerTop[3] = {DISKS-1,-1,-1};

int tries = 0; 
int score = 0; 

void gotoxy(int x, int y){
//gotoxy 함수를 정의하여 콘솔에서 커서의 위치를 설정한다.
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
//setcursor 함수를 정의하여 커서의 가시성과 크기를 제어한다.
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void instructions(){
//게임 방법을 설명하는 창을 뛰운다.	
	
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
//drawTile 함수는 한 개의 디스크를 기둥에 그린다.

	int x;
	if( tower == 1 ) x = T1POS;
	else if( tower == 2 ) x = T2POS;
	else if( tower == 3 ) x = T3POS;
	
	x -= tileNo;
	
	for(int j=0; j<((tileNo)*2)-1; j++){
		gotoxy(x,y);
		cout<<"ㅁ";
		x++;
	}
}
void drawTower(int tower){
//drawTower 함수는 모든 디스크가 있는 기둥 전체를 그린다.

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
//isEmpty 함수는 기둥이 비어 있는지 확인한다.

	for(int i=0; i<DISKS; i++)
		if( towers[towerNo][i] != 0 )
			return 0;
	return 1;
}
int validate(int from, int to){
//validate 함수는 게임의 규칙에 따라 이동이 유효한지 확인한다.
	if( !isEmpty(to) ){
		  
		if( towers[from][towerTop[from]] < towers[to][towerTop[to]] )
			return 1;
		else 
			return 0;
	}
	return 1;
}
int move(int from, int to){
//move 함수는 유효한 경우 한 기둥에서 다른 기둥으로 이동한다.

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
//win 함수는 플레이어가 게임에 승리했는지 확인한다.

	for(int i=0; i<DISKS; i++)
		if( towers[2][i] != DISKS-i )
			return 0;
	return 1;
}

void play(){ 
//play 함수는 게임의 초기 상태를 설정하고 게임 루프를 구현한다.

	int from, to, count=0;
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
			gotoxy(10,5);cout<<"============================================================"<<endl;
			gotoxy(10,6);cout<<"                           게임 종료                        "<<endl;
		        gotoxy(10,7);cout<<"                           시도 횟수:                       "<<count<<endl;
			gotoxy(10,8);cout<<"============================================================"<<endl;
			cout<<endl<<endl<<endl;
			getch();
			break;
		}
		
		gotoxy(10,15);
		cout<<"옮길 디스크 (디스크: 1,2,3): ";
		cin>>from;
		gotoxy(10,16);
		cout<<"옮길 위치 (위치: 1,2,3): ";
		count= count+1;
		cin>>to;
		
		if( to < 1 || to > 3 ) continue;
		if( from < 1 || from > 3 ) continue;
		if( from == to )  continue;
		
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
//main 함수는 메인 메뉴를 표시하고 사용자 입력을 처리하여 게임을 시작하거나 게임 방법을 표시하거나 프로그램을 종료한다.
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
