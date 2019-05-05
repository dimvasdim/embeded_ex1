#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
  FILE *fp;
  struct timeval tv;
  int samples,i;
  int useconds;

  if (argc != 3)
  {
      printf("Need two arguments to operate properly...\n");
      printf("The first one is the total time of sampling in seconds\n");
      printf("and the second is the interval between samples in seconds\n");
      exit(1);
  }

  int exec_time = atoi(argv[1]);
  float interval = atof(argv[2]);
  samples = exec_time/interval + 1;
  struct timeval *table = malloc(samples * sizeof(struct timeval));
  useconds = (int) 1000000 * interval;
  printf("Number of samples is: %d\n", samples);
  printf("useconds: %d\n", useconds);

  for (i=0; i<samples; i++)
  {
      gettimeofday(&tv, NULL);
      table[i] = tv;
      usleep(useconds);
  }

  fp = fopen("timer1_res.csv", "w");
  if (fp == NULL)
  {
      printf("Could not open file");
      exit(1);
  }
  for (i=0; i<samples; i++)
  {
      fprintf(fp, "%ld,%ld\n", table[i].tv_sec, table[i].tv_usec);
  }
  fclose(fp);

	tv.tv_sec = table[samples-1].tv_sec - table[0].tv_sec;
	tv.tv_usec = table[samples-1].tv_usec - table[0].tv_usec;
	if (tv.tv_usec < 0)
	{
		tv.tv_sec = (tv.tv_sec*1000000 + tv.tv_usec)/1000000;
		tv.tv_usec = 1000000 + tv.tv_usec;
	}
	printf("Total time : %ld sec, %ld usec\n",tv.tv_sec, tv.tv_usec);
	printf("Time[0] : %ld sec, %ld usec\n",table[0].tv_sec, table[0].tv_usec);
	i = samples-1;
	printf("Time[%d] : %ld sec, %ld usec\n",i,table[i].tv_sec, table[i].tv_usec);

  free(table);
  return 0;

}
