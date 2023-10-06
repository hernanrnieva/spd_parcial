/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 * Dummy variables to use VSCode without undeclared variable errors.
 * Variables sin uso para poder usar VSCode sin errores de variables no declaradas.
*/
#define INPUT_PULLUP 0
#define OUTPUT 0
#define A4 0
#define A5 0
#define LOW 0
#define HIGH 0
int digitalRead(int pin) {
  return 0; 
}
void digitalWrite(int pin, int value) {
  return; 
}
void pinMode(int pin, int mode) {
  return; 
}
void delay(int secs) {
  return;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Código Arduino */

// Constantes
#define A 12
#define B 13
#define C 7
#define D 8
#define E 9
#define F 11
#define G 10
#define UP 5
#define DOWN 4
#define RESET 3
#define UNITS A4
#define TENS A5
#define MS_DISPLAYON 25

// Variables globales
int countDigit = 0;
int up = 1;
int previousUp = 1;
int down = 1;
int previousDown = 1;
int reset = 1;
int previousReset = 1;

// Setup
void setup () {
  // Inicializo pines
  for(int i = 3; i < 14; i++) {
    if(i < 7)
      pinMode(i, INPUT_PULLUP);
    else
      pinMode(i, OUTPUT);
  }

  pinMode(UNITS, OUTPUT);
  pinMode(TENS, OUTPUT);
  
  // Muestro 0 en ambos displays
  digitalWrite(UNITS, 0);
  digitalWrite(TENS, 0);
  printDigit(0);
}

void loop(){
  int pressed = press();
  
  if(pressed == UP) {
    countDigit ++;

    if(countDigit > 99)
      countDigit = 0;

  } else if(pressed == DOWN) {
    countDigit --;

    if(countDigit < 0)
      countDigit = 99;

  } else if(pressed == RESET)
    countDigit = 0;

  printCount(countDigit);
}

/*
 * Lee diferencias entre estado anterior de un botón y posterior.
 * Establece una presionada cuando se suelta un botón previamente presionado,
 * y devuelve el valor correspondiente al botón.
*/
int press() {
  // Leo todos los estados actuales.
  up = digitalRead(UP);
  down = digitalRead(DOWN);
  reset = digitalRead(RESET);
  
  // De no estar presionados, asumo el estado previo como no presionados.
  if(up == 1)
    previousUp = 1;
  if(down == 1)
    previousDown = 1;
  if(reset == 1)
    previousReset = 1;
  
  // En la primera condición verifico que no esté presionado y que previamente lo haya estado.
  if(!up && up != previousUp) {
    // Seteo el estado anterior como presionado para evitar entrar nuevamente en la condición si se mantiene presionado.
    previousUp = up;
    return UP;
  }
  
  // Repito la lógica para los otros dos botones.
  if(!down && down != previousDown) {
    previousDown = down;
    return DOWN;
  }
  
  if(!reset && reset != previousReset) {
    previousReset = reset;
    return RESET;
  }
  
  // Devuelvo un 0 genérico que hace que no se modifique el valor de count.
  return 0;
}

void printDigit(int digit) {
  // Apago todos lo segmentos.
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);

  // Prendo los segmentos acorde a cada número.
  switch(digit) {
    case 1: {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    } case 2: {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 3: {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 4: {
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 5: {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 6: {
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 7: {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    } case 8: {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 9: {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    } case 0: {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      break;
    }
  }
}

void turnDigit(int digit) {
  // Enciendo las unidades por el tiempo de display establecido.
  if(digit == UNITS) {
    digitalWrite(UNITS, LOW);
    digitalWrite(TENS, HIGH);
  	delay(MS_DISPLAYON);
  // Enciendo las decenas por el tiempo de display establecido.
  } else if(digit == TENS) {
    digitalWrite(UNITS, HIGH);
    digitalWrite(TENS, LOW);
  	delay(MS_DISPLAYON);
  // Enciendo ambas indefinidamente.
  } else {   
    digitalWrite(UNITS, LOW);
    digitalWrite(TENS, LOW);
  }
}

void printCount(int count) {
  turnDigit(0);
  // Prendo los segmentos pertenecientes a las decenas.
  printDigit(count/10);
  // Los envío al display de decenas.
  turnDigit(TENS);
  turnDigit(0);
  // Prendo los segmentos pertenecientes a las unidades.
  printDigit(count - 10*((int)count/10));
  // Los envío al display de unidades.
  turnDigit(UNITS);
}