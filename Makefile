# Definir el compilador
CXX = g++

# Definir las banderas del compilador
CXXFLAGS = -Wall -std=c++11

# Definir los archivos de origen
SRCS = SumaPrefijos.cpp main.cpp

# Definir el nombre del ejecutable
TARGET = a

# Regla para compilar el programa
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regla para limpiar los archivos compilados
clean:
	rm -f $(TARGET)
