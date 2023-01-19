#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
//KaterineCandy Lima Esperilla
using namespace std;
//	Establecemos el color de fondo
void Iniciar()
{
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);// Color de fondo
	glClear(GL_COLOR_BUFFER_BIT); // Limpia buffer de color
	glMatrixMode(GL_PROJECTION); // establece la matriz de proyección
	gluOrtho2D(-40, 40, -40, 40); // Area de visualización en el plano cartesiano
}
// ---------------------------------------------------------------
//La función se encarga de dibujar todas las lineas en el plano cartesiano
void dibujarLinea(GLint x0, GLint y0, GLint xf, GLint yf)
{
	glColor3f(0.0f, 0.5f, 0.5f); // Color de las lineas
	glPointSize(1); // Tamanio de Puntos en las lineas

	for (float i = -39.5; i < 40; i++)// Dibuja todas las lineas horizontales
	{
		glBegin(GL_LINES);// dibuja cada linea 
		glVertex3f(i, 40, 1);
		glVertex3f(i, -40, 1); 
		glEnd();
	}
	for (float i = -39.5; i < 40; i++)//Dibuja las lineas Verticales
	{
		glBegin(GL_LINES);//dibuja cada linea
		glVertex3f(40, i, 1); 
		glVertex3f(-40, i, 1);
		glEnd(); 
	}

	glColor4b(1.0f, 0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex2i(40, 0);
	glVertex2i(-40, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(0, 40);
	glVertex2i(0, -40);
	glEnd();
}
//función que se encarga de pintar el punto en el plano cartesiano
void PintaPixel(GLint x, GLint y)
{
	glColor3f(0.0f, 0.0f, 0.0f); // Color del pixel
	glPointSize(9); // Tamanio de punto
	glBegin(GL_POINTS); // Inicio de dibujo de una primitiva
	glVertex2i(x, y); // Grafica un punto
	glEnd(); // Termina el dibujo de la primitiva
}
//Funcion que implementa el algoritmo de punto medio para dibujar una linea recta
void PuntoMedioPRecta(int x0, int y0, int xf, int yf)
{
	//Declaramos variable de tipo flotante
	float ax, ay, m, p; //ax,ay:componentes del vector, m:Pendiente y p:variable de decision
	float x, y;//coordenadas del ixel actual
	float pmx, pmy;//Coordenadas del punto medio entre el pixel actual y el siguiente
	ax = xf - x0;//diferencia de x
	ay = yf - y0;//diferencia de y
	m = ay / ax;//pendiente
	//lineas que inicializan las variables x, y con las cooordenadas iniciales de la línea
	x = x0;
	y = y0;
	if (m <= 1)// si la pendiente es menor o igual a 1
	{
		//inicializamos el punto medio entre el pixel actual y el siguiente
		pmx = x + 1;
		pmy = y + 0.5;
		//se ejecuta mientras cumple con la condición
		while (x <= xf)
		{
			p = ay * pmx - ax * pmy - x0 + ay * ax + y0; //valor de la variable de decisión
			PintaPixel(x, y);
			if (p <= 0)//si la pendiente es menor o igual a 0
			{
				x = x + 1;// incrementa en uno x
				y = y;//permance y
			}
			//si la pendiente es mayor a 0
			else
			{
				x = x + 1;//incrementa en uno x
				y = y + 1;//incrementa en uno y
			}
			//actualizamos los valores de punto medio del pixel actual y el siguiente
			pmx = x + 1;
			pmy = y + 0.5;
		}
	}
	if (m > 1)// si la pendiente es mayor a 1
	{
		//inicializamos el punto medio entre el pixel actual y el siguiente
		pmx = x + 0.5;
		pmy = y + 1;
		//se ejecuta mientras cumple con la condición
		while (y <= yf)
		{
			p = ay * pmx - ax * pmy - x0 * ay + ax * y0;//valor de la variable de decisión
			PintaPixel(x, y);
			if (p <= 0)//si la pendiente es menor o igual a 0
			{
				x = x + 1;//incrementa en uno x
				y = y + 1;//incrementa en uno y
			}
			//si la pendiente es mayor a 0
			else
			{
				x = x;//permance x
				y = y + 1;//incrementa en unno y
			}
			//inicializamos el punto medio entre el pixel actual y el siguiente
			pmx = x + 0.5;
			pmy = y + 1;
		}
	}
}
//Se encarga de ingresar los valores 
void IngresarDatos(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//Limpia el buffer de color
	GLint X0,Y0,Xf,Yf;//Almacenamiento de las coordenadas de inicio y final de la linea
	cout << "****************  ALGORITMO DE PUNTO MEDIO PARA UNA RECTA************"<<endl;
	cout << "Ingresa  x0: ";
	cin >> X0;
	cout << "Ingresa y0: ";
	cin >> Y0;
	cout << "Ingresa xf: ";
	cin >> Xf;
	cout << "Ingresa yf: ";
	cin >> Yf;
	PuntoMedioPRecta(X0, Y0, Xf, Yf);//llama a la función PuntoMedioPRecta
	dibujarLinea(X0, Y0, Xf, Yf);//llama a la función dibujarLinea
	glFlush();//marca el final de IngresarDatos
}
//
int main(int argc, char* argv[])//definimos la main
{
	glutInit(&argc, argv);//Está funcion inicializa Glut
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//visualizacion de ventana
	glutInitWindowSize(800, 800);// medida de ventana de ancho y alto en pixeles
	glutInitWindowPosition(200, 200);//ubicacion de la ventanan de derecha y izquierda
	glutCreateWindow("Linea Punto Medio");
	Iniciar();
	glutDisplayFunc(IngresarDatos);
	glutMainLoop();
}
