//1971194
//김택신

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include<winbase.h>

// 색상 정의
#define BLACK   0
#define BLUE1   1
#define GREEN1   2
#define CYAN1   3
#define RED1   4
#define MAGENTA1 5
#define YELLOW1   6
#define GRAY1   7
#define GRAY2   8
#define BLUE2   9
#define GREEN2   10
#define CYAN2   11
#define RED2   12
#define MAGENTA2 13
#define YELLOW2   14
#define WHITE   15

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define ESC   0x1b // ESC key 값

#define WIDTH 120
#define HEIGHT 40

#define N_SHAPE   4 // 무늬수 4
#define N_ONE_SET   52 // 13까지이므로
#define N_CARDS   208 // 무늬당 13장*4 덱이 4개 이므로 208장
#define N_DEAL   2 // 한명당 2장

//사용할 변수들을 전역변수로 선언   사용다했을 때 다시 초기화 시킬 예정
int total_money = 10000000;            // 자본금 입력
int round_count = 0;
int round_money = 0; //배팅 금액,  판돈
int shape1 = 0;
int shape2 = 0;
int x = 41;
int y = 41;
int player_card[21] = { 0 }; //플레이어가 추가한 카드숫자
int player_shape[21] = { 0 }; //플레이어가 추가한 카드모양
int playersum = 0; //플레이어의 카드 합
int dealer_card[21] = { 0 }; //딜러가 추가한 카드숫자
int dealer_shape[21] = { 0 }; //딜러가 추가한 카드모양
int dealersum = 0; //딜러의 카드 합
int hit = 0; //카드를 추가로 받을지 결정
int Ace = 0; //A를 1로 사용할지 11로 사용할지 결정
int Card[52] = { 1,2,3,4,5,6,7,8,9,10,10,10,10,
             1,2,3,4,5,6,7,8,9,10,10,10,10,
             1,2,3,4,5,6,7,8,9,10,10,10,10,
             1,2,3,4,5,6,7,8,9,10,10,10,10 }; //52장의 모든 카드
int menu_num = 1; //  메뉴선택번호    1, 게임시작  2, 게임 설명  3, 종료
void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
    COORD pos; // Windows.h 에 정의
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}
void red()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
}
void green()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}
void white()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void blue()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
}
void intensity()//회색
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
}
void removeCursor(void) { // 커서를 안보이게 한다
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // 커서를 보이게 한다
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void cls(int text_color, int bg_color) // 화면 지우기
{
    char cmd[100];
    system("cls");
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}
// box 그리기 함수, ch 문자로 (x1,y1) ~ (x2,y2) box를 그린다.
void draw_box(int x1, int y1, int x2, int y2, char ch)//첫화면 박스 함수
{
    int x, y;
    for (x = x1; x <= x2; x++) {
        gotoxy(x, y1);
        printf("%c", ch);
        gotoxy(x, y2);
        printf("%c", ch);
    }
    for (y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        printf("%c", ch);
        gotoxy(x2, y);
        printf("%c", ch);
    }
}
void draw_table(int x1, int y1, int x2, int y2, char* ch)//게임 테이블 만들기
{
    int x, y;
    cls(BLACK, GREEN1);
    for (x = x1; x <= x2; x++) {
        gotoxy(x, y1);
        printf("%s", ch);
        gotoxy(x, y2);
        printf("%s", ch);
    }
    for (y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        printf("%s", ch);
        gotoxy(x2, y);
        printf("%s", ch);
    }
}
void draw_deck() {
    white();
    gotoxy(8, 3);  printf("┌─────────────┐ ");
    gotoxy(8, 4);  printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 5);  printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 6);  printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 7);  printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 8);  printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 9);  printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 10); printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 11); printf("│  ▩▩▩▩▩ │ ");
    gotoxy(8, 12); printf("└─────────────┘ ");
    textcolor(WHITE, GREEN1);
}
void information() {
    gotoxy(8, 33);   printf("┌─────────────────────────┐ ");
    gotoxy(8, 34);   printf("│                         │ ");
    gotoxy(8, 35);   printf("│                         │ ");
    gotoxy(8, 36);   printf("│                         │ ");
    gotoxy(8, 37);   printf("│                         │ ");
    gotoxy(8, 38);   printf("└─────────────────────────┘ ");
    gotoxy(10, 35); printf("남은 돈 : %d 만원", total_money);
    gotoxy(10, 36); printf("판   수 : %d 판째", round_count);
    gotoxy(10, 37); printf("배팅 금 : %d   원", round_money);
}
void print_dealer_card(int* count1, char* card_type[]) {
    int a;
    char A = 'A';
    gotoxy(73, 18);
    for (int i = 1; i < *count1; i++) {
        a = dealer_shape[i];
        if (dealer_card[i] == 1 || dealer_card[i] == 11)
            printf(" %s%2c", card_type[a], A);
        else
            printf(" %s%2d", card_type[a], dealer_card[i]);
    }
    for (int i = 1; i < *count1; i++) {
        a = dealer_shape[i];
        if (dealer_card[i] == 1) {
            gotoxy(y, 2);  printf("│%s%2c        │ ", card_type[a], A);
            gotoxy(y, 9);  printf("│        %s%2c│ ", card_type[a], A);

        }
        else {
            gotoxy(y, 2);  printf("│%s%2d        │ ", card_type[a], dealer_card[i]);
            gotoxy(y, 9);  printf("│        %s%2d│ ", card_type[a], dealer_card[i]);
        }
        gotoxy(y, 1);  printf("┌────────────┐ ");

        gotoxy(y, 3);  printf("│            │ ");
        gotoxy(y, 4);  printf("│            │ ");
        gotoxy(y, 5);  printf("│            │ ");
        gotoxy(y, 6);  printf("│            │ ");
        gotoxy(y, 7);  printf("│            │ ");
        gotoxy(y, 8);  printf("│            │ ");

        gotoxy(y, 10);  printf("└────────────┘ ");
        y = y + 7;
    }

}

