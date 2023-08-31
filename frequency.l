%%
.|\n;
%%

int yywrap() {return 1;}

int main() {
    char target[100], word[100];
    int count = 0;

    printf("Enter target word: ");
    scanf("%s", target);

    printf("Enter words (Ctrl+D to stop):\n");
    while (scanf("%s", word) != EOF) {
        if (strcmp(target, word) == 0)
            count++;
    }

    printf("Frequency of '%s': %d\n", target, count);
    return 0;
}
