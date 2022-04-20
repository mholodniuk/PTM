#include "GLOBAL.h"
 
volatile uint8_t minuty, sekundy;
volatile uint16_t liczba7Seg;
 
volatile char znaki[4];
 
char cyfra[10] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
		0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011};
 
//Inicjalizacja Timer1 do wywolywania przerwania co 1s
void TimerInit() {
	//Wybranie trybu pracy CTC z TOP OCR1A
 
	//Wybranie dzielnika czestotliwosci
 
	//Zapisanie do OCR1A wartosci odpowiadajacej 0,5s
 
	//Uruchomienie przerwania OCIE1A
 
}
 
//Inicjalizacja portow do obsługi wyswietlacza 7 segmentowego
void seg7Init() {
	//Inicjalizacja kolumn
 	for(int i=0; i<8; ++i) {
		sbi(DDRC, i);
		cbi(PORTC, i);
	}
	//Inicjalizacja segmentu
 
}
 
//Wyswietla na wyswietlaczu 7 segmentowym cyfre z argumentu
void seg7ShowCyfra(uint8_t cyfraDoWyswietlenia) {
	PORTC = cyfra[cyfraDoWyswietlenia];
}
 
//Wyswietla na wyswietlaczu 7 segmentowym wartosc ze zmiennej liczba7Seg
void seg7Show4Cyfry() {
 
}
 
//Funkcja wyswietla na wyswietlaczu litery, cyfry z tablicy znaki
/*      zadanie na ocenę 5.5              */
void seg7Show4Litery() {
 
}
 
int main() {
	minuty = 0;
	sekundy = 0;
	liczba7Seg = 0;
	TimerInit();
	seg7Init();
 
	sei();	//funkcja uruchamia globalne przerwania
 
	while (1) {
		seg7ShowCyfra(5);
		_delay_ms(100);
	}
 
	return 0;
}
 
//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer1
ISR(TIMER1_COMPA_vect) {
	tbi(); // ???
}