#include "Note.h" // Include la dichiarazione della classe Note
// Costruttore: inizializza titolo e testo usando una initializer list
Note::Note(const std::string& title, const std::string& text)
    : title(title), text(text) {}
// Ritorna il titolo (come riferimento costante)
const std::string& Note::getTitle() const {
    return title;
}
// Ritorna il testo (come riferimento costante)
const std::string& Note::getText() const {
    return text;
}
// Imposta un nuovo titolo per la nota
// Se la nota è bloccata, la modifica non è consentita
// Il valore di ritorno indica se l’operazione è andata a buon fine
bool Note::setTitle(const std::string& newTitle) {
    if (locked) {
        return false;
    }
    title = newTitle;
    return true;
}

bool Note::setText(const std::string& newText) {
    if (locked) {
        return false;
    }
    text = newText;
    return true;
}
// Blocca la nota. Dopo questa chiamata, titolo e testo non possono più essere modificati
void Note::lock() {
    locked = true;
}
// Indica se la nota è attualmente bloccata. Metodo const perché non altera lo stato dell’oggetto
bool Note::isLocked() const {
    return locked;
}
// Indica se la nota è attualmente bloccata
// Metodo const perché non altera lo stato dell’oggetto
void Note::setImportant(bool value) {
    if (!locked) {
        important = value;
    }
}
// Restituisce true se la nota è marcata come importante
// Metodo const perché è solo di consultazione
bool Note::isImportant() const {
    return important;
}
