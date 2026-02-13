#include "Notebook.h"
#include <algorithm>

Notebook::Notebook(const std::string& name) //costruttore classe
    : name(name) {}//lista inizializzazione
const std::string& Notebook::getName() const { // (const per evitare copie) ritorna nome notebook
    return name;
}

bool Notebook::addNote(const std::shared_ptr<Note>& note) {//aggiunge nota, riceve sharedptr perchè le note sono condivise
    if (contains(note)) { //se la nota è gia presente non la aggiungo due volte
        return false;
    }
    notes.push_back(note);//inserisce la nota nel vettore
    notifyObservers();  // Notifica gli observer che la dimensione del notebook è cambiata
    return true;
}

bool Notebook::removeNote(const std::shared_ptr<Note>& note) {//rimuove una nota dal notebook se non è bloccata
    if (note->isLocked()) {
        return false;
    }

    auto it = std::find(notes.begin(), notes.end(), note);//cerca nota nel vettore, le scorre e find restituisce posizione
    if (it == notes.end()) {   // Se non è stata trovata, non possiamo rimuoverla
        return false;
    }

    notes.erase(it);// Rimuove la nota dal vettore
    notifyObservers();//notifica gli observer
    return true;//operazione riuscita
}

size_t Notebook::size() const { // ritorna numero di note nel vettore(size)
    return notes.size();
}

bool Notebook::contains(const std::shared_ptr<Note>& note) const { //verifica se la nota è già contenuta nel notebook
    return std::find(notes.begin(), notes.end(), note) != notes.end();//std..find restituisce un iteratore alla nota se trovata
    // Ritorna true se nota è presente nel vettore
}

const std::vector<std::shared_ptr<Note>>& Notebook::getNotes() const { // dà tutte le note
    return notes;
}

std::shared_ptr<Note> Notebook::getNoteAt(size_t index) const { //dà nota a un indice specifico
    if (index >= notes.size()) return nullptr;
    return notes[index];
}

bool Notebook::removeNoteAt(size_t index) { //rimuove nota tramite indice specifico
    if (index >= notes.size()) return false;
    return removeNote(notes[index]); //se locked -> false
}

void Notebook::addObserver(NotebookObserver* observer) { //aggiunge un observer alla lista degli observer
    observers.push_back(observer); //inserisce il ptr all'obbserver nel vettore
}

void Notebook::removeObserver(NotebookObserver* observer) {//rimuove un observer alla lista degli observer
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),//std::remove sposta in fondo gli elementi da rimuovere ed erase li rimuove
        observers.end()
    );
}

void Notebook::notifyObservers() { //notifica gli observer
    for (auto* obs : observers) { // cicla su tutti gli observer , chiama il metodo definito nell'interfaccia e passa il numero attuale di note
        obs->onNotebookSizeChanged(notes.size());
    }
}