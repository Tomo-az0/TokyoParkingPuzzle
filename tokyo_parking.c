// -*- coding: Shift_JIS -*-

#include<stdio.h>
#include<stdlib.h>

#define HEIGHT 6
#define WIDTH 6

#define MAX 4


int is_vert[MAX + 1] = { -1,0,1,0,1 };
int car_length[MAX + 1] = { -1, 2,3,2,2 };
int x, y, tmp;

void init_board(int board[][WIDTH + 2]) {
    int i, j;
    for (i = 0; i <= HEIGHT + 1; i++) {
        for (j = 0; j <= WIDTH + 1; j++) {
            if (i == 3 && j == 7)board[i][j] = 0;
            else board[i][j] = -1;
        }
    }
    for (i = 1; i <= HEIGHT; i++) {
        for (j = 1; j <= WIDTH; j++) {
            board[i][j] = 0;
            if (j == 5 && (i == 1 || i == 2 || i == 3))board[i][j] = 2;
            else if (j == 4 && (i == 4 || i == 5))board[i][j] = 4;
            else if (i == 3 && (j == 3 || j == 4))board[i][j] = 1;
            else if (i == 5 && (j == 5 || j == 6))board[i][j] = 3;
        }
    }
}

void print_board(int board[][WIDTH + 2]) {
    int i, j;
    for (i = 0; i <= HEIGHT + 1; i++) {
        for (j = 0; j <= WIDTH + 1; j++) {
            if (i == 0 && j == 7) { printf("┐"); }
            else if (i == 0 && j == 0) { printf("┌"); }
            else if (i == 7 && j == 0) { printf("└"); }
            else if (i == 7 && j == 7) { printf("┘"); }
            else if ((i == 0 || i == 7) != 0) { printf("--"); }
            else if ((j == 0 || j == 7) != 0 && board[i][j] == -1) { printf("│"); }

            if (board[i][j] == 0)printf("・");
            else if (board[i][j] == 1)printf("☆");
            else if (board[i][j] == 2)printf("■");
            else if (board[i][j] == 3)printf("▲");
            else if (board[i][j] == 4)printf("△");
            if (i == 3 && j == 7)printf("  EXIT");
            if (j == 7)printf("\n");
        }
    }
}

int is_vertical(int car) {
    if (is_vert[car] == 1)return 1;
    else return 0;
}

void change_board(int car, int op, int board[][WIDTH + 2]) {

    if (is_vertical(car) == 0) {
        if (op == 1) {
            board[x][y - car_length[car]] = board[x][y];
            board[x][y] = tmp;
        }
        else if (op == 2) {
            board[x][y + 1] = board[x][y - car_length[car] + 1];
            board[x][y - car_length[car] + 1] = tmp;
        }
    }
    else if (is_vertical(car) == 1) {
        if (op == 1) {
            board[x - car_length[car]][y] = board[x][y];
            board[x][y] = tmp;
        }
        else if (op == 2) {
            board[x + 1][y] = board[x - car_length[car] + 1][y];
            board[x - car_length[car] + 1][y] = tmp;
        }
    }
}

int check_op(int car, int op, int board[][WIDTH + 2]) {
    tmp = 0;
    if (is_vertical(car) == 0) {
        if (op == 1) tmp = board[x][y - car_length[car]];
        else if (op == 2) tmp = board[x][y + 1];
    }

    else if (is_vertical(car) == 1) {
        if (op == 1) tmp = board[x - car_length[car]][y];
        else if (op == 2) tmp = board[x + 1][y];
    }

    if (tmp == 0)return 1;
    else return 0;
}

int check_board(int board[][WIDTH + 2]) {
    if (board[3][7] != 0)return 1;
    else return 0;
}

int main(void) {

    int board[HEIGHT + 2][WIDTH + 2];
    int car, op, i, j;
    x = 0;
    y = 0;
    car = 0;
    op = 0;

    init_board(board);
    while (check_board(board) == 0) {
        while (1) {
            system("cls");/*画面クリアコマンド*/
            print_board(board);
            printf("どの車を動かしますか？（☆:1,■:2,▲:3,△:4)\n");
            scanf_s("%d", (const char *) &car);
            for (i = 1; i <= HEIGHT; i++) {
                for (j = 1; j <= WIDTH; j++) {
                    if (board[i][j] == car) {
                        x = i;
                        y = j;
                    }
                }
            }
            if (is_vertical(car) == 0) 	printf("どの方向に動かしますか？（←:1,→:2,キャンセル:0)\n");
            else if (is_vertical(car) == 1) printf("どの方向に動かしますか？（↑:1,↓:2,キャンセル:0)\n");
            scanf_s("%d", (const char *) &op);
            if (op == 0) {
                break;
            }
            if (check_op(car, op, board) == 1) {
                change_board(car, op, board);
                break;
            }
            else if (check_op(car, op, board) == 0) {
                printf("その操作は無効です。\n");
                break;
            }
        }
    }
    print_board(board);
    printf("おめでとうございます。ゲームクリアです。\n");
    return 0;
}