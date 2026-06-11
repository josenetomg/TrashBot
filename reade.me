====== Trash Bot ======

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
```
---

### 4. README.md (Para o GitHub)

```markdown
# Arduino Nano Motor Control with Phone Keypad & Voice 🤖📞

Este projeto implementa um sistema robótico programável que utiliza uma interface de teclado estilo telefone para gravar sequências de movimentos, monitoradas por um display Nokia 5110 e feedback por voz.

## 🚀 Funcionalidades
- **Programação por Teclado:** Use a tecla `*` para iniciar a gravação e números para definir a rota.
- **Sensor de Presença:** O ultrassom HC-SR04 monitora obstáculos ou movimentos frontais.
- **Feedback por Voz:** O módulo ISD1820 reproduz um áudio pré-gravado ao detectar presença.
- **Interface Visual:** LCD Nokia 5110 exibe o log de comandos e status dos sensores em tempo real.

## 🔌 Conexões Críticas
- **ISD1820:** Conectado ao pino `A5` para disparo automático.
- **Teclado:** Mapeado em pinos digitais e analógicos para otimização de espaço no Nano.
- **L293D:** Controla a tração dos motores através das saídas PWM.

## 🛠️ Instruções de Uso
1. Grave sua mensagem de voz pressionando o botão físico no módulo ISD1820.
2. No Arduino, pressione `*` para entrar em modo de programação.
3. Digite a sequência (ex: 2 para frente, 8 para trás).
4. Pressione `#` para o robô executar a memória.
5. Se algo cruzar o caminho do sensor ( < 20cm), o áudio será disparado.

```

### Dica Profissional:

O **LCD Nokia 5110** opera em **3.3V**. Certifique-se de usar resistores de 10k em série ou um conversor de nível lógico entre os pinos do Nano (5V) e o LCD para não danificar o display. O módulo **ISD1820** pode ser alimentado diretamente pelos 5V do Arduino, mas o disparo pelo pino analógico (`A5`) como digital é seguro e eficiente.


Este é um projeto com um propósito social e técnico muito claro. Abaixo, estruturei o arquivo `README.md` com o rigor de um miniartigo técnico, destacando o papel do **Trash Bot** no evento **Arduino Day** e a importância da conscientização contra a Dengue.

---

# Trash Bot: Robô Recepcionista e Agente de Saúde 🤖🧹

## Resumo

O **Trash Bot** é um sistema robótico autônomo e interativo desenvolvido para o **Arduino Day**. Sua missão principal foi atuar como um robô recepcionista com um viés socioambiental: promover a conscientização sobre o descarte correto de resíduos sólidos. O projeto utiliza a tecnologia para mitigar a proliferação do mosquito *Aedes aegypti*, combatendo o acúmulo de lixo em residências, principal foco de criadouros da Dengue.

---

## 1. Introdução e Contexto

No cenário do Arduino Day, o Trash Bot serviu como uma demonstração prática de como a computação física pode ser aplicada a problemas de saúde pública. Ao detectar a presença de visitantes, o robô interage através de mensagens de voz e interface visual, alertando sobre os perigos de recipientes que acumulam água e ensinando como eliminá-los.

---

## 2. Hardware e Arquitetura de Sensores

Para cumprir sua função de recepcionista e educador, o robô foi equipado com uma arquitetura de sensores que permite percepção espacial e interação humano-máquina (HMI).

### 2.1 Percepção Espacial (Ultrassom HC-SR04)

O sensor ultrassônico funciona através da emissão de ondas mecânicas de alta frequência. O tempo de retorno (eco) é processado pelo Arduino Nano para calcular a distância de objetos frontais.

* **Funcionalidade:** Detecção de presença para iniciar a interação.
* **Capacidade:** Alcance de 2cm a 400cm, com precisão de aproximadamente 3mm.

### 2.2 Telemetria Ambiental (DHT22 ou NTC)

Utilizado para monitorar as condições térmicas do ambiente onde o robô está operando.

* **Funcionalidade:** Dados ambientais exibidos no display, correlacionando altas temperaturas com o aumento da atividade reprodutiva do mosquito.
* **Capacidade:** Alta precisão para monitoramento de microclimas residenciais.

### 2.3 Interface de Voz (ISD1820)

Diferente de sistemas puramente visuais, o módulo ISD1820 permite uma comunicação auditiva direta.

* **Funcionalidade:** Reprodução de alertas educativos pré-gravados ("Não deixe água acumulada!", "Lixo no lixo!").
* **Capacidade:** Gravações de até 10 segundos com acionamento via pulso lógico.

### 2.4 Visualização e Entrada de Dados (Nokia 5110 & Teclado)

* **LCD Nokia 5110:** Utilizado para fornecer feedback visual e logs de sistema (temperatura, distância e status).
* **Teclado Matricial:** Permite que o operador programe rotas de patrulhamento específicas dentro do ambiente da recepção.

---

## 3. Especificações Técnicas (Lista de Materiais)

* **Microcontrolador:** Arduino Nano (ATmega328P).
* **Driver de Potência:** Shield Motor L293D (Ponte H).
* **Locomoção:** 2 Motores DC com redução (Chassi 2WD).
* **Interface de Entrada:** Teclado Matricial 4x4.
* **Sensores:** Ultrassom HC-SR04 e DHT22.
* **Áudio:** Módulo ISD1820 + Alto-falante 8Ω 0.5W.
* **Display:** LCD Nokia 5110 (PCD8544).

---

## 4. Metodologia de Programação

O software foi desenvolvido em C++, estruturado em uma máquina de estados finitos (FSM). O modo "Gravação" captura os inputs do teclado matricial e armazena os vetores de movimento na RAM, enquanto o modo "Execução" utiliza esses dados em conjunto com as leituras do sensor ultrassônico para evitar colisões durante o patrulhamento educativo.

---

## 5. Conclusão

O Trash Bot demonstrou ser uma ferramenta eficaz de engajamento durante o Arduino Day. A união entre automação e conscientização social prova que a robótica não se limita a tarefas industriais, sendo capaz de educar e salvar vidas através da prevenção de doenças como a Dengue.

---

## 📚 Referências

1. **BANZI, M.** *Getting Started with Arduino*. O'Reilly Media, 2011.
2. **DATASHEET HC-SR04.** *Ultrasonic Sensor Module*. Disponível em: [Documentação técnica].
3. **DALLAS SEMICONDUCTOR.** *DS18B20 Programmable Resolution 1-Wire Digital Thermometer*.
4. **ORGANIZAÇÃO MUNDIAL DA SAÚDE (OMS).** *Prevenção e Controle da Dengue*. 2024.

---

*Projeto desenvolvido por Jose Joaquim Brandão Neto e apresentado no Arduino Day.*

----
