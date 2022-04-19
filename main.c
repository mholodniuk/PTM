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

// funkcja dodaj¹ca cyfrê na koniec liczby
int addToCurrentNumber(int current, int other) {
	return current * 10 + other;
}

int getKey16() {
	for (int i = 0; i < 4; i++) {
		// stan niski dla wiersza
		cbi(PORTC, i + 4);
		for (int j = 0; j < 4; j++) {
			// sprawdzenie czy przycisk jest wcisniety -> stan niski dla kolumny
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
	// zmienna do wypisywania
	char text[20];
	// symbol wybrany na klawiaturze
	char symbol;
	// indeks zczytany z macierzy klawiatury
	int input = 0;
	// wybrana operacja arytmetyczna
	char operacja;
	// bool czy wczytano juz pierwsza cyfre z liczby
	int wczytano = -1;

	// zmienna pomocniczna do sumowania cyfr
	// chyba da sie wyleliminowac te zmienna
	int liczba1 = 0;
	// pierwsza z liczb na ktorych bedzie wykonywana operacja arytmetyczna
	int liczba1final = -1;
	// druga z liczb na ktorych bedzie wykonywana operacja arytmetyczna
	int liczba2final = -1;
	// wynik operacji arytmetycznej
	int suma = 0;

	while (1) {

		// wypisanie aktualnie przechowywanej liczby
		LCD_Clear();
		LCD_GoTo(0, 0);
		sprintf(text, "liczba: %d", suma);
		LCD_WriteText(text);
		LCD_GoTo(0, 1);

		// pobranie danych z klawiatury
		input = getKey16();

		if(input != 0) {
			// przypisanie odpowiedniej wartoœci z klawiatury do symbolu
			symbol = symbols[input];

			switch(symbol) {
			case '1':
				if(wczytano < 0) { // jesli to pierwsza cyfra wprowadzona
					// przypisanie wartoœci do zmiennych
					liczba1 = 1;
					suma = liczba1;
					// zaznaczenie ze wczyatno jedna cyfre
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else { // jesli to kolejna wczytywana liczba
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
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 4);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '5':
				if(wczytano < 0) {
					liczba1 = 5;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 5);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '6':
				if(wczytano < 0) {
					liczba1 = 6;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 6);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '7':
				if(wczytano < 0) {
					liczba1 = 7;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 7);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '8':
				if(wczytano < 0) {
					liczba1 = 8;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 8);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '9':
				if(wczytano < 0) {
					liczba1 = 9;
					suma = liczba1;
					wczytano = 1;
					sprintf(text, "Pressed: %d", liczba1);
				} else {
					liczba1 = addToCurrentNumber(liczba1, 9);
					suma = liczba1;
					sprintf(text, "Pressed: %d", liczba1);
				}
				break;
			case '+':
				// zapamiêtanie odpowiedniej operacji
				operacja = '+';
				// wczytanie zmiennej tymczasowej do pierwszej zmiennej finalnej
				liczba1final = liczba1;
				// zresetowanie zmiennych pomocnicznych
				liczba1 = 0;
				wczytano = -1;
				// do sprawdzenia co jest w zmiennych
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '*':
				operacja = '*';
				liczba1final = liczba1;
				liczba1 = 0;
				wczytano = -1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '-':
				operacja = '-';
				liczba1final = liczba1;
				liczba1 = 0;
				wczytano = -1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '=':
				// wczytanie zmiennej tymczasowej do drugiej zmiennej finalnej
				liczba2final = liczba1;
				// wykonanie odpowiednich operacji
				if(operacja == '+') {
					suma = liczba1final + liczba2final;
				}
				if(operacja == '*') {
					suma = liczba1final * liczba2final;
				}
				if(operacja == '-') {
					suma = liczba1final - liczba2final;
				}
				sprintf(text, "Pressed: %c", symbol);
				// zresetowanie wszystkich zmiennych
				liczba1 = 0;
				liczba1final = -1;
				liczba2final = -1;
				wczytano = -1;
				break;
			default:
				break;
			}
			LCD_WriteText(text);
			_delay_ms(200);
		}
		_delay_ms(200);
		// czekanie az uzytkownik nie pusci przycisku
		// to umozliwia zobaczyc co aktualnie zostalo klikniete
		while (bit_is_clear(PINC, PD0) || bit_is_clear(PINC, PD1) || bit_is_clear(PINC, PD2) || bit_is_clear(PINC, PD3))
			_delay_ms(100);
	}
	return 0;
}