#include <stdio.h>
#include <string.h>
#define MAX_N 100
int n_test;
int n;
char a[MAX_N + 9];
int n_ans;
char ans[MAX_N * 20 + 9];

int main() {
	scanf("%d", &n_test);
	for(int i_test = 1; i_test <= n_test; i_test++) {
		scanf("%s", a + 1);
		n = strlen(a + 1);
		n_ans = 0;
		int depth = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i] - '0' < depth) {
				for(int rep = 0; rep < depth - (a[i] - '0'); rep++) {
					n_ans++;
					ans[n_ans] = ')';
				}
			}
			else {
				for(int rep = 0; rep < a[i] - '0' - depth; rep++) {
					n_ans++;
					ans[n_ans] = '(';
				}
			}
			n_ans++;
			ans[n_ans] = a[i];
			depth = a[i] - '0';
		}
		for(int rep = 0; rep < depth; rep++) {
			n_ans++;
			ans[n_ans] = ')';
		}
		ans[n_ans + 1] = 0;
		printf("Case #%d: %s\n", i_test, ans + 1);
	}
	return 0;
}