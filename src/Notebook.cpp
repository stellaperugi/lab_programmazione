#include "Notebook.h"                  // Include l’header della classe Notebook (dichiarazioni metodi e membri)
#include <algorithm>                   // Serve per usare std::find e std::remove

Notebook::Notebook(const std::string& name)
    : name(name) {}                    // Costruttore: inizializza il nome del notebook con initializer list

const std::string& Notebook::getName() const {
    return name;                       // Restituisce il nome del notebook (riferimento const per evitare copie)
}

bool Notebook::addNote(const std::shared_ptr<Note>& note) {
    if (contains(note)) {              // Se la nota è già presente, non la aggiungiamo (evita duplicati)
        return false;                  // Segnala fallimento dell’operazione
    }
    notes.push_back(note);             // Inserisce la nota nella collezione
    notifyObservers();                 // Notifica gli observer che la dimensione del notebook è cambiata
    return true;                       // Segnala successo dell’operazione
}

bool Notebook::removeNote(const std::shared_ptr<Note>& note) {
    if (note->isLocked()) {            // Regola di business: una nota bloccata non può essere rimossa
        return false;                  // Segnala fallimento
    }

    auto it = std::find(notes.begin(), notes.end(), note);
    // Cerca la nota nel vettore; confronto per shared_ptr (stessa istanza condivisa)

    if (it == notes.end()) {           // Se non è stata trovata, non possiamo rimuoverla
        return false;                  // Segnala fallimento
    }

    notes.erase(it);                   // Rimuove la nota dalla collezione
    notifyObservers();                 // Notifica gli observer che la dimensione del notebook è cambiata
    return true;                       // Segnala successo
}

size_t Notebook::size() const {
    return notes.size();               // Restituisce quante note sono presenti nel notebook
}

bool Notebook::contains(const std::shared_ptr<Note>& note) const {
    return std::find(notes.begin(), notes.end(), note) != notes.end();
    // Ritorna true se la nota è presente nel vettore, false altrimenti
}

const std::vector<std::shared_ptr<Note>>& Notebook::getNotes() const {
    return notes;
}

std::shared_ptr<Note> Notebook::getNoteAt(size_t index) const {
    if (index >= notes.size()) return nullptr;
    return notes[index];
}

bool Notebook::removeNoteAt(size_t index) {
    if (index >= notes.size()) return false;
    return removeNote(notes[index]); // usa la regola: se locked -> false
}


void Notebook::addObserver(NotebookObserver* observer) {
    observers.push_back(observer);     // Registra un observer (puntatore non posseduto: la vita dell’observer è esterna)
}

void Notebook::removeObserver(NotebookObserver* observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer), // Sposta in coda tutte le occorrenze dell’observer
        observers.end()                                           // Elimina fisicamente le occorrenze dal vettore
    );
    // Pattern erase-remove: modo standard per rimuovere elementi da std::vector
}

void Notebook::notifyObservers() {
    for (auto* obs : observers) {      // Scorre tutti gli observer registrati
        obs->onNotebookSizeChanged(notes.size());
        // Notifica a ciascun observer la nuova dimensione del notebook
    }
}