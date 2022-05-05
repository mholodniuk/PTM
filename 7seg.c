#include "GLOBAL.h"

volatile uint8_t minuty, sekundy;
volatile uint16_t liczba7Seg;

volatile char znaki[4];

char cyfra[10] = { 0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
    0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1110011};

//Inicjalizacja Timer1 do wywolywania przerwania co 1s
void TimerInit() {
  //Wybranie trybu pracy CTC z TOP OCR1A
  sbi(TCCR1B, WGM12);    //Uruchomienie CTC

  //Wybranie dzielnika czestotliwosci
  sbi(TCCR1B, CS10);
  sbi(TCCR1B, CS12);

  //Zapisanie do OCR1A wartosci odpowiadajacej 0,5s
  OCR1A = 3906;

  //Uruchomienie przerwania OCIE1A
  //sbi(TIMSK, OCIE1A);

}

//Inicjalizacja portow do obsługi wyswietlacza 7 segmentowego
void seg7Init() {
  //Inicjalizacja kolumn
  for(int i=0; i<7; i++){
    sbi(DDRC, i);
  }

  //Inicjalizacja segmentu

}

//Wyswietla na wyswietlaczu 7 segmentowym cyfre z argumentu
void seg7ShowCyfra(uint8_t cyfraDoWyswietlenia) {
  PORTC = cyfra[cyfraDoWyswietlenia];   //co to robi - wytlumaczyc prowadzacemu
}

//Wyswietla na wyswietlaczu 7 segmentowym wartosc ze zmiennej liczba7Seg
void seg7Show4Cyfry() {
  
sbi(PORTD, PD0);
sbi(DDRD, PD3);
cbi(PORTD, PD3);
PORTC = cyfra[2];
_delay_ms(20);

sbi(PORTD, PD3);
sbi(DDRD, PD2);
cbi(PORTD, PD2);
PORTC = cyfra[1];
_delay_ms(20);

sbi(PORTD, PD2);
sbi(DDRD, PD1);
cbi(PORTD, PD1);
PORTC = cyfra[3];
_delay_ms(20);

sbi(PORTD, PD1);
sbi(DDRD, PD0);
cbi(PORTD, PD0);
PORTC = cyfra[7];
_delay_ms(20);

}

//Funkcja wyswietla na wyswietlaczu litery, cyfry z tablicy znaki
/*      zadanie na ocenę 5.5              */
void seg7Show4Litery() {

}


int main() {

  minuty = 0;
  sekundy = 0;
  liczba7Seg = 0;
  //TimerInit();
  seg7Init();

  //sbi(DDRD, PD6);

  sei();  //funkcja uruchamia globalne przerwania

  while (1) {
//    seg7ShowCyfra(9);
//    _delay_ms(100);

      seg7Show4Cyfry();
  }

  return 0;
}

//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer1
ISR(TIMER1_COMPA_vect) {
//tbi(PORTD, PD6);
}