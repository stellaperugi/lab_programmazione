#include "Note.h"
Note::Note(const std::string& title, const std::string& text) //costruttore
    : title(title), text(text) {} //inizializza private title e text
const std::string& Note::getTitle() const { //restituisce il titolo della nota
    return title;
}
const std::string& Note::getText() const {//restituisce il testo della nota
    return text;
}

bool Note::setTitle(const std::string& newTitle) {//modifica titolo nota se non è bloccata
    if (locked) {
        return false;
    }
    title = newTitle;
    return true;
}

bool Note::setText(const std::string& newText) {//modifica testo nota se non è bloccata
    if (locked) {
        return false;
    }
    text = newText;
    return true;
}

void Note::lock() { //blocca la nota
    locked = true;
}

bool Note::isLocked() const { //restituisce se nota è bloccata
    return locked;
}

void Note::setImportant(bool value) { //imposta importante se non è bloccata
    if (!locked) {
        important = value;
    }
}

bool Note::isImportant() const { //restituisce se nota è importante
    return important;
}
