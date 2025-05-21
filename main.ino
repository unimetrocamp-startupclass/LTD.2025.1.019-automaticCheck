#include "HX711.h" //importando biblioteca HX711

HX711 scale;

// declarando pinos e variaveis úteis

//HX711
const int pinSCK = A0; // pino SDK ligado a entrada A0
const int pinDT = A1; //pino DT ligado a entrada A1
float peso = 0; // status do peso 

//Botão
const int pinBot = A2; //pino de entrada do botão
int statusBot = 0; //status do botão

//Led
const int pinLed = A3; //pino de entrada do led

void setup() {
  Serial.begin(9600);

  Serial.println("inicializando escala.");
  scale.begin(pinDT, pinSCK);

  Serial.println("inicializando tara.");
  scale.tare();

  Serial.println("inicializando calibração.");
  scale.set_scale(420); //2kg = 840

  Serial.println("inicializando botão");
  pinMode(pinBot, INPUT_PULLUP);

  Serial.println(("inicializando led"));
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, HIGH);
  delay(500);
  digitalWrite(pinLed, LOW);

  Serial.println("pronto.");
}


void loop() {
  statusBot = digitalRead(pinBot); //definindo status do botão

  //condição de botão pressinado para nova tara
  if (statusBot == LOW) {
    Serial.println("nova tara.");
    scale.tare();
  }
  
  peso = scale.get_units(); //definindo variavel do peso usado na estrutura do led

  //condição do aviso
  if (peso < 0){
    digitalWrite(pinLed, HIGH); //ascende o led
    delay(200);
    digitalWrite(pinLed, LOW); //apaga o led
    delay(200);
    Serial.println("abaixo do peso."); // aviso de peso limite ultrapassado
  }
  //condição de pesagem
  else{
    //mostra o peso 
    Serial.print(peso, 1);
    Serial.println(" kg");
    delay(500);
  }
}
