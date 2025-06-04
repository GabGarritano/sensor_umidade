# Monitor de Umidade do Solo com Arduino Uno

## 🚀 **BAIXE O CÓDIGO AQUI:** [sensor_umidade_solo.ino](https://github.com/GabGarritano/sensor_umidade/blob/main/code.ino) 

---

Este projeto demonstra um sistema simples para monitorar a umidade do solo, utilizando um par de fios de cobre como sensor improvisado, um Arduino Uno, um display LCD, um buzzer e LEDs para feedback visual e sonoro.

---

## 1. Objetivos do Projeto

O objetivo principal deste projeto é criar um sistema de **monitoramento de umidade do solo de baixo custo e fácil montagem**, ideal para iniciantes em eletrônica e Arduino. Especificamente, o projeto visa:

* **Medir a umidade do solo:** Utilizando um sensor de umidade improvisado (fios de cobre), determinar o nível de umidade presente no substrato.
* **Fornecer feedback visual:** Exibir o valor da umidade em um display LCD 16x2.
* **Alertar sobre solo seco:** Ativar um buzzer e um LED vermelho quando a umidade do solo cair abaixo de um nível pré-definido, indicando a necessidade de rega.
* **Indicar solo úmido:** Acender um LED verde quando a umidade do solo estiver em níveis adequados.

---

## 2. Materiais Necessários

Para montar este projeto, você precisará dos seguintes componentes:

* **Placa Microcontroladora:** Arduino Uno
* **Display:** Liquid Crystal Display (LCD) 16x2
* **Sensor de Umidade do Solo:** Sensor improvisado com dois fios de cobre e jumpers (alternativamente, pode usar um sensor de umidade do solo capacitivo ou resistivo).
* **Atuador Sonoro:** Buzzer
* **LEDs:**
    * 1x LED Vermelho (para indicar solo seco)
    * 1x LED Verde (para indicar solo úmido)
* **Resistores:**
    * 2x resistores de 220Ω (para os LEDs)
    * Outros resistores podem ser necessários para o LCD, dependendo do modelo.
* **Jumpers:** Fios macho-macho e macho-fêmea
* **Protoboard:** Para montagem dos circuitos
* **Cabo USB:** Para alimentar e programar o Arduino Uno

---

## 3. Montagem do Circuito

A montagem do circuito envolve a conexão do sensor, display, buzzer e LEDs ao Arduino Uno.

### 3.1. Conexões Comuns (Alimentação)

* Conecte o pino **GND** de todos os componentes (LCD, buzzer, LEDs e sensor) ao pino **GND** do Arduino Uno.
* Conecte o pino **5V** do LCD, buzzer e LEDs ao pino **5V** do Arduino Uno.

### 3.2. Conexões Específicas dos Componentes

* **Display Liquid Crystal (LCD 16x2):**
    * `RS` (LCD) $\rightarrow$ Pino **Digital 13** do Arduino
    * `Enable` (LCD) $\rightarrow$ Pino **Digital 12** do Arduino
    * `D4` (LCD) $\rightarrow$ Pino **Digital 5** do Arduino
    * `D5` (LCD) $\rightarrow$ Pino **Digital 4** do Arduino
    * `D6` (LCD) $\rightarrow$ Pino **Digital 3** do Arduino
    * `D7` (LCD) $\rightarrow$ Pino **Digital 2** do Arduino
    * Conecte os pinos de contraste (`Vo`), VSS e VDD conforme a documentação específica do seu LCD (geralmente, VSS ao GND, VDD ao 5V e Vo a um potenciômetro ou diretamente ao GND/5V para ajuste de contraste).

* **Sensor de Umidade (Fios de Cobre):**
    * Um dos fios de cobre $\rightarrow$ Pino **Analógico A0** do Arduino
    * O outro fio de cobre $\rightarrow$ Pino **5V** do Arduino (ou GND, dependendo da calibração que você fará no código para a leitura de umidade).
    * *Importante:* Para este tipo de sensor resistivo, a leitura analógica varia conforme a condutividade da água no solo.

* **Buzzer:**
    * Pino Positivo (+) do Buzzer $\rightarrow$ Pino **Digital 8** do Arduino
    * Pino Negativo (-) do Buzzer $\rightarrow$ Pino **GND** do Arduino

