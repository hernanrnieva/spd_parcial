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
#define UNIDADES A4
#define DECENAS A5
#define SWITCH 5
#define TEMPERATURA A2
#define TEMPERATURA_MINIMA 185
#define FUERZA A3
#define PRIMER_INCREMENTO 385
#define SEGUNDO_INCREMENTO 165
#define SIGUIENTE true
#define ANTERIOR false

// Configuración de pines como entradas o salidas
void setup() {
  for(int i = 3; i < 14; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(TEMPERATURA, INPUT);
  pinMode(FUERZA, INPUT);
  pinMode(UNIDADES, OUTPUT);            // Display 1
  pinMode(DECENAS, OUTPUT);	          // Display 2

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
int lectura = 0;
bool mostrarNumPrimos = false;
  
void loop() {      
  // Ejecucion del antirrebote
  int presionoTecla = teclaPresionada(); 
  int incremento = definirIncremento(analogRead(FUERZA));
  mostrarNumPrimos = digitalRead(SWITCH) == LOW;

  // Acción sobre el pulsador en base a tecla presionada
  if(presionoTecla == SUBE) {
    if(digitalRead(SWITCH) == LOW)
      contadorNumeros += 1 * incremento;
    else
      contadorNumeros = obtenerPrimo(contadorNumeros, SIGUIENTE, incremento);
   
    if(contadorNumeros > 99)
      contadorNumeros = 0;
  } else if(presionoTecla == BAJA) {
    if(digitalRead(SWITCH) == LOW)
      contadorNumeros -= 1 * incremento;
    else
      contadorNumeros = obtenerPrimo(contadorNumeros, ANTERIOR, incremento);

    if(contadorNumeros < 0)
      contadorNumeros = 99;
  } else if(presionoTecla == RESET)
     contadorNumeros = 0;
  
  // Llamamos a la funcion para el manejo de los display
  controladorDisplay(contadorNumeros);
}

int definirIncremento(int lecturaFuerza) {
  if(lecturaFuerza > PRIMER_INCREMENTO)
    return 1;
  else if(lecturaFuerza > SEGUNDO_INCREMENTO)
    return 2;
   
  return 3;
}

int obtenerPrimo(int numero, bool siguiente, int incremento) {
  int original = numero;
  if(incremento == 1) {
    while(true) {
      // Busco el siguiente primo
      if(siguiente) {
        numero ++;
        if(numero > 99)
          numero = 0;
      }

      // Busco el anterior primo
      else {
        numero --;
        if(numero <= 0)
          numero = 99;
      }

      if (numPrimo(numero) && numero != original)
        return numero;
    }
  }
  else {
    // Si incremento no es uno, significa que debo llamar a la misma función, pero esta vez con el primo siguiente (o anterior)
    // y disminuyendo el incremento en 1. Si el incremento fuese 3 el llamado se haría dos veces, primero con incremento = 2,
    // con el primo siguiente (o anterior), y luego una vez más con incremento = 1, con el segundo primo siguiente (o anterior)
    if(siguiente)
      return obtenerPrimo(obtenerPrimo(numero + 1, siguiente, 1), siguiente, incremento - 1);
  	else
      return obtenerPrimo(obtenerPrimo(numero - 1, siguiente, 1), siguiente, incremento - 1);
  }
}

bool numPrimo(int numero) {
  if (numero <= 1)
    // Falso (no es primo)
    return false;  
    
  for (int index = 2; index <= numero/2; index++) {
    if (numero % index == 0)
      // Falso (no es primo)
      return false;  
  }
  
  // Verdadero (es primo)
  return true;  
}

// Control del funcionamiento de los display
void controladorDisplay(int contadorNumeros) {
  float temperatura = analogRead(TEMPERATURA);
    
  if(temperatura > TEMPERATURA_MINIMA) {
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
  } else
    // No hay temperatura suficiente
    prenderDisplay(HIGH, HIGH);	
}

// Funcion para mostrar los numeros en el display
void numerosDisplay(int numero) {
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
void borrarDisplay() {
  digitalWrite(A, LOW); 
	digitalWrite(B, LOW); 
	digitalWrite(C, LOW); 
	digitalWrite(D, LOW); 
	digitalWrite(E, LOW); 
	digitalWrite(F, LOW); 
	digitalWrite(G, LOW); 
}

// Funcion que controla el encendido de los display
void prenderDisplay(int display1, int display2) {
  digitalWrite(UNIDADES, display2);
  digitalWrite(DECENAS, display1);
}

int teclaPresionada(void) {
  // Función para detectar la pulsación de botones y gestionar el antirrebote.
  // Devuelve SUBE, BAJA o RESET en caso de pulsación o 0 en caso contrario.
  leerReiniciar = digitalRead(RESET);
  leerSumar = digitalRead(SUBE);
  leerRestar = digitalRead(BAJA);
  
  if(leerSumar == 1)
    sumarAnterior = 1;
  
  if(leerRestar  == 1)
    restarAnterior = 1;

  if(leerReiniciar  == 1)
    reiniciarAnterior = 1;
  
  // ANTIRREBOTE 
  if(leerSumar == 0 && leerSumar != sumarAnterior) {
  	sumarAnterior = leerSumar;
    return SUBE;
  }
  
  if(leerRestar == 0 && leerRestar != restarAnterior) {
  	restarAnterior = leerRestar;
    return BAJA;
  }
  
  if(leerReiniciar == 0 && leerReiniciar != reiniciarAnterior) {
  	reiniciarAnterior = leerReiniciar;
    return RESET;
  }

  // Devuelve 0 en caso de que no pase nada de lo anterior
  return 0;
}