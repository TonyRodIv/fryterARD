#define VALVFUNDO 8
#define SENSORLIQU A2
#define LEDB 12
#define LEDW 13
#define LEDR 4

int fluidSensor;
int contador = 0;

void setup() {
    pinMode(VALVFUNDO, OUTPUT);
    pinMode(LEDB, OUTPUT);
    pinMode(LEDW, OUTPUT);
    pinMode(LEDR, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    fluidSensor = map(analogRead(SENSORLIQU), 0, 1023, 0, 20);
    Serial.println(fluidSensor);
    if (fluidSensor > 14) {
        digitalWrite(LEDB, HIGH);
        digitalWrite(LEDW, LOW);
        if (contador <= 20) {
            if (contador == 19) {
                waterDetected();
            } else {
                if (fluidSensor < 15) {
                    contador = 21;
                } else {
                    Serial.println(contador);
                    delay(1000);
                    contador++;
                }
            }
        }
    } else {
        digitalWrite(LEDW, HIGH);
        oilDetected();
    }
}

void waterDetected() {
    digitalWrite(VALVFUNDO, HIGH);
    digitalWrite(LEDR, HIGH);
}

void oilDetected() {
    digitalWrite(VALVFUNDO, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDR, LOW);
    contador = 0;
}
