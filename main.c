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

// pusty pierwszy symbol bo getKey16() zwraca od 1-16
char symbols[] = {' ','7','8','9','-','4','5','6','+','1','2','3','C','*','0','#','='};

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
				while(bit_is_clear(PIND, j)) 
					_delay_ms(5);
				sbi(PORTC, i + 4);
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
	char operacja = ' ';
	// bool czy wczytano juz pierwsza cyfre z liczby
	int wczytano = -1;

	// zmienna pomocniczna do sumowania cyfr
	// chyba da sie wyleliminowac te zmienna
	int tmp = 0;
	// pierwsza z liczb na ktorych bedzie wykonywana operacja arytmetyczna
	int liczba1final = -1;
	// druga z liczb na ktorych bedzie wykonywana operacja arytmetyczna
	int liczba2final = -1;
	// wynik operacji arytmetycznej
	int wynik = 0;

	while (1) {

		// wypisanie aktualnie przechowywanej liczby
		LCD_Clear();
		LCD_GoTo(0, 0);
		sprintf(text, "liczba: %d", wynik);
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
					tmp = 1;
					wynik = tmp;
					// zaznaczenie ze wczyatno jedna cyfre
					wczytano = 1;
					sprintf(text, "Pressed: %d", 1);
				} else { // jesli to kolejna wczytywana liczba
					tmp = addToCurrentNumber(tmp, 1);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 1);
				}
				break;
			case '2':
				if(wczytano < 0) {
					tmp = 2;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 2);
				} else {
					tmp = addToCurrentNumber(tmp, 2);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 2);
				}
				break;
			case '3':
				if(wczytano < 0) {
					tmp = 3;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 3);
				} else {
					tmp = addToCurrentNumber(tmp, 3);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 3);
				}
				break;
			case '4':
				if(wczytano < 0) {
					tmp = 4;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 4);
				} else {
					tmp = addToCurrentNumber(tmp, 4);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 4);
				}
				break;
			case '5':
				if(wczytano < 0) {
					tmp = 5;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 5);
				} else {
					tmp = addToCurrentNumber(tmp, 5);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 5);
				}
				break;
			case '6':
				if(wczytano < 0) {
					tmp = 6;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 6);
				} else {
					tmp = addToCurrentNumber(tmp, 6);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 6);
				}
				break;
			case '7':
				if(wczytano < 0) {
					tmp = 7;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 7);
				} else {
					tmp = addToCurrentNumber(tmp, 7);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 7);
				}
				break;
			case '8':
				if(wczytano < 0) {
					tmp = 8;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 8);
				} else {
					tmp = addToCurrentNumber(tmp, 8);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 8);
				}
				break;
			case '9':
				if(wczytano < 0) {
					tmp = 9;
					wynik = tmp;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 9);
				} else {
					tmp = addToCurrentNumber(tmp, 9);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 9);
				}
				break;
			case '0':
				if(wczytano < 0) {
					// nie zmieniam wartoœci zmiennej finalnej jak pierwsze jest zero
					tmp = 0;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 0);
				} else {
					tmp = addToCurrentNumber(tmp, 0);
					wynik = tmp;
					sprintf(text, "Pressed: %d", 0);
				}
				break;
			case 'C':
				tmp = 0;
				liczba1final = -1;
				liczba2final = -1;
				wczytano = -1;
				wynik = 0;
				sprintf(text, "Pressed: %c", 'C');
				break;
			case '+':
				// zapamiêtanie odpowiedniej operacji
				operacja = '+';
				// wczytanie zmiennej tymczasowej do pierwszej zmiennej finalnej
				liczba1final = tmp;
				// zresetowanie zmiennych pomocnicznych
				tmp = 0;
				wczytano = -1;
				// do sprawdzenia co jest w zmiennych
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '*':
				operacja = '*';
				liczba1final = tmp;
				tmp = 0;
				wczytano = -1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '-':
				operacja = '-';
				liczba1final = tmp;
				tmp = 0;
				wczytano = -1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '=':
				// wczytanie zmiennej tymczasowej do drugiej zmiennej finalnej
				liczba2final = tmp;
				// wykonanie odpowiednich operacji jesli wczytano dwie liczby
				if(operacja == '+' && liczba2final != -1 && liczba1final != -1) {
					wynik = liczba1final + liczba2final;
				}
				if(operacja == '*' && liczba2final != -1 && liczba1final != -1) {
					wynik = liczba1final * liczba2final;
				}
				if(operacja == '-' && liczba2final != -1 && liczba1final != -1) {
					wynik = liczba1final - liczba2final;
				}
				sprintf(text, "Pressed: %c", symbol);
				// zresetowanie wszystkich zmiennych
				tmp = 0;
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
		// to umozliwia zobaczyc co aktualnie jest klikniete
		while (bit_is_clear(PINC, PD0) || bit_is_clear(PINC, PD1) || bit_is_clear(PINC, PD2) || bit_is_clear(PINC, PD3))
			_delay_ms(100);
	}
	return 0;
}
