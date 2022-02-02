////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////

#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6


//Variables globales
int i = 0;
char comando[20];
char cadena[40];

int pwm_step = 10;  //Pasos de Aumento/Decremento
int pwm = 105;       //Velocidad incial
int lim_inf = 0;    //Limite de velocidad inferior
int lim_sup = 255;  //Límite de velocidad superior

int ppr = 2376;        //Pulsos por revolución
int PosEnc = 0;        //Posición del encoder en pulsos, se inicia en 0
int MSB = 0;
int LSB = 0;
int lastEncoded = 0;

int moveAngle = 0;      //Grados que se van a  mover
int error = 50;
float ratio = (float)360/ppr;     //360/ppr;  //Pulsos por grado

int setpoint;

//Banderas
bool moving = false;
bool inverso = false;
bool entradaCompleta = false;

////////////////////////////////////////////////////////////////////////////////
//Funciones utilizadas
void menu(void);    //Desplega el menu en la consola
void accion(void);  //Selecciona una acción según el comando recibido (String)
void apagar(void);

////////////////////////////////////////////////////////////////////////////////
void setup() {
  //Inicializamos las variables correspondientes al motor 1
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);



  Serial.begin(9600);
  menu();                   //Imprimimos el menú de opciones

}

void loop() {
  if(entradaCompleta){
    //Se ejecuta si se envia un comando
    accion();
    entradaCompleta = false;
  }

  if(moving){
    //Si se desea mover una cantidad de grados definida

  }
}

//Se envian datos desde el puerto serial
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if(inChar > 96){
      inChar -= 32;
    }
    if (inChar != '\n') { //Terminador de cadena (enter)
      comando[i] += inChar;
      i++;
    }else{
      i = 0;
      entradaCompleta = true;
    }
  }
}


////////////////////////////////////////////////////////////////////////////////
//Funciones
void menu(){
  Serial.println("Control del motor (Funciones básicas)");
  Serial.println("");
  Serial.println("Comandos:");
  Serial.println("[S]    PARO");
  Serial.println("[F]    ADELANTE (CW)");
  Serial.println("[R]    REVERSA (CCW)");
  Serial.println("[IS]   INCREMENTAR VELOCIDAD");
  Serial.println("[DS]   DISMINUIR VELOCIDAD");
  Serial.println("[MT X] MOVER X GRADOS");
  Serial.println("");
  Serial.println("Opciones:");
  Serial.println("[GP]   MOSTRAR POSICION ACTUAL DEL ENCODER (GRADOS)");
  Serial.println("[GS]   MOSTRAR VELOCIDAD (PWM)");
  Serial.println("[MN]   IMPRIMIR LISTA DE COMANDOS/OPCIONES");
  Serial.println("");
}

void accion(){
  apagar();
  if(!strcmp(comando, "S")) {
    PosEnc = 0;
    digitalWrite(LED1, HIGH);
  }

  if(!strcmp(comando, "F")){
    digitalWrite(LED2, HIGH);
  }

  if(!strcmp(comando, "R")){
    digitalWrite(LED3, HIGH);
  }

  if(!strcmp(comando, "IS")){
    pwm += pwm_step;
    if(pwm > lim_sup) pwm = lim_sup;
    digitalWrite(LED4, HIGH);
  }

  if(!strcmp(comando, "DS")){
    pwm -= pwm_step;
    if(pwm < lim_inf) pwm = lim_inf;
    digitalWrite(LED5, HIGH);
  }


  if(!strncmp(comando, "MT", 2)){
    char aux[5];
    sscanf(comando, "%s %d", aux, &moveAngle);
    sprintf(cadena, "Se debe mover: %d grados", moveAngle);
  

    if (moveAngle < 0){
      //Habilita el movimiento con ángulos "negativos" (CCW)
      moveAngle = (-1)*moveAngle;
    }

    PosEnc = moveAngle;
  }

  if(!strcmp(comando, "GP")){
    Serial.println(PosEnc);
  }

  if(!strcmp(comando, "GS")){
    Serial.println(pwm);
  }

  memset(comando, 0, 20);
}

void apagar(){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
}


// *FIN DEL CÓDIGO