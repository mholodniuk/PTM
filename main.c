#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "lcd/HD44780.h"

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit) reg |= (_BV(bit))
#endif
#ifndef cbi
#define cbi(reg,bit) reg &= ~(_BV(bit))
#endif

char symbols[] = {'0','7','8','9','-','4','5','6','+','1','2','3','C','*','0','#','='};

int addToCurrentNumber(int current, int other) {
	return current * 10 + other;
}

int getKey16() {
	for (int i = 0; i < 4; i++) {
		// stan niski dla wiersza
		cbi(PORTC, i + 4);
		for (int j = 0; j < 4; j++) {
			// sprawdzenie czy przycisk jest wcisniety
			if (bit_is_clear(PINC, j)) {
				_delay_ms(20);
				return i * 4 + j + 1; // [1 - 16] jak na plytce
			}
		}
		// stan wysoki dla wiersza
		sbi(PORTC, i + 4);
	}
	return 0;
}

int main()
{
	// inicjalizacja portów
	for(int i = 0; i < 4; i++) {
		// wejœcie PULL UP na PC0-PC3 --> kolumny
		cbi(DDRC, i);
		sbi(PORTC, i);
		// wyjœcie stan wysoki na PC4-PC7 --> wiersze
		sbi(DDRC, i + 4);
		sbi(PORTC, i + 4);
	}

	LCD_Initalize();
	LCD_Home();
	char text[20];
	char symbol;
	int data = 0;
	char operacja;
	int wczytano = -1;

	int liczba1 = 0;
	int liczba1final = -1;
	int liczba2 = 0;
	int liczba2final = -1;
	int suma = 0;

	while (1) {
		LCD_Clear();

		LCD_GoTo(0, 0);
		sprintf(text, "liczba: %d", suma);
		LCD_WriteText(text);
		LCD_GoTo(0, 1);
		data = getKey16();

		if(data != 0) {
			symbol = symbols[data];

			switch(symbol) {
			case '1':
				if(wczytano < 0) {
					liczba1 = 1;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 1);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '2':
				if(wczytano < 0) {
					liczba1 = 2;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 2);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '3':
				if(wczytano < 0) {
					liczba1 = 3;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 3);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '4':
				if(wczytano < 0) {
					liczba1 = 4;
					wczytano = 1;
					sprintf(text, "Pressed 4: %d", liczba1);
				} else {
					liczba2 = 4;
					sprintf(text, "Pressed: %d", liczba2);
				}
				break;
			case '5':
				if(wczytano < 0) {
					liczba1 = 5;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba2 = 5;
					sprintf(text, "Pressed: %d", liczba2);
				}
				break;
			case '6':
				if(wczytano < 0) {
					liczba1 = 6;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba2 = 6;
					sprintf(text, "Pressed: %d", liczba2);
				}
				break;
			case '7':
				if(wczytano < 0) {
					liczba1 = 7;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba2 = 7;
					sprintf(text, "Pressed: %d", liczba2);
				}
				break;
			case '8':
				if(wczytano < 0) {
					liczba1 = 8;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba2 = 8;
					sprintf(text, "Pressed: %d", liczba2);
				}
				break;
			case '9':
				if(wczytano < 0) {
					liczba1 = 9;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba2 = 9;
					sprintf(text, "Pressed: %d", liczba2);
				}
				break;
			case '+':
				operacja = '+';
				if(liczba1final == -1 && liczba2final == -1)
					liczba1final = liczba1;
				else
					liczba2final = liczba1;
				liczba1 = 0;
				wczytano = -1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '-':
				operacja = '-';
				sprintf(text, "Pressed: %c", symbol);
				break;
			case '=':
				if(operacja == '+') {
					suma = liczba1final + liczba2final;
				}
				if(operacja == '-') {
					suma = liczba1 - liczba2;
				}
				sprintf(text, "Pressed: %c", symbol);
				liczba1 = 0;
				liczba2 = 0;
				liczba1final = 0;
				liczba2final = 0;
				wczytano = -1;
				break;
			default:
				break;
			}
			LCD_WriteText(text);
			_delay_ms(200);
		}
		//LCD_WriteText(text);
		_delay_ms(200);
		while (bit_is_clear(PINC, PD0) || bit_is_clear(PINC, PD1) || bit_is_clear(PINC, PD2) || bit_is_clear(PINC, PD3))
			_delay_ms(100);
	}
	return 0;
}
