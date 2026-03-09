cmake_minimum_required(VERSION 3.10)
project(Monkeytype)

# Стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пытаемся найти SFML в системе автоматически
# На macOS он найдет Homebrew, на Windows — то, что прописано в PATH
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Папка с заголовками
include_directories(inc)

# Собираем список всех исходных файлов
file(GLOB SOURCES "src/*.cpp")

# Имя исполняемого файла
add_executable(Monkeytype ${SOURCES})

# Линковка библиотек
target_link_libraries(Monkeytype sfml-graphics sfml-window sfml-system)

# Настройка вывода в папку build (по желанию)
set_target_properties(Monkeytype PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")