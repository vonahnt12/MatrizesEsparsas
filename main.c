#include <stdio.h>
#include <stdlib.h>


struct matrix {
    struct matrix *right;
    struct matrix *below;
    int line;
    int column;
    float info;
};
typedef struct matrix Matrix;

Matrix* matrix_create( void );
void matrix_print( Matrix *m );
void matrix_destroy( Matrix *m );
Matrix* matrix_add( Matrix *m, Matrix *n );
float matrix_getelem( Matrix *m, int x, int y );
void matrix_setelem( Matrix *m, int x, int y, float elem );
Matrix* matrix_transpose( Matrix *m );
Matrix* matrix_multiply( Matrix *m, Matrix* n );

int main()
{
   
    Matrix *A = matrix_create();
    matrix_print( A );
    Matrix *B = matrix_create(); 
    matrix_print( B );
    Matrix *C = matrix_add( A, B ); 
    matrix_print( C );
    matrix_destroy( C );
    C = matrix_multiply( A, B ); 
    matrix_print( C );
    matrix_destroy( C );
    C = matrix_transpose( A ); 
    matrix_print( C );
    matrix_destroy( C );
    matrix_destroy( A );
    matrix_destroy( B );
    return 0;
}

Matrix* matrix_create( void ){
    Matrix *head, *p, *head_linha, *head_coluna, *new_element, *busca;
    int linhas, colunas, i, j;
    float valor;

    head = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
    head->line = -1;
    head->column = -1;
    head->below = head;
    head->right = head;

    printf( "Numero de Linhas e de Colunas da Matriz: \n" );
    scanf( "%d %d", &linhas, &colunas );

    p = head;
    for( i = 0; i < linhas; i++ ){
        head_linha = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
        head_linha->line = -1;
        head_linha->below = head;
        head_linha->right = head_linha;
        p->below = head_linha;
        p = head_linha;
    }

    p = head;
    for( i = 0; i < colunas; i++ ){
        head_coluna = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
        head_coluna->column = -1;
        head_coluna->right = head;
        head_coluna->below = head_coluna;
        p->right = head_coluna;
        p = head_coluna;
    }

    printf( "Digite um valor diferente de 0 para colocar elementos: \n" );
    scanf( "%d %d %f", &i, &j, &valor );
    while(i != 0){
        new_element = ( Matrix * ) malloc( 1 * sizeof( Matrix ) );
        new_element->line = i;
        new_element->column = j;
        new_element->info = valor;
        p = head;
        for( int k = 0; k < new_element->column; k++ ){
            p = p->right;
        }
        head_coluna = p;
        busca = head_coluna->below;
        while( ( new_element->line > busca->line ) && ( busca->column != -1 ) ) {
            p = busca;
            busca = busca->below;
        }
        new_element->below = busca;
        p->below = new_element;

        p = head;
        for( int k = 0; k < new_element->line; k++ ){
            p = p->below;
        }
        head_linha = p;
        busca = head_linha->right;
        while( ( new_element->column > busca->column ) && ( busca->line != -1 ) ) {
            p = busca;
            busca = busca->right;
        }
        new_element->right = busca;
        p->right = new_element;

        scanf( "%d %d %f", &i, &j, &valor );
    }
    return head;
}

void matrix_print( Matrix *m ) {
    Matrix *head, *head_linha, *p;
    int linhas = 0, colunas = 0;
    head = m;

    for( p = head->right; p != head; p = p->right ) {
        colunas++;
        printf( "coluna: %d\n", colunas );
    }

    for( p = head->below; p != head; p = p->below ) {
        linhas++;
        printf( "linha: %d\n", linhas );
    }

    printf( "Numero de Linhas: %d \nNumero de Colunas: %d\n", linhas, colunas );

    p = head;
    for( int i = 0; i < linhas; i++ ) {
        p = p->below;
        head_linha = p;
        while( p->right != head_linha ) {
            p = p->right;
            
            printf( "Posicao: %d %d , Valor: %f\n", p->line, p->column, p->info );
                    
        }
        p = head_linha;
    }
}

