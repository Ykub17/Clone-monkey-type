# Настройки компилятора
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra 

# ПУТИ К ИНКЛУДАМ (Добавил -Iinclude)
INCLUDES = -Iinc \
           -I/opt/homebrew/Cellar/sfml@2/2.6.2_1/include \
           -I/opt/homebrew/opt/freetype/include/freetype2 \
           -I/opt/homebrew/opt/libpng/include/libpng16

# ПУТИ К БИБЛИОТЕКАМ (Для линковки на macOS)
LDFLAGS = -L/opt/homebrew/Cellar/sfml@2/2.6.2_1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Файлы проекта
SOURCES = src/main.cpp src/Game.cpp src/TypingHandler.cpp src/Renderer.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TARGET = build/Monkeytype

# Правило сборки исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Правило сборки объектных файлов
build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf build/*.o $(TARGET)