#include "GLOBAL.h"

volatile uint8_t minuty, sekundy;
volatile uint16_t liczba7Seg;
volatile uint16_t licz;

volatile char znaki[4] = { ~(0b01110111), ~(0b01111100), ~(0b00111001), ~(0b01011110)};


char cyfra[10] = { ~(0b00111111), ~(0b00000110), ~(0b01011011), ~(0b01001111), ~(0b01100110), ~(0b01101101),
                   ~(0b01111101), ~(0b00000111), ~(0b01111111), ~(0b01101111)};

char min[10] = { ~(0b0111111), ~(0b0000110), ~(0b1011011), ~(0b1001111), ~(0b1100110), ~(0b1101101),
                   ~(0b1111101), ~(0b0000111), ~(0b1111111), ~(0b1101111)};



void ADC_init() {
    // konfiguracja napięcia referencyjnego – wybrać napięcie AVCC
	sbi(ADMUX, REFS0);
		cbi(ADMUX, REFS1);

	//	Czestotliwosc sygnalu taktujacego 62,5 kHz
		sbi(ADCSRA, ADPS0);
		sbi(ADCSRA, ADPS1);
		sbi(ADCSRA, ADPS2);

		sbi(ADCSRA, ADEN); //Wlaczenie przetwornika

	//	Konfiguracja ustawia ADC do pomiaru
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


uint16_t ConvertToVoltage(uint16_t  adc) {
    return ((5.00 * adc / 1023.00) * 100.00);
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

  // 100Hz
  OCR1A = 78;
  //Uruchomienie przerwania OCIE1A
  sbi(TIMSK, OCIE1A);
}


void seg7Init() {

  //Inicjalizacja kolumn
   for(int i=0; i<7; i++){
    	sbi(DDRD, i);
    }

  for(int i=0; i<4; i++){
    	sbi(DDRC, i);
    }
  //Inicjalizacja segmentu

}



void seg7ShowCyfra(uint8_t cyfraDoWyswietlenia) {			//Wyswietla na wyswietlaczu 7 segmentowym cyfre z argumentu
  PORTD = cyfra[cyfraDoWyswietlenia];
}

void seg7ShowMin(uint8_t cyfraDoWyswietlenia) {
  PORTD = min[cyfraDoWyswietlenia];   //co to robi - wytlumaczyc prowadzacemu
}

//Wyswietla na wyswietlaczu 7 segmentowym wartosc ze zmiennej liczba7Seg
void seg7Show4Cyfry(uint16_t liczba) {
  PORTC = 0b1110;
      seg7ShowCyfra(liczba%10);
      _delay_ms(2);
      if (liczba > 9)
      {
        PORTC = 0b1101;
        seg7ShowCyfra((liczba % 100) / 10);
      }
      _delay_ms(2);
      if (liczba > 99)
      {
        PORTC = 0b1011;
        seg7ShowCyfra((liczba % 1000) / 100);
      }
      _delay_ms(2);
      if (liczba > 999)
      {
        PORTC = 0b0111;
        seg7ShowCyfra((liczba % 10000) / 1000);
      }
      _delay_ms(2);
      if (liczba > 9999)
      {
        liczba = 0;
        PORTC = 0b1110;
        seg7ShowCyfra(liczba);
      }
      //_delay_ms(2);
}


volatile int pomiar;


int main() {
  minuty = 0;
  sekundy = 0;
  TimerInit();
  seg7Init();
  ADC_init();
  licz=0;

  sei();  //funkcja uruchamia globalne przerwania


      while(1)
      {
			pomiar = ConvertToVoltage(ADC_10bit());
    	  //seg7Show4Cyfry(ConvertToVoltage(ADC_10bit()));
    	  //seg7Show4Cyfry(ConvertToVoltage(500));
    	  // seg7Show4Cyfry(2137);
        _delay_ms(100);
      }

  return 0;
}

//Funkcja uruchamiana z przerwaniem po przepelnieniu licznika w timer1
ISR(TIMER1_COMPA_vect) {
	//seg7Show4Cyfry(ConvertToVoltage(ADC_10bit()));
	seg7Show4Cyfry(pomiar);
}
