const int sensorPinIZ = 2;
const int sensorPinDER = 3;

float medicionesIZ = 0;
float medicionesDER = 0;

int valueIZ = 0;
int valueDER = 0;

int i;

int checkIZ = 0;
int checkDER = 0;

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

unsigned long tiempoAhora = 0;
int intervalo = 500;

unsigned long tiempoAhora2 = 0;
int intervalo2 = 500;

int pwmDER = 120;
int pwmIZ = 60;

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


void loop() {
//--------------------------------------------------------ENCODER IZQUIERDA--------------------------------------------------------------
  valueIZ = digitalRead(sensorPinIZ);  //lectura digital de pin

  if (valueIZ == LOW && checkIZ == 0) {
    medicionesIZ++;
    millisMedicionesIZ++;
//    Serial.print("Mediciones:");
//    Serial.println(medicionesIZ);
    checkIZ = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueIZ == HIGH && checkIZ == 1) {
    checkIZ = 0;
  }
  float vueltasIZ = medicionesIZ / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones
  /*Esto lo podria comentar*/
//  if (Serial.available() > 0) {
//    if (Serial.read() == '1') {
//      Serial.print("Vueltas:");
//      Serial.println (vueltasIZ);
//    }
//  }
/**/
//--------------------------------------------------------FIN ENCODER IZQUIERDA--------------------------------------------------------------
//---------------------------------------------------------ENCODER DERECHA--------------------------------------------------------------
  valueDER = digitalRead(sensorPinDER );  //lectura digital de pin

  if (valueDER == LOW && checkDER == 0) {
    medicionesDER++;
    millisMedicionesDER++;
//    Serial.print("Mediciones 2:");
//    Serial.println(medicionesDER);
    checkDER = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueDER == HIGH && checkDER == 1) {
    checkDER = 0;
  }
  float vueltasDER = medicionesDER / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones
  /*Esto lo podria comentar*/
//  if (Serial.available() > 0) {
//    if (Serial.read() == '2') {
//      Serial.print("Vueltas 2:");
//      Serial.println (vueltasDER);
//    }
//  }
/**/
//--------------------------------------------------------FIN ENCODER DERECHA--------------------------------------------------------------
//  if (prueba1 == true){
//    analogWrite(ENADER, 167);
//    digitalWrite(IN1DER, HIGH);
//    digitalWrite(IN2DER, LOW);
//  }
//  if (prueba2 == true){
//    analogWrite(ENBIZ, 255);
//    digitalWrite(IN3IZ, HIGH);
//    digitalWrite(IN4IZ, LOW);
//  }
//
//
//  if (medicionesIZ > 226.8)
//  {
//     analogWrite(ENADER, 0);
//    digitalWrite(IN1DER, HIGH);
//    digitalWrite(IN2DER, HIGH);
//    prueba1 =false;
//    }
//   if (medicionesIZ > 200)
//  {
//     analogWrite(ENADER, 0);
//    digitalWrite(IN1DER, HIGH);
//    digitalWrite(IN2DER, HIGH);
//    pollo = true;
//    Serial.print ("Mediciones: ");
//    Serial.println (medicionesIZ);
//    Serial.print ("tiempo: ");
//    Serial.println (millis());
//    
//    }
//    if (millis() - tiempo0 > 7000)
//    {
//      analogWrite(ENADER, 0);
//      analogWrite(ENBIZ,  0);
//      pollo = true;
//      digitalWrite(IN1DER, HIGH);
//      digitalWrite(IN2DER, HIGH);
//      digitalWrite(IN3IZ, HIGH);
//      digitalWrite(IN4IZ, HIGH);
//      Serial.print ("Motor derecho: ");
//      Serial.println (medicionesDER);
//      Serial.print ("Motor izquierdo: ");
//      Serial.println (medicionesIZ);
//      }
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
//----------------------------------------------------------FIN DE MANEJO DE PWM-----------------------------------------------------
//Codigo Javier
float diferenciaDER = vueltasDER - vueltasIZ;
float diferenciaIZ = vueltasIZ - vueltasDER;



float vpsDER;
float vpsIZ;

if(millis() == (tiempoAhora + intervalo)){
  tiempoAhora = millis();
  
  vpsDER = millisMedicionesDER / divisionesRueda;
  vpsIZ = millisMedicionesIZ / divisionesRueda;

  diferenciaVPS = (vpsDER - vpsIZ)*20;

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

if((millis() == (tiempoAhora2 + intervalo2)) && (pollo == false)){
  tiempoAhora2 = millis();
  }

//correcion de pwmDER
if(diferenciaVPS != 0){
    Serial.print("Diferencia de VPS: ");
    Serial.println(diferenciaVPS);
    Serial.print("PWM DERECHA REDUCIDO 2, VALOR: ");
    Serial.println(pwmDER);
    pwmDER = pwmDER - diferenciaVPS;
    if (pwmDER < 0) {
      pwmDER = 0;
    }
    diferenciaVPS = 0;
}
//correcion de pwmIZ
//FIN correcion de pwmIZ
//CORRECION TERMINADA
if(vueltasDER == 80){
  
  
  analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
  analogWrite(ENBIZ, 0);
//control direction
  digitalWrite(IN1DER, LOW);
  digitalWrite(IN2DER, LOW);
  digitalWrite(IN3IZ, LOW);
  digitalWrite(IN4IZ, LOW);

  while(1) ;
}
//FIN CORRECION TERMINADA

//Fin Codigo Javier

//        Serial.print ("vueltas1: ");
//        Serial.print (medicionesDER);
//        Serial.print ("vuesltas2: ");
//        Serial.println (medicionesIZ);
//        Serial.print ("time : ");

//----------------------------------------------------------MUESTRA DE DATOS POR PUERTO SERIE-----------------------------------------------------
//     if ((medicionesIZ >= 86.83) || (medicionesDER >= 86.83))
//      {
//          Serial.print ("vueltas1: ");
//          Serial.print (vueltasDER);
//          Serial.print ("vueltas2: ");
//          Serial.println (vueltasIZ);
//          Serial.print ("time : ");
//          Serial.println (millis());
//          
//          analogWrite(ENADER, 0);
//          analogWrite(ENBIZ, 0);
//          
//          digitalWrite(IN1DER, LOW);
//          digitalWrite(IN2DER, LOW);
//          digitalWrite(IN3IZ, LOW);
//          digitalWrite(IN4IZ, LOW);
//          
//          pollo = true;  
//     }
//----------------------------------------------------------FIN DE MUESTRA DE DATOS POR PUERTO SERIE-----------------------------------------------------
//Codigo Juan
//    if (pollo == true){
//      int diferencia;
//      diferencia = abs(medicionesDER) - abs(medicionesIZ);
//      if (medicionesDER > medicionesIZ){
//        int correccionDER;
//        
//        correccionDER =  (diferencia/medicionesDER);
//        pwmDER = 255 - (255*correccionDER);
//      }
//      if (medicionesIZ > medicionesDER){
//        int correccionIZ;
//        
//        correccionIZ =  (diferencia/medicionesIZ);
//        pwmIZ = 255 - (255*correccionIZ);
//      }
//      Serial.print ("Derecha: ");
//      Serial.println (medicionesDER);
//      Serial.print ("Izquierda: ");
//      Serial.println (medicionesIZ);
//      delay (1000);
//      
//      medicionesIZ = 0;
//      medicionesDER = 0;
//      pollo = false;
//      
//    }
//Fin Codigo Juan
    //  digitalWrite(motor1pin1, HIGH);
    //  digitalWrite(motor1pin2, LOW);
    //
    //  digitalWrite(motor2pin1, HIGH);
    //  digitalWrite(motor2pin2, LOW);
    //
    // if (vueltas1 > 40 )
    // {   digitalWrite(motor1pin1, LOW);
    //  digitalWrite(motor1pin2, LOW);
    //  }
    //if (vueltas > 40)
    //{
    //    digitalWrite(motor2pin1, LOW);
    //  digitalWrite(motor2pin2, LOW);
    //  }


  }
 
