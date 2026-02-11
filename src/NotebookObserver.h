#ifndef NOTEAPP_CPP_NOTEBOOKOBSERVER_H
#define NOTEAPP_CPP_NOTEBOOKOBSERVER_H

#pragma once
// Evita inclusioni multiple

#include <cstddef>
// Necessario per usare size_t

class NotebookObserver {
public:
    virtual ~NotebookObserver() = default;
    // Distruttore virtuale per permettere la distruzione corretta

    virtual void onNotebookSizeChanged(size_t newSize) = 0;
    // Metodo chiamato quando cambia il numero di note
};

#endif //NOTEAPP_CPP_NOTEBOOKOBSERVER_H