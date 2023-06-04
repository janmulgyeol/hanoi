#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>
//�ڵ��� ó���� �ʿ��� ��� ������ ���ԵǾ� �ִ�.

#define WIN_WIDTH 70 

#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 5
//����� �����Ͽ� â�� �ʺ� �� ��� �� ��ũ�� ��ġ�� �����Ѵ�.

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
 
int towers[3][DISKS];
int towerTop[3] = {DISKS-1,-1,-1};

int tries = 0; 
int score = 0; 

void gotoxy(int x, int y){
//gotoxy �Լ��� �����Ͽ� �ֿܼ��� Ŀ���� ��ġ�� �����Ѵ�.
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
//setcursor �Լ��� �����Ͽ� Ŀ���� ���ü��� ũ�⸦ �����Ѵ�.
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void updateScore(){
//updateScore �Լ��� ���� ������ ������Ʈ�ϰ� ǥ���Ѵ�.
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Tries: "<<tries<<endl;
}
void instructions(){
//���� ����� �����ϴ� â�� �ٿ��.	
	
	system("cls");
	cout<<"���� ���";
	cout<<"\n----------------";
	cout<<"\n ��ũ�� Ÿ�� 1���� Ÿ�� 3���� �̵�. ";
	cout<<"\n ���� ��ũ���� ū ��ũ�� ��ġ�� �� �����ϴ�";
	cout<<"\n Ÿ�� ��ȣ�� 1, 2, 3�Դϴ�";
	cout<<"\n\n�ƹ� Ű�� ������ �޴��� ���ư��ϴ�";
	getch();
}
void drawTile(int tower, int tileNo, int y){
//drawTile �Լ��� �� ���� ��ũ�� ��տ� �׸���.

	int x;
	if( tower == 1 ) x = T1POS;
	else if( tower == 2 ) x = T2POS;
	else if( tower == 3 ) x = T3POS;
	
	x -= tileNo;
	
	for(int j=0; j<((tileNo)*2)-1; j++){
		gotoxy(x,y);
		cout<<"��";
		x++;
	}
}
void drawTower(int tower){
//drawTower �Լ��� ��� ��ũ�� �ִ� ��� ��ü�� �׸���.

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
//isEmpty �Լ��� ����� ��� �ִ��� Ȯ���Ѵ�.

	for(int i=0; i<DISKS; i++)
		if( towers[towerNo][i] != 0 )
			return 0;
	return 1;
}
int validate(int from, int to){
//validate �Լ��� ������ ��Ģ�� ���� �̵��� ��ȿ���� Ȯ���Ѵ�.
	if( !isEmpty(to) ){
		  
		if( towers[from][towerTop[from]] < towers[to][towerTop[to]] )
			return 1;
		else 
			return 0;
	}
	return 1;
}
int move(int from, int to){
//move �Լ��� ��ȿ�� ��� �� ��տ��� �ٸ� ������� �̵��Ѵ�.

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
//win �Լ��� �÷��̾ ���ӿ� �¸��ߴ��� Ȯ���Ѵ�.

	for(int i=0; i<DISKS; i++)
		if( towers[2][i] != DISKS-i )
			return 0;
	return 1;
}

void play(){ 
//play �Լ��� ������ �ʱ� ���¸� �����ϰ� ���� ������ �����Ѵ�.

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
		cout<<"                         �ϳ����� ž                        "<<endl;
		cout<<"============================================================"<<endl<<endl;
		
		drawTower(1);
		drawTower(2);
		drawTower(3);
		
		if( win() ){
			system("cls");
			cout<<"============================================================"<<endl;
			cout<<"                           ���� ����                        "<<endl;
			cout<<"============================================================"<<endl;
			cout<<endl<<endl<<endl;
			cout<<"�ƹ� Ű�� ������ �޴��� ���ư��ϴ�.";
			getch();
			break;
		}
		
		gotoxy(10,15);
		cout<<"�ű� ��ũ (��ũ: 1,2,3): ";
		cin>>from;
		gotoxy(10,16);
		cout<<"�ű� ��ġ (��ġ: 1,2,3): ";
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
//main �Լ��� ���� �޴��� ǥ���ϰ� ����� �Է��� ó���Ͽ� ������ �����ϰų� ���� ����� ǥ���ϰų� ���α׷��� �����Ѵ�.
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |       �ϳ����� ž      | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. ���� ����";
		gotoxy(10,10); cout<<"2. ���� ���";	 
		gotoxy(10,11); cout<<"3. ������";
		gotoxy(10,13); cout<<"�ɼ� ����: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		 
	}while(1);
	
	return 0;
}