void print_dealer_init_card(int* count1, char* card_type[]) {
    int a;
    char A = 'A';
    white();
    a = dealer_shape[*count1];
    if (*count1 == 1) {                                 // 2번째 카드
        gotoxy(48, 1);  printf("┌─────────────┐ ");
        gotoxy(48, 2);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 3);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 4);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 5);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 6);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 7);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 8);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 9);  printf("│  ▩▩▩▩▩ │ ");
        gotoxy(48, 10); printf("└─────────────┘ ");
    }
    else {                                             //1번째 카드
        if (dealer_card[*count1] == 1) {                // A인지 확인
            gotoxy(41, 2);  printf("│%s%2c        │ ", card_type[a], A);
            gotoxy(41, 9);  printf("│        %s%2c│ ", card_type[a], A);
        }
        else {
            gotoxy(41, 2);  printf("│%s%2d        │ ", card_type[a], dealer_card[*count1]);
            gotoxy(41, 9);  printf("│        %s%2d│ ", card_type[a], dealer_card[*count1]);
        }
        gotoxy(41, 1);  printf("┌────────────┐ ");

        gotoxy(41, 3);  printf("│            │ ");
        gotoxy(41, 4);  printf("│            │ ");
        gotoxy(41, 5);  printf("│            │ ");
        gotoxy(41, 6);  printf("│            │ ");
        gotoxy(41, 7);  printf("│            │ ");
        gotoxy(41, 8);  printf("│            │ ");

        gotoxy(41, 10);  printf("└────────────┘ ");
    }
}
void print_player_card(int* count2, char* card_type[]) {// x좌표는 7씩
    int b;
    char A = 'A';
    white();
    for (int i = *count2; i <= *count2; i++) {
        _sleep(500);
        b = player_shape[i];
        if (player_card[i] == 1) {
            gotoxy(x, 31);  printf("│%s%2c        │ ", card_type[b], A);
            gotoxy(x, 38);  printf("│        %s%2c│ ", card_type[b], A);
        }
        else {
            gotoxy(x, 31);  printf("│%s%2d        │ ", card_type[b], player_card[i]);
            gotoxy(x, 38);  printf("│        %s%2d│ ", card_type[b], player_card[i]);
        }

        gotoxy(x, 30);  printf("┌────────────┐ ");

        gotoxy(x, 32);  printf("│            │ ");
        gotoxy(x, 33);  printf("│            │ ");
        gotoxy(x, 34);  printf("│            │ ");
        gotoxy(x, 35);  printf("│            │ ");
        gotoxy(x, 36);  printf("│            │ ");
        gotoxy(x, 37);  printf("│            │ ");

        gotoxy(x, 39);  printf("└────────────┘ ");
        x = x + 7;
    }
}

void menu() {
    int y = 21;
    unsigned char ch; // 특수키 0xe0 을 입력받으려면 unsigned char 로 선언해야 함
     //1, 게임시작  2, 게임 설명  3, 종료
    gotoxy(40, 19); printf("┌------------------------------------┐ ");
    gotoxy(40, 27); printf("└------------------------------------┘ ");
    textcolor(WHITE, BLACK);
    gotoxy(40, 21); printf("               1, 게임시작               ");
    gotoxy(40, 23); printf("               2, 게임설명               ");
    gotoxy(40, 25); printf("               3, 종    료               ");
    gotoxy(90, 35); printf("※ 방향키 위(↑), 아래(↓) ");
    gotoxy(90, 36); printf("       고르고  엔터 ");
    red(); gotoxy(50, 21); printf("☞");
    while (1) {
        //up키 값 72 down키 값 80 enter키 값 13
        if (kbhit() == 1) {  // 키보드가 눌려져 있으면

            ch = getch();
            if (ch == ESC)
                break;

            if (ch == UP) {
                gotoxy(50, y); printf("　");
                y = y - 2;
                if (y <= 21)
                    y = 21;
                gotoxy(50, y); printf("☞");
            }
            else if (ch == DOWN) {
                gotoxy(50, y); printf("　");
                y = y + 2;
                if (y >= 25)
                    y = 25;
                gotoxy(50, y); printf("☞");
            }
            else if (ch == 13) {
                if (y == 21)
                    menu_num = 1;
                else if (y == 23)
                    menu_num = 2;
                else if (y == 25)
                    menu_num = 3;
                break;
            }
        }
    }
}
void batting(int* total_money, int* round_money, int* round_count) {
    unsigned char ch; // 특수키 0xe0 을 입력받으려면 unsigned char 로 선언해야 함
    int up_count = 0, down_count = 0;
    int a, b = 0;
    a = rand() % 16;
    textcolor(a, a - 3);
    system("cls");
    for (b = 0; b <= 8; b++) {                            //전광판 예상
        a = rand() % 16;
        textcolor(a, a - 3);
        gotoxy(45, 19); printf("                                   ");
        gotoxy(45, 20); printf("♠♥♣◆ 게임을 시작합니다 ♠♥♣◆");
        gotoxy(45, 21); printf("                                   ");
        Sleep(400);
    }

    system("cls");
    draw_table(0, 0, WIDTH, HEIGHT, "▩");
    draw_deck();
    information();
    gotoxy(40, 19); printf("┌────────────────────────────────────────┐ ");
    gotoxy(40, 27); printf("└────────────────────────────────────────┘ ");
    gotoxy(45, 20); printf("↓↓↓ 총 자본을 입력하세요 ↓↓↓ ");
    gotoxy(45, 22); printf("        방향키 < ↑ / ↓ > ");
    //배팅금액 정하고, 남은금액, 판 수 를 표시해주는 부분
    while (1) {
        removeCursor();
        if (kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = getch();
            if (ch == ESC)
                break;
            if (ch == UP) {
                up_count++;
                *round_money = up_count * 10000;
                red();
                gotoxy(42, 23); printf("                                      ");
                gotoxy(42, 24); printf(" 현재 배팅금(단위: 1만원) : [  %d", *round_money); printf(" ]");
                gotoxy(42, 25); printf("                                      ");
                information();
            }
            else if (ch == DOWN) {
                up_count--;
                if (*round_money == 0) {                  // if 문은 배팅금액이 0원인데 -하면 안되니까 방지하기 위함
                    up_count++;
                }
                else {
                    *round_money = up_count * 10000;
                }
                red();
                gotoxy(42, 23); printf("                                      ");
                gotoxy(42, 24); printf(" 현재 배팅금(단위: 1만원) : [  %d", *round_money); printf(" ]");
                gotoxy(42, 25); printf("                                      ");
                information();
            }
            else if (ch == 13) {
                *round_count = *round_count + 1;
                *total_money = *total_money - *round_money;
                break;
            }
        }
    }
}
void gameplay() {

    unsigned char ch; // 특수키 0xe0 을 입력받으려면 unsigned char 로 선언해야 함
    srand((unsigned)time(NULL));
    draw_table(0, 0, WIDTH, HEIGHT, "▩");
    draw_deck();
    batting(&total_money, &round_money, &round_count);
    //system("cls");
    //draw_table(0, 0, WIDTH, HEIGHT, "▩");

    information();

    //게임시작
    int count1 = 0, count2 = 0;  //몇번째 카드인지 카운드함 // 나중에 카드 그릴 때 사용될 예정
    int cards[N_CARDS] = { 0 }; // 전체 카드를 1차원 Array에 저장, 1이면 이미 나눠준 카드
    int card, card_value;
    //int dealer_card_count = 1, player_card_count = 1;          왜 있는지 모름
    int dealer_behind = 0; //뒤집을 카드
    int type = 0, no;
    int dealer_blackjack = 0, dealer_A_count = 0;
    int player_blackjack = 0, player_A_count = 0;
    char* card_type[] = { "♤", "♥", "♧","◆" }; // 카드무늬 "ㅁ" 누르고 한자키.
    //      0~51♤   52~103♥   104~155♧   156~207◆
    // A ~ 10, J, Q, K x4 한 것
    char* card_no[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
                        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
                        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
                        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    playersum = 0;
    dealersum = 0;
    gotoxy(60, 18); printf(" 딜러 : ");                                             //딜러에게 카드 2장

    for (int i = 0; i < N_DEAL; i++) { // 카드 2장 분배  N_DEAL=2
       // 이미 나눠준 카드인지 체크하면서, 나눠준 카드면 표시한다.
       // card 번호 0 ~ N_CARDS 로 card_type과 card_no, joker인지 구분해서 출력한다.
       //      0~51♤   52~103♥   104~155♧   156~207◆
        do {
            card = rand() % N_CARDS;
        } while (cards[card] == 1);
        cards[card] = 1;

        no = card % N_ONE_SET;         //N_ONE_SET=52   no의 범위는 0~51
        card_value = (no % 13) + 1;
        if (card_value == 11 || card_value == 12 || card_value == 13) {
            card_value = 10;
            dealer_blackjack = dealer_blackjack + card_value;
        }
        if (card_value == 1) {                     //A값 정의
            dealer_blackjack = dealer_blackjack + 11;
            dealer_A_count++;
        }

        dealersum = dealersum + card_value;

        if (card >= 0 && card <= 51)
            type = 0;
        else if (card >= 52 && card <= 103)
            type = 1;
        else if (card >= 104 && card <= 155)
            type = 2;
        else if (card >= 156 && card <= 207)
            type = 3;
        dealer_card[count1] = card_value;
        dealer_shape[count1] = type;
        if (dealer_behind == 0) {     //dealer_behind 첫장만 오픈하려고 0을 입력해주고 1이면 뒤집음
            printf("%s%2s", card_type[type], card_no[no]);                                 ////// 딜러가 받은 카드 위치
            dealer_behind = 1;
        }
        else if (dealer_behind != 0) {
            gotoxy(72, 18); printf("  ??  ");
        }
        print_dealer_init_card(&count1, card_type);
        count1++;
    }
    printf("\n");

    gotoxy(60, 28); printf("   나: ");                                 //플레이어에게 카드 2장
    for (int i = 0; i < N_DEAL; i++) { // 카드 2장 분배
       // 이미 나눠준 카드인지 체크하면서, 나눠준 카드면 표시한다.
       // card 번호 0 ~ N_CARDS 로 card_type과 card_no 구분해서 출력한다.
       //      0~51♤   52~103♥   104~155♧   156~207◆
        do {
            card = rand() % N_CARDS;
        } while (cards[card] == 1);
        cards[card] = 1;

        no = card % N_ONE_SET;         //N_ONE_SET=52   no의 범위는 0~51
        card_value = (no % 13) + 1;
        if (card_value == 11 || card_value == 12 || card_value == 13) {
            card_value = 10;
            player_blackjack = player_blackjack + 10;
        }
        if (card_value == 1) {                     //A값 정의
            player_blackjack = player_blackjack + 11;
            player_A_count++;
        }

        if (card >= 0 && card <= 51)
            type = 0;
        else if (card >= 52 && card <= 103)
            type = 1;
        else if (card >= 104 && card <= 155)
            type = 2;
        else if (card >= 156 && card <= 207)
            type = 3;

        player_card[count2] = card_value;
        player_shape[count2] = type;
        playersum = playersum + card_value;
        if (count2 == 0) {
            printf("%s%2s ", card_type[type], card_no[no]);
        }
        else {
            gotoxy(72, 28); printf("%s%2s ", card_type[type], card_no[no]);
        }
        print_player_card(&count2, card_type);
        count2++;
    }
    gotoxy(39, 28); printf(" playersum = %d ", playersum);
    printf("\n");
    if (dealer_blackjack == 21) {                                          // 딜러가 처음 받은 2장이 블랙잭 인경우
        gotoxy(19, 20); printf("                  ");
        gotoxy(19, 21); printf("    BLACK JACK    ");
        gotoxy(19, 22); printf(" dealer ※ WIN ※ ");
        gotoxy(19, 23); printf("                  ");
        print_dealer_card(&count1, card_type);
        total_money = total_money - 0;
        information();
        getch();
        return;
    }
    else if (player_blackjack == 21 && dealer_blackjack == 21) {
        gotoxy(19, 21); printf("                ");
        gotoxy(19, 22); printf("     무승부     ");
        gotoxy(19, 23); printf("                ");
        print_dealer_card(&count1, card_type);
        total_money = total_money + round_money;;
        information();
        getch();
        return;
    }
    else if (player_blackjack == 21) {                                          // 플레이어가 처음 받은 2장이 블랙잭 인경우
        gotoxy(19, 20); printf("                  ");
        gotoxy(19, 21); printf("    BLACK JACK    ");
        gotoxy(19, 22); printf(" player ※ WIN ※ ");
        gotoxy(19, 23); printf("                  ");
        total_money = total_money + round_money + round_money;
        information();
        getch();
        return;
    }
    int last_key = 0;
    gotoxy(9, 30); printf("┌--------------------┐ ");
    gotoxy(9, 31); printf("│                    │ ");
    gotoxy(9, 32); printf("└--------------------┘ ");
    gotoxy(14, 31); printf("STAY");
    gotoxy(23, 31); printf("HIT");
    int a = 77;
    int b = 77;
    white(); gotoxy(19, 31); printf("☜");
    while (1) {
        removeCursor();
        if (kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = getch();
            if (ch == ESC)
                break;
            if (ch == RIGHT) {
                white(); gotoxy(19, 31); printf("☞");
                last_key = 1;
            }
            else if (ch == LEFT) {
                white(); gotoxy(19, 31); printf("☜");
                last_key = 0;
            }
            else if (ch == 13) {
                if (last_key == 0) {         //STAY선택
                   //STAY선택
                    x = 41;
                    y = 48;
                    if (player_A_count >= 1) {
                        int A_key = 0;
                        gotoxy(9, 26); printf("   player  A  1  or 11 ");
                        gotoxy(9, 27); printf("┌--------------------┐ ");
                        gotoxy(9, 28); printf("│                    │ ");
                        gotoxy(9, 29); printf("└--------------------┘ ");
                        gotoxy(14, 28); printf(" 1 ");
                        gotoxy(23, 28); printf(" 11 ");
                        white(); gotoxy(19, 28); printf("☜");
                        while (player_A_count > 0) {
                            gotoxy(9, 25); printf("   player  A x %d  ", player_A_count);
                            player_A_count--;
                            while (1) {
                                removeCursor();
                                if (kbhit() == 1) {  // 키보드가 눌려져 있으면
                                    ch = getch();
                                    if (ch == ESC)
                                        break;
                                    if (ch == RIGHT) {
                                        white(); gotoxy(19, 28); printf("☞");
                                        A_key = 1;
                                    }
                                    else if (ch == LEFT) {
                                        white(); gotoxy(19, 28); printf("☜");
                                        A_key = 0;
                                    }
                                    else if (ch == 13) {
                                        if (A_key == 0)          //1 선택
                                            playersum = playersum + 0;

                                        else if (A_key == 1)
                                            playersum = playersum + 10;

                                        gotoxy(39, 28); printf(" playersum = %d ", playersum);
                                        break;
                                    }
                                }
                            }
                        }
                        // 이만큼 다시 초록으로 만들기
                        textcolor(GREEN1, GREEN1);
                        gotoxy(9, 25); printf("   player  A x       ");
                        gotoxy(9, 26); printf("   player  A  1  or 11 ");
                        gotoxy(9, 27); printf("┌--------------------┐ ");
                        gotoxy(9, 28); printf("│                    │ ");
                        gotoxy(9, 29); printf("└--------------------┘ ");
                        gotoxy(14, 28); printf(" 1 ");
                        gotoxy(23, 28); printf(" 11 ");
                        white();
                    }

                    if (dealersum < 17) {                                    // 딜러가 17보다 작았을때 딜러는 카드를 더 받고 승패를 결정함
                        for (;;) {
                            do {
                                card = rand() % N_CARDS;
                            } while (cards[card] == 1);
                            cards[card] = 1;

                            no = card % N_ONE_SET;         //N_ONE_SET=52   no의 범위는 0~51
                            card_value = (no % 13) + 1;
                            if (card_value == 11 || card_value == 12 || card_value == 13)
                                card_value = 10;
                            else if (card_value == 1) {                                    // A카드 컨트롤하는 부분
                                card_value = 1;
                                int card_value11 = 11;

                                if ((dealersum + card_value11) > playersum)
                                    if ((dealersum + card_value11) > 21)
                                        card_value = 1;
                                    else
                                        card_value = 11;
                                else
                                    if (dealersum < 10)
                                        card_value = 11;
                                    else
                                        card_value = 1;
                            }

                            dealersum = dealersum + card_value;
                            if (card >= 0 && card <= 51)
                                type = 0;
                            else if (card >= 52 && card <= 103)
                                type = 1;
                            else if (card >= 104 && card <= 155)
                                type = 2;
                            else if (card >= 156 && card <= 207)
                                type = 3;
                            dealer_card[count1] = card_value;

                            gotoxy(b, 18); printf("  ??  ");
                            b = b + 6;
                            dealer_shape[count1] = type;
                            count1++;

                            if (dealersum >= 17) {                                       //17이상이 되면 반복문 종료
                                gotoxy(39, 18); printf("dealersum = %d ", dealersum);
                                print_dealer_card(&count1, card_type);//★17넘어가면 카드 공개하는 부분
                                break;
                            }
                        }
                        if (dealersum > playersum && dealersum <= 21 && playersum <= 21 && dealersum >= 17) {               // 딜러가 이기는 조건
                            gotoxy(19, 21); printf("                ");
                            gotoxy(19, 22); printf("dealer ※ WIN ※");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + 0;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }
                        else if (playersum <= 21 && dealersum >= 22 && dealersum >= 17) {                       // 딜러가 BUST 되고 플레이어가 21보다 장은경우
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("   dealer BUST  ");
                            gotoxy(19, 22); printf("player ※ WIN ※");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money + round_money;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }
                        else if (playersum == dealersum && playersum <= 21 && dealersum <= 21 && dealersum >= 17) {            //무승부
                            gotoxy(19, 21); printf("                ");
                            gotoxy(19, 22); printf("     무승부     ");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money;;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }

                        else if (playersum > dealersum && playersum <= 21 && dealersum >= 17) {                        // 플레이이가 이기는 조건
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("player ※ WIN ※");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money + round_money;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }
                        return;
                    }
                    //else if(dealersum==21&&){}
                    else {
                        if (dealersum > playersum && playersum <= 21 && dealersum >= 17 && dealersum <= 21) {                        //딜러가 이김
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("dealer ※ WIN ※");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + 0;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }

                        else if (dealersum == playersum && dealersum <= 21 && playersum <= 21) {               //무승부
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("     무승부     ");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money;;
                            information();
                            gotoxy(39, 18); printf("dealersum = %d ", dealersum);
                            return;
                        }
                        else if (dealersum < playersum && playersum <= 21 && dealersum >= 17) {
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("player ※ WIN ※");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money + round_money;         //플레이어가 이기면       배팅금의 두배를 돌려줌
                            information();
                            gotoxy(39, 18); printf("dealersum = %d ", dealersum);
                            return;
                        }

                    }
                }
                else if (last_key == 1) {      //HIT 선택
                   //HIT 선택
                    int last_key2 = 1;
                    while (last_key2 == 1) {
                        do {
                            card = rand() % N_CARDS;
                        } while (cards[card] == 1);
                        cards[card] = 1;

                        no = card % N_ONE_SET;         //N_ONE_SET=52   no의 범위는 0~51
                        card_value = (no % 13) + 1;
                        if (card_value == 11 || card_value == 12 || card_value == 13)
                            card_value = 10;
                        if (card_value == 1) {
                            card_value = 1;
                            player_A_count++;
                        }

                        if (card >= 0 && card <= 51)
                            type = 0;
                        else if (card >= 52 && card <= 103)
                            type = 1;
                        else if (card >= 104 && card <= 155)
                            type = 2;
                        else if (card >= 156 && card <= 207)
                            type = 3;
                        player_card[count2] = card_value;
                        playersum = playersum + card_value;
                        player_shape[count2] = type;
                        gotoxy(39, 28); printf(" playersum = %d ", playersum);
                        print_player_card(&count2, card_type);
                        count2++;
                        gotoxy(a, 28); printf("%s%2s ", card_type[type], card_no[no]);               ////////// 플레이어가 받은 카드 위치
                        a = a + 5;
                        if (playersum >= 22) {
                            x = 41;
                            y = 48;
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("   player BUST  ");
                            gotoxy(19, 22); printf("dealer ※ WIN ※");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            information();
                            return;
                        }
                        while (1) {
                            removeCursor();
                            if (kbhit() == 1) {  // 키보드가 눌려져 있으면
                                ch = getch();
                                if (ch == ESC)
                                    break;
                                if (ch == RIGHT) {
                                    white(); gotoxy(19, 31); printf("☞");
                                    last_key = 1;
                                }
                                else if (ch == LEFT) {
                                    white(); gotoxy(19, 31); printf("☜");
                                    last_key = 0;
                                }
                                else if (ch == 13) {
                                    last_key2 = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    }

                }

            }

        }
        //return;                                             //게임 다 작성되면 게임다 돌고 메뉴가는창
    }
}
void explain() {      // menu_num = 2 일 때 
    srand((unsigned)time(NULL));

    system("cls");
    draw_table(0, 0, WIDTH, HEIGHT, "▩");

    //while (1) {// ??전광판 넣고싶음.
       //a = rand() % 16;
       //b = rand() % 16;
       //textcolor(a, a-4);
    gotoxy(50, 4); printf(" < 게임 설명 > ");
    //Sleep(1000);
 //}
    textcolor(YELLOW2, GREEN1);
    gotoxy(10, 10); printf("게임 규칙은 카드의 합이 21점 혹은 21점에 가장 가까운 사람이 이기는 게임입니다.");
    gotoxy(10, 11); printf("카드를 받기 전 기본금을 베팅하고 딜러의 첫 번째 카드를 제외한 모든 카드는 공개합니다.");
    gotoxy(10, 12); printf(" A 카드는 자신에게 유리하게 1점 혹은 11점으로 계산할 수 있고, J,Q,K 는 10점으로 계산합니다.");
    gotoxy(10, 13); printf("처음 2장의 카드가 21점이면 '블랙잭'이 되고, 승리시 2배를 받게 됩니다.");
    gotoxy(10, 14); printf("딜러와 플레이어 모두 '블랙잭'인 경우 무승부로 베팅액은 돌려받게 됩니다.");
    gotoxy(10, 15); printf("플레이어는 '블랙잭'이 아닌 경우 21점에 가까워지기 위해 추가 카드를 요구할 수 있습니다.");
    gotoxy(10, 16); printf("플레이어의 판단에 따라 Hit 혹은 Stand 합니다.");
    red(); gotoxy(10, 17); printf("주의!!");
    textcolor(YELLOW2, GREEN1); gotoxy(16, 17); printf("  21점을 초과할 경우 !BUST!0점 처리됩니다. (딜러도 해당)");
    gotoxy(10, 19); printf("딜러는 플레이어의 카드 추가 후 자신이 카드를 추가할 것인지 여부를 결정합니다.");
    gotoxy(10, 20); printf("딜러는 17 미만인 경우 1장을 추가하고, 17 이상인 경우 추가하지 않습니다..");

    gotoxy(10, 27); printf(" - Hit - 카드를 추가로 가져오는 것.");
    gotoxy(10, 28); printf(" - Stand (Stay) - 더 이상 카드를 받지 않는 것.");
    gotoxy(10, 29); printf(" - Bust - 숫자의 합이 21을 넘을 경우.");
    red(); gotoxy(10, 33); printf("☞ 아무키나 누르시면 2page로 갑니다.");
    getch();

    system("cls");
    draw_table(0, 0, WIDTH, HEIGHT, "▩");
    textcolor(YELLOW2, GREEN1);
    gotoxy(10, 10); printf("게임에 필요한 키!!  ↑, ↓, ←, → , enter_key 만 사용");
    gotoxy(10, 11); printf("게임시작시 ↑, ↓ 를 이용해서 배팅금액을 설정하고 enter_key누르기");
    gotoxy(10, 12); printf("배팅 완료시 자동으로 player와 dealer에게 카드 2장씩 나눠줌");
    gotoxy(10, 13); printf("카드를 더 받고싶으면 ←, → 를 이용해서 STAY와 HIT를 고르고 enter_key누르기");
    gotoxy(10, 14); printf("HIT를 누르면 카드를 한장씩 더 받는다.");
    gotoxy(10, 15); printf("STAY를 누르면 A의 값을 결정하고 승패가 나오게된다.");
    gotoxy(10, 16); printf("아무키나 누르면 다시 메뉴로 돌아간다");

    gotoxy(10, 24); printf("▶  player가 이기면 2배");
    gotoxy(10, 25); printf("▶  ex) 10000원 배팅하고 이기면 20000원 으로 돌려줌");
    red(); gotoxy(10, 30); printf("아무키나 누르시면 메뉴로 돌아갑니다!");
    getch();

    return;
}
void main() {
    int i, x, y;
    char buf[100];
    system("title 블랙잭 ");
    while (1) {
        cls(WHITE, BLACK);      // 한바퀴 돌때마다 배경을 다시 검정으로 초기화 시켜줌
        removeCursor(); // 커서를 안보이게 한다
        gotoxy(40, 11); printf(" 한성대학교 컴퓨터공학부 프로그래밍랩\n");
        gotoxy(40, 13); printf("             1971194 김택신 \n");
        gotoxy(40, 14); printf("--------------------------------------");
        gotoxy(40, 16); printf("--------------------------------------");
        gotoxy(40, 15); textcolor(RED2, BLACK); printf("               - 블랙잭 - ");
        draw_box(0, 0, WIDTH, HEIGHT, '*'); // 화면에 box를 그린다.
        gotoxy(40, 19);      //menu
        showCursor();
        menu();
        if (menu_num == 1) {
            gameplay();
            getch();
        }
        else if (menu_num == 2) {
            explain();
            getch();
        }
        else if (menu_num == 3) {
            system("cls");
            textcolor(WHITE, BLACK);
            gotoxy(40, 11); printf("          종료를 선택하셨습니다.\n");
            gotoxy(40, 13); information();
            _sleep(1000);

            gotoxy(40, 35);      // 계속하려면 아무 키나 누르십시오 . . . 자리
            break;
        }
        gotoxy(40, 35);      // 계속하려면 아무 키나 누르십시오 . . . 자리
    }
}