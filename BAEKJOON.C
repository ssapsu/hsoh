#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int get_num,n=0;
	char score[80];
	int your_point=0,is_sequence=1;
	scanf("%d", &get_num);
	while (n < get_num)
	{
		scanf("%s", score);
		for (int j = 0; j < strlen(score); j++)
		{
			if (score[j] == 'O')
			{
				your_point += is_sequence;
				if (score[j] == score[j + 1])
					is_sequence++;
				else
					is_sequence = 1;
			}
		}
		printf("%d\n", your_point);
		your_point = 0;
		n++;
	}
	return 0;
}