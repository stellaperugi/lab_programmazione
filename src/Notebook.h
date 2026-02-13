#ifndef NOTEAPP_CPP_NOTEBOOK_H
#define NOTEAPP_CPP_NOTEBOOK_H

#pragma once


#include <string>
#include <vector>
#include <memory>
#include "Note.h"
#include "NotebookObserver.h"

class Notebook {
public:
    explicit Notebook(const std::string& name); // inizializza il notebook con un nome, explicit per evitare conversioni implicite

    const std::string& getName() const;

    bool addNote(const std::shared_ptr<Note>& note);

    bool removeNote(const std::shared_ptr<Note>& note);

    size_t size() const;  //numero note del notebook

    bool contains(const std::shared_ptr<Note>& note) const;// Verifica se una determinata nota è contenuta nel notebook

    const std::vector<std::shared_ptr<Note>>& getNotes() const; // restituisce tutte le note

    std::shared_ptr<Note> getNoteAt(size_t index) const; //restituisce la nota alla posizione index

    bool removeNoteAt(size_t index);// rimuove la nota alla posizione index

    void addObserver(NotebookObserver* observer);  //Avvisa quando il numero di note nel Notebook cambia

    void removeObserver(NotebookObserver* observer);

private:
    void notifyObservers();

    std::string name; //nome notebook

    std::vector<std::shared_ptr<Note>> notes; //contiene puntatore a note ed esse possono essere condivise, una nota puo appartenere a piu notebook

    std::vector<NotebookObserver*> observers; //contiene puntatori agli observer, grezzi perchè notebook non è proprietario degli observer
};

#endif //NOTEAPP_CPP_NOTEBOOK_H