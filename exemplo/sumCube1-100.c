#include <stdio.h>
#include <stdlib.h>

#define cxmax 200
#define stacksize 500

enum fct {

    LIT,
    OPR,
    LOD,
    STO,
    CAL,
    INT,
    JMP,
    JPC

};

typedef struct {

    enum fct f;
    int l;
    int a;

}  instruction;

instruction code[ cxmax ];

int p, b, t;
int s[ stacksize ];


int base( int l ) {

    int b1;
    b1 = b;

    while( l > 0 ) {

        b1 = s[ b1 ];
        l = l - 1;

    }

    return b1;

}

int main() {

    /* simplified entry( representation )

    INT 0 6 (space)
    LIT 0 2 (contactor)
    STO 0 3 (move contactor)
    LIT 0 100(max interaction)
    STO 0 4 (move max intection)
    LIT 0 1 (inicial summation)
    STO 0 5 (move summation)
    LOD 0 3 (load contactor x)
    LOD 0 3 (load contactor x*x)
    LOD 0 3 (load contactor x*x*x)
    OPR 0 4 (mult)
    OPR 0 4 (mul)
    OPR 0 2 (sum)
    LOD 0 3 (load contactor)
    LOD 0 4 (load max)
    OPR 0 10 (counter less than summation ?)
    JPC 0 21 (Jump condition)
    LOD 0 3 (load contactor)
    OPR 0 2 (sum)
    STO 0 3 (add new contactor)
    JMP 0 7 (jump line seven)
    OPR 0 0 (return 0 - fim)

    */

        int index = 0;
        code[index].f = INT; code[index].l = 0; code[index].a = 6; index++;
        code[index].f = LIT; code[index].l = 0; code[index].a = 2; index++;
        code[index].f = STO; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = LIT; code[index].l = 0; code[index].a = 100; index++;
        code[index].f = STO; code[index].l = 0; code[index].a = 4; index++;
        code[index].f = LIT; code[index].l = 0; code[index].a = 1; index++;
        code[index].f = STO; code[index].l = 0; code[index].a = 5; index++;
        code[index].f = LOD; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = LOD; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = LOD; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = OPR; code[index].l = 0; code[index].a = 4; index++;
        code[index].f = OPR; code[index].l = 0; code[index].a = 4; index++;
        code[index].f = OPR; code[index].l = 0; code[index].a = 2; index++;
        code[index].f = LOD; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = LOD; code[index].l = 0; code[index].a = 4; index++;
        code[index].f = OPR; code[index].l = 0; code[index].a = 10; index++;
        code[index].f = JPC; code[index].l = 0; code[index].a = 21; index++;
        code[index].f = LOD; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = OPR; code[index].l = 0; code[index].a = 2; index++;
        code[index].f = STO; code[index].l = 0; code[index].a = 3; index++;
        code[index].f = JMP; code[index].l = 0; code[index].a = 7; index++;
        code[index].f = OPR; code[index].l = 0; code[index].a = 0; index++;

    instruction i;
    {

        t = 0;
        b = 1;
        p = 0;

        s[1] = 0;
        s[2] = 0;
        s[3] = 0;

        printf("\n| p  | b  | t  |      0    1    2    3    4    5    6     7" );
        printf("\n=============================================================" );

        do {

            i =  code[ p ];
            printf("\n| %2d | %2d | %2d | -> ", p, b, t );
            p = p + 1;

            switch ( i.f ) {

                case LIT:

                    t = t + 1;
                    s[ t ] = i.a;
                    break;

                case OPR:

                    switch( i.a ) {

                        // Return
                        case 0:

                            t = b - 1;
                            p = s[ t + 3 ];
                            b = s[ t + 2 ];
                            break;
                        // Negative
                        case 1:

                            s[ t ] = -s[ t ];
                            break;
                        // Sum
                        case 2:

                            t = t - 1;
                            s[ t ] = s[ t ] + s[t + 1];
                            break;
                        // Sub
                        case 3:
                            t = t - 1;
                            s[ t ] = s[ t ] - s[t + 1];
                            break;
                        // Mult
                        case 4:

                            t = t - 1;
                            s[ t ] = s[ t ] * s[ t + 1 ];
                            break;
                        // Div
                        case 5:

                            t = t - 1;
                            s[ t ] = s[ t ] / s[ t + 1 ];
                            break;
                        // Mod
                        case 6:

                            s[ t ] = ( s[ t ] ) % 2;
                            break;
                        // pair
                        case 7:

                            s[ t ] = ( s[ t ] % 2 == 1 );
                            break;
                        // Equals
                        case 8:

                            t = t - 1;
                            s[ t ] = ( s[ t ] == s[ t + 1 ] );
                            break;
                        // Not Equals
                        case 9:

                            t = t - 1;
                            s[ t ] = ( s[ t ] != s[ t + 1 ]);
                            break;
                        // kess than
                        case 10:

                            t = t - 1;
                            s[ t ] = ( s[ t ] < s[ t + 1 ] );
                            break;
                        // kess or equal
                        case 11:

                            t = t - 1;
                            s[ t ] = ( s[ t ] <= s[ t + 1 ] );
                            break;
                        // Bigger then
                        case 12:

                            t = t - 1;
                            s[  t] = ( s[ t ] > s[ t + 1 ] );
                            break;
                        // Bigger or equal
                        case 13:

                            t = t - 1;
                            s[ t ] = ( s[ t ] >= s[ t + 1 ] );
                            break;

                    }

                    break;

                case LOD:

                    t = t + 1;
                    s[ t ] = s[ base( i.l ) + i.a ];
                    break;

                case STO:

                    s[ base( i.l ) + i.a ] = s[ t ];
                    t = t - 1;
                    break;

                case CAL:

                    {
                        s[ t + 1 ] = base( i.l );
                        s[ t + 2 ] = b;
                        s[ t + 3 ] = p;
                        b = t + 1;
                        p = i.a;
                    }

                    break;

                case INT:

                    t = t + i.a;
                    break;

                case JMP:

                    p = i.a;
                    break;

                case JPC:

                    if ( s[t] == 0 ) {
                        p = i.a;
                        t = t - 1;
                    }

                    break;

            }
            for( int j = 1; j <= t; j++ ) {

                printf( "[ %1d ]", s[ j ] );

            }

        } while( p != 0 );

    }

}
