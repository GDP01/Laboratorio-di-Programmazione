cmake_minimum_required(VERSION 3.10)

project(ProgettoTutorAutostrade VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#ottimizzazione -O2
if (MSVC)
  add_compile_options(/O2 /W4)
else()
  add_compile_options(-O2 -Wall -Wextra -Wpedantic)
endif()

#eseguibile Simulatore
add_executable(simulator
  src/mainSimulator.cpp
  src/Simulator.cpp
  src/Highway.cpp
  src/Veicolo.cpp
)

#Include directory simulator
target_include_directories(simulator PRIVATE ${CMAKE_SOURCE_DIR}/Include)

#eseguibile Tutor
add_executable(tutor
  src/mainTutor.cpp
  src/Tutor.cpp
  src/Highway.cpp
)

#Include directory tutor
target_include_directories(tutor PRIVATE ${CMAKE_SOURCE_DIR}/Include)

#copio /Data dentro la build per poter usare i file di input
add_custom_command(TARGET simulator POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/Data
          $<TARGET_FILE_DIR:simulator>/Data
)

add_custom_command(TARGET tutor POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/Data
          $<TARGET_FILE_DIR:tutor>/Data

)
