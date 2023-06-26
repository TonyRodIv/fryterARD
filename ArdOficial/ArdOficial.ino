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
int pushButton = 5;

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

  // Define o pino de entrada do botão
  pinMode(pushButton, INPUT);

  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Lê a distância em milímetros do sensor ultrassônico
  int distanceM = ultraSensor.distanceInMillimeters();

  // Mapeia a distância para uma variação entre 0 e 100
  variation = map(distanceM,20,4000,0,100);

  // Se a variação for menor que 1, desliga o LED branco e a válvula da tampa
  if (variation < 1) {
    digitalWrite(LEDW, LOW);
    digitalWrite(VALVTAMPA, LOW);
    // delay(20000); // Comentado pois não é usado
  } 
  // Senão, liga o LED branco e a válvula da tampa
  else {
    digitalWrite(VALVTAMPA, HIGH);
    digitalWrite(LEDW, HIGH);
  }

  // Lê o valor analógico do sensor de fluído e mapeia para uma escala entre 0 e 10

  fluidSensor = map(analogRead(SENSORLIQU),0,1023,0,10);

  // Imprime o valor do sensor de fluído na serial
  Serial.println(fluidSensor);

  // Se o valor do sensor for maior que 5, assume que é água
  if (fluidSensor > 5) {
    // Liga o LED azul e a válvula do fundo
    digitalWrite(LEDB, HIGH);
    digitalWrite(VALVFUNDO, HIGH);
  } 
  // Senão, assume que não é água
  else {
    // Desliga o LED azul e a válvula do fundo
    digitalWrite(VALVFUNDO, LOW);
    digitalWrite(LEDB, LOW);
  }

  // Chama a função para ler o botão
  readButton();
}

// Função para ler o botão
void readButton() {
  // Lê o estado do botão
  int buttonState = digitalRead(pushButton);

  // Imprime o estado do botão na serial
  // Serial.println(buttonState);
  // Aguarda um milissegundo
  delay(1);

  // Se o botão estiver pressionado, liga o LED vermelho
  if (buttonState > 0) {
    digitalWrite(LEDR, HIGH);
  } 
  // Senão, desliga o LED vermelho
  else {
    digitalWrite(LEDR, LOW);
  }
}
