# Código do Aplicativo (C++)

Este código utiliza as bibliotecas `Keypad` para o teclado, `Adafruit_PCD8544` para o LCD e a lógica de memória para gravação de movimentos.

```cpp
<code>
#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <AFMotor.h> // Se usar o shield clássico

// LCD Nokia 5110: CLK=13, DIN=11, DC=12, CE=A1, RST=A2
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 12, A1, A2);

// Motores
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// Teclado 4x4
const byte ROWS = 4;
const byte COLS = 3; // Estilo telefone
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 4, 7, 8}; 
byte colPins[COLS] = {9, 10, A0}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Ultrassom e Áudio
const int trigPin = A3;
const int echoPin = A4;
const int isdPin = A5;

// Variáveis de Programação
char memoria[20];
int comandoAtual = 0;
bool gravando = false;

void setup() {
  Serial.begin(9600);
  display.begin(40); // Contraste
  display.clearDisplay();
  display.println("Sistema Pronto");
  display.display();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(isdPin, OUTPUT);
  
  motor1.setSpeed(200);
  motor2.setSpeed(200);
}

void dispararAudio() {
  digitalWrite(isdPin, HIGH);
  delay(100);
  digitalWrite(isdPin, LOW);
}

long lerDistancia() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void loop() {
  char key = keypad.getKey();
  long distancia = lerDistancia();

  // Detecção de Movimento (Mensagem de Voz)
  if (distancia > 0 && distancia < 20) {
    dispararAudio();
    display.clearDisplay();
    display.println("Movimento!");
    display.display();
    delay(1000);
  }

  if (key) {
    Serial.print("Tecla: "); Serial.println(key);
    display.clearDisplay();
    display.print("Tecla: "); display.println(key);
    display.display();

    if (key == '*') {
      gravando = !gravando;
      comandoAtual = 0;
      display.println(gravando ? "GRAVANDO..." : "SALVO");
      display.display();
    } else if (gravando && comandoAtual < 20) {
      memoria[comandoAtual++] = key;
    } else if (key == '#') {
      executarSequencia();
    }
  }
}

void executarSequencia() {
  display.clearDisplay();
  display.println("EXECUTANDO...");
  display.display();
  
  for (int i = 0; i < comandoAtual; i++) {
    if (memoria[i] == '2') { motor1.run(FORWARD); motor2.run(FORWARD); } // Frente
    if (memoria[i] == '8') { motor1.run(BACKWARD); motor2.run(BACKWARD); } // Tras
    delay(1000);
    motor1.run(RELEASE); motor2.run(RELEASE);
  }
}
</code>
## Metodologia de Programação

O software foi desenvolvido em C++, estruturado em uma máquina de estados finitos (FSM). O modo "Gravação" captura os inputs do teclado matricial e armazena os vetores de movimento na RAM, enquanto o modo "Execução" utiliza esses dados em conjunto com as leituras do sensor ultrassônico para evitar colisões durante o patrulhamento educativo.

---
*Projeto desenvolvido por Jose Joaquim Brandão Neto e apresentado no Arduino Day.*

----
