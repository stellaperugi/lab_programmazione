#ifndef NOTEAPP_CPP_NOTEBOOK_H
#define NOTEAPP_CPP_NOTEBOOK_H

#pragma once
// Evita inclusioni multiple dello stesso file header durante la compilazione

#include <string>               // Necessario per usare std::string
#include <vector>               // Necessario per usare std::vector
#include <memory>               // Necessario per usare std::shared_ptr
#include "Note.h"               // Include la classe Note gestita dal Notebook
#include "NotebookObserver.h"   // Include l’interfaccia Observer per il pattern Observer

class Notebook {
public:
    explicit Notebook(const std::string& name);
    // Costruttore esplicito: inizializza il notebook con un nome

    const std::string& getName() const;
    // Restituisce il nome del notebook
    // Ritorna un riferimento costante per evitare copie inutili

    bool addNote(const std::shared_ptr<Note>& note);
    // Aggiunge una nota al notebook
    // Ritorna false se la nota è già presente

    bool removeNote(const std::shared_ptr<Note>& note);
    // Rimuove una nota dal notebook
    // L’operazione fallisce se la nota è bloccata

    size_t size() const;
    // Restituisce il numero di note presenti nel notebook

    bool contains(const std::shared_ptr<Note>& note) const;
    // Verifica se una determinata nota è contenuta nel notebook

    const std::vector<std::shared_ptr<Note>>& getNotes() const;
    std::shared_ptr<Note> getNoteAt(size_t index) const;
    bool removeNoteAt(size_t index);

    void addObserver(NotebookObserver* observer);
    // Registra un observer che verrà notificato quando cambia il numero di note

    void removeObserver(NotebookObserver* observer);
    // Rimuove un observer precedentemente registrato

private:
    void notifyObservers();
    // Notifica tutti gli observer del nuovo numero di note presenti

    std::string name;
    // Nome del notebook

    std::vector<std::shared_ptr<Note>> notes;
    // Collezione delle note contenute nel notebook
    // Si usa shared_ptr perché una nota può appartenere a più collezioni

    std::vector<NotebookObserver*> observers;
    // Lista degli observer registrati
    // I puntatori non sono posseduti dal notebook:
    // la loro gestione della vita è esterna
};

#endif //NOTEAPP_CPP_NOTEBOOK_H