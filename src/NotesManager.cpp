#include "NotesManager.h"
#include <memory>

NotesManager::NotesManager() //costruttore
    : mainNb("MyNotebook"), importantNb("Important") {}//inizializza un notebook principale e uno importante

const Notebook& NotesManager::mainNotebook() const { //getter notebook principale
    return mainNb;
}

const Notebook& NotesManager::importantNotebook() const {//getter notebook importante
    return importantNb;
}

void NotesManager::addNote(const std::string& title, const std::string& text) { //aggiunge nota a quello principale
    auto note = std::make_shared<Note>(title, text);//crea nota gestita da shared ptr perchè la nota può essere condivisa tra più notebook
    mainNb.addNote(note); //aggiunge note al vettore notes del notebook mainNb
}

bool NotesManager::editNote(size_t index, const std::string& newTitle, const std::string& newText) {//modifica title e text di una nota data la sua posizione  nel main notebook
    auto note = mainNb.getNoteAt(index); //recupera nota alla posizione index dal main notebbok
    if (!note) return false; //se indice è fuori range getNoteAt ritorna nullptr

    bool ok1 = note->setTitle(newTitle); //prova a cambiare titolo (se locked ritorna false)
    bool ok2 = note->setText(newText);
    return ok1 && ok2; //successo se entrambi sono andate a buon fine
}

bool NotesManager::lockNote(size_t index) { //blocca nota alla posizione index nel main notebook, ritorna false se index non è valido
    auto note = mainNb.getNoteAt(index);
    if (!note) return false;

    note->lock();
    return true;
}

bool NotesManager::removeNote(size_t index) {// rimuove nota alla posizione index dal main e se è importante rimossa anche da quello
    auto note = mainNb.getNoteAt(index);
    if (!note) return false; //ritorna falso se index invalido o nota bloccata

    if (note->isImportant()) {
        importantNb.removeNote(note);
    }

    return mainNb.removeNoteAt(index);
}

bool NotesManager::toggleImportant(size_t index) {//attiva e disattiva label important e la aggiunge/toglie dal main notebook se non è bloccata
    auto note = mainNb.getNoteAt(index);//recupera nota da main notebook
    if (!note) return false;//se non esiste fallisce

    bool was = note->isImportant();// was dipende dall'importanza della nota
    note->setImportant(!was); //le cambia il valore

    if (note->isImportant() == was) return false; // se nuovo important è = a quello vecchio vuol dire che è bloccata, rimane uguale

    if (note->isImportant()) {
        importantNb.addNote(note); //aggiungo a immportantNb se diventa importante
    } else {
        importantNb.removeNote(note); //se era importante e quindi ho fatto toggle, rimuovo da importantNb
    }
    return true;
}
