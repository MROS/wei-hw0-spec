/* 可控制O上下左右，但仍有許多問題尚待解決
 * 例如一下子輸入好幾個指令，會等到後面好幾格才執行完，demo性質較重
 * 你會需要重寫大多數程式碼
 * */

#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <unistd.h>

int kbhit() {
	int ch = getch();
	if (ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, const char *argv[])
{
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	nodelay(stdscr, TRUE); // 若沒有nodelay，getch就會卡住等輸入，有開啟nodelay，則沒有輸入就會返回ERR

	int pos_x = 0, pos_y = 0;
	int dic_x = 1, dic_y = 0;
	while (1) {
		// 清除上次位置
		mvaddstr(pos_y, pos_x, " ");
		refresh();

		if (kbhit()) {
			int c;
			switch (c = getch()) {
				case 'w':
					dic_x = 0;
					dic_y = -1;
					break;
				case 's':
					dic_x = 0;
					dic_y = 1;
					break;
				case 'a':
					dic_x = -1;
					dic_y = 0;
					break;
				case 'd':
					dic_x = 1;
					dic_y = 0;
					break;
			}
		}
		pos_x += dic_x;
		pos_y += dic_y;

		mvaddstr(pos_y, pos_x, "O");
		refresh();
		sleep(1);
	}
	endwin();

	return 0;
}
