//1971194
//���ý�

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include<winbase.h>

// ���� ����
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

#define SPECIAL1 0xe0 // Ư��Ű�� 0xe0 + key ������ �����ȴ�.
#define SPECIAL2 0x00 // keypad ��� 0x00 + key �� �����ȴ�.

#define UP  0x48 // Up key�� 0xe0 + 0x48 �ΰ��� ���� ���´�.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define ESC   0x1b // ESC key ��

#define WIDTH 120
#define HEIGHT 40

#define N_SHAPE   4 // ���̼� 4
#define N_ONE_SET   52 // 13�����̹Ƿ�
#define N_CARDS   208 // ���̴� 13��*4 ���� 4�� �̹Ƿ� 208��
#define N_DEAL   2 // �Ѹ�� 2��

//����� �������� ���������� ����   �������� �� �ٽ� �ʱ�ȭ ��ų ����
int total_money = 10000000;            // �ں��� �Է�
int round_count = 0;
int round_money = 0; //���� �ݾ�,  �ǵ�
int shape1 = 0;
int shape2 = 0;
int x = 41;
int y = 41;
int player_card[21] = { 0 }; //�÷��̾ �߰��� ī�����
int player_shape[21] = { 0 }; //�÷��̾ �߰��� ī����
int playersum = 0; //�÷��̾��� ī�� ��
int dealer_card[21] = { 0 }; //������ �߰��� ī�����
int dealer_shape[21] = { 0 }; //������ �߰��� ī����
int dealersum = 0; //������ ī�� ��
int hit = 0; //ī�带 �߰��� ������ ����
int Ace = 0; //A�� 1�� ������� 11�� ������� ����
int Card[52] = { 1,2,3,4,5,6,7,8,9,10,10,10,10,
             1,2,3,4,5,6,7,8,9,10,10,10,10,
             1,2,3,4,5,6,7,8,9,10,10,10,10,
             1,2,3,4,5,6,7,8,9,10,10,10,10 }; //52���� ��� ī��
int menu_num = 1; //  �޴����ù�ȣ    1, ���ӽ���  2, ���� ����  3, ����
void gotoxy(int x, int y) //���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
    COORD pos; // Windows.h �� ����
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
void intensity()//ȸ��
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
}
void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // Ŀ���� ���̰� �Ѵ�
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void cls(int text_color, int bg_color) // ȭ�� �����
{
    char cmd[100];
    system("cls");
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}
// box �׸��� �Լ�, ch ���ڷ� (x1,y1) ~ (x2,y2) box�� �׸���.
void draw_box(int x1, int y1, int x2, int y2, char ch)//ùȭ�� �ڽ� �Լ�
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
void draw_table(int x1, int y1, int x2, int y2, char* ch)//���� ���̺� �����
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
    gotoxy(8, 3);  printf("������������������������������ ");
    gotoxy(8, 4);  printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 5);  printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 6);  printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 7);  printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 8);  printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 9);  printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 10); printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 11); printf("��  �̢̢̢̢� �� ");
    gotoxy(8, 12); printf("������������������������������ ");
    textcolor(WHITE, GREEN1);
}
void information() {
    gotoxy(8, 33);   printf("������������������������������������������������������ ");
    gotoxy(8, 34);   printf("��                         �� ");
    gotoxy(8, 35);   printf("��                         �� ");
    gotoxy(8, 36);   printf("��                         �� ");
    gotoxy(8, 37);   printf("��                         �� ");
    gotoxy(8, 38);   printf("������������������������������������������������������ ");
    gotoxy(10, 35); printf("���� �� : %d ����", total_money);
    gotoxy(10, 36); printf("��   �� : %d ��°", round_count);
    gotoxy(10, 37); printf("���� �� : %d   ��", round_money);
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
            gotoxy(y, 2);  printf("��%s%2c        �� ", card_type[a], A);
            gotoxy(y, 9);  printf("��        %s%2c�� ", card_type[a], A);

        }
        else {
            gotoxy(y, 2);  printf("��%s%2d        �� ", card_type[a], dealer_card[i]);
            gotoxy(y, 9);  printf("��        %s%2d�� ", card_type[a], dealer_card[i]);
        }
        gotoxy(y, 1);  printf("���������������������������� ");

        gotoxy(y, 3);  printf("��            �� ");
        gotoxy(y, 4);  printf("��            �� ");
        gotoxy(y, 5);  printf("��            �� ");
        gotoxy(y, 6);  printf("��            �� ");
        gotoxy(y, 7);  printf("��            �� ");
        gotoxy(y, 8);  printf("��            �� ");

        gotoxy(y, 10);  printf("���������������������������� ");
        y = y + 7;
    }

}