* **LED Vermelho (Solo Seco):**
    * Perna mais longa (Anodo) do LED $\rightarrow$ Resistor de 220Ω $\rightarrow$ Pino **Digital 9** do Arduino
    * Perna mais curta (Catodo) do LED $\rightarrow$ Pino **GND** do Arduino

* **LED Verde (Solo Úmido):**
    * Perna mais longa (Anodo) do LED $\rightarrow$ Resistor de 220Ω $\rightarrow$ Pino **Digital 10** do Arduino
    * Perna mais curta (Catodo) do LED $\rightarrow$ Pino **GND** do Arduino

---

## 4. Como Utilizar o Código (Arduino IDE)

### 4.1. Preparação da Arduino IDE

1.  **Instalar Bibliotecas Necessárias:**
    * Vá em `Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...`.
    * Pesquise e instale a seguinte biblioteca:
        * **`LiquidCrystal by Arduino`** (geralmente já vem instalada com a IDE, mas verifique se há alguma atualização ou se é a versão correta).

### 4.2. Configuração do Código

1.  **Abra o Código:** Carregue o arquivo `monitor_umidade_solo.ino` na Arduino IDE.

2.  **Ajuste o Limite de Umidade (`seco`):**
    * No seu código, a linha `const int seco = 10;` define o limiar de umidade abaixo do qual o solo é considerado "seco".
    * Você precisará **calibrar este valor** experimentalmente para o seu sensor improvisado e tipo de solo.
    * **Calibração:**
        1.  Com o sensor inserido em solo bem seco, observe a leitura de `umidade` no `Serial Monitor`. Anote esse valor.
        2.  Com o sensor inserido em solo úmido (mas não encharcado), observe a leitura de `umidade` no `Serial Monitor`. Anote esse valor.
        3.  Defina `seco` como um valor intermediário que você considere adequado para indicar a necessidade de rega. Por exemplo, se o solo seco dá 700 e o úmido 300, um valor de `seco` de 400 ou 500 pode ser um bom ponto de partida. Ajuste conforme sua necessidade.

3.  **Configuração dos LEDs (Ajuste no Código):**
    * No código fornecido, quando a umidade é `< seco`, o LED e o buzzer são ativados. Isso corresponde ao seu LED vermelho.
    * Na parte `else`, o LED e o buzzer são desativados. Para acender o LED verde neste caso, você precisará adicionar uma linha:

    ```cpp
    if (umidade < seco) {
      digitalWrite(led, HIGH); // LED VERMELHO (solo seco)
      digitalWrite(seco, LOW); // Garante que o LED verde está desligado
      digitalWrite(buzzer, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Solo muito seco, regar");
    } else {
      digitalWrite(led, LOW); // LED VERMELHO DESLIGA
      digitalWrite(seco, HIGH); // LED VERDE LIGA (solo umido)
      digitalWrite(buzzer, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Solo umido");
    }
    ```
    * **Observação:** No seu código, você usou `const int seco = 10;` e depois `digitalWrite(seco, LOW/HIGH);`. Isso fará com que o pino digital 10 seja controlado. Certifique-se de que o LED verde está conectado ao pino 10, e que `led` (pino 9) é o LED vermelho.

### 4.3. Upload do Código

1.  Conecte o Arduino Uno ao seu computador usando o cabo USB.
2.  Em `Ferramentas > Porta`, selecione a porta serial correspondente ao seu Arduino Uno.
3.  Em `Ferramentas > Placa`, selecione "Arduino Uno".
4.  Clique no botão "Upload" (seta para a direita) para compilar e enviar o código para o Arduino.

---

## 5. Funcionamento

Após o upload do código e a montagem correta do circuito:

1.  O display LCD exibirá "Hello There" por 3 segundos e depois limpará.
2.  A cada 50 milissegundos (definido por `delay(50)`), o Arduino lerá o valor de umidade do sensor no pino analógico A0.
3.  A leitura da umidade será exibida no display LCD na primeira linha.
4.  Se a leitura de umidade for menor que o valor definido em `seco`:
    * O LED vermelho acenderá.
    * O buzzer emitirá um som.
    * A segunda linha do LCD exibirá "Solo muito seco, regar".
5.  Se a leitura de umidade for igual ou maior que o valor definido em `seco`:
    * O LED vermelho apagará.
    * O LED verde acenderá.
    * O buzzer parará de emitir som.
    * A segunda linha do LCD exibirá "Solo umido".

Este sistema simples fornecerá feedback imediato sobre as condições de umidade do solo, ajudando a manter suas plantas saudáveis.
