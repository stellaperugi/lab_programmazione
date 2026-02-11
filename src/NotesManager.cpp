#include "NotesManager.h"

#include "NotesManager.h"
#include <memory>

NotesManager::NotesManager()
    : mainNb("MyNotebook"), importantNb("Important") {}

const Notebook& NotesManager::mainNotebook() const {
    return mainNb;
}

const Notebook& NotesManager::importantNotebook() const {
    return importantNb;
}

void NotesManager::addNote(const std::string& title, const std::string& text) {
    auto note = std::make_shared<Note>(title, text);
    mainNb.addNote(note);
}

bool NotesManager::editNote(size_t index, const std::string& newTitle, const std::string& newText) {
    auto note = mainNb.getNoteAt(index);
    if (!note) return false;

    bool ok1 = note->setTitle(newTitle);
    bool ok2 = note->setText(newText);
    return ok1 && ok2;
}

bool NotesManager::lockNote(size_t index) {
    auto note = mainNb.getNoteAt(index);
    if (!note) return false;

    note->lock();
    return true;
}

bool NotesManager::removeNote(size_t index) {
    auto note = mainNb.getNoteAt(index);
    if (!note) return false;

    if (note->isImportant()) {
        importantNb.removeNote(note);
    }

    return mainNb.removeNoteAt(index);
}

bool NotesManager::toggleImportant(size_t index) {
    auto note = mainNb.getNoteAt(index);
    if (!note) return false;

    bool was = note->isImportant();
    note->setImportant(!was);

    // se la nota è locked, setImportant non cambia nulla
    if (note->isImportant() == was) return false;

    if (note->isImportant()) {
        importantNb.addNote(note);
    } else {
        importantNb.removeNote(note);
    }
    return true;
}
