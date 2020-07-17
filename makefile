# se declara un bloque de variables
# se coloca el nombre del archivo sin extensión
ARCHIVO = generadorLaberintos

# reglas a ejecutar
all: compilar ejecutar

compilar:
		g++ -g -lm $(ARCHIVO).cpp -o $(ARCHIVO)

ejecutar:
		./$(ARCHIVO)

# regla que sirva para poder borrar los archivos creados
clean:
		rm $(ARCHIVO)