void matrix_destroy( Matrix *m ) {
    Matrix *head, *busca, *head_linha, *p, *remover;
    head = m;
    for( p = head->below; p != head; p = p->below ) {
        head_linha = p;
        busca = head_linha->right;
        while( busca != head_linha ) {
            remover = busca;
            busca = busca->right;
            free( remover );
        }
    }

    busca = head->below;
    while( busca != head ) {
        remover = busca;
        busca = busca->below;
        free( remover );
    }

    busca = head->right;
    while( busca != head ) {
        remover = busca;
        busca = busca->right;
        free( remover );
    }

    free( head );
}

Matrix* matrix_add( Matrix *m, Matrix *n ) {
    Matrix *head_a, *head_b, *head_c, *p, *head_linha, *head_coluna, *q, *new_element, *r, *busca, *head_coluna_c, *head_linha_c, *s, *head_linha_b;
    Matrix *s_left, *s_up, *busca_s_up;
    int linhas_a = 0, colunas_a = 0, linhas_b = 0, colunas_b = 0;
    
    head_a = m;
    head_b = n;

    for( p = head_a->right; p != head_a; p = p->right ) {
        colunas_a++;
    }

    for( p = head_a->below; p != head_a; p = p->below ) {
        linhas_a++;
    }
    for( p = head_b->right; p != head_b; p = p->right ) {
        colunas_b++;
    }

    for( p = head_b->below; p != head_b; p = p->below ) {
        linhas_b++;
    }

    if( linhas_a != linhas_b || colunas_a != colunas_b ) {
        printf( "Soma Impossivel" );
        return NULL;
    } else {
        head_c = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );

        p = head_c;
        for( int i = 0; i < linhas_a; i++ ) {
            head_linha = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
            head_linha->line = -1;
            head_linha->below = head_c;
            head_linha->right = head_linha;
            p->below = head_linha;
            p = head_linha;
        }

        p = head_c;
        for( int i = 0; i < colunas_a; i++ ) {
            head_coluna = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
            head_coluna->column = -1;
            head_coluna->right = head_c;
            head_coluna->below = head_coluna;
            p->right = head_coluna;
            p = head_coluna;
        }

       for( p = head_a->below; p != head_a; p = p->below ) {
            head_linha = p;
            q = head_linha->right;
            while( q != head_linha ) {
                new_element = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
                new_element->line = q->line;
                new_element->column = q->column;
                new_element->info = q->info;
                r = head_c;
                for( int k = 0; k < new_element->column; k++ ){
                    r = r->right;
                }
                head_coluna_c = r;
                busca = head_coluna_c->below;
                while( ( new_element->line > busca->line ) && ( busca->column != -1 ) ) {
                    r = busca;
                    busca = busca->below;
                }
                new_element->below = busca;
                r->below = new_element;

                r = head_c;
                for( int k = 0; k < new_element->line; k++ ) {
                    r = r->below;
                }
                head_linha_c = r;
                busca = head_linha_c->right;
                while( ( new_element->column > busca->column ) && ( busca->line != -1 ) ) {
                    r = busca;
                    busca = busca->right;
                }
                new_element->right = busca;
                r->right = new_element;
                
                q = q->right;
            }
        }
       
        r = head_c->below;

       for( p = head_b->below; p != head_b; p = p->below ) {
            head_linha_b = p;
            q = head_linha_b->right;
            while( q != head_linha_b ) {
                head_linha_c = r;
                s_left = head_linha_c;
                s = head_linha_c->right;
                while( s != head_linha_c ) {
                    if( q->line == s->line && q->column == s->column ) {
                        s->info = s->info + q->info;
                        if( s->info == 0 ) {
                            s_left->right = s->right;
                            busca_s_up = s->below;
                            while( busca_s_up != s ) {
                                s_up = busca_s_up;
                                busca_s_up = busca_s_up->below;
                            }
                            s_up->below = s->below;
                            free( s );

                        }
                        break;
                    } 
                    s_left = s;
                    s = s->right;

                }
                if( s == head_linha_c ) {
                    new_element = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
                    new_element->line = q->line;
                    new_element->column = q->column;
                    new_element->info = q->info;
                    s = head_c;
                    for( int k = 0; k < new_element->column; k++ ) {
                        s = s->right;
                    }
                    head_coluna_c = s;
                    busca = head_coluna_c->below;
                    while( ( new_element->line > busca->line ) && ( busca->column != -1 ) ) {
                        s = busca;
                        busca = busca->below;
                    }
                    new_element->below = busca;
                    s->below = new_element;

                    s = head_c;
                    for( int k = 0; k < new_element->line; k++ ) {
                        s = s->below;
                    }
                    head_linha_c = s;
                    busca = head_linha_c->right;
                    while( ( new_element->column > busca->column ) && ( busca->line != -1 ) ) {
                        s = busca;
                        busca = busca->right;
                    }
                    new_element->right = busca;
                    s->right = new_element; 
                
                }

                q = q->right;
                
            }
            r = r->below;
        
       }

    }
    return head_c;   
}

float matrix_getelem( Matrix *m, int x, int y ) {
    Matrix *head, *p, *head_linha;
    head = m;

    p = head;
    for( int i = 0; i < x; i++ ) {
        p = p->below;
    }
    head_linha = p;
    
    p = head_linha->right;
    while( p != head_linha ) {
        if( p->column == y ) {
            return p->info;
        } else {
            p = p->right;
        }
    }
    return 0;
}

void matrix_setelem( Matrix *m, int x, int y, float elem ) {
    Matrix *head, *p, *head_linha, *new_element, *busca, *head_coluna;

    head = m;
    p = head;
    for( int i = 0; i < x; i++ ) {
        p = p->below;
    }
    head_linha = p;
    p = head_linha->right;
    while( p != head_linha ) {
        if( p->column == y ) {
            p->info = elem;
            
        }
        p = p->right;
    }
    if( p == head_linha ) {

        new_element = ( Matrix * ) malloc( 1 * sizeof( Matrix ) );
        new_element->info = elem;
        new_element->line = x;
        new_element->column = y;
        busca = head_linha->right;
        p = head_linha;
        while( ( y > busca->column ) && ( busca->line != -1 ) ) {
            p = busca;
            busca = busca->right;
        }
        new_element->right = busca;
        p->right = new_element;

        p = head;
            for( int k = 0; k < y; k++ ) {
                p = p->right;
            }
            head_coluna = p;
            busca = head_coluna->below;
            while( ( x > busca->line ) && ( busca->column != -1 ) ) {
                p = busca; 
                busca = busca->below;
            }
            new_element->below = busca;
            p->below = new_element;
    }
}

Matrix* matrix_transpose( Matrix *m ) {
    Matrix *head_a, *head_t, *p, *q, *head_linha_a, *head_linha_t, *head_coluna_t, *new_element, *r, *busca;
    int linhas_a = 0, colunas_a = 0, linhas_t, colunas_t;
    head_a = m;
    for( p = head_a->right; p != head_a; p = p->right ) {
        colunas_a++;
    }

    for( p = head_a->below; p != head_a; p = p->below ) {
        linhas_a++;
    }
    linhas_t = colunas_a;
    colunas_t = linhas_a;

    head_t = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );

    p = head_t;
    for( int i = 0; i < linhas_t; i++ ) {
        head_linha_t = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
        head_linha_t->line = -1;
        head_linha_t->below = head_t;
        head_linha_t->right = head_linha_t;
        p->below = head_linha_t;
        p = head_linha_t;
    }

    p = head_t;
    for( int i = 0; i < colunas_t; i++ ) {
        head_coluna_t = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
        head_coluna_t->column = -1;
        head_coluna_t->right = head_t;
        head_coluna_t->below = head_coluna_t;
        p->right = head_coluna_t;
        p = head_coluna_t;
    }
    for( p = head_a->below; p != head_a; p = p->below ) {
            head_linha_a = p;
            q = head_linha_a->right;
            while( q != head_linha_a ) {
                new_element = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
                new_element->line = q->column;
                new_element->column = q->line;
                new_element->info = q->info;
                r = head_t;
                for( int k = 0; k < new_element->column; k++ ) {
                    r = r->right;
                }
                head_coluna_t = r;
                busca = head_coluna_t->below;
                while( ( new_element->line > busca->line ) && ( busca->column != -1 ) ) {
                    r = busca;
                    busca = busca->below;
                }
                new_element->below = busca;
                r->below = new_element;

                r = head_t;
                for( int k = 0; k < new_element->line; k++ ) {
                    r = r->below;
                }
                head_linha_t = r;
                busca = head_linha_t->right;
                while( ( new_element->column > busca->column ) && ( busca->line != -1 ) ) {
                    r = busca;
                    busca = busca->right;
                }
                new_element->right = busca;
                r->right = new_element;
                
                q = q->right;
            }
        }
    return head_t;
}

