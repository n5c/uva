/**
1:  1
2:  2: 4, 8, 16, 32, ...
    1: 
3:  3: 6, 12, 24, 48, ...
   10: 20, 40, 80, 160, ...
    5:
   16:
4:
5:
6:
7: 22: 44, 88, 176, ...
   11:
   34: 68, 136, 272, ...
   17:
   52: 104, 208, 316, ...
   26:
   13:
   40:
8:
9: ...
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 1000000

struct number {
	unsigned int prev; /* previous number */
	unsigned int clen; /* cycle length */
	unsigned int gnum; /* greater number with greater cycle length */
};

int main(int argc, char *argv[])
{
	struct number *nums;

	nums = calloc(1, (sizeof(*nums) * MAXINPUT));
	if (nums == NULL) {
		printf("can't alloc memory\n");
		exit(-1);
	}

	/* calculate the numbers' cycle length (from 1 till 999999) */
	unsigned int i, num, next;

	nums[1].clen = 1;
	for (i = 2; i < MAXINPUT; i++) {
		if (nums[i].clen != 0)
			continue;

		num = next = i;
		nums[num].clen = 1;

		do {
			if (next & 0x1)
				next = ((next * 3) + 1);
			else
				next = (next / 2);

			if (next >= MAXINPUT) {
				nums[num].clen++;
				continue;
			}

			nums[next].prev = num;
			num = next;

			if (nums[num].clen != 0)
				break;

			nums[num].clen = 1;

		} while(1);

		while (nums[num].prev != 0) {
			nums[nums[num].prev].clen += nums[num].clen;
			num = nums[num].prev;

			next = (num * 2);
			while (next < MAXINPUT) {
				if (nums[next].clen != 0)
					break;
				nums[next].clen = (nums[(next / 2)].clen + 1);
				next = (next * 2);
			}
		}
	}

	/* calculate greater numbers */
	for (i = (MAXINPUT - 2); i > 0; i--) {
		num = (i + 1);
		while (num != 0) {
			if (nums[num].clen > nums[i].clen) {
				nums[i].gnum = num;
				break;
			}
			num = nums[num].gnum;
		}
	}

	int input1, input2, min, max;
	while (scanf("%d %d", &input1, &input2) == 2) {
		if ((input1 <= 0) || (input1 >= MAXINPUT) ||
				(input2 <= 0) || (input2 >= MAXINPUT))
			break;

		min = num = input1;
		max = input2;
		if (input1 > input2) {
			min = num = input2;
			max = input1;
		}

		while (1) {
			if (nums[num].gnum == 0)
				break;
			if (nums[num].gnum > max)
				break;
			num = nums[num].gnum;
		}
		printf("%d %d %d\n", input1, input2, nums[num].clen);
	}

	free(nums);

	return 0;
}
