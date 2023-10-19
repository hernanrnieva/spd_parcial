// Constantes 
#define A 12
#define B 13
#define C 9
#define D 8
#define E 7
#define F 11
#define G 10
#define SUBE 2
#define BAJA 3
#define RESET 4
#define DISPLAY_DELAY 25
#define SW_1 5

// Configuración de pines como entradas o salidas
void setup()
{
  for(int i = 3; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(A4, OUTPUT);            // Display 1
  pinMode(A5, OUTPUT);			      // Display 2
   
  pinMode(RESET, INPUT_PULLUP);		// Pulsador de reinicio
  pinMode(BAJA, INPUT_PULLUP);		// Pulsador -
  pinMode(SUBE, INPUT_PULLUP);		// Pulsador +
}

// Inicializacion de variables para utilizar en el codigo
// A utilizar en el estado de los botones y manejar el antirrebote
int contadorNumeros = 0;
int leerReiniciar = 0;
int leerSumar = 0;
int leerRestar = 0;
int restarAnterior = 1;
int sumarAnterior = 1;
int reiniciarAnterior = 1;
bool mostrarNumPrimos = false;
  
void loop()
{      
  // Ejecucion del antirrebote
  int presionoTecla = teclaPresionada();

  // Acción sobre el pulsador en base a tecla presionada
  if(presionoTecla == SUBE) {
    if(digitalRead(SW_1) == LOW) {
      contadorNumeros += 1;
    } else {
      contadorNumeros = obtenerPrimo(contadorNumeros + 1, true);
    }
   
    if(contadorNumeros > 99)
    {
      contadorNumeros = 0;
    }
  }
  else if(presionoTecla == BAJA)
  {
    if(digitalRead(SW_1) == LOW) {
      contadorNumeros -= 1;
    } else {
      contadorNumeros = obtenerPrimo(contadorNumeros - 1, false);
    }

    if(contadorNumeros < 0)
    {
      contadorNumeros = 99;
    }
  }
  else if(presionoTecla == RESET)
  {
     contadorNumeros = 0;
  }

  mostrarNumPrimos = digitalRead(SW_1) == LOW;
  
  // Llamamos a la funcion para el manejo de los display
  controladorDisplay(contadorNumeros);
}

int obtenerPrimo(int numero, bool siguiente){
  while (true){
    // Busco el siguiente primo
    if(siguiente) {
      numero ++;
      if(numero > 99) {
        numero = 0;
      } 
    }

    // Busco el anterior primo
    else {
      numero --;
      if(numero <= 0) {
        numero = 99;
      } 
    }

    if (numPrimo(numero)){
      return numero;
    }
  }
}

bool numPrimo(int numero) {
  if (numero <= 1) {
    return false;  // Falso (no es primo)
  }
    
  for (int index = 2; index <= numero/2; index++) {
    if (numero % index == 0) {
      return false;  // Falso (no es primo)
    }
  }
  
  return true;  // Verdadero (es primo)
}

// Control del funcionamiento de los display
void controladorDisplay(int contadorNumeros)
{
  // Sacar las unidades y decenas del contador
  int unidades = contadorNumeros % 10;
  int decenas = contadorNumeros / 10;

  // Mostrar las unidades en el primer display
  numerosDisplay(unidades);
  prenderDisplay(LOW, HIGH);
  delay(DISPLAY_DELAY); 

  // Mostrar las decenas en el segundo display
  numerosDisplay(decenas);
  prenderDisplay(HIGH, LOW);
  delay(DISPLAY_DELAY); 
}

// Funcion para mostrar los numeros en el display
void numerosDisplay(int numero){
  borrarDisplay();
      
  switch(numero) {
  	case 0:
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH); 
      digitalWrite(C, HIGH); 
      digitalWrite(D, HIGH); 
      digitalWrite(E, HIGH); 
      digitalWrite(F, HIGH); 
      break;
  	case 1: 
      digitalWrite(B, HIGH); 
      digitalWrite(C, HIGH); 
    	break;
    case 2: 
      digitalWrite(A, HIGH);
    	digitalWrite(B, HIGH); 
      digitalWrite(G, HIGH); 
    	digitalWrite(E, HIGH); 
    	digitalWrite(D, HIGH); 
    	break;
    case 3: 
      digitalWrite(A, HIGH);
    	digitalWrite(B, HIGH); 
      digitalWrite(G, HIGH); 
    	digitalWrite(C, HIGH); 
    	digitalWrite(D, HIGH); 
    	break;
    case 4: 
      digitalWrite(F, HIGH);
    	digitalWrite(B, HIGH); 
      digitalWrite(G, HIGH); 
    	digitalWrite(C, HIGH); 
    	break;
    case 5: 
      digitalWrite(A, HIGH);
    	digitalWrite(F, HIGH); 
      digitalWrite(G, HIGH); 
    	digitalWrite(C, HIGH);
    	digitalWrite(D, HIGH);
    	break;
    case 6: 
      digitalWrite(A, HIGH);
    	digitalWrite(F, HIGH); 
      digitalWrite(G, HIGH); 
    	digitalWrite(C, HIGH);
    	digitalWrite(E, HIGH);
    	digitalWrite(D, HIGH);
    	break;
    case 7: 
      digitalWrite(A, HIGH);
    	digitalWrite(B, HIGH); 
    	digitalWrite(C, HIGH);
    	break;
    case 8: 
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH); 
      digitalWrite(C, HIGH); 
      digitalWrite(D, HIGH); 
      digitalWrite(E, HIGH); 
      digitalWrite(F, HIGH);
    	digitalWrite(G, HIGH);
    	break;
    case 9: 
      digitalWrite(A, HIGH); 
      digitalWrite(B, HIGH); 
      digitalWrite(C, HIGH);  
      digitalWrite(F, HIGH);
    	digitalWrite(G, HIGH);
    	break;
  }
}

// Apaga todos los segmentos del display
void borrarDisplay(){
  digitalWrite(A, LOW); 
	digitalWrite(B, LOW); 
	digitalWrite(C, LOW); 
	digitalWrite(D, LOW); 
	digitalWrite(E, LOW); 
	digitalWrite(F, LOW); 
	digitalWrite(G, LOW); 
}

// Funcion que controla el encendido de los display
void prenderDisplay(int display1, int display2){
  digitalWrite(A5, display1);
  digitalWrite(A4, display2);
}

int teclaPresionada(void)
{
  // Función para detectar la pulsación de botones y gestionar el antirrebote.
  // Devuelve SUBE, BAJA o RESET en caso de pulsación o 0 en caso contrario.
  leerReiniciar = digitalRead(RESET);
  leerSumar = digitalRead(SUBE);
  leerRestar = digitalRead(BAJA);
  
  if(leerSumar == 1)
  {
    sumarAnterior = 1;
  }
  
  if(leerRestar  == 1)
  {
    restarAnterior = 1;
  }

  if(leerReiniciar  == 1)
  {
    reiniciarAnterior = 1;
  }
  
  // ANTIRREBOTE 
  if(leerSumar == 0 && leerSumar != sumarAnterior)
  {
  	sumarAnterior = leerSumar;
    return SUBE;
  }
  
  if(leerRestar == 0 && leerRestar != restarAnterior)
  {
  	restarAnterior = leerRestar;
    return BAJA;
  }
  
  if(leerReiniciar == 0 && leerReiniciar != reiniciarAnterior)
  {
  	reiniciarAnterior = leerReiniciar;
    return RESET;
  }

  // Devuelve 0 en caso de que no pase nada de lo anterior
  return 0;
}