Matrix* matrix_multiply( Matrix *m, Matrix* n ) {
    Matrix *head_a, *head_b, *p, *head_c, *head_linha_c, *head_coluna_c, *head_linha_a, *r, *q, *s, *head_coluna_b, *new_element, *busca, *t;
    int linhas_a = 0, colunas_a = 0, linhas_b = 0, colunas_b = 0, linha_c = 0, coluna_c = 0;
    float multi, soma;
    head_a = m;
    head_b = n;

    for( p = head_a->right; p != head_a; p = p->right ) {
        colunas_a++;
    }

    for( p = head_a->below; p != head_a; p = p->below ) {
        linhas_a++;
    }
    for( p = head_b->right; p != head_b; p = p->right ) {
        colunas_b++;
    }

    for( p = head_b->below; p != head_b; p = p->below ) {
        linhas_b++;
    }
     
    if( colunas_a != linhas_b ) {
        printf( "Multiplicacao Impossivel" );
        return NULL;
    } else {
        head_c = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
        p = head_c;
        for( int i = 0; i < linhas_a; i++ ) {
            head_linha_c = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
            head_linha_c->line = -1;
            head_linha_c->below = head_c;
            head_linha_c->right = head_linha_c;
            p->below = head_linha_c;
            p = head_linha_c;
        }

        p = head_c;
        for( int i = 0; i < colunas_b; i++ ) {
            head_coluna_c = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
            head_coluna_c->column = -1;
            head_coluna_c->right = head_c;
            head_coluna_c->below = head_coluna_c;
            p->right = head_coluna_c;
            p = head_coluna_c;
        }
        

        for( p = head_a->below; p != head_a; p = p->below ) {
            head_linha_a = p;
            for( r = head_b->right; r != head_b; r = r->right ) {
                head_coluna_b = r;
                 q = head_linha_a->right;
                soma = 0;
                while( q != head_linha_a ) {
                    s = head_coluna_b->below;
                    while( s != head_coluna_b ) {
                        if( q->column == s->line ) {
                            multi = q->info * s->info;
                            soma = soma + multi;
                            multi = 0;
                            if( linha_c == 0 ) {
                                linha_c = q->line;
                                coluna_c = s->column;
                            }
                            break;
                        }                    
                        s = s->below;
                        
                    }
                    q = q->right;                
                }
                
                if( soma != 0 ) {
                    new_element = ( Matrix * ) malloc ( 1 * sizeof( Matrix ) );
                    new_element->info = soma;
                    new_element->line = linha_c;
                    new_element->column = coluna_c;
                    t = head_c;
                    for( int k = 0; k < new_element->column; k++ ) {
                        t = t->right;
                    }
                    head_coluna_c = t;
                    busca = head_coluna_c->below;
                    while( ( new_element->line > busca->line ) && ( busca->column != -1 ) ) {
                        t = busca;
                        busca = busca->below;
                    }
                    new_element->below = busca;
                    t->below = new_element;

                    t = head_c;
                    for( int k = 0; k < new_element->line; k++ ) {
                        t = t->below;
                    }
                    head_linha_c = t;
                    busca = head_linha_c->right;
                    while( ( new_element->column > busca->column ) && ( busca->line != -1 ) ) {
                        t = busca;
                        busca = busca->right;
                    }
                    new_element->right = busca;
                    t->right = new_element;

                }
                linha_c = 0;
                coluna_c = 0;
                
            }
        }
        return head_c;
    }

}
