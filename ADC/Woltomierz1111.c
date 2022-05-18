#include "GLOBAL.h"

volatile uint8_t minuty, sekundy;
volatile uint16_t liczba7Seg;
volatile uint16_t licz;

volatile char znaki[4] = { ~(0b01110111), ~(0b01111100), ~(0b00111001), ~(0b01011110)};


char cyfra[10] = { ~(0b00111111), ~(0b00000110), ~(0b01011011), ~(0b01001111), ~(0b01100110), ~(0b01101101),
                   ~(0b01111101), ~(0b00000111), ~(0b01111111), ~(0b01101111)};

char min[10] = { ~(0b10111111), ~(0b10000110), ~(0b11011011), ~(0b11001111), ~(0b11100110), ~(0b11101101),
                   ~(0b11111101), ~(0b10000111), ~(0b11111111), ~(0b11101111)};



void ADC_init() {
    // konfiguracja napięcia referencyjnego – wybrać napięcie AVCC
    cbi(ADMUX, REFS1);
    sbi(ADMUX, REFS0);

    // konfiguracja podzielnika częstotliwości dla układu przetwornika (częstotliwość sygnału taktującego)
    // 8M / DivisionFactor
    sbi(ADCSRA, ADPS0);
    sbi(ADCSRA, ADPS1);
    sbi(ADCSRA, ADPS2);

    // uruchomienie układu przetwornika
    sbi(ADCSRA, ADEN);

    // konfiguracja | wybór kanału/pinu na którym będzie dokonywany pomiar
    cbi(ADMUX, MUX0);
    cbi(ADMUX, MUX1);
    cbi(ADMUX, MUX2);
    cbi(ADMUX, MUX3);
    cbi(ADMUX, MUX4);
}

uint16_t ADC_10bit() {
    sbi(ADCSRA, ADSC);
    loop_until_bit_is_set(ADCSRA, ADSC);
    return ADC;
}


int ConvertToVoltage(uint16_t ADC) {
    return (5 * ADC / 1023) * 100;

}


//Inicjalizacja Timer1 do wywolywania przerwania co 1s
void TimerInit() {
  //Wybranie trybu pracy CTC z TOP OCR1A
  cbi(TCCR1B, WGM13);
  sbi(TCCR1B, WGM12);
  cbi(TCCR1A, WGM11);
  cbi(TCCR1A, WGM10);
  //Wybranie dzielnika czestotliwosci
  sbi(TCCR1B, CS10);
  cbi(TCCR1B, CS11);
  sbi(TCCR1B, CS12);
  
  //Zapisanie do OCR1A wartosci odpowiadajacej 0,5s
  OCR1A = 3906/2;
  //Uruchomienie przerwania OCIE1A
  sbi(TIMSK, OCIE1A);
}

//Inicjalizacja portow do obsługi wyswietlacza 7 segmentowego
void seg7Init() {
  //Inicjalizacja kolumn
  DDRD = 0xFF;
  DDRC = 0x1;
  //Inicjalizacja segmentu

}

//Wyswietla na wyswietlaczu 7 segmentowym cyfre z argumentu
void seg7ShowCyfra(uint8_t cyfraDoWyswietlenia) {
  PORTD = cyfra[cyfraDoWyswietlenia];   //co to robi - wytlumaczyc prowadzacemu
}

void seg7ShowMin(uint8_t cyfraDoWyswietlenia) {
  PORTD = min[cyfraDoWyswietlenia];   //co to robi - wytlumaczyc prowadzacemu
}

//Wyswietla na wyswietlaczu 7 segmentowym wartosc ze zmiennej liczba7Seg
void seg7Show4Cyfry(uint16_t liczba) {
  PORTC = 0b1110;
      seg7ShowCyfra(liczba%10);
     // _delay_ms(1);
      if (liczba > 9)
      {
        PORTC = 0b1101;
        seg7ShowCyfra((liczba % 100) / 10);
      }
    //  _delay_ms(1);
      if (liczba > 99)
      {
        PORTC = 0b1011;
        seg7ShowCyfra((liczba % 1000) / 100);
      }
    //  _delay_ms(1);
      if (liczba > 999)
      {
        PORTC = 0b0111;
        seg7ShowCyfra((liczba % 10000) / 1000);
      }
     // _delay_ms(1);
      if (liczba > 9999)
      {
        liczba = 0;
        PORTC = 0b1110;
        seg7ShowCyfra(liczba);
      }
      _delay_ms(1);
}

void seg7zegarek(uint16_t liczba) {
  PORTC = 0b1110;
      seg7ShowCyfra(liczba%10);

      if (liczba > 9)
      {
        PORTC = 0b1101;
        seg7ShowCyfra((liczba % 60) / 10);
      }

      if (liczba > 59)
      {
        PORTC = 0b1011;
        seg7ShowMin((liczba % 600) / 60);
      }

      if (liczba > 599)
      {
        PORTC = 0b0111;
        seg7ShowCyfra((liczba % 6000) / 600);
      }

      if (liczba > 5999)
      {
        liczba = 0;
        PORTC = 0b1110;
        seg7ShowCyfra(liczba);
      }

}

//Funkcja wyswietla na wyswietlaczu litery, cyfry z tablicy znaki
/*      zadanie na ocenę 5.5              */
void seg7Show4Litery(uint8_t cyfraDoWyswietlenia) {
  PORTD = znaki[cyfraDoWyswietlenia];
}

int main() {
  minuty = 0;
  sekundy = 0;
  liczba7Seg = 0;
  TimerInit();
  seg7Init();
  licz=0;

  sei();  //funkcja uruchamia globalne przerwania



  // Wyświetlanie 1 cyfry
//      PORTC = 0x0;
//      while (1) {
//        seg7ShowCyfra(0);
//        _delay_ms(100);
//      }

  //  // Wyświetlanie 4 cyfr
//      while (1) {
//      seg7zegarek(licz);
//      }

// Wyświetlanie Liter
//      while(1)
//      {
//        seg7Show4Litery(1);
//      }

      while(1)
      {
        //seg7Show4Cyfry(ConvertToVoltage(ADC_10bit()));
        _delay_ms(2000);
      }

  return 0;
}

//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer1
ISR(TIMER1_COMPA_vect) {
  // seg7Show4Cyfry(ConvertToVoltage(ADC_10bit()));
}
