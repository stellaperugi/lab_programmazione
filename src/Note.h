#ifndef NOTEAPP_CPP_NOTE_H
#define NOTEAPP_CPP_NOTE_H
#pragma once // Evita inclusioni multiple dello stesso header
#include <string>// Serve per usare std::string

class Note {
public:
    // Costruttore: inizializza una nota con titolo e testo
    Note(const std::string& title, const std::string& text);

    // getters// Restituisce il titolo e testo della nota
    const std::string& getTitle() const;
    const std::string& getText() const;

    // setters (ritornano false se la nota è bloccata)// Imposta un nuovo titolo e testo
    bool setTitle(const std::string& newTitle);
    bool setText(const std::string& newText);

    // Blocca la nota, impedendo modifiche future
    void lock();
    // Indica se la nota è bloccata
    bool isLocked() const;

    // Imposta o rimuove il flag di nota importante
    void setImportant(bool value);
    // Indica se la nota è marcata come importante
    bool isImportant() const;

private:
    std::string title; // titolo della nota
    std::string text; // contenuto della nota
    bool locked{false}; // Indica se la nota è bloccata (inizialmente no)
    bool important{false};// Indica se la nota è importante (inizialmente no
};

#endif //NOTEAPP_CPP_NOTE_H