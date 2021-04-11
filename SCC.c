//強連結成分分解

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5 //頂点数
#define push(a) ((L[sp++] = (a)))
#define pop() (L[--sp])

int count;           //カウンタ
int dfsnum[N];       //v以前に訪問した頂点数
int low[N];          //vの部分木から後退辺か交差辺で到達可能な頂点の最小dfsnum，そのような辺がない→low[v]=dfsnum[v]
int A[N + 1][N + 1]; //隣接行列
int T[N + 1][N + 1]; //有向木T
int L[100], sp = 0;  //訪問中の頂点を保持するためのスタック

// 引数の小さい方を返す
int min(int a, int b);

//強連結成分分解関数
void SCC();
void visit(int p);

int main()
{
    unsigned int seed;

    /* 現在時刻を元に seed を決定*/
    seed = (unsigned)time(NULL);
    srand(seed);

    // 隣接行列Aを作成する
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 2;
        }
    }

    // int edge = 0;
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         if (A[i][j] == 1)
    //             edge++;
    //     }
    // }
    // printf("辺：%d\n", edge);

    // clock_t start, end;
    // start = clock();
    SCC();
    // end = clock();
    // printf("%.2f秒かかりました\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

// 引数の小さい方を返す
int min(int a, int b)
{
    return a < b ? a : b;
}

void SCC()
{
    //カウンタを0に初期化
    count = 0;

    //すべてのvに対して，辺x->vを持つ新しい頂点xを隣接行列Aに追加する
    int x = N;
    for (int i = 0; i < x; i++)
    {
        A[x][i] = 1;
    }
    visit(x);
}

void visit(int p)
{
    printf("%dに来ました\n", p);
    int i, q, v, j;
    push(p);
    dfsnum[p] = count++;
    low[p] = dfsnum[p];
    for (q = 0; q < N + 1; q++)
    {
        int flag = 0;
        if (A[p][q] == 1)
        { //全ての辺p->qについて
            for (i = 0; i < N + 1; i++)
            {
                if (T[i][q] == 1)
                {
                    //qが既にTに入っていたら，flag++しループを抜ける
                    flag++;
                    break;
                }
            }
            if (flag == 0)
            { //qが既にTに入っていなかったら，Tにp->qを追加
                T[p][q] = 1;
                visit(q);
                low[p] = min(low[p], low[q]);
            }
            else
            {
                low[p] = min(low[p], dfsnum[q]);
            }
        }
    }
    if (low[p] == dfsnum[p])
    {
        printf("%dに戻りました\n", p);
        printf("Component:");
        do
        {
            v = pop();
            printf(" %d", v);
            for (i = 0; i < N + 1; i++)
            { //隣接行列Aからvを削除
                A[i][v] = 0;
            }
        } while (v != p);
        printf("\n\n");
    }
}