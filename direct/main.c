#include <stdio.h>
#include <time.h>

char ans[1000000];
int at = 0;

void printInt(int x) {
    if (x >= 100) {
        int i = x / 100;
        ans[at++] = (i + '0');
        x -= i * 100;
        i = x / 10;
        ans[at++] = (i + '0');
        x -= i * 10;
    } else if (x >= 10) {
        int i = x / 10;
        ans[at++] = (i + '0');
        x -= i * 10;
    }
    ans[at++] = (x + '0');
}

int m[700 * 700];

char buffer[4096];
int bAt = 0;
int limit = 0;

int isspace(int ch) {
    return ch < '0' || ch > '9';
}

int getch() {
    while (bAt >= limit) {
        limit = fread(buffer, 1, 4096, stdin);
        bAt = 0;
    }
    if (limit == 0) {
        return -1;
    }
    return buffer[bAt++];
}

int readInt() {
    int x = 0;
    int ch;
    while (isspace(ch = getch()));
    do {
        if (ch == -1) {
            return 0;
        }
        x *= 10;
        x += ch - '0';
    } while (!isspace(ch = getch()));
    return x;
}

int main() {
#ifdef LOCAL
    freopen("gen.out", "r", stdin);
    int time = clock();
#endif
    int f = readInt();
    int c = readInt();
    for (int i = 0; i < f * c; i++) {
        m[i] = readInt();
    }
#ifdef LOCAL
    fprintf(stderr, "Read = %d\n", clock() - time);
    time = clock();
#endif

    int row = 0;
    int col;
    for (int i = 0; ; i++) {
        if (m[i] == 1) {
            col = i;
            break;
        }
    }
    int pos = col;
    int qty = 0;
    char last = 0;
    int next = 2;
    while (1) {
        char ndir;
        if (row != f - 1 && m[pos + c] == next) {
            ndir = 'D';
            pos += c;
            row++;
        } else if (col != c - 1 && m[pos + 1] == next) {
            ndir = 'R';
            pos++;
            col++;
        } else if (row != 0 && m[pos - c] == next) {
            ndir = 'U';
            pos -= c;
            row--;
        } else if (col != 0 && m[pos - 1] == next) {
            ndir = 'L';
            pos--;
            col--;
        } else {
            break;
        }
        if (ndir != last) {
            if (qty > 0) {
                printInt(qty);
                ans[at++] = (last);
            }
            last = ndir;
            qty = 1;
        } else {
            qty++;
        }
        next++;
    }
    if (qty > 0) {
        printInt(qty);
        ans[at++] = (last);
        ans[at++] = ' ';
    }
    if (row != 0 && row != f - 1 && col != 0 && col != c - 1) {
        ans[at++] = 'N';
    }
    ans[at++] = 'E';
    ans[at++] = '\n';
#ifdef LOCAL
    fprintf(stderr, "Work = %d\n", clock() - time);
    time = clock();
#endif
    fwrite(ans, 1, at, stdout);
#ifdef LOCAL
    fprintf(stderr, "Write = %d\n", clock() - time);
#endif
    return 0;
}
