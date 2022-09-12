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

void main() {

    /* simplified entry( representation )
    INT 0 6
    LIT 0 11
    STO 0 5
    LIT 0 2
    OPR 0 2
    OPR 0 0
    */

    // Iniciando
    int index = 0;
    code[index].f = INT;
    code[index].l = 0;
    code[index].a = 6; index++;
    // Inserindo o litaral '11'.
    code[index].f = LIT;
    code[index].l = 0;
    code[index].a = 11; index++;
    // Movendo literal '64'.
    code[index].f = STO;
    code[index].l = 0;
    code[index].a = 5; index++;
    // Inserindo o literal '2'.
    code[index].f = LIT;
    code[index].l = 0;
    code[index].a = 2; index++;
    // Operando soma
    code[index].f = OPR;
    code[index].l = 0;
    code[index].a = 2; index++;
    // Finalizando execução
    code[index].f = OPR;
    code[index].l = 0;
    code[index].a = 0; index++;

    instruction i;
    {

        t = 0;
        b = 1;
        p = 0;

        s[1] = 0;
        s[2] = 0;
        s[3] = 0;

        printf( "\n | p | b | t | -> ---------------STACK------------------" );

        do {

            i =  code[ p ];
            printf( "\n | %d | %d | %d | -> ", p, b, t );
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
                        // Negativo
                        case 1:

                            s[ t ] = -s[ t ];
                            break;
                        // Soma
                        case 2:

                            t = t - 1;
                            s[ t ] = s[ t ] + s[t + 1];
                            break;
                        // Subtração
                        case 3:
                            t = t - 1;
                            s[ t ] = s[ t ] - s[t + 1];
                            break;
                        // Multiplicação
                        case 4:

                            t = t - 1;
                            s[ t ] = s[ t ] * s[ t + 1 ];
                            break;
                        // Divisão
                        case 5:

                            t = t - 1;
                            s[ t ] = s[ t ] / s[ t + 1 ];
                            break;
                        // Mod
                        case 6:

                            s[ t ] = ( s[ t ] ) % 2;
                            break;
                        // Impar
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
                        // Menor que
                        case 10:

                            t = t - 1;
                            s[ t ] = ( s[ t ] < s[ t + 1 ] );
                            break;
                        // Menor ou igual
                        case 11:

                            t = t - 1;
                            s[ t ] = ( s[ t ] >= s[ t + 1 ] );
                            break;
                        // Maior que
                        case 12:

                            t = t - 1;
                            s[  t] = ( s[ t ] > s[ t + 1 ] );
                            break;
                        // Maior ou igual
                        case 13:

                            t = t - 1;
                            s[ t ] = ( s[ t ] <= s[ t + 1 ] );
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

                printf( "[ %d ]", s[ j ] );

            }

        } while( p != 0 );

    }

}
