#include <AFMotor.h>
#define trig A0
#define echo A1
#define buzzer 12

#define botaoVoltar 2
#define botaoEsquerda 3
#define botaoDireita 4

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botaoVoltar, INPUT);
  pinMode(botaoEsquerda, INPUT);
  pinMode(botaoDireita, INPUT);

  motor1.setSpeed(150);
  motor2.setSpeed(150);
}

void loop() {
  if (digitalRead(botaoVoltar) == HIGH) {
    voltar();
    return;
  }
  if (digitalRead(botaoEsquerda) == HIGH) {
    virarEsquerda();
    return;
  }
  if (digitalRead(botaoDireita) == HIGH) {
    virarDireita();
    return;
  }

  long distancia = medirDistancia();

  if (distancia < 10) {
    digitalWrite(buzzer, HIGH);
    virarDireita(); // ou esquerda, tanto faz
    delay(400);
    digitalWrite(buzzer, LOW);
  } else if (distancia < 20) {
    virarEsquerda();
  } else {
    frente();
  }
}

long medirDistancia() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long tempo = pulseIn(echo, HIGH);
  long distancia = tempo * 0.034 / 2;
  return distancia;
}

void frente() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void voltar() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(500);
}

void virarDireita() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(400);
}

void virarEsquerda() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(400);
}
