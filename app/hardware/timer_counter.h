/**********INTERRUPT*************/
volatile unsigned int tcnt2; //valore da cui il contatore del timer1 partirà ad ogni ciclo
volatile int counter = 0;


void setTimer()
{
  //inizializzo i registri utili per fa funzionare il timer
  TIMSK2 &= ~(1 << TOIE2);                  //setto a zero il "timer overflow interrupt enable" così per essere sicuro che sia disattivato
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20)); //setto a 0 WGM21, WGM20 e WGM22 per
  TCCR2B &= ~(1 << WGM22);                  //impostare la modalità normal mode of operation
  ASSR &= ~(1 << AS2);                      //metto a zero AS2 per non usare al clock
  TIMSK2 &= ~(1 << OCIE2A);                 //metto a zero OCIE2A per abilitare l'interrupt del compare macht A, interrupt fortnito dal comparatore fra tcnt2 e TOP (normal mode)
  TCCR2B |= (1 << CS22);                    //setto i CS2x a 111 per impostare 1024
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  tcnt2 = 0; //da cambiare nel caso si volesse cambiare la velocità
}

void startTimer()
{
  if (!(TIMSK2 && B00000001))
  {
    TCNT2 = tcnt2;          //imposto il contatore
    TIMSK2 |= (1 << TOIE2); //setto a uno il "timer overflow interrupt enable
  }
}

ISR(TIMER2_OVF_vect) //routine chiamata quando avviene il match con il TOP
{
  TCNT2 = tcnt2; //riporto il counter al valore iniziale da cui voglio farlo partire
  counter++;
  //TIMSK2 &= ~(1 << TOIE2); //disabilito l'interrupt overflow per stoppare il contatore
}
