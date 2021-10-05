#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
/* The begin of initial data */
long nslv;
long na = 4;
long nb = 3;
long ia[4] = { 10, 3, 7, 4 };
long ib[3] = { 5, 4, 10 };
double an[4] = { 0.2, 0.3, 0.4, -0.7 };
double bn[3] = { 0.6, 0.7, 0.5 };
/* The end of initial data */
long nc;
long ic[100];
double cn[100];
long ip[100000];
double a[100000], b[100000], c[100000];

//void slv();
void slv_standard();

long ts, te, tsm, tem;
double tsd, ted, dt;
struct _timeb tstruct;

int main()
{
    long i, ii, iii;
    for (i = 0; i < 100000; i++)
        ip[i] = -1;

    printf("\n");
    printf("this is initial data - ia  ib  an  bn  :\n");
    for (i = 0; i < na; i++)
        printf("%3d", ia[i]);
    printf("\n");
    for (i = 0; i < nb; i++)
        printf("%3d", ib[i]);
    printf("\n");
    for (i = 0; i < na; i++)
        printf("%15.7e", an[i]);
    printf("\n");
    for (i = 0; i < nb; i++)
        printf("%15.7e", bn[i]);
    printf("\n");
    printf("verify initial data and press Enter to return\n");
    getchar();

    a[10] = 0.2;
    a[3] = 0.3;
    a[7] = 0.4;
    a[4] = -0.7;
    b[5] = 10.6;
    b[4] = 0.7;
    b[10] = 0.5;

    nslv = 10;
    printf("chislo slozhenii vektorov =%d \n", nslv);
    _ftime(&tstruct);
    ts = tstruct.time;
    tsm = tstruct.millitm;
    tsd = (double)ts;
    tsd = tsd * 1000.0 + (double)tsm;

    for (ii = 0; ii < nslv; ii++) {
        slv_standard(an, ia, bn, ib, cn, ic, na, nb, &nc);
    }

    _ftime(&tstruct);
    te = tstruct.time;
    tem = tstruct.millitm;
    ted = (double)te;
    ted = ted * 1000.0 + (double)tem;
    dt = ted - tsd;
    printf("delta time = %e\n", dt);
    printf("write delta time in report and press Enter to return\n");
    getchar();
    printf("this is initial data - ia  ib  an  bn  :\n");
    for (i = 0; i < na; i++)
        printf("%3d", ia[i]);
    printf("\n");
    for (i = 0; i < nb; i++)
        printf("%3d", ib[i]);
    printf("\n");
    for (i = 0; i < na; i++)
        printf("%15.7e", an[i]);
    printf("\n");
    for (i = 0; i < nb; i++)
        printf("%15.7e", bn[i]);
    printf("\n");
    printf("this is rezults - nc   ic   cn  :\n");
    printf("%3d", nc);
    printf("\n");
    for (i = 0; i < nc; i++)
        printf("%3d", ic[i]);
    printf("\n");
    for (i = 0; i < nc; i++)
        printf("%15.7e", cn[i]);
    printf("\n");
    printf("verify rezults and press Enter to return\n");
    getchar();
    return 0;
}
void slv_standard(an, ia, bn, ib, cn, ic, na, nb, nc) long na, nb;
long* nc;
double an[], bn[], cn[];
long ia[], ib[], ic[];
{
    //standart program
    //1 shag algoritma
    register i, j, k, m;
    for (i = 0; i < na; i++) {
        cn[i] = an[i];
        ic[i] = ia[i];
    }
    *nc = na;
    //2 shag algoritma
    //Vash kod

    for (j = 0; j < nb; j++) {
        m = 0;

        for (k = 0; k < na; k++) {
            if (m == 1)
                break;
            if (ia[k] == ib[j]) {
                cn[k] = an[k] + bn[j];
                m = 1;
            }
        }

        if (m == 0) {
            cn[*nc] = bn[j];
            ic[*nc] = ib[j];
            *nc = *nc + 1;
        }
    }

    return;
}
