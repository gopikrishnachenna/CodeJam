#include <stdio.h>
#define MAX_N 100
int n_test;
int n;
char ans[MAX_N + 9];

int main() {
	scanf("%d%d", &n_test, &n);
	for(int i_test = 1; i_test <= n_test; i_test++) {
		int same_pos = -1;
		int dif_pos = -1;
		char resp[1];
		for(int i = 1; i <= (n + 1) / 2; i++) {
			if(i % 4 == 1) {
				if(same_pos != -1) {
					printf("%d\n", same_pos);
					fflush(stdout);
					scanf("%s", resp);
					if(*resp != ans[same_pos]) {
						for(int j = 1; j <= n; j++) {
							if(ans[j] == '0') {
								ans[j] = '1';
							}
							else {
								ans[j] = '0';
							}
						}
					}
				}
				else {
					printf("1\n");
					fflush(stdout);
					scanf("%s", resp);
				}
				if(dif_pos != -1) {
					printf("%d\n", dif_pos);
					fflush(stdout);
					scanf("%s", resp);
					if(*resp != ans[dif_pos]) {
						for(int j = 1; j <= n / 2; j++) {
							char tmp = ans[j];
							tmp = ans[j];
							ans[j] = ans[n - j + 1];
							ans[n - j + 1] = tmp;
						}
					}
				}
				else {
					printf("1\n");
					fflush(stdout);
					scanf("%s", resp);
				}
			}
			printf("%d\n", i);
			fflush(stdout);
			scanf("%s", resp);
			ans[i] = *resp;
			printf("%d\n", n - i + 1);
			fflush(stdout);
			scanf("%s", resp);
			ans[n - i + 1] = *resp;
			if(ans[i] == ans[n - i + 1]) {
				same_pos = i;
			}
			else {
				dif_pos = i;
			}
		}
		ans[n + 1] = 0;
		printf("%s\n", ans + 1);
		fflush(stdout);
		scanf("%s", resp);
		if(*resp == 'N') {
			break;
		}
	}
	return 0;
}