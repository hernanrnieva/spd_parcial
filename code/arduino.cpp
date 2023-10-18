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

// Configuración de pines como entradas o salidas
void setup()
{
  for(int i = 7; i < 14; i++) {
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
  
void loop()
{      
  // Ejecucion del antirrebote
  int presionoTecla = teclaPresionada();

  // Acción sobre el pulsador en base a tecla presionada
  if(presionoTecla == SUBE)
  {
  	contadorNumeros += 1;
   
    if(contadorNumeros > 99)
    {
      contadorNumeros = 0;
    }
  }
  else if(presionoTecla == BAJA)
  {
    contadorNumeros -= 1;

    if(contadorNumeros < 0)
    {
      contadorNumeros = 99;
    }
  }
  else if(presionoTecla == RESET)
  {
     contadorNumeros = 0;
  }
  
  // Llamamos a la funcion para el manejo de los display
  controladorDisplay(contadorNumeros);
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
  borrar_display();
      
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
void borrar_display(){
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