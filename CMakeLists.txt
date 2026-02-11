cmake_minimum_required(VERSION 4.1)
project(noteapp_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(noteapp_cpp src/main.cpp
        src/Note.cpp
        src/Note.h
        src/Notebook.cpp
        src/Notebook.h
        src/NotebookObserver.h
        src/NotesManager.cpp
        src/NotesManager.h)
