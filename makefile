# se declara un bloque de variables
# se coloca el nombre del archivo sin extensión
ARCHIVO = generadorLaberintos
ARCHIVO2 = resolver
XINICIO = 12
YINICIO = 15
XFINAL = 39
YFINAL = 89
CANTMOV = 10


# reglas a ejecutar
all: compilar ejecutar

compilar:
		g++ -g -lm $(ARCHIVO).cpp -o $(ARCHIVO)
		gcc -o $(ARCHIVO2) $(ARCHIVO2).c -I -lpthread

ejecutar:
		./$(ARCHIVO) > laberinto.txt
solucionar
		./$(ARCHIVO2) $(XINICIO) $(YINICIO) $(XFINAL) $(YFINAL) $(CANTMOV) < laberinto.txt

# regla que sirva para poder borrar los archivos creados
clean:
		rm $(ARCHIVO)
		rm $(ARCHIVO2)
