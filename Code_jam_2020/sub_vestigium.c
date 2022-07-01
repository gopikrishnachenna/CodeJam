#include <stdio.h>
#include <string.h>
#define MAX_N 100
int n_test;
int n;
int a[MAX_N + 9][MAX_N + 9];
int ans1;
int ans2;
int ans3;
int used[MAX_N + 9];

int main() {
	scanf("%d", &n_test);
	for(int i_test = 1; i_test <= n_test; i_test++) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		ans1 = 0;
		for(int i = 1; i <= n; i++) {
			ans1 += a[i][i];
		}
		ans2 = 0;
		for(int i = 1; i <= n; i++) {
			memset(used, 0, sizeof(int) * (n + 1));
			int flag = 0;
			for(int j = 1; j <= n; j++) {
				if(!used[a[i][j]]) {
					used[a[i][j]] = 1;
				}
				else {
					flag = 1;
					break;
				}
			}
			if(flag) {
				ans2++;
			}
		}
		ans3 = 0;
		for(int j = 1; j <= n; j++) {
			memset(used, 0, sizeof(int) * (n + 1));
			int flag = 0;
			for(int i = 1; i <= n; i++) {
				if(!used[a[i][j]]) {
					used[a[i][j]] = 1;
				}
				else {
					flag = 1;
					break;
				}	
			}
			if(flag) {
				ans3++;
			}
		}
		printf("Case #%d: %d %d %d\n", i_test, ans1, ans2, ans3);
	}
}
