#include "Notebook.h"
#include <algorithm>

Notebook::Notebook(const std::string& name)
    : name(name) {}
const std::string& Notebook::getName() const { // (const per evitare copie)
    return name;
}

bool Notebook::addNote(const std::shared_ptr<Note>& note) {
    if (contains(note)) {
        return false;
    }
    notes.push_back(note);
    notifyObservers();  // Notifica gli observer che la dimensione del notebook è cambiata
    return true;
}

bool Notebook::removeNote(const std::shared_ptr<Note>& note) {
    if (note->isLocked()) {
        return false;
    }

    auto it = std::find(notes.begin(), notes.end(), note);

    if (it == notes.end()) {   // Se non è stata trovata, non possiamo rimuoverla
        return false;
    }

    notes.erase(it);// Rimuove la nota dalla collezione
    notifyObservers();
    return true;
}

size_t Notebook::size() const {
    return notes.size();
}

bool Notebook::contains(const std::shared_ptr<Note>& note) const {
    return std::find(notes.begin(), notes.end(), note) != notes.end();
    // Ritorna true se nota è presente nel vettore
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
    return removeNote(notes[index]); //se locked -> false
}

void Notebook::addObserver(NotebookObserver* observer) {
    observers.push_back(observer);
}

void Notebook::removeObserver(NotebookObserver* observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void Notebook::notifyObservers() {
    for (auto* obs : observers) {
        obs->onNotebookSizeChanged(notes.size());
    }
}