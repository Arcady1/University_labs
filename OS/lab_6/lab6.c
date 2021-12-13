#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>

typedef void (*sighandler)(int);

void brake(int);
int is_win();

jmp_buf pos;
static char *dice[] = {"|\b", "/\b", "-\b", "\\\b"};
static char *dice_values[] = {"1\n", "2\n", "3\n", "4\n", "5\n", "6\n"};
static int result[2] = {0, 0};
static char digit[3];
static char *who[] = {"First player: ", "Second player: ", "Bye.\n"};
int dice_index = 0;
int dice_value = 0;

int main(int argc, char **argv)
{
	int j = 0;
	digit[0] = '1' + getpid() % 6;
	digit[1] = '\b';
	digit[2] = '\n';
	signal(SIGINT, (sighandler)brake);
	j = sigsetjmp(pos, 1);

	if (j < 4)
	{
		write(STDOUT_FILENO, who[(j < 2 ? 0 : 1)], strlen(who[(j < 2 ? 0 : 1)]));
		for (;;)
		{
			dice_index = (dice_index == 4) ? 0 : dice_index;
			dice_value = rand() % 6;
			write(STDOUT_FILENO, dice[dice_index++], 2);
			usleep(50000);
		}
	}
	signal(SIGINT, SIG_DFL);
	if (is_win() == 0)
	{
		write(STDOUT_FILENO, "First player win\n", 17);
	}
	if (is_win() == 1)
	{
		write(STDOUT_FILENO, "Second player win\n", 18);
	}
	if (is_win() == -1)
	{
		write(STDOUT_FILENO, "Players have the same number of points\n", 39);
	}

	exit(0);
}

int is_win()
{
	if (result[0] > result[1])
	{
		return 0;
	}
	else
	{
		if (result[0] < result[1])
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
}

void brake(int c)
{
	static int j = 0;

	dice_index = (dice_index == 4) ? 0 : dice_index;
	dice_value = rand() % 6;
	write(STDOUT_FILENO, dice_values[dice_value], strlen(dice_values[dice_value]));

	int res = atoi(dice_values[dice_value]);

	result[(j < 2 ? 0 : 1)] = res + result[(j < 2 ? 0 : 1)];
	printf("%d player's current amount = %d\n", ((j < 2 ? 0 : 1) + 1), result[(j < 2 ? 0 : 1)]);
	siglongjmp(pos, ++j);
}
