#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "HD44780.h"

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
char symbols[] = {' ',
				  '7','8','9','+',
				  '4','5','6','-',
				  '1','2','3','*',
				  '#','0','C','='};

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
				_delay_ms(10);
				// to sprawia ze nie widac w trakcie klikniecia co jest klikniete
				// ale chyba w rzeczywistoœci tak powinno by
				while(bit_is_clear(PINC, j)) _delay_ms(5);
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

	// pierwsza z liczb na ktorych bedzie wykonywana operacja arytmetyczna
	int liczba1final = -1;
	// druga z liczb na ktorych bedzie wykonywana operacja arytmetyczna
	int liczba2final = -1;
	// wynik operacji arytmetycznej
	int wynik = 0;
	int flaga = 1;

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
					wynik = 1*flaga;
					// zaznaczenie ze wczyatno jedna cyfre
					wczytano = 1;
					sprintf(text, "Pressed: %d", 1);
				} else { // jesli to kolejna wczytywana liczba
					wynik = addToCurrentNumber(wynik, 1*flaga);
					sprintf(text, "Pressed: %d", 1);
				}
				break;
			case '2':
				if(wczytano < 0) {
					wynik = 2*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 2);
				} else {
					wynik = addToCurrentNumber(wynik, 2*flaga);
					sprintf(text, "Pressed: %d", 2);
				}
				break;
			case '3':
				if(wczytano < 0) {
					wynik = 3*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 3);
				} else {
					wynik = addToCurrentNumber(wynik, 3*flaga);
					sprintf(text, "Pressed: %d", 3);
				}
				break;
			case '4':
				if(wczytano < 0) {
					wynik = 4*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 4);
				} else {
					wynik = addToCurrentNumber(wynik, 4*flaga);
					sprintf(text, "Pressed: %d", 4);
				}
				break;
			case '5':
				if(wczytano < 0) {
					wynik = 5*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 5);
				} else {
					wynik = addToCurrentNumber(wynik, 5*flaga);
					sprintf(text, "Pressed: %d", 5);
				}
				break;
			case '6':
				if(wczytano < 0) {
					wynik = 6*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 6);
				} else {
					wynik = addToCurrentNumber(wynik, 6*flaga);
					sprintf(text, "Pressed: %d", 6);
				}
				break;
			case '7':
				if(wczytano < 0) {
					wynik = 7*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 7);
				} else {
					wynik = addToCurrentNumber(wynik, 7*flaga);
					sprintf(text, "Pressed: %d", 7);
				}
				break;
			case '8':
				if(wczytano < 0) {
					wynik = 8*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 8);
				} else {
					wynik = addToCurrentNumber(wynik, 8*flaga);
					sprintf(text, "Pressed: %d", 8);
				}
				break;
			case '9':
				if(wczytano < 0) {
					wynik = 9*flaga;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 9);
				} else {
					wynik = addToCurrentNumber(wynik, 9*flaga);
					sprintf(text, "Pressed: %d", 9);
				}
				break;
			case '0':
				if(wczytano < 0) {
					// nie zmieniam wartoœci zmiennej finalnej jak pierwsze jest zero
					wynik=0;
					wczytano = 1;
					sprintf(text, "Pressed: %d", 0);
				} else {
					wynik = addToCurrentNumber(wynik, 0);
					sprintf(text, "Pressed: %d", 0);
				}
				break;
			case '#':
				if(wczytano < 0)
					// nie zmieniam wartoœci zmiennej finalnej jak pierwsze jest zero
					flaga *= -1;
				break;
			case 'C':
				liczba1final = -1;
				liczba2final = -1;
				wczytano = -1;
				flaga = 1;
				wynik = 0;
				sprintf(text, "Pressed: %c", 'C');
				break;
			case '+':
				// zapamiêtanie odpowiedniej operacji
				operacja = '+';
				// wczytanie zmiennej tymczasowej do pierwszej zmiennej finalnej
				liczba1final = wynik;
				// zresetowanie zmiennych pomocnicznych
				//wynik = 0;
				wczytano = -1;
				flaga = 1;
				// do sprawdzenia co jest w zmiennych
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '*':
				operacja = '*';
				liczba1final = wynik;
				//wynik = 0;
				wczytano = -1;
				flaga = 1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '-':
				operacja = '-';
				liczba1final = wynik;
				//wynik = 0;
				wczytano = -1;
				flaga = 1;
				sprintf(text, "Pressed: %c %d %d", symbol, liczba1final, liczba2final);
				break;
			case '=':
				// wczytanie zmiennej tymczasowej do drugiej zmiennej finalnej
				liczba2final = wynik;
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
				//wynik = 0;
				liczba1final = -1;
				liczba2final = -1;
				wczytano = -1;
				flaga = 1;
				break;
			default:
				break;
			}
			LCD_WriteText(text);
		}
		_delay_ms(100);
	}
	return 0;
}