void print_dealer_init_card(int* count1, char* card_type[]) {
    int a;
    char A = 'A';
    white();
    a = dealer_shape[*count1];
    if (*count1 == 1) {                                 // 2��° ī��
        gotoxy(48, 1);  printf("������������������������������ ");
        gotoxy(48, 2);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 3);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 4);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 5);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 6);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 7);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 8);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 9);  printf("��  �̢̢̢̢� �� ");
        gotoxy(48, 10); printf("������������������������������ ");
    }
    else {                                             //1��° ī��
        if (dealer_card[*count1] == 1) {                // A���� Ȯ��
            gotoxy(41, 2);  printf("��%s%2c        �� ", card_type[a], A);
            gotoxy(41, 9);  printf("��        %s%2c�� ", card_type[a], A);
        }
        else {
            gotoxy(41, 2);  printf("��%s%2d        �� ", card_type[a], dealer_card[*count1]);
            gotoxy(41, 9);  printf("��        %s%2d�� ", card_type[a], dealer_card[*count1]);
        }
        gotoxy(41, 1);  printf("���������������������������� ");

        gotoxy(41, 3);  printf("��            �� ");
        gotoxy(41, 4);  printf("��            �� ");
        gotoxy(41, 5);  printf("��            �� ");
        gotoxy(41, 6);  printf("��            �� ");
        gotoxy(41, 7);  printf("��            �� ");
        gotoxy(41, 8);  printf("��            �� ");

        gotoxy(41, 10);  printf("���������������������������� ");
    }
}
void print_player_card(int* count2, char* card_type[]) {// x��ǥ�� 7��
    int b;
    char A = 'A';
    white();
    for (int i = *count2; i <= *count2; i++) {
        _sleep(500);
        b = player_shape[i];
        if (player_card[i] == 1) {
            gotoxy(x, 31);  printf("��%s%2c        �� ", card_type[b], A);
            gotoxy(x, 38);  printf("��        %s%2c�� ", card_type[b], A);
        }
        else {
            gotoxy(x, 31);  printf("��%s%2d        �� ", card_type[b], player_card[i]);
            gotoxy(x, 38);  printf("��        %s%2d�� ", card_type[b], player_card[i]);
        }

        gotoxy(x, 30);  printf("���������������������������� ");

        gotoxy(x, 32);  printf("��            �� ");
        gotoxy(x, 33);  printf("��            �� ");
        gotoxy(x, 34);  printf("��            �� ");
        gotoxy(x, 35);  printf("��            �� ");
        gotoxy(x, 36);  printf("��            �� ");
        gotoxy(x, 37);  printf("��            �� ");

        gotoxy(x, 39);  printf("���������������������������� ");
        x = x + 7;
    }
}

