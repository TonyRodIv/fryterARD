#include <hcsr04.h>

// Define as constantes dos pinos
#define TRIG 7
#define ECHO 10
#define VALVFUNDO 8
#define VALVTAMPA 6
#define SENSORLIQU A2
#define LEDB 12
#define LEDW 13
#define LEDR 4

// Define a constante da distância
#define DISTANCIA 50

// Cria o objeto do sensor ultrassônico
HCSR04 ultraSensor(TRIG, ECHO, 20, 4000);

// Define a variável do botão
int contador = 0;

// Define as variáveis globais do sensor de fluído e da variação
int fluidSensor;
int variation;

void setup() {
  // Define os pinos de saída
  pinMode(VALVFUNDO, OUTPUT);
  pinMode(VALVTAMPA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDW, OUTPUT);
  pinMode(LEDR, OUTPUT);
  
  // Define os pinos do sensor ultrassônico
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);


  // Inicializa a comunicação serial
  Serial.begin(9600);
  repetir();
}

void loop() {
  
  echoSensor();
  // Lê o valor analógico do sensor de fluído e mapeia para uma escala entre 0 e 10

  fluidSensor = map(analogRead(SENSORLIQU),0,1023,0,10);

  // Imprime o valor do sensor de fluído na serial
  // Serial.println(fluidSensor);

  // Se o valor do sensor for maior que 5, assume que é água
  if (fluidSensor <= 5) {
    // Desliga o LED azul e a válvula do fundo
    repetir();
  } 
  // Senão, assume que não é água
  else {
    // Liga o LED azul e a válvula do fundo
    digitalWrite(LEDB, HIGH);
    repetir();
  }

  // Chama a função para ler o botão
}

void echoSensor(){
  // Lê a distância em milímetros do sensor ultrassônico
  int distanceM = ultraSensor.distanceInMillimeters();

  // Mapeia a distância para uma variação entre 0 e 100
  variation = map(distanceM,20,4000,0,100);

  // Se a variação for menor que 1, desliga o LED branco e a válvula da tampa
  if (variation < 1) {
    digitalWrite(LEDW, LOW);
    delay(800);
    digitalWrite(VALVTAMPA, LOW);
    // delay(20000); // Comentado pois não é usado
  } 
  // Senão, liga o LED branco e a válvula da tampa
  else {
    digitalWrite(LEDW, HIGH);
    delay(300);
    digitalWrite(VALVTAMPA, HIGH);
  }
}
// Função para ler o botão
void fluidSensorWater() {
    delay(500);
    digitalWrite(LEDR,HIGH);
    digitalWrite(VALVFUNDO, HIGH);
}
void fluidSensorOther() {
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDB,LOW);
    digitalWrite(VALVFUNDO, LOW);
    contador = 0;
}

void repetir() {
  // Incrementa o contador em um
  // Imprime o valor do contador na porta serial
  Serial.println(contador);
  
  // Se o contador for menor que 20, chama a função novamente
  if(fluidSensor>5){

  if (contador < 20) {
  contador = contador + 1;
  echoSensor();
    delay(1000);
        if(contador==19){
         fluidSensorWater();
     }
    repetir();
  }
  }else{
    echoSensor();
      fluidSensorOther();
  }
}
