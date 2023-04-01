#include <stdio.h>
#include <stdlib.h>

char rock_paper_scissors(char a, char b) {
    if ((a == 'R' && b == 'P') || (a == 'P' && b == 'R')) return 'P';
    if ((a == 'R' && b == 'S') || (a == 'S' && b == 'R')) return 'R';
    if ((a == 'S' && b == 'P') || (a == 'P' && b == 'S')) return 'S';
    return a;
}

void stage_one(FILE* path, FILE* output) {
    int n;
    fscanf(path, "%d\n", &n);

    for (unsigned int i = 0; i < n; i++) {
        char c1, c2;
        fscanf(path, "%c%c\n", &c1, &c2);
        fprintf(output, "%c\n", rock_paper_scissors(c1, c2));
    }
}

void stage_two(FILE* path, FILE* output) {
    int n, m;

    fscanf(path, "%d ", &n);
    fscanf(path, "%d\n", &m);

    char* s = (char*) malloc(m);
    char* aux = (char*) malloc(m/4);

    for (unsigned int j = 0; j < n; j++) {
        fscanf(path, "%s", s);

        for (unsigned int i = 0; i < m; i += 2) {
            s[i/2] = rock_paper_scissors(s[i], s[i + 1]);
        }

        if (m != 2) {
            for (unsigned int i = 0; i < m / 2; i += 2) {
                aux[i/2] = rock_paper_scissors(s[i], s[i + 1]);
            }
        }
        fprintf(output, "%s\n", aux);
    }
}

int min(unsigned int a, unsigned int b) {
    if (a < b) return a;
    return b;
}

void stage_three(FILE* path, FILE* output) {
    int n, m, counter;
    unsigned int rocks, papers, scissors;
    char c;
    fscanf(path, "%d ", &n);
    fscanf(path, "%d\n", &m);

    char* s = (char*) malloc(m);
    counter = 0;

    fscanf(path, "%d%c %d%c %d%c", &rocks, &c, &papers, &c, &scissors, &c);
    if (rocks <= papers) {
        for (unsigned int i = 0; i < rocks; i++) {
            s[counter] = 'R';
            counter++;
        }
        for (unsigned int i = 0; i < papers; i++) {
            s[counter] = 'P';
            counter++;
        }
        for (unsigned int i = 0; i < scissors; i++) {
            s[counter] = 'S';
            counter++;
        }
        fprintf(output, "%s\n", s);
        return;
    }

    if (rocks != 0 && papers != 0) {
        s[0] = 'R';
        s[1] = 'P';
        rocks--;
        papers--;
        counter += 2;
    }

    for (unsigned int i = 0; i < rocks/2; i++) {
        s[counter] = 'R';
        s[counter + 1] = 'R';
        counter += 2;
    }

    rocks = rocks % 2;

    if (rocks != 0 && papers != 0) {
        s[counter] = 'R';
        s[counter + 1] = 'P';
        rocks--;
        papers--;
        counter += 2;
    }

    for (unsigned int i = 0; i < papers; i++) {
        s[2 * counter] = 'P';
        counter++;
    }

    for (int i = 0; i < scissors; i++) {
        s[counter] = 'S';
        counter++;
    }
    fprintf(output, "%s\n", s);
}

int main() {
    FILE* path = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w+");

    stage_three(path, output);
    fclose(path);
    fclose(output);
    return 0;
}
