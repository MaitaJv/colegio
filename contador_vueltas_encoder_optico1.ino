const int sensorPinIZ = 2;
const int sensorPinDER = 3;

float medicionesIZ = 0; //Javier gei
float medicionesDER = 0; //Ariel pro 
float medicionesIZvolatil = 0; 
float medicionesDERvolatil = 0;  

int valueIZ = 0;
int valueDER = 0;


int checkIZ = 0;
int checkDER = 0;

bool checkIZ2 = false;
bool checkDER2 = false;

float divisionesRueda = 20;

const int ENADER = 6;
const int IN1DER = 7;
const int IN2DER = 8;
const int IN3IZ = 9;
const int IN4IZ = 10;
const int ENBIZ = 11;

bool prueba = false;
bool pollo = false;
bool prueba1 = true;
bool prueba2 = true;
bool fran = false; 
bool hola = false;
bool recorridoant = false;
bool stop = false;

unsigned long tiempoAhora = 0;
int intervalo = 1000;

unsigned long tiempoAhora2 = 0;
int intervalo2 = 500;

int pwmDER = 200;
int pwmIZ = 200;

float diferenciaVPS;

float millisMedicionesDER;
float millisMedicionesIZ;

void setup () {
  Serial.begin(9600);   //iniciar puerto serie
  
  pinMode(sensorPinIZ , INPUT);  //definir pin como entrada
  pinMode(sensorPinDER , INPUT);
  
  //Verificacion de funcionamiento de los encoder a travez de l primare division
  if (valueIZ == LOW && checkIZ == 0) {
    Serial.println("Optointerruptor activado");
  }
  if (valueDER == LOW && checkDER == 0) {
    Serial.println("Optointerruptor 2 activado");
  }
  
  // Seteo de entradas y salidas
   pinMode(IN1DER, OUTPUT);
   pinMode(IN2DER, OUTPUT);
   pinMode(ENADER, OUTPUT);
   pinMode(IN3IZ, OUTPUT);
   pinMode(IN4IZ, OUTPUT);
   pinMode(ENBIZ, OUTPUT);
}

void crasheate() {
  while (1);
}

void girar(){

  if ((medicionesDERvolatil <= 5) && (recorridoant == true) )
  {
    Serial.println("girando");
    analogWrite(ENADER, pwmDER);
    analogWrite(ENBIZ, pwmIZ);

    digitalWrite(IN1DER, HIGH);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, LOW);
    digitalWrite(IN4IZ, HIGH);
    stop = true;

  }



}

