#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tot, frameCount, pageCount, counter, flag1, flag2, flag3, pos, max, faults;
int frames[10], pages[20], temp[10], timer[10], i, j, k;
int findLRU(int timer[], int n);
void algLRU();
void algOPR();

int main() {
  tot = 20;
  pageCount = 5;
  counter = 0;
  faults = 0;

  srand(time(NULL));

	printf("Enter number of frames: ");
	scanf("%d", &frameCount);

	printf("Enter reference string: ");
  for (int n = 0; n < tot; n++) {
    pages[n] = (rand() %5) + 1;
    printf("%d", pages[n]);
    printf(" ");
  }

  printf("LRU Algoritm: \n");
  algLRU();

  faults = 0;

  printf("OPR Algotithm: \n");
  algOPR();

  return 0;
}

void algLRU() {
  for(i = 0; i < frameCount; ++i) {
    frames[i] = -1;
  }

  for(i = 0; i < pageCount; ++i) {
    flag1 = flag2 = 0;

    for(j = 0; j < frameCount; ++j) {
    	if(frames[j] == pages[i]) {
	    	counter++;
	    	timer[j] = counter;
	   		flag1 = flag2 = 1;
	   		break;
   		}
    }

    if(flag1 == 0) {
			for(j = 0; j < frameCount; ++j) {
	    	if(frames[j] == -1) {
	    		counter++;
	    		faults++;
	    		frames[j] = pages[i];
	    		timer[j] = counter;
	    		flag2 = 1;
	    		break;
	    	}
    	}
    }

    if(flag2 == 0) {
    	pos = findLRU(timer, frameCount);
    	counter++;
    	faults++;
    	frames[pos] = pages[i];
    	timer[pos] = counter;
    }

    printf("\n");

    for(j = 0; j < frameCount; ++j) {
    	printf("%d\t", frames[j]);
    }
	}

	printf("\n\nTotal Page Faults = %d", faults);
  printf("\n");
}

int findLRU(int timer[], int n) {
	int i, minimum = timer[0], pos = 0;

	for(i = 1; i < n; ++i) {
		if(timer[i] < minimum) {
			minimum = timer[i];
			pos = i;
		}
	}

	return pos;
}

void algOPR() {
  for(i = 0; i < frameCount; ++i) {
    frames[i] = -1;
  }

  for(i = 0; i < pageCount; ++i) {
    flag1 = flag2 = 0;

    for(j = 0; j < frameCount; ++j) {
      if(frames[j] == pages[i]) {
        flag1 = flag2 = 1;
        break;
      }
    }

    if(flag1 == 0){
      for(j = 0; j < frameCount; ++j) {
        if(frames[j] == -1) {
          faults++;
          frames[j] = pages[i];
          flag2 = 1;
          break;
        }
      }
    }

    if(flag2 == 0) {
      flag3 =0;

      for(j = 0; j < frameCount; ++j) {
        temp[j] = -1;

        for(k = i + 1; k < pageCount; ++k) {
          if(frames[j] == pages[k]) {
          	temp[j] = k;
          	break;
          }
        }
      }

      for(j = 0; j < frameCount; ++j) {
        if(temp[j] == -1) {
          pos = j;
          flag3 = 1;
          break;
        }
      }

      if(flag3 ==0) {
        max = temp[0];
        pos = 0;

        for(j = 1; j < frameCount; ++j) {
          if(temp[j] > max) {
          	max = temp[j];
          	pos = j;
          }
        }
      }

			frames[pos] = pages[i];
			faults++;
    }

    printf("\n");

    for(j = 0; j < frameCount; ++j) {
      printf("%d\t", frames[j]);
    }
  }

  printf("\n\nTotal Page Faults = %d", faults);
  printf("\n");
}
