const int IN1DER = 7;
const int IN2DER = 8;
const int IN3IZ = 9;
const int IN4IZ = 10;

void setup(){

pinMode(IN1DER, OUTPUT);
pinMode(IN2DER, OUTPUT);
pinMode(IN3IZ, OUTPUT);
pinMode(IN4IZ, OUTPUT);

Serial.begin(9600);
}

void loop(){
    digitalWrite(IN1DER, HIGH);
    digitalWrite(IN2DER, LOW);
    digitalWrite(IN3IZ, HIGH);
    digitalWrite(IN4IZ, LOW);
}