void loop() {
//--------------------------------------------------------ENCODER IZQUIERDA--------------------------------------------------------------
  valueIZ = digitalRead(sensorPinIZ);  //lectura digital de pin

  if (valueIZ == LOW && checkIZ == 0) {
    medicionesIZ++;
    medicionesIZvolatil++;

    checkIZ = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueIZ == HIGH && checkIZ == 1) {
    checkIZ = 0;
  }
  float vueltasIZ = medicionesIZ / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones
  
//--------------------------------------------------------FIN ENCODER IZQUIERDA--------------------------------------------------------------
//---------------------------------------------------------ENCODER DERECHA--------------------------------------------------------------
  valueDER = digitalRead(sensorPinDER );  //lectura digital de pin

  if (valueDER == LOW && checkDER == 0) {
    medicionesDER++;
    medicionesDERvolatil++;
    checkDER = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueDER == HIGH && checkDER == 1) {
    checkDER = 0;
  }
  float vueltasDER = medicionesDER / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones
  
//--------------------------------------------------------FIN ENCODER DERECHA--------------------------------------------------------------

//----------------------------------------------------------MANEJO DE PWM-----------------------------------------------------
 if (pollo == false ){
   analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
   analogWrite(ENBIZ, pwmIZ); 
 //control direction
   digitalWrite(IN1DER, HIGH);
   digitalWrite(IN2DER, LOW);
   digitalWrite(IN3IZ, HIGH);
   digitalWrite(IN4IZ, LOW);
 }

 if (pollo == true ){
   analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
   analogWrite(ENBIZ, 0); 
 //control direction
   digitalWrite(IN1DER, LOW);
   digitalWrite(IN2DER, LOW);
   digitalWrite(IN3IZ, LOW);
   digitalWrite(IN4IZ, LOW);
   recorridoant = false;
   medicionesDERvolatil = 0;
   medicionesIZvolatil = 0;
 }

//----------------------------------------------------------FIN DE MANEJO DE PWM-----------------------------------------------------
//Codigo Javier
/*
float diferenciaDER = vueltasDER - vueltasIZ;
float diferenciaIZ = vueltasIZ - vueltasDER;

float vpsDER;
float vpsIZ;

if(millis() == (tiempoAhora + intervalo)){
  tiempoAhora = millis();
  
  vpsDER = millisMedicionesDER / divisionesRueda;
  vpsIZ = millisMedicionesIZ / divisionesRueda;

  diferenciaVPS = (vpsDER - vpsIZ)*5;

  Serial.print("Vueltas por segundo MOTOR-DERECHA: ");
  Serial.print(vpsDER);
  Serial.print(" ");
  Serial.print("Vueltas por segundo MOTOR-IZQUIERDA: ");
  Serial.println(vpsIZ);
  Serial.print("Tiempo:");
  Serial.println(millis());
  Serial.print("PWM-DERECHA:");
  Serial.print(pwmDER);
  Serial.print(" ");
  Serial.print("PWM-IZQUIERDA:");
  Serial.println(pwmIZ);
  Serial.print("millisMedicionesDER: ");
  Serial.print(millisMedicionesDER);
  Serial.print(" ");
  Serial.print("millisMedicionesIZ: ");
  Serial.println(millisMedicionesIZ);

  millisMedicionesDER = 0;
  millisMedicionesIZ = 0;
  
  vpsDER = 0;
  vpsIZ = 0;
}

//if((millis() == (tiempoAhora2 + intervalo2)) && (pollo == false)){
//  tiempoAhora2 = millis();
//  }

//correcion de pwmDER
//if(diferenciaVPS != 0){
//    Serial.print("Diferencia de VPS: ");
//    Serial.println(diferenciaVPS);
//    Serial.print("PWM DERECHA REDUCIDO 2, VALOR: ");
//    Serial.println(pwmDER);
//    pwmDER = pwmDER - diferenciaVPS;
//    if (pwmDER < 0) {
//      pwmDER = 0;
//    }
//    diferenciaVPS = 0;
//}
*/
//correcion de pwmIZ
//FIN correcion de pwmIZ
//CORRECION TERMINADA

if ( stop == true)
{
   analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
   analogWrite(ENBIZ, 0); 
   //control direction
   digitalWrite(IN1DER, LOW);
   digitalWrite(IN2DER, LOW);
   digitalWrite(IN3IZ, LOW);
   digitalWrite(IN4IZ, LOW);





}
if(vueltasDER == 11.4){

  girar();

  int TiempoFinal = (millis() /1000);

  float VueltasPorSegundoDerecha = (medicionesDER/(20 * TiempoFinal));
  float VueltasPorSegundoIzquierda = (medicionesIZ/(20 * TiempoFinal));

  Serial.println("---------------------Terminado--------------------------");
  Serial.print("Vueltas por segundo Motor Derecha: ");
  Serial.print(VueltasPorSegundoDerecha);
  Serial.print("Vueltas por segundo Motor Izquierda: ");
  Serial.print(VueltasPorSegundoIzquierda);
  Serial.println(pwmDER);
  
  analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
  analogWrite(ENBIZ, 0);
//control direction
  digitalWrite(IN1DER, LOW);
  digitalWrite(IN2DER, LOW);
  digitalWrite(IN3IZ, LOW);
  digitalWrite(IN4IZ, LOW);
  pollo = true;
  


  //while(1) ;
}
//FIN CORRECION TERMINADA

//Fin Codigo Javier
}
 
