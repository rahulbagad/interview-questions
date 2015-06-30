

#include <stdio.h>
#include <assert.h>

struct array_node {
	int value;
	struct array_node *up;
	struct array_node *down;
	struct array_node *top;
};

static void merge_stacks(struct array_node *below, struct array_node *above) {
	if (below->up == NULL) {
		below->up = above;
	} else {
		assert(below->down == NULL);
		below->down = above;
	}

	if (above->up == NULL) {
		above->up = below;
	} else {
		assert(above->down == NULL);
		above->down = below;
	}
}

void fold(struct array_node arr[], const char cmds[], size_t cmds_sz) {

	size_t beg = 0;
	size_t arr_sz = 1 << cmds_sz;
	size_t len = arr_sz;

	size_t i;
	for (i = 0; i < cmds_sz; i++) {
		size_t j, k;
		for (j = beg, k = beg+arr_sz-1; j < beg+arr_sz/2; j++, k--) {
			if (cmds[i] == 'L') {
				merge_stacks(arr[k].top, arr[j].top);
				arr[k].top = &arr[j];
			} else if (cmds[i] == 'R') {
				merge_stacks(arr[j].top, arr[k].top);
				arr[j].top = &arr[k];
			} else {
				assert(0);
			}
		}

		arr_sz /= 2;

		if (cmds[i] == 'L') {
			beg += arr_sz;
		}
	}

	assert(arr_sz == 1);

	struct array_node *curr = arr[beg].top;
	struct array_node *prev = NULL;
	struct array_node *next;

	for (i = 0; i < len; i++) {
		printf("%d ", curr->value);
		if (curr->up == NULL || curr->up == prev) {
			next = curr->down;
		} else {
			next = curr->up;
		}
		prev = curr;
		curr = next;
	}

	printf("\n");
}

int main(void) {
	printf("Enter N followed by the sequence of commands.\n");
	printf("> ");

	size_t n;
	while (scanf("%zu", &n) == 1) {
		struct array_node values[1 << n];

		size_t i;
		for (i = 0; i < (1 << n); i++) {
			values[i].value = i+1;
			values[i].top = &values[i];
			values[i].up = values[i].down = NULL;
		}

		char cmds[n];
		for (i = 0; i < n; i++) {
			scanf(" %c", &cmds[i]);
		}

		fold(values, cmds, n);
		printf("> ");
	}

	return 0;
}