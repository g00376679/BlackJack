#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
struct playerList{
	char cardFace;
	playerList *next;
};
struct gamesList{
	int players[4][1];
	gamesList *next;
};
gamesList *headgl=NULL;
gamesList *tempNodegl;
gamesList *tempNodegl1;
playerList *player[4]={NULL,NULL,NULL,NULL};
playerList *tempNode;
playerList *tempNode1;
char choice,deck=NULL,players='0';
char *deckCard;
int index=0;
int deckofCards=0;
int gameResult[4][1];
char card[52]={'2','2','2','2','3','3','3','3','4','4','4','4','5','5','5','5','6','6','6','6','7','7','7','7','8','8','8','8','9','9','9','9','1','1','1','1','J','J','J','J','K','K','K','K','Q','Q','Q','Q','A','A','A','A'};
void newGame();
void saveGame();
void main_menu();
void terminate();
void gameIntro();
void allCards(int);
void shuflCards(int);
int cardValue(char);
void tableView(int,bool);
void tableViewAll(int,bool);
void decks();
void allCardsView(int);
int calSum(int);
void hit(int);
void gameManue();
void addNode(int);
void addNode(int,char);
void showNode(int);
void result(int);
void removeNodes();
void addNodegl();
void resumeGame();
void saveExit();

	//Functions fo Designing
	void loadingBar();
	void bgColor(int);
	void pwellcome();
	void printString(char str[]);
	void br(int);
	void pre(int);
	void pressKey();
	void midLine();
	void midTab();
int main(){
	system("title GMIT-Porject Blackjeck21");
	system("mode con: cols=88 lines=30");
	loadingBar();
	pwellcome();
	Sleep(300);
	midLine();
	pre(3);
	pressKey();
	main_menu();
	getch();
	return 0;
}
void main_menu(){
	system("CLS");//cls();
	do{
		br(5); pre(3); printf(">> 1. Start A New Game."); Sleep(400);
		br(2); pre(3); printf(">> 2. Start A Saved Game."); Sleep(400);
		br(2); pre(3); printf(">> 3. Exit.");  Sleep(400);
		br(2); pre(3);
		scanf("%s" , &choice);
		system("CLS");//cls();
		switch(choice){
			case '1':{
				gameIntro();
				newGame();
				break;
			}
			case '2':{
				saveGame();
				break;
			}
			case '3':{
				terminate();
				break;
			}
			default:{
				midLine();
				midTab();
				printf("Invalid input.\n"); Sleep(400);
				break;
			}
		}
	}while(!(choice == '1' || choice == '2'));
	br(1);
}
void newGame(){
	midLine();
	pre(1);
	printString("Remainder!!!...");
	br(1);
	pre(2);
	printString("Minimum of two players (The dealer and player 1).");
	br(1);
	pre(2);
	printString("Maximum of four players (The dealer and player 1, 2 and 3).");
	do{
		br(3);
		pre(1);
		printString("How many players are playing ?  ");
		scanf("%s" , &players);
		system("CLS");//cls();
		switch(players){
			case '1':
			case '2':
			case '3':{
				if(deckofCards==0){
					decks();
				}
				shuflCards(deckofCards);
				for(int i=0;i<(players-48)+1;i++){
					addNode(i);
					addNode(i);
				}
				break;
			}
			default:{
				midLine();
				midTab();
				printf("Invalid Input.\n");
				break;
			}
		}
	}while(!(players=='1'||players=='2'||players=='3'));
	resumeGame();
}
void resumeGame(){
	tableViewAll((players-48)+1,true);
	for(int i=1;i<((players-48)+1);i++){
		do{
			if(calSum(i)>21){
				break;
			}else{
				pre(1);
				tableView(i,true);
				gameManue();
				br(2);
				pre(4);
				scanf("%s", &choice);
				switch(choice){
					case '1':{
						hit(i);
						break;
					}
					case '2':{
						//Stand
						break;
					}
					case '3':{
						//Split
						break;
					}
					case '4':{
						//save & exit
						saveExit();
						terminate();
						break;
					}
					case '5':{
						terminate();
						break;
					}
					default:{
						midLine();
						midTab();
						printf("Invalid input.\n"); Sleep(400);
						break;
					}
				}
			}
		}while((choice=='1'||choice=='3'||choice=='3'));
	}
	while(calSum(0) <= 17){
		hit(0);
	}
	tableViewAll(((players-48)+1),false);
	result((players-48)+1);
	addNodegl();
	removeNodes();
	newGame();
}
void saveGame(){
	char ch;
	FILE *fp;
	fp=fopen ("playerList.txt", "r");
	if(fp!=NULL){
		int i=-1;
	    ch = fgetc(fp);
	    while (ch != EOF)
	    {
	    	if(ch=='.'){
	    		i++;
			}else if(ch!=',' && ch!='\n'){
				addNode(i,ch);	
			}
			ch = fgetc(fp);
	    }
	    fclose(fp);
	    i=i+48;
		players=i;
	}
	
	fp=fopen ("dataList.txt", "r");
	if(fp!=NULL){
		ch = fgetc(fp);
		deck=ch;
		ch = fgetc(fp);
		index=(48-ch);
		deckCard=new char[(deck-48)*52];
		int i=0;
	    while (ch != EOF)
	    {
	    	if(ch!=','&&ch!='\n'){
	    		deckCard[i]=ch;
	    		i++;
			}
			ch = fgetc(fp);
	    }	
	}
	fclose (fp);
	resumeGame();
}
void gameManue(){
	br(2);
	pre(3);
	printString(">>1. Hit");
	br(1);
	pre(3);
	printString(">>2. Stand");
	br(1);
	pre(3);
	printString(">>3. Split");
	br(1);
	pre(3);
	printString(">>4. Save & Exit");
	br(1);
	pre(3);
	printString(">>5. Exit");
}
void hit(int pNum){
	if(index>=(52*(deck-48))){
		shuflCards(deck-48);
		index=0;
	}
	addNode(pNum);
}
void decks(){
	system("CLS");//cls();
	midLine();
	pre(1);
	printString("Remainder!!!...");
	br(1);
	pre(2);
	printString("The number of decks is selected by player 1.");
	do{
		br(3);
		pre(1);
		printString("Player 1: Enter The Number of decks : ");
		scanf("%s" , &deck);
		system("CLS");//cls();
		switch(deck){
			case '1':{
				deckofCards=1;
				deckCard=new char[52];
				allCards(1);
				break;
			}
			case '2':{
				deckofCards=2;
				deckCard=new char[52*2];
				allCards(2);
				break;
			}
			case '3':{
				deckofCards=3;
				deckCard=new char[52*3];
				allCards(3);
				break;
			}
			case '4':{
				deckofCards=4;
				deckCard=new char[52*4];
				allCards(4);
				break;
			}
			default:{
				midLine();
				midTab();
				printf("Invalid Input.\n");
				break;
			}
		}
	}while(!(deck=='1'||deck=='2'||deck=='3'||deck=='4'));	
}
void tableView(int pNum,bool holeCard){
	br(1);
	pre(1);
	if(pNum==0){
		printf("Dealer:");
		pre(2);
		if(holeCard){
			printf(" X ");
			pre(1);
			printf(" X ");
		}else{
			printf(" %i ", calSum(pNum));
			pre(1);
		}
	}else if(pNum==1){
		printf("Player 1:");
		pre(1);
		printf(" %i ", calSum(pNum));
		pre(1);
	}
	else if(pNum==2){
		printf("Player 2:");
		pre(1);
		printf(" %i ", calSum(pNum));
		pre(1);
	}
	else{
		printf("Player 3:");
		pre(1);
		printf(" %i ", calSum(pNum));
		pre(1);
	}
	showNode(pNum);
	br(1);
}
void showNode(int pNum){
	if(!player[pNum]==NULL){
		tempNode=player[pNum];
		while(tempNode!=NULL){
			if(tempNode->cardFace=='1'){
				printf("10, ");
			}else{
				printf("%c, ", tempNode->cardFace);
			}
			tempNode=tempNode->next;
		}
	}
}
void saveExit(){
	FILE *fp;
	fp=fopen ("playerList.txt", "w");
	if(fp){
		for(int i=0;i<(players-48)+1;i++){
			if(!player[i]==NULL){
				tempNode=player[i];
				//fprintf (fp, "%i,", i);
				fprintf(fp,".");
				while(tempNode!=NULL){
					fprintf (fp, "%c,", tempNode->cardFace);
					tempNode=tempNode->next;
				}
				//fprintf (fp, "\n");
			}
		}
	}
	fclose (fp);
	fp=fopen ("dataList.txt", "w");
	if(fp){
		fprintf (fp, "%i,%i\n",deckofCards,index);
		for(int i=0;i<(52*deckofCards);i++){
			fprintf(fp,"%c",deckCard[i]);
		}	
	}
	fclose (fp);
}
void addNode(int pNum){
	if(player[pNum]==NULL){
		player[pNum]=new playerList;
		player[pNum]->cardFace=deckCard[index];
		player[pNum]->next=NULL;
	}else{
		tempNode=player[pNum];
		while(tempNode->next!=NULL){
			tempNode=tempNode->next;
		}
		tempNode1=new playerList;
		tempNode1->cardFace=deckCard[index];
		tempNode1->next=NULL;
		tempNode->next=tempNode1;
	}
	index++;
}
void addNode(int pNum,char ch){
	//printf("|%i - %c|",pNum,ch);
	if(player[pNum]==NULL){
		player[pNum]=new playerList;
		player[pNum]->cardFace=ch;
		player[pNum]->next=NULL;
	}else{
		tempNode=player[pNum];
		while(tempNode->next!=NULL){
			tempNode=tempNode->next;
		}
		tempNode1=new playerList;
		tempNode1->cardFace=ch;
		tempNode1->next=NULL;
		tempNode->next=tempNode1;	
	}
}
void addNodegl(){
	if(headgl==NULL){
		headgl=new gamesList;
		for(int i=0;i<4;i++){
			headgl->players[i][0]=gameResult[i][0];
			gameResult[i][0]=NULL;
		}
		headgl->next=NULL;
	}else{
		tempNodegl=headgl;
		while(tempNodegl->next!=NULL){
			tempNodegl=tempNodegl->next;
		}
		tempNodegl1=new gamesList;
		for(int i=0;i<4;i++){
			tempNodegl1->players[i][0]=gameResult[i][0];
			gameResult[i][0]=NULL;
		}
		tempNodegl1->next=NULL;
		tempNodegl1->next=tempNodegl;	
	}
}
void tableViewAll(int plyr,bool holeCard){
	system("CLS");//cls();
	br(2);
	pre(3);
	printf("Sum \t\t\ Cards");
	br(1);
	pre(1);
	printf("______________________________________________________________________");
	for(int pNum=0;pNum<plyr;pNum++){
		br(1);
		pre(1);
		if(pNum==0){
			printf("Dealer:");
			pre(2);
			if(holeCard){
				printf(" X ");
				pre(1);
				printf(" X ");
			}else{
				printf(" %i ", calSum(pNum));
				pre(1);
			}
		}else if(pNum==1){
			printf("Player 1:");
			pre(1);
			printf(" %i ", calSum(pNum));
			pre(1);
		}
		else if(pNum==2){
			printf("Player 2:");
			pre(1);
			printf(" %i ", calSum(pNum));
			pre(1);
		}
		else{
			printf("Player 3:");
			pre(1);
			printf(" %i ", calSum(pNum));
			pre(1);
		}
		if(calSum(pNum)>21){
			printf("BUSTED, ");
		}else if(calSum(pNum)==21){
			printf("Blackjack, ");
		}
		showNode(pNum);
	}
	br(1);
}
int calSum(int pNum){
	int sum=0;
	int flg=0;
	if(!player[pNum]==NULL){
		tempNode=player[pNum];
		while(tempNode!=NULL){
			if(tempNode->cardFace=='A'){
				flg++;
			}else{
				sum+=cardValue(tempNode->cardFace);
			}
			tempNode=tempNode->next;
		}
	}
	if(sum>=10){
		sum+=flg;
	}else{
		sum+=(11*flg);
	}
	return sum;
}
void result(int totalPlyr){
	int p[4];
	for(int i=0;i<totalPlyr;i++){
		p[i]=calSum(i);
	}
	for(int i=0;i<totalPlyr;i++){
		br(1);
		pre(1);
		if(i==0){
			printf("Dealer:");
			pre(2);
			if(p[0]>21){
				printf(" Bust.");
				gameResult[0][0]=4;
			}else if(p[0]==21){
				printf(" Blackjack.");
				gameResult[0][0]=1;
			}else{
				gameResult[0][0]=0;
			}
		}else if(i==1){
			printf("Player 1:");
			pre(1);
			if(p[0]<p[1] && p[1]<22){
				printf("Won.");
				gameResult[1][0]=2;
			}else if(p[0]==p[1]){
				printf("Draw.");
				gameResult[1][0]=3;
			}else if(p[0]>p[1] && p[0]<22){
				printf("Lose.");
				gameResult[1][0]=5;
			}else if(p[0]>p[1] && p[0]>21){
				if(p[1]>21){
					printf("Draw.");
					gameResult[1][0]=3;
				}else{
					printf("Won.");
					gameResult[1][0]=2;
				}
			}else if(p[0]<p[1] && p[1]>21){
				if(p[0]>21){
					printf("Draw.");
					gameResult[1][0]=3;
				}
				else{
					printf("Lose.");
					gameResult[1][0]=5;
				}
			}
		}
		else if(i==2){
			printf("Player 2:");
			pre(1);
			if(p[0]<p[2] && p[2]<22){
				printf("Won.");
				gameResult[2][0]=2;
			}else if(p[0]==p[2]){
				printf("Draw.");
				gameResult[2][0]=3;
			}else if(p[0]>p[2] && p[0]<22){
				printf("Lose.");
				gameResult[2][0]=5;
			}else if(p[0]>p[2] && p[0]>21){
				if(p[2]>21){
					printf("Draw.");
					gameResult[2][0]=3;
				}else{
					printf("Won.");
					gameResult[2][0]=2;
				}
			}else if(p[0]<p[2] && p[2]>21){
				if(p[0]>21){
					printf("Draw.");
					gameResult[2][0]=3;
				}
				else{
					printf("Lose.");
					gameResult[2][0]=5;
				}
			}
		}
		else if(i==3){
			printf("Player 3:");
			pre(1);
			if(p[0]<p[3] && p[3]<22){
				printf("Won.");
				gameResult[3][0]=2;
			}else if(p[0]==p[3]){
				printf("Draw.");
				gameResult[3][0]=3;
			}else if(p[0]>p[3] && p[0]<22){
				printf("Lose.");
				gameResult[3][0]=5;
			}else if(p[0]>p[3] && p[0]>21){
				if(p[3]>21){
					printf("Draw.");
					gameResult[3][0]=3;
				}else{
					printf("Won.");
					gameResult[3][0]=2;
				}
			}else if(p[0]<p[3] && p[3]>21){
				if(p[0]>21){
					printf("Draw.");
					gameResult[3][0]=3;
				}
				else{
					printf("Lose.");
					gameResult[3][0]=5;
				}
			}
		}
		pre(2);
		printf(" %i ", p[i]);
	}
}
void removeNodes(){
	for(int i=0;i<4;i++){
		if(!player[i]==NULL){
			tempNode=player[i];
			while(tempNode!=NULL){
				tempNode1=tempNode;
				tempNode=tempNode->next;
				//delete tempNode1;
				tempNode1->cardFace=NULL;
				tempNode1->next=NULL;
			}
			player[i]==NULL;
		}
	}
}
int cardValue(char c){
	switch(c){
		case '2':{
			return 2;
			break;
		}
		case '3':{
			return 3;
			break;
		}
		case '4':{
			return 4;
			break;
		}
		case '5':{
			return 5;
			break;
		}
		case '6':{
			return 6;
			break;
		}
		case '7':{
			return 7;
			break;
		}
		case '8':{
			return 8;
			break;
		}
		case '9':{
			return 9;
			break;
		}
		case 'A':{
			return 11;
			break;
		}
		case '1':
		case 'J':
		case 'K':
		case 'Q':
		{
			return 10;
			break;
		}
		default:{
			return 0;
			break;
		}
	}
}
void shuflCards(int dec){
	int a;
	char temp;
	for(int i=0;i<(52*dec);i++){
		a=rand() % ((51*dec) + 0 );
		temp=deckCard[i];
		deckCard[i]=deckCard[a];
		deckCard[a]=temp;
	}
}
void allCards(int dec){
	int i;
	for(i=0;i<(52*dec);i++){
		deckCard[i]=card[(i/dec)];
	}
}
void allCardsView(int dec){
	system("CLS");//cls();
	midLine();
	pre(2);
	int i;
	for(i=0;i<(52*dec);i++){
		if(i%4==0){
			br(1);
			pre(2);
		}
		if(deckCard[i]=='1'){
			printf(" | 10 - %i \t ",cardValue(deckCard[i]));
		}else{
			printf(" | %c - %i \t ",deckCard[i],cardValue(deckCard[i]));
		}
	}
}
void terminate(){
	system("CLS");//cls();
	midLine(); pre(3); printf("Thank You For Playing.");
	br(3);pre(3); printf("Name: Muhammad Aamir Nazir.");
	br(2);pre(3); printf("Roll No: MCSE-F18-044");
	midLine();
	Sleep(1000);
	exit(1);
}
void loadingBar(void){
	system("CLS");//cls();
	for (int i=15;i<=100;i+=5){
		system("CLS");//cls();
		printf("\n\n\n\n\n\n\n\t\t\t\t");
		printf("%d %% Loading...\n\n\t\t",i);
		printf("");
		for (int j=0; j<i;j+=2){
			bgColor(160+j);
			printf(" ");
			bgColor(26);
		}
		Sleep(100);
		if(i==90 || i==50 || i==96 || i==83){
			Sleep(100);
		}
	}
}
void bgColor(int clr){
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsole, clr);
//the above code displays colorful background. if you want colorful then you can remove the above comment but not the code, only comment//
}
void pwellcome(){
	system("CLS");//cls();
	bgColor(26);
	char welcome[10]="WELCOME";
	char welcome2[3]="TO";
	char welcome3[15]="Blackjack 21";
	char welcome4[15]="GMIT-Porject";
	br(5);
	pre(3);
	for(int wlc=0; wlc<strlen(welcome);wlc++){
		printf(" %c",welcome[wlc]);
		Sleep(100);
	}
	bgColor(26);
	br(2);
	pre(4);
	for(int wlc2=0; wlc2<strlen(welcome2) ;wlc2++){
		printf(" %c",welcome2[wlc2]);
		Sleep(100);
	}
	bgColor(26);
	br(2);
	pre(3);
	for(int wlc3=0; wlc3<strlen(welcome3) ;wlc3++){
		printf(" %c",welcome3[wlc3]);
		Sleep(100);
	}
	bgColor(26);
	br(3);
	pre(4);
	for(int wlc3=0; wlc3<strlen(welcome4) ;wlc3++){
		printf(" %c",welcome4[wlc3]);
		Sleep(100);
	}
	bgColor(26);

}
void br(int line){
	for(int i=0; i<line;i++){
		printf("\n");
	}
}
void pre(int tab){

	for(int i=0; i<tab;i++){
		printf("\t");
	}

}
void midLine(void){
	printf("\n\n\n\n\n\n\n");
}
void midTab(void){
	printf("\t\t\t\t\t");
}
void pressKey(){
	br(2);
	pre(1);
	printf("Press Any Key To Continue ...");
	getch();
	system("CLS");//cls();
}
void printString(char str[]){
	bool flag=false;
	for(int i=0; i<strlen(str) ;i++){
		if((i%50==0 && i>49) || flag){
			flag=true;
			if(str[i]==' '){
				flag=false;
				br(1);
				pre(2);
			}else{
				printf("%c",str[i]);	
			}
		}else{
			printf("%c",str[i]);
		}
		Sleep(10);
	}
}
void gameIntro(){
	system("CLS");//cls();
	midLine();
	pre(1);
	printString("Game Overview");
	br(1);
	pre(2);
	printString("In this game, players compete against the dealer rather than each other.The objective is to get a hand total of closer to 21 than the dealer without going over 21.");
	br(3);
	pre(1);
	printString("Card Values");
	br(1);
	pre(2);
	printString("Blackjack is played with a standard international deck of cards with the Jokers removed, leaving 52 cards. \n\n\t\tWhen playing Blackjack the numeral cards 2 to 10 have their face values, Jacks, Queens and Kings are valued at 10, and Aces can have a value of either 1 or 11. The Ace is always valued at 11 unless that would result in the hand going over 21, in which case it is valued as 1.");
	pressKey();
	midLine();
	pre(2);
	printString("The value of a hand is the sum of the point values of the individual cards. Except, a \"blackjack\" is the highest hand, consisting of an ace and any 10-point card, and it outranks all other 21-point hands.");
	br(2);
	pre(2);
	printString("To beat the dealer the player must first not bust (go over 21) and second either outscore the dealer or have the dealer bust. Here are the full rules of the game.");
	br(2);
	pre(2);
	printString("A starting hand of a 10 valued card and an Ace is called a Blackjack or natural and beats all hands other than another Blackjack.");
	br(2);
	pre(2);
	printString("If both the player and dealer have Blackjack, the result is a draw between them players.");
	pressKey();
}
