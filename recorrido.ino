#define sensorPinIZ  2
#define sensorPinDER  3
#define ENADER  6
#define IN1DER  7
#define IN2DER  8
#define IN3IZ  9
#define IN4IZ  10
#define ENBIZ  11

float medicionesIZ = 0;
float medicionesDER = 0; 
float medicionesIZvolatil = 0; 
float medicionesDERvolatil = 0;  

int valueIZ = 0;
int valueDER = 0;

int checkIZ = 0;
int checkDER = 0;

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
bool medicionesVolatil = false;

unsigned long tiempoAhora = 0;
int intervalo = 1000;

unsigned long tiempoAhora2 = 0;
int intervalo2 = 500;

int pwmDER = 200;
int pwmIZ = 200;

float diferenciaVPS;

float millisMedicionesDER;
float millisMedicionesIZ;

float vueltasDER;
float vueltasIZ;

void setup () {
  Serial.begin(115200);   //iniciar puerto serie
  
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

void caminar(){

  while (vueltasDER < 8)
  {
    analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
    analogWrite(ENBIZ, pwmIZ); 
    //control direction
    digitalWrite(IN1DER, HIGH);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, HIGH);
    digitalWrite(IN4IZ, LOW);
  }
  
 if(vueltasDER == 8) {
    recorridoant++;
  }
}

void girar(){

  medicionesVolatil = true;

  while (medicionesDERvolatil <= 10)
  {
    analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
    analogWrite(ENBIZ, pwmIZ); 
    //control direction
    digitalWrite(IN1DER, HIGH);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, LOW);
    digitalWrite(IN4IZ, HIGH);
  }
  
  if (medicionesDERvolatil > 10)
  {
    analogWrite(ENADER, 0);//Se utiliza pwm para manejar las velocidades del motor
    analogWrite(ENBIZ, 0); 
    //control direction
    digitalWrite(IN1DER, LOW);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, LOW);
    digitalWrite(IN4IZ, LOW);

    recorridoant++;
    vueltasDER = 0;
    medicionesIZ = 0;
    medicionesDER = 0;
    medicionesDERvolatil = 0;
    medicionesVolatil = false;
  }
}


void caminar2(){
  while (vueltasDER < 8)
  {
    analogWrite(ENADER, pwmDER);//Se utiliza pwm para manejar las velocidades del motor
    analogWrite(ENBIZ, pwmIZ); 
    //control direction
    digitalWrite(IN1DER, HIGH);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, HIGH);
    digitalWrite(IN4IZ, LOW);
  }
  
 if(vueltasDER == 8){
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
}

void loop() {
//--------------------------------------------------------ENCODER IZQUIERDA--------------------------------------------------------------
  valueIZ = digitalRead(sensorPinIZ);  //lectura digital de pin

  if (valueIZ == LOW && checkIZ == 0) {
    medicionesIZ++;
    if (medicionesVolatil == true)
    {
      medicionesIZvolatil++;
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
    medicionesDER++;
    if (medicionesVolatil == true)
    {
      medicionesDERvolatil++;
    }
    checkDER = 1;
  }
  if (valueDER == HIGH && checkDER == 1) {
    checkDER = 0;
  }
  
//--------------------------------------------------------FIN ENCODER DERECHA--------------------------------------------------------------
//Codigo Javier

  vueltasIZ = medicionesIZ / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones
  vueltasDER = medicionesDER / divisionesRueda;//se calculan las vueltas realizadas en base a las mediciones

  switch(recorridoant){
    case 1: caminar();
    break;
    
    case 2: girar();
    break;
    
    case 3: caminar2();
    break;
    
    default: parar();
  }
}