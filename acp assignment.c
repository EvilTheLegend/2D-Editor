#include <stdio.h>
#include <math.h>

#define ROWS 40
#define COLS 80
#define MAX 10

#define LINE      1
#define RECTANGLE 2
#define TRIANGLE  3
#define CIRCLE    4

char a[ROWS][COLS];

struct Object {
    int type;
    int p[6];
};

struct Object objects[MAX];
int num = 0;

void clearCanvas() {
    int i, j;
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            a[i][j] = '_';
}

void display() {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++)
            printf("%c", a[i][j]);
        printf("\n");
    }
}

/* ── Draw functions ───────────────────────────────────────────── */

void drawLine(int row) {
    int i;
    for (i = 0; i < COLS; i++)
        a[row][i] = '*';
}

void drawRectangle(int r, int c, int h, int w) {
    int i, j;
    for (i = r; i < r+h && i < ROWS; i++)
        for (j = c; j < c+w && j < COLS; j++)
            if (i==r || i==r+h-1 || j==c || j==c+w-1)
                a[i][j] = '*';
}

void drawTriangle(int r, int c, int h) {
    int i, j;
    for (i = 0; i < h; i++)
        for (j = 0; j <= i; j++)
            if (r+i < ROWS && c+j < COLS)
                a[r+i][c+j] = '*';
}

void drawCircle(int cx, int cy, int r) {
    int i, j;
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++) {
            int dx = i-cx, dy = j-cy;
            if ((int)round(sqrt(dx*dx + dy*dy)) == r)
                a[i][j] = '*';
        }
}

/* ── Render all objects ───────────────────────────────────────── */

void render() {
    int i;
    clearCanvas();
    for (i = 0; i < num; i++) {
        int *p = objects[i].p;
        switch (objects[i].type) {
            case LINE:      drawLine(p[0]);                     break;
            case RECTANGLE: drawRectangle(p[0],p[1],p[2],p[3]); break;
            case TRIANGLE:  drawTriangle(p[0],p[1],p[2]);       break;
            case CIRCLE:    drawCircle(p[0],p[1],p[2]);         break;
        }
    }
}

/* ── List objects ─────────────────────────────────────────────── */

void listObjects() {
    int i;
    if (num == 0) { printf("No objects.\n"); return; }
    for (i = 0; i < num; i++) {
        int *p = objects[i].p;
        printf("%d: ", i+1);
        switch (objects[i].type) {
            case LINE:      printf("line      row=%d\n", p[0]); break;
            case RECTANGLE: printf("rectangle row=%d col=%d h=%d w=%d\n", p[0],p[1],p[2],p[3]); break;
            case TRIANGLE:  printf("triangle  row=%d col=%d h=%d\n", p[0],p[1],p[2]); break;
            case CIRCLE:    printf("circle    cx=%d cy=%d r=%d\n", p[0],p[1],p[2]); break;
        }
    }
}

/* ── Add ──────────────────────────────────────────────────────── */

void addObject() {
    int type;
    int *p;
    if (num >= MAX) { printf("Max objects reached.\n"); return; }
    printf("Shape (1=Line 2=Rectangle 3=Triangle 4=Circle): ");
    scanf("%d", &type);
    objects[num].type = type;
    p = objects[num].p;
    switch (type) {
        case LINE:
            printf("Enter row: ");
            scanf("%d", &p[0]);
            break;
        case RECTANGLE:
            printf("Enter row col height width: ");
            scanf("%d %d %d %d", &p[0],&p[1],&p[2],&p[3]);
            break;
        case TRIANGLE:
            printf("Enter row col height: ");
            scanf("%d %d %d", &p[0],&p[1],&p[2]);
            break;
        case CIRCLE:
            printf("Enter center row col radius: ");
            scanf("%d %d %d", &p[0],&p[1],&p[2]);
            break;
        default:
            printf("Invalid shape.\n");
            return;
    }
    num++;
    render();
    printf("Added as object %d.\n", num);
}

/* ── Delete ───────────────────────────────────────────────────── */

void deleteObject() {
    int n, i;
    listObjects();
    printf("Delete which number? ");
    scanf("%d", &n);
    n--;
    if (n < 0 || n >= num) { printf("Invalid.\n"); return; }
    for (i = n; i < num-1; i++)
        objects[i] = objects[i+1];
    num--;
    render();
    printf("Deleted.\n");
}

/* ── Modify ───────────────────────────────────────────────────── */

void modifyObject() {
    int n;
    int *p;
    listObjects();
    printf("Modify which number? ");
    scanf("%d", &n);
    n--;
    if (n < 0 || n >= num) { printf("Invalid.\n"); return; }
    p = objects[n].p;
    switch (objects[n].type) {
        case LINE:
            printf("New row: ");
            scanf("%d", &p[0]);
            break;
        case RECTANGLE:
            printf("New row col height width: ");
            scanf("%d %d %d %d", &p[0],&p[1],&p[2],&p[3]);
            break;
        case TRIANGLE:
            printf("New row col height: ");
            scanf("%d %d %d", &p[0],&p[1],&p[2]);
            break;
        case CIRCLE:
            printf("New center row col radius: ");
            scanf("%d %d %d", &p[0],&p[1],&p[2]);
            break;
    }
    render();
    printf("Modified.\n");
}

/* ── Main ─────────────────────────────────────────────────────── */

int main() {
    int ch;
    clearCanvas();
    do {
        printf("\n--- 2D Graphics Editor ---\n");
        printf("1. Add object\n");
        printf("2. Delete object\n");
        printf("3. Modify object\n");
        printf("4. List objects\n");
        printf("5. Display canvas\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: addObject();    break;
            case 2: deleteObject(); break;
            case 3: modifyObject(); break;
            case 4: listObjects();  break;
            case 5: display();      break;
            case 6: printf("Bye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 6);
    return 0;
}