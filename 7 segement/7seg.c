#include "GLOBAL.h"
#include <avr/io.h>
#include<avr/interrupt.h>
volatile uint8_t minuty, sekundy;
volatile uint16_t liczba7Seg;

volatile char znaki[4];

char cyfra[10] = { 0b0000011, 0b10011111, 0b00100101, 0b00001101, 0b10011001,
		0b01001001, 0b01000001, 0b00011111, 0b00000001, 0b00001001};

//Inicjalizacja Timer1 do wywolywania przerwania co 1s (0,5s ???)
void TimerInit() {
	//Wybranie trybu pracy CTC z TOP OCR1A
	cbi(TCCR1B, WGM13);
	sbi(TCCR1B, WGM12);
	cbi(TCCR1A, WGM11);
	cbi(TCCR1A, WGM10);
	//Wybranie dzielnika czestotliwosci
	sbi(TCCR1B, CS12);
	cbi(TCCR1B, CS11);
	sbi(TCCR1B, CS10); // 1024
	//Zapisanie do OCR1A wartosci odpowiadajacej 0,5s
	//OCR1A = 3906;
	OCR1A = 2*3906;
	//Uruchomienie przerwania OCIE1A
	sbi(TIMSK, OCIE1A);
}

//Inicjalizacja portow do obsługi wyswietlacza 7 segmentowego
void seg7Init() {
	//Inicjalizacja kolumn
	DDRA = 0xF0;
	PORTA = 0xF0;
	//Inicjalizacja segmentu
	DDRC = 0xFF;
	PORTC = 0xFF;
}

//Wyswietla na wyswietlaczu 7 segmentowym cyfre z argumentu
void seg7ShowCyfra(uint8_t cyfraDoWyswietlenia) {
	PORTC = cyfra[cyfraDoWyswietlenia];   //co to robi - wytlumaczyc prowadzacemu
}

//Wyswietla na wyswietlaczu 7 segmentowym wartosc ze zmiennej liczba7Seg
void seg7Show4Cyfry() {
	uint16_t liczba;
	liczba = liczba7Seg;


	seg7ShowCyfra(liczba/1000);
	cbi(PORTA, PA7);
	_delay_ms(2);
	sbi(PORTA, PA7);

	seg7ShowCyfra((liczba/100)%10);
	cbi(PORTA, PA6);
	_delay_ms(2);
	sbi(PORTA, PA6);

	seg7ShowCyfra((liczba/10)%10);
	cbi(PORTA, PA5);
	_delay_ms(2);
	sbi(PORTA, PA5);

	seg7ShowCyfra(liczba%10);
	cbi(PORTA, PA4);
	_delay_ms(2);
	sbi(PORTA, PA4);
}

//Funkcja wyswietla na wyswietlaczu litery, cyfry z tablicy znaki
/*      zadanie na ocenę 5.5              */
void seg7Show4Litery() {

}

int main() {
	minuty = 0;
	sekundy = 58;
	liczba7Seg = 0;
	TimerInit();
	seg7Init();

	//ustawienie PD6 jako wyjścia (stan wysoki)
	DDRD = 1 << 5;
	PORTD = 1 << 5;
	DDRD |= 1 << 7;
	PORTD |= 1 << 7;

	sei();	//funkcja uruchamia globalne przerwania

	cbi(PORTA, PA7);

	while (1) {
		//tbi(PORTD, PD5);
		seg7Show4Cyfry();
	}

	return 0;
}

//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer1
ISR(TIMER1_COMPA_vect) {
	//tbi(PORTD, PD7);

	/*++liczba7Seg;
	if(liczba7Seg > 9999) liczba7Seg = 0;*/

	++sekundy;
	if(!(sekundy%60)){
		++minuty;
		sekundy = 0;
	}
	liczba7Seg = 100*minuty+sekundy;
}
