#include <stdio.h>
#include <Windows.h>
#include <thread>
#include <conio.h>

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

char m[3] = "00", s[3] = "00", ms[3] = "00";
bool timerEnable = false;
void timerFunc()
{
	while (timerEnable)
	{
		int mi, si, msi;

		mi = (m[0] - '0') * 10 + m[1] - '0';
		si = (s[0] - '0') * 10 + s[1] - '0';
		msi = (ms[0] - '0') * 10 + ms[1] - '0';

		if (msi < 100)
		{
			msi++;
		}
		else
		{
			msi = 0;

			if (si < 60)
			{
				si++;
			}
			else
			{
				si = 0;
				mi++;
			}
		}

		m[0] = mi / 10 + '0';
		m[1] = mi % 10 + '0';
		s[0] = si / 10 + '0';
		s[1] = si % 10 + '0';
		ms[0] = msi / 10 + '0';
		ms[1] = msi % 10 + '0';

		gotoxy(7, 12);
		printf("%s : %s.%s", m, s, ms);
		Sleep(10);
	}
}

char cards[16][3] = { 0, };

void randSet()
{
	int fin = 0, pair1, pair2;
	srand(time(NULL));

	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "☆");
	strcpy(cards[pair2], "☆");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "★");
	strcpy(cards[pair2], "★");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "◇");
	strcpy(cards[pair2], "◇");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "◆");
	strcpy(cards[pair2], "◆");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "♤");
	strcpy(cards[pair2], "♤");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "♠");
	strcpy(cards[pair2], "♠");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "♡");
	strcpy(cards[pair2], "♡");
	do
	{
		pair1 = rand() % 16;
		pair2 = rand() % 16;
	} while (pair1 == pair2 || cards[pair1][0] != 0 || cards[pair2][0] != 0);
	strcpy(cards[pair1], "♥");
	strcpy(cards[pair2], "♥");
}

int turnCard(int fin)
{
	char inp1, inp2;
	char val1[3], val2[3];

	inp1 = getch();
	switch (inp1)
	{
	case '1':
		gotoxy(2, 1);
		strcpy(val1, cards[0]);
		break;
	case '2':
		gotoxy(8, 1);
		strcpy(val1, cards[1]);
		break;
	case '3':
		gotoxy(14, 1);
		strcpy(val1, cards[2]);
		break;
	case '4':
		gotoxy(20, 1);
		strcpy(val1, cards[3]);
		break;
	case 'q':
		gotoxy(2, 4);
		strcpy(val1, cards[4]);
		break;
	case 'w':
		gotoxy(8, 4);
		strcpy(val1, cards[5]);
		break;
	case 'e':
		gotoxy(14, 4);
		strcpy(val1, cards[6]);
		break;
	case 'r':
		gotoxy(20, 4);
		strcpy(val1, cards[7]);
		break;
	case 'a':
		gotoxy(2, 7);
		strcpy(val1, cards[8]);
		break;
	case 's':
		gotoxy(8, 7);
		strcpy(val1, cards[9]);
		break;
	case 'd':
		gotoxy(14, 7);
		strcpy(val1, cards[10]);
		break;
	case 'f':
		gotoxy(20, 7);
		strcpy(val1, cards[11]);
		break;
	case 'z':
		gotoxy(2, 10);
		strcpy(val1, cards[12]);
		break;
	case 'x':
		gotoxy(8, 10);
		strcpy(val1, cards[13]);
		break;
	case 'c':
		gotoxy(14, 10);
		strcpy(val1, cards[14]);
		break;
	case 'v':
		gotoxy(20, 10);
		strcpy(val1, cards[15]);
		break;
	default:
		return fin;
	}
	printf("%s", val1);

	RE:
	do
	{
		inp2 = getch();
	} while (inp1 == inp2);

	switch (inp2)
	{
	case '1':
		gotoxy(2, 1);
		strcpy(val2, cards[0]);
		break;
	case '2':
		gotoxy(8, 1);
		strcpy(val2, cards[1]);
		break;
	case '3':
		gotoxy(14, 1);
		strcpy(val2, cards[2]);
		break;
	case '4':
		gotoxy(20, 1);
		strcpy(val2, cards[3]);
		break;
	case 'q':
		gotoxy(2, 4);
		strcpy(val2, cards[4]);
		break;
	case 'w':
		gotoxy(8, 4);
		strcpy(val2, cards[5]);
		break;
	case 'e':
		gotoxy(14, 4);
		strcpy(val2, cards[6]);
		break;
	case 'r':
		gotoxy(20, 4);
		strcpy(val2, cards[7]);
		break;
	case 'a':
		gotoxy(2, 7);
		strcpy(val2, cards[8]);
		break;
	case 's':
		gotoxy(8, 7);
		strcpy(val2, cards[9]);
		break;
	case 'd':
		gotoxy(14, 7);
		strcpy(val2, cards[10]);
		break;
	case 'f':
		gotoxy(20, 7);
		strcpy(val2, cards[11]);
		break;
	case 'z':
		gotoxy(2, 10);
		strcpy(val2, cards[12]);
		break;
	case 'x':
		gotoxy(8, 10);
		strcpy(val2, cards[13]);
		break;
	case 'c':
		gotoxy(14, 10);
		strcpy(val2, cards[14]);
		break;
	case 'v':
		gotoxy(20, 10);
		strcpy(val2, cards[15]);
		break;
	default:
		goto RE;
	}
	printf("%s", val2);

	if (!strcmp(val1, val2))
	{
		return fin + 1;
	}
	else
	{
		Sleep(1000);

		switch (inp1)
		{
		case '1':
			gotoxy(2, 1);
			printf(" 1");
			break;
		case '2':
			gotoxy(8, 1);
			printf(" 2");
			break;
		case '3':
			gotoxy(14, 1);
			printf(" 3");
			break;
		case '4':
			gotoxy(20, 1);
			printf(" 4");
			break;
		case 'q':
			gotoxy(2, 4);
			printf("Q ");
			break;
		case 'w':
			gotoxy(8, 4);
			printf("W ");
			break;
		case 'e':
			gotoxy(14, 4);
			printf("E ");
			break;
		case 'r':
			gotoxy(20, 4);
			printf("R ");
			break;
		case 'a':
			gotoxy(2, 7);
			printf(" A");
			break;
		case 's':
			gotoxy(8, 7);
			printf(" S");
			break;
		case 'd':
			gotoxy(14, 7);
			printf(" D");
			break;
		case 'f':
			gotoxy(20, 7);
			printf(" F");
			break;
		case 'z':
			gotoxy(2, 10);
			printf("Z ");
			break;
		case 'x':
			gotoxy(8, 10);
			printf("X ");
			break;
		case 'c':
			gotoxy(14, 10);
			printf("C ");
			break;
		case 'v':
			gotoxy(20, 10);
			printf("V ");
			break;
		}
		switch (inp2)
		{
		case '1':
			gotoxy(2, 1);
			printf(" 1");
			break;
		case '2':
			gotoxy(8, 1);
			printf(" 2");
			break;
		case '3':
			gotoxy(14, 1);
			printf(" 3");
			break;
		case '4':
			gotoxy(20, 1);
			printf(" 4");
			break;
		case 'q':
			gotoxy(2, 4);
			printf("Q ");
			break;
		case 'w':
			gotoxy(8, 4);
			printf("W ");
			break;
		case 'e':
			gotoxy(14, 4);
			printf("E ");
			break;
		case 'r':
			gotoxy(20, 4);
			printf("R ");
			break;
		case 'a':
			gotoxy(2, 7);
			printf(" A");
			break;
		case 's':
			gotoxy(8, 7);
			printf(" S");
			break;
		case 'd':
			gotoxy(14, 7);
			printf(" D");
			break;
		case 'f':
			gotoxy(20, 7);
			printf(" F");
			break;
		case 'z':
			gotoxy(2, 10);
			printf("Z ");
			break;
		case 'x':
			gotoxy(8, 10);
			printf("X ");
			break;
		case 'c':
			gotoxy(14, 10);
			printf("C ");
			break;
		case 'v':
			gotoxy(20, 10);
			printf("V ");
			break;
		}
	}

	return fin;
}

int main()
{
	system("title Cards");
	system("mode con:cols=24 lines=13");
	printf("┏━┓┏━┓┏━┓┏━┓");
	printf("┃ 1┃┃ 2┃┃ 3┃┃ 4┃");
	printf("┗━┛┗━┛┗━┛┗━┛");
	printf("┏━┓┏━┓┏━┓┏━┓");
	printf("┃Q ┃┃W ┃┃E ┃┃R ┃");
	printf("┗━┛┗━┛┗━┛┗━┛");
	printf("┏━┓┏━┓┏━┓┏━┓");
	printf("┃ A┃┃ S┃┃ D┃┃ F┃");
	printf("┗━┛┗━┛┗━┛┗━┛");
	printf("┏━┓┏━┓┏━┓┏━┓");
	printf("┃Z ┃┃X ┃┃C ┃┃V ┃");
	printf("┗━┛┗━┛┗━┛┗━┛");

	randSet();
	//FILE *fp = fopen("answer.txt", "w");
	//for (int i = 0; i < 15; i++)
	//{
	//	fprintf(fp, "%s ", cards[i]);
	//}
	//fclose(fp);

	timerEnable = true;
	std::thread timer(&timerFunc);

	int fin = 0;
	while (fin < 8)
	{
		fin = turnCard(fin);
	}
	timerEnable = false;
	timer.join();

	system("cls");

	char conf;
	gotoxy(0, 4);
	printf("    RECORD : %s:%s.%s\n\n", m, s, ms);
	printf("    Do you want to\n save your record?(y/n)");
	do
	{
		conf = getche();
	} while (conf != 'y' && conf != 'n');
	if (conf == 'y')
	{
		system("sendOutlookMail.exe");
	}

	return 0;
}