void menu() {
    int y = 21;
    unsigned char ch; // Ư��Ű 0xe0 �� �Է¹������� unsigned char �� �����ؾ� ��
     //1, ���ӽ���  2, ���� ����  3, ����
    gotoxy(40, 19); printf("��------------------------------------�� ");
    gotoxy(40, 27); printf("��------------------------------------�� ");
    textcolor(WHITE, BLACK);
    gotoxy(40, 21); printf("               1, ���ӽ���               ");
    gotoxy(40, 23); printf("               2, ���Ӽ���               ");
    gotoxy(40, 25); printf("               3, ��    ��               ");
    gotoxy(90, 35); printf("�� ����Ű ��(��), �Ʒ�(��) ");
    gotoxy(90, 36); printf("       ����  ���� ");
    red(); gotoxy(50, 21); printf("��");
    while (1) {
        //upŰ �� 72 downŰ �� 80 enterŰ �� 13
        if (kbhit() == 1) {  // Ű���尡 ������ ������

            ch = getch();
            if (ch == ESC)
                break;

            if (ch == UP) {
                gotoxy(50, y); printf("��");
                y = y - 2;
                if (y <= 21)
                    y = 21;
                gotoxy(50, y); printf("��");
            }
            else if (ch == DOWN) {
                gotoxy(50, y); printf("��");
                y = y + 2;
                if (y >= 25)
                    y = 25;
                gotoxy(50, y); printf("��");
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
    unsigned char ch; // Ư��Ű 0xe0 �� �Է¹������� unsigned char �� �����ؾ� ��
    int up_count = 0, down_count = 0;
    int a, b = 0;
    a = rand() % 16;
    textcolor(a, a - 3);
    system("cls");
    for (b = 0; b <= 8; b++) {                            //������ ����
        a = rand() % 16;
        textcolor(a, a - 3);
        gotoxy(45, 19); printf("                                   ");
        gotoxy(45, 20); printf("�������� ������ �����մϴ� ��������");
        gotoxy(45, 21); printf("                                   ");
        Sleep(400);
    }

    system("cls");
    draw_table(0, 0, WIDTH, HEIGHT, "��");
    draw_deck();
    information();
    gotoxy(40, 19); printf("������������������������������������������������������������������������������������ ");
    gotoxy(40, 27); printf("������������������������������������������������������������������������������������ ");
    gotoxy(45, 20); printf("���� �� �ں��� �Է��ϼ��� ���� ");
    gotoxy(45, 22); printf("        ����Ű < �� / �� > ");
    //���ñݾ� ���ϰ�, �����ݾ�, �� �� �� ǥ�����ִ� �κ�
    while (1) {
        removeCursor();
        if (kbhit() == 1) {  // Ű���尡 ������ ������
            ch = getch();
            if (ch == ESC)
                break;
            if (ch == UP) {
                up_count++;
                *round_money = up_count * 10000;
                red();
                gotoxy(42, 23); printf("                                      ");
                gotoxy(42, 24); printf(" ���� ���ñ�(����: 1����) : [  %d", *round_money); printf(" ]");
                gotoxy(42, 25); printf("                                      ");
                information();
            }
            else if (ch == DOWN) {
                up_count--;
                if (*round_money == 0) {                  // if ���� ���ñݾ��� 0���ε� -�ϸ� �ȵǴϱ� �����ϱ� ����
                    up_count++;
                }
                else {
                    *round_money = up_count * 10000;
                }
                red();
                gotoxy(42, 23); printf("                                      ");
                gotoxy(42, 24); printf(" ���� ���ñ�(����: 1����) : [  %d", *round_money); printf(" ]");
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

    unsigned char ch; // Ư��Ű 0xe0 �� �Է¹������� unsigned char �� �����ؾ� ��
    srand((unsigned)time(NULL));
    draw_table(0, 0, WIDTH, HEIGHT, "��");
    draw_deck();
    batting(&total_money, &round_money, &round_count);
    //system("cls");
    //draw_table(0, 0, WIDTH, HEIGHT, "��");

    information();

    //���ӽ���
    int count1 = 0, count2 = 0;  //���° ī������ ī����� // ���߿� ī�� �׸� �� ���� ����
    int cards[N_CARDS] = { 0 }; // ��ü ī�带 1���� Array�� ����, 1�̸� �̹� ������ ī��
    int card, card_value;
    //int dealer_card_count = 1, player_card_count = 1;          �� �ִ��� ��
    int dealer_behind = 0; //������ ī��
    int type = 0, no;
    int dealer_blackjack = 0, dealer_A_count = 0;
    int player_blackjack = 0, player_A_count = 0;
    char* card_type[] = { "��", "��", "��","��" }; // ī�幫�� "��" ������ ����Ű.
    //      0~51��   52~103��   104~155��   156~207��
    // A ~ 10, J, Q, K x4 �� ��
    char* card_no[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
                        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
                        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
                        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    playersum = 0;
    dealersum = 0;
    gotoxy(60, 18); printf(" ���� : ");                                             //�������� ī�� 2��

    for (int i = 0; i < N_DEAL; i++) { // ī�� 2�� �й�  N_DEAL=2
       // �̹� ������ ī������ üũ�ϸ鼭, ������ ī��� ǥ���Ѵ�.
       // card ��ȣ 0 ~ N_CARDS �� card_type�� card_no, joker���� �����ؼ� ����Ѵ�.
       //      0~51��   52~103��   104~155��   156~207��
        do {
            card = rand() % N_CARDS;
        } while (cards[card] == 1);
        cards[card] = 1;

        no = card % N_ONE_SET;         //N_ONE_SET=52   no�� ������ 0~51
        card_value = (no % 13) + 1;
        if (card_value == 11 || card_value == 12 || card_value == 13) {
            card_value = 10;
            dealer_blackjack = dealer_blackjack + card_value;
        }
        if (card_value == 1) {                     //A�� ����
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
        if (dealer_behind == 0) {     //dealer_behind ù�常 �����Ϸ��� 0�� �Է����ְ� 1�̸� ������
            printf("%s%2s", card_type[type], card_no[no]);                                 ////// ������ ���� ī�� ��ġ
            dealer_behind = 1;
        }
        else if (dealer_behind != 0) {
            gotoxy(72, 18); printf("  ??  ");
        }
        print_dealer_init_card(&count1, card_type);
        count1++;
    }
    printf("\n");

    gotoxy(60, 28); printf("   ��: ");                                 //�÷��̾�� ī�� 2��
    for (int i = 0; i < N_DEAL; i++) { // ī�� 2�� �й�
       // �̹� ������ ī������ üũ�ϸ鼭, ������ ī��� ǥ���Ѵ�.
       // card ��ȣ 0 ~ N_CARDS �� card_type�� card_no �����ؼ� ����Ѵ�.
       //      0~51��   52~103��   104~155��   156~207��
        do {
            card = rand() % N_CARDS;
        } while (cards[card] == 1);
        cards[card] = 1;

        no = card % N_ONE_SET;         //N_ONE_SET=52   no�� ������ 0~51
        card_value = (no % 13) + 1;
        if (card_value == 11 || card_value == 12 || card_value == 13) {
            card_value = 10;
            player_blackjack = player_blackjack + 10;
        }
        if (card_value == 1) {                     //A�� ����
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
    if (dealer_blackjack == 21) {                                          // ������ ó�� ���� 2���� ���� �ΰ��
        gotoxy(19, 20); printf("                  ");
        gotoxy(19, 21); printf("    BLACK JACK    ");
        gotoxy(19, 22); printf(" dealer �� WIN �� ");
        gotoxy(19, 23); printf("                  ");
        print_dealer_card(&count1, card_type);
        total_money = total_money - 0;
        information();
        getch();
        return;
    }
    else if (player_blackjack == 21 && dealer_blackjack == 21) {
        gotoxy(19, 21); printf("                ");
        gotoxy(19, 22); printf("     ���º�     ");
        gotoxy(19, 23); printf("                ");
        print_dealer_card(&count1, card_type);
        total_money = total_money + round_money;;
        information();
        getch();
        return;
    }
    else if (player_blackjack == 21) {                                          // �÷��̾ ó�� ���� 2���� ���� �ΰ��
        gotoxy(19, 20); printf("                  ");
        gotoxy(19, 21); printf("    BLACK JACK    ");
        gotoxy(19, 22); printf(" player �� WIN �� ");
        gotoxy(19, 23); printf("                  ");
        total_money = total_money + round_money + round_money;
        information();
        getch();
        return;
    }
    int last_key = 0;
    gotoxy(9, 30); printf("��--------------------�� ");
    gotoxy(9, 31); printf("��                    �� ");
    gotoxy(9, 32); printf("��--------------------�� ");
    gotoxy(14, 31); printf("STAY");
    gotoxy(23, 31); printf("HIT");
    int a = 77;
    int b = 77;
    white(); gotoxy(19, 31); printf("��");
    while (1) {
        removeCursor();
        if (kbhit() == 1) {  // Ű���尡 ������ ������
            ch = getch();
            if (ch == ESC)
                break;
            if (ch == RIGHT) {
                white(); gotoxy(19, 31); printf("��");
                last_key = 1;
            }
            else if (ch == LEFT) {
                white(); gotoxy(19, 31); printf("��");
                last_key = 0;
            }
            else if (ch == 13) {
                if (last_key == 0) {         //STAY����
                   //STAY����
                    x = 41;
                    y = 48;
                    if (player_A_count >= 1) {
                        int A_key = 0;
                        gotoxy(9, 26); printf("   player  A  1  or 11 ");
                        gotoxy(9, 27); printf("��--------------------�� ");
                        gotoxy(9, 28); printf("��                    �� ");
                        gotoxy(9, 29); printf("��--------------------�� ");
                        gotoxy(14, 28); printf(" 1 ");
                        gotoxy(23, 28); printf(" 11 ");
                        white(); gotoxy(19, 28); printf("��");
                        while (player_A_count > 0) {
                            gotoxy(9, 25); printf("   player  A x %d  ", player_A_count);
                            player_A_count--;
                            while (1) {
                                removeCursor();
                                if (kbhit() == 1) {  // Ű���尡 ������ ������
                                    ch = getch();
                                    if (ch == ESC)
                                        break;
                                    if (ch == RIGHT) {
                                        white(); gotoxy(19, 28); printf("��");
                                        A_key = 1;
                                    }
                                    else if (ch == LEFT) {
                                        white(); gotoxy(19, 28); printf("��");
                                        A_key = 0;
                                    }
                                    else if (ch == 13) {
                                        if (A_key == 0)          //1 ����
                                            playersum = playersum + 0;

                                        else if (A_key == 1)
                                            playersum = playersum + 10;

                                        gotoxy(39, 28); printf(" playersum = %d ", playersum);
                                        break;
                                    }
                                }
                            }
                        }
                        // �̸�ŭ �ٽ� �ʷ����� �����
                        textcolor(GREEN1, GREEN1);
                        gotoxy(9, 25); printf("   player  A x       ");
                        gotoxy(9, 26); printf("   player  A  1  or 11 ");
                        gotoxy(9, 27); printf("��--------------------�� ");
                        gotoxy(9, 28); printf("��                    �� ");
                        gotoxy(9, 29); printf("��--------------------�� ");
                        gotoxy(14, 28); printf(" 1 ");
                        gotoxy(23, 28); printf(" 11 ");
                        white();
                    }

                    if (dealersum < 17) {                                    // ������ 17���� �۾����� ������ ī�带 �� �ް� ���и� ������
                        for (;;) {
                            do {
                                card = rand() % N_CARDS;
                            } while (cards[card] == 1);
                            cards[card] = 1;

                            no = card % N_ONE_SET;         //N_ONE_SET=52   no�� ������ 0~51
                            card_value = (no % 13) + 1;
                            if (card_value == 11 || card_value == 12 || card_value == 13)
                                card_value = 10;
                            else if (card_value == 1) {                                    // Aī�� ��Ʈ���ϴ� �κ�
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

                            if (dealersum >= 17) {                                       //17�̻��� �Ǹ� �ݺ��� ����
                                gotoxy(39, 18); printf("dealersum = %d ", dealersum);
                                print_dealer_card(&count1, card_type);//��17�Ѿ�� ī�� �����ϴ� �κ�
                                break;
                            }
                        }
                        if (dealersum > playersum && dealersum <= 21 && playersum <= 21 && dealersum >= 17) {               // ������ �̱�� ����
                            gotoxy(19, 21); printf("                ");
                            gotoxy(19, 22); printf("dealer �� WIN ��");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + 0;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }
                        else if (playersum <= 21 && dealersum >= 22 && dealersum >= 17) {                       // ������ BUST �ǰ� �÷��̾ 21���� �������
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("   dealer BUST  ");
                            gotoxy(19, 22); printf("player �� WIN ��");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money + round_money;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }
                        else if (playersum == dealersum && playersum <= 21 && dealersum <= 21 && dealersum >= 17) {            //���º�
                            gotoxy(19, 21); printf("                ");
                            gotoxy(19, 22); printf("     ���º�     ");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money;;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }

                        else if (playersum > dealersum && playersum <= 21 && dealersum >= 17) {                        // �÷����̰� �̱�� ����
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("player �� WIN ��");
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
                        if (dealersum > playersum && playersum <= 21 && dealersum >= 17 && dealersum <= 21) {                        //������ �̱�
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("dealer �� WIN ��");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + 0;
                            information();
                            gotoxy(39, 18); printf(" dealersum = %d ", dealersum);
                            return;
                        }

                        else if (dealersum == playersum && dealersum <= 21 && playersum <= 21) {               //���º�
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("     ���º�     ");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money;;
                            information();
                            gotoxy(39, 18); printf("dealersum = %d ", dealersum);
                            return;
                        }
                        else if (dealersum < playersum && playersum <= 21 && dealersum >= 17) {
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("player �� WIN ��");
                            gotoxy(19, 22); printf("                ");
                            print_dealer_card(&count1, card_type);
                            total_money = total_money + round_money + round_money;         //�÷��̾ �̱��       ���ñ��� �ι踦 ������
                            information();
                            gotoxy(39, 18); printf("dealersum = %d ", dealersum);
                            return;
                        }

                    }
                }
                else if (last_key == 1) {      //HIT ����
                   //HIT ����
                    int last_key2 = 1;
                    while (last_key2 == 1) {
                        do {
                            card = rand() % N_CARDS;
                        } while (cards[card] == 1);
                        cards[card] = 1;

                        no = card % N_ONE_SET;         //N_ONE_SET=52   no�� ������ 0~51
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
                        gotoxy(a, 28); printf("%s%2s ", card_type[type], card_no[no]);               ////////// �÷��̾ ���� ī�� ��ġ
                        a = a + 5;
                        if (playersum >= 22) {
                            x = 41;
                            y = 48;
                            gotoxy(19, 20); printf("                ");
                            gotoxy(19, 21); printf("   player BUST  ");
                            gotoxy(19, 22); printf("dealer �� WIN ��");
                            gotoxy(19, 23); printf("                ");
                            print_dealer_card(&count1, card_type);
                            information();
                            return;
                        }
                        while (1) {
                            removeCursor();
                            if (kbhit() == 1) {  // Ű���尡 ������ ������
                                ch = getch();
                                if (ch == ESC)
                                    break;
                                if (ch == RIGHT) {
                                    white(); gotoxy(19, 31); printf("��");
                                    last_key = 1;
                                }
                                else if (ch == LEFT) {
                                    white(); gotoxy(19, 31); printf("��");
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
        //return;                                             //���� �� �ۼ��Ǹ� ���Ӵ� ���� �޴�����â
    }
}
void explain() {      // menu_num = 2 �� �� 
    srand((unsigned)time(NULL));

    system("cls");
    draw_table(0, 0, WIDTH, HEIGHT, "��");

    //while (1) {// ??������ �ְ����.
       //a = rand() % 16;
       //b = rand() % 16;
       //textcolor(a, a-4);
    gotoxy(50, 4); printf(" < ���� ���� > ");
    //Sleep(1000);
 //}
    textcolor(YELLOW2, GREEN1);
    gotoxy(10, 10); printf("���� ��Ģ�� ī���� ���� 21�� Ȥ�� 21���� ���� ����� ����� �̱�� �����Դϴ�.");
    gotoxy(10, 11); printf("ī�带 �ޱ� �� �⺻���� �����ϰ� ������ ù ��° ī�带 ������ ��� ī��� �����մϴ�.");
    gotoxy(10, 12); printf(" A ī��� �ڽſ��� �����ϰ� 1�� Ȥ�� 11������ ����� �� �ְ�, J,Q,K �� 10������ ����մϴ�.");
    gotoxy(10, 13); printf("ó�� 2���� ī�尡 21���̸� '����'�� �ǰ�, �¸��� 2�踦 �ް� �˴ϴ�.");
    gotoxy(10, 14); printf("������ �÷��̾� ��� '����'�� ��� ���ºη� ���þ��� �����ް� �˴ϴ�.");
    gotoxy(10, 15); printf("�÷��̾�� '����'�� �ƴ� ��� 21���� ��������� ���� �߰� ī�带 �䱸�� �� �ֽ��ϴ�.");
    gotoxy(10, 16); printf("�÷��̾��� �Ǵܿ� ���� Hit Ȥ�� Stand �մϴ�.");
    red(); gotoxy(10, 17); printf("����!!");
    textcolor(YELLOW2, GREEN1); gotoxy(16, 17); printf("  21���� �ʰ��� ��� !BUST!0�� ó���˴ϴ�. (������ �ش�)");
    gotoxy(10, 19); printf("������ �÷��̾��� ī�� �߰� �� �ڽ��� ī�带 �߰��� ������ ���θ� �����մϴ�.");
    gotoxy(10, 20); printf("������ 17 �̸��� ��� 1���� �߰��ϰ�, 17 �̻��� ��� �߰����� �ʽ��ϴ�..");

    gotoxy(10, 27); printf(" - Hit - ī�带 �߰��� �������� ��.");
    gotoxy(10, 28); printf(" - Stand (Stay) - �� �̻� ī�带 ���� �ʴ� ��.");
    gotoxy(10, 29); printf(" - Bust - ������ ���� 21�� ���� ���.");
    red(); gotoxy(10, 33); printf("�� �ƹ�Ű�� �����ø� 2page�� ���ϴ�.");
    getch();

    system("cls");
    draw_table(0, 0, WIDTH, HEIGHT, "��");
    textcolor(YELLOW2, GREEN1);
    gotoxy(10, 10); printf("���ӿ� �ʿ��� Ű!!  ��, ��, ��, �� , enter_key �� ���");
    gotoxy(10, 11); printf("���ӽ��۽� ��, �� �� �̿��ؼ� ���ñݾ��� �����ϰ� enter_key������");
    gotoxy(10, 12); printf("���� �Ϸ�� �ڵ����� player�� dealer���� ī�� 2�徿 ������");
    gotoxy(10, 13); printf("ī�带 �� �ް������ ��, �� �� �̿��ؼ� STAY�� HIT�� ���� enter_key������");
    gotoxy(10, 14); printf("HIT�� ������ ī�带 ���徿 �� �޴´�.");
    gotoxy(10, 15); printf("STAY�� ������ A�� ���� �����ϰ� ���а� �����Եȴ�.");
    gotoxy(10, 16); printf("�ƹ�Ű�� ������ �ٽ� �޴��� ���ư���");

    gotoxy(10, 24); printf("��  player�� �̱�� 2��");
    gotoxy(10, 25); printf("��  ex) 10000�� �����ϰ� �̱�� 20000�� ���� ������");
    red(); gotoxy(10, 30); printf("�ƹ�Ű�� �����ø� �޴��� ���ư��ϴ�!");
    getch();

    return;
}
void main() {
    int i, x, y;
    char buf[100];
    system("title ���� ");
    while (1) {
        cls(WHITE, BLACK);      // �ѹ��� �������� ����� �ٽ� �������� �ʱ�ȭ ������
        removeCursor(); // Ŀ���� �Ⱥ��̰� �Ѵ�
        gotoxy(40, 11); printf(" �Ѽ����б� ��ǻ�Ͱ��к� ���α׷��ַ�\n");
        gotoxy(40, 13); printf("             1971194 ���ý� \n");
        gotoxy(40, 14); printf("--------------------------------------");
        gotoxy(40, 16); printf("--------------------------------------");
        gotoxy(40, 15); textcolor(RED2, BLACK); printf("               - ���� - ");
        draw_box(0, 0, WIDTH, HEIGHT, '*'); // ȭ�鿡 box�� �׸���.
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
            gotoxy(40, 11); printf("          ���Ḧ �����ϼ̽��ϴ�.\n");
            gotoxy(40, 13); information();
            _sleep(1000);

            gotoxy(40, 35);      // ����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . . �ڸ�
            break;
        }
        gotoxy(40, 35);      // ����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . . �ڸ�
    }
}