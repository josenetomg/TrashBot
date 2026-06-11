# Trash Bot 

Este é um projeto de automação e robótica bastante completo, integrando interface de entrada (teclado), saída visual (LCD Nokia), detecção de presença (Ultrassom) e áudio (ISD1820).

Como o **Arduino Nano** possui recursos limitados de memória e pinagem, utilizaremos uma organização rigorosa dos pinos para evitar conflitos com o Shield L293D e a comunicação SPI do display.

---

### 1. Lista de Peças

* **1x Arduino Nano** (ATmega328P).
* **1x Shield Motor L293D** (Versão compatível com Nano ou módulos independentes).
* **1x Teclado Matricial 4x4** (Teclado de telefone).
* **1x Display LCD Nokia 5110** (84x48 pixels).
* **1x Sensor Ultrassom HC-SR04**.
* **1x Módulo de Voz ISD1820** (Com alto-falante).
* **2x Motores DC**.
* **Jumpers e Protoboard**.

---

### 2. Mapeamento de Pinos (Pinout Sugerido)

| Componente | Pinos Arduino Nano | Observação |

| **L293D** | D11, D3, D5, D6 | Motores 1 e 2 (PWM) |

| **Teclado (Linhas)** | D2, D4, D7, D8 | Entradas Digitais |

| **Teclado (Colunas)** | D9, D10, A0 | Entradas Digitais |

| **LCD Nokia 5110** | D13 (CLK), D11 (DIN), D12 (DC), A1 (CE), A2 (RST) | SPI Protocol |

| **Ultrassom HC-SR04** | A3 (Trig), A4 (Echo) | Sensor de proximidade |

| **ISD1820** | A5 | Pino de Play (Trigger) |

---

### 3. Código do Aplicativo (C++)

Este código utiliza as bibliotecas `Keypad` para o teclado, `Adafruit_PCD8544` para o LCD e a lógica de memória para gravação de movimentos.

```cpp
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
```
### Dica Profissional:

O **LCD Nokia 5110** opera em **3.3V**. Certifique-se de usar resistores de 10k em série ou um conversor de nível lógico entre os pinos do Nano (5V) e o LCD para não danificar o display. O módulo **ISD1820** pode ser alimentado diretamente pelos 5V do Arduino, mas o disparo pelo pino analógico (`A5`) como digital é seguro e eficiente.


## 📚 Referências

1. **BANZI, M.** *Getting Started with Arduino*. O'Reilly Media, 2011.
2. **DATASHEET HC-SR04.** *Ultrasonic Sensor Module*. Disponível em: [Documentação técnica].
3. **DALLAS SEMICONDUCTOR.** *DS18B20 Programmable Resolution 1-Wire Digital Thermometer*.
4. **ORGANIZAÇÃO MUNDIAL DA SAÚDE (OMS).** *Prevenção e Controle da Dengue*. 2024.

---

*Projeto desenvolvido por Jose Joaquim Brandão Neto e apresentado no Arduino Day.*

----
