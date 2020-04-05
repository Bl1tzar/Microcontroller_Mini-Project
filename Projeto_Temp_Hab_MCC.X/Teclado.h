#ifndef TECLADO_H
#define	TECLADO_H

//Para as vari�veis passarem de um ficheiro .c para outro .c (teclado.c -> main.c)
extern unsigned char tecla_premida; // Guarda a tecla que foi premida
extern int tecla_n; //Indica se alguma tecla foi premida
extern int tecla_limpar; // Indica que � para limpar o LCD

//Func�es
void teclado_coluna_1 (void);
void teclado_coluna_2 (void);
void teclado_coluna_3 (void);


#endif	/* TECLADO_H */

