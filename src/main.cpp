
#include<Arduino.h>
const  int PulseIN = 7;      // pulse counter pin
float ONCycle;              //oncycle  variable 
float OFFCycle;             // offcycle variable got microsecond
float  T;                    // tota l time to one cycle ONCycle + OFFcycle
int F;                      //  Frequency = 1/T
float DutyCycle;            // D = (TON/(TON+TOFF))*100 %
float frequency[200] = {0};
int qtdFrequency = 0;
double somaFrequency = 0;
float mediaFrequency = 0;


void  setup()
{
  pinMode(PulseIN, INPUT);
  Serial.begin(9600);
}

// Função de comparação para qsort
int comparar(const void *a, const void *b) {
    float diferenca = (*(float*)a - *(float*)b);
    if (diferenca > 0) return 1;
    else if (diferenca < 0) return -1;
    else return 0;
}

void  loop()
{
  while (qtdFrequency <200){
    ONCycle = pulseIn(PulseIN, HIGH);
    OFFCycle = pulseIn(PulseIN,  LOW);
    // Serial.println(ONCycle);
    // Serial.println(OFFCycle);
    if(ONCycle != 0 || OFFCycle != 0){
      T =  ONCycle + OFFCycle;
      DutyCycle = (ONCycle / T) * 100;
      F = 1000000 / T;                    // 1000000= microsecond 10^-6 goes to upper
      if (F >0){
        frequency[qtdFrequency] = F;
        qtdFrequency +=1;
      }
    }
  }
  int tamanho = sizeof(frequency) / sizeof(frequency[0]);
  qsort(frequency, tamanho, sizeof(float), comparar);

  qtdFrequency = 20;
  for(int i = 0; i < qtdFrequency; i++){
    somaFrequency += frequency[i];
  }

  int lt_length = sizeof(frequency) / sizeof(frequency[0]);
  

  

  mediaFrequency = somaFrequency / qtdFrequency;

  Serial.print("Media Frequency  = ");
  Serial.print(mediaFrequency);
  Serial.print(" Hz");
  Serial.print("\n");
  Serial.print("DutyCycle = ");
  Serial.print(DutyCycle, 2);
  Serial.print("  %");
  Serial.print("\n");
  delay(3000);

  qtdFrequency = 0;
  somaFrequency = 0;

}