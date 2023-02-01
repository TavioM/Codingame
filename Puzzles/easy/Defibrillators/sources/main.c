#include "file.h"

int main()
{
	int		N;
	char	LON[51];
	char	LAT[51];
	
	scanf("%s", LON);
	scanf("%s", LAT);
	scanf("%d", &N);
	fgetc(stdin);
	for (int i = 0; i < N; i++)
	{
		char	DEFIB[257];
		scanf("%[^\n]", DEFIB);
		fgetc(stdin);
	}
	printf("answer\n");
	return 0;
}
