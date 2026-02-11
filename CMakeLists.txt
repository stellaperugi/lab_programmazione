cmake_minimum_required(VERSION 3.20)
project(noteapp_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# LIBRERIA con le classi (src)
# ---------------------------
add_library(notes_lib
        src/Note.cpp
        src/Notebook.cpp
        src/NotesManager.cpp
)

target_include_directories(notes_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ---------------------------
# ESEGUIBILE APP (main)
# ---------------------------
add_executable(noteapp_cpp
        src/main.cpp
)

target_link_libraries(noteapp_cpp
        PRIVATE
        notes_lib
)

# ---------------------------
# TEST (GoogleTest)
# ---------------------------
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(noteapp_tests
        test/test_note.cpp
        test/test_notebook.cpp
        test/test_notebook_observer.cpp
        test/test_notes_manager.cpp
)

target_link_libraries(noteapp_tests
        PRIVATE
        gtest_main
        notes_lib
)

# include path per i test (così #include "Note.h" funziona)
target_include_directories(noteapp_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(noteapp_tests)
