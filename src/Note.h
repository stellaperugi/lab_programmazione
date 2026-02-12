#ifndef NOTEAPP_CPP_NOTE_H
#define NOTEAPP_CPP_NOTE_H
#pragma once
#include <string>

class Note {
public:
    Note(const std::string& title, const std::string& text);

    const std::string& getTitle() const;
    const std::string& getText() const;

    bool setTitle(const std::string& newTitle);
    bool setText(const std::string& newText);

    // Blocca la nota, impedendo modifiche future
    void lock();
    bool isLocked() const;

    // Imposta o rimuove il flag di nota importante
    void setImportant(bool value);
    bool isImportant() const;

private:
    std::string title;
    std::string text;
    bool locked{false};
    bool important{false};
};

#endif //NOTEAPP_CPP_NOTE_H