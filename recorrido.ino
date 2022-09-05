const int sensorPinIZ = 2;
const int sensorPinDER = 3;

const int ENADER = 6;
const int IN1DER = 7;
const int IN2DER = 8;
const int IN3IZ = 9;
const int IN4IZ = 10;
const int ENBIZ = 11;

float medicionesIZ = 0;
float medicionesDER = 0; 
float medicionesIZvolatil = 0; 
float medicionesDERvolatil = 0;  

int valueIZ = 0;
int valueDER = 0;

int checkIZ = 0;
int checkDER = 0;

bool checkIZgiro = false;
bool checkDERgiro = false;

int recorridoant = 1;

bool checkIZ2 = false;
bool checkDER2 = false;

float divisionesRueda = 20;


bool prueba = false;
bool pollo = false;
bool prueba1 = true;
bool prueba2 = true;
bool fran = false; 
bool hola = false;
bool stop = false;

bool boolCaminar = false;

unsigned long tiempoAhora = 0;
int intervalo = 1000;

unsigned long tiempoAhora2 = 0;
int intervalo2 = 500;

int pwmDER = 200;
int pwmIZ = 200;

float diferenciaVPS;

float millisMedicionesDER;
float millisMedicionesIZ;

float vueltasIZ = medicionesIZ / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones
float vueltasDER = medicionesDER / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones

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

void girar(){

  //--------------------------------------------------------ENCODER IZQUIERDA--------------------------------------------------------------
  valueIZ = digitalRead(sensorPinIZ);  //lectura digital de pin

  if (valueIZ == LOW && checkIZgiro == 0) {
    medicionesIZvolatil++;

    checkIZgiro = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueIZ == HIGH && checkIZgiro == 1) {
    checkIZgiro = 0;
  }
  
//--------------------------------------------------------FIN ENCODER IZQUIERDA--------------------------------------------------------------
//---------------------------------------------------------ENCODER DERECHA--------------------------------------------------------------
  valueDER = digitalRead(sensorPinDER );  //lectura digital de pin

  if (valueDER == LOW && checkDERgiro == 0) {
    medicionesDERvolatil++;
    checkDERgiro = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueDER == HIGH && checkDERgiro == 1) {
    checkDERgiro = 0;
  }
  
//--------------------------------------------------------FIN ENCODER DERECHA--------------------------------------------------------------

  if (medicionesDERvolatil <= 5)
    {
       analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
       analogWrite(ENBIZ, pwmIZ); 
     //control direction
       digitalWrite(IN1DER, HIGH);
       digitalWrite(IN2DER, LOW);
       digitalWrite(IN3IZ, LOW);
       digitalWrite(IN4IZ, HIGH);
    }
    else if (medicionesDERvolatil > 19)
    {
       analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
       analogWrite(ENBIZ, 0); 
     //control direction
       digitalWrite(IN1DER, LOW);
       digitalWrite(IN2DER, LOW);
       digitalWrite(IN3IZ, LOW);
       digitalWrite(IN4IZ, LOW);
        recorridoant++;
    }
}

void caminar() {
    boolCaminar = true;

    if (vueltasDER <= 11.4){
        analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
        analogWrite(ENBIZ, pwmIZ); 
        //control direction
        digitalWrite(IN1DER, HIGH);
        digitalWrite(IN2DER, LOW);
        digitalWrite(IN3IZ, HIGH);
        digitalWrite(IN4IZ, LOW);
    }
    if(vueltasDER > 11.4){
        recorridoant++;
    }
}

void caminar2(){
  if (pollo == false ){
    analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
    analogWrite(ENBIZ, pwmIZ); 
    //control direction
    digitalWrite(IN1DER, HIGH);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, HIGH);
    digitalWrite(IN4IZ, LOW);
  }
 if(vueltasDER == 5){
    recorridoant++;
  }
}

void parar(){
  analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
  analogWrite(ENBIZ, 0);
//control direction
  digitalWrite(IN1DER, LOW);
  digitalWrite(IN2DER, LOW);
  digitalWrite(IN3IZ, LOW);
  digitalWrite(IN4IZ, LOW);
  pollo = true;
}

void loop() {
//--------------------------------------------------------ENCODER IZQUIERDA--------------------------------------------------------------
  valueIZ = digitalRead(sensorPinIZ);  //lectura digital de pin

  if (valueIZ == LOW && checkIZ == 0) {
    if (boolCaminar == true)
    {
        medicionesIZ++;    
    }
    checkIZ = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
  }
  if (valueIZ == HIGH && checkIZ == 1) {
    checkIZ = 0;
  }
  
  
//--------------------------------------------------------FIN ENCODER IZQUIERDA--------------------------------------------------------------
//---------------------------------------------------------ENCODER DERECHA--------------------------------------------------------------
  valueDER = digitalRead(sensorPinDER );  //lectura digital de pin

    if (valueDER == LOW && checkDER == 0) {
        if (boolCaminar == true)
        {
            medicionesDER++;    
        }
        checkDER = 1;//¿checkIZ podria ser una boleana?¿en realmente necesaria?
    }
    if (valueDER == HIGH && checkDER == 1) {
        checkDER = 0;
    }
//--------------------------------------------------------FIN ENCODER DERECHA--------------------------------------------------------------

//Codigo Javier

  switch(recorridoant){
        case 1: caminar();
        break;
        
        case 2: girar();
        break;
        
        case 3: caminar2();
        break;
        
        default: parar();
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
}