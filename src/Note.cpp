#include "Note.h"
Note::Note(const std::string& title, const std::string& text)
    : title(title), text(text) {}
const std::string& Note::getTitle() const {
    return title;
}
const std::string& Note::getText() const {
    return text;
}

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

void Note::lock() {
    locked = true;
}

bool Note::isLocked() const {
}

void Note::setImportant(bool value) {
    if (!locked) {
        important = value;
    }
}

bool Note::isImportant() const {
    return important;
}
