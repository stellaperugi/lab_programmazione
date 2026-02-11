#include <iostream>
#include <string>
#include "NotesManager.h"
#include "NotebookObserver.h"

// Observer che stampa su console quando cambia la size del notebook
class ConsoleObserver : public NotebookObserver {
public:
    explicit ConsoleObserver(const std::string& label) : label(label) {}

    void onNotebookSizeChanged(size_t newSize) override {
        std::cout << ">> [" << label << "] size = " << newSize << "\n";
    }

private:
    std::string label;
};

static void printNotebook(const Notebook& nb) {
    const auto& notes = nb.getNotes();
    std::cout << "\n--- " << nb.getName() << " ---\n";
    if (notes.empty()) {
        std::cout << "(empty)\n";
        return;
    }

    for (size_t i = 0; i < notes.size(); ++i) {
        const auto& n = notes[i];
        std::cout << "[" << i << "] "
                  << "\"" << n->getTitle() << "\""
                  << " | locked=" << (n->isLocked() ? "YES" : "NO")
                  << " | important=" << (n->isImportant() ? "YES" : "NO")
                  << "\n";
    }
}

int main() {
    NotesManager app;
    ConsoleObserver obsMain("MAIN");
    ConsoleObserver obsImp("IMPORTANT");

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Notes App ===\n";
        std::cout << "1) Add note\n";
        std::cout << "2) List MAIN\n";
        std::cout << "3) List IMPORTANT\n";
        std::cout << "4) Edit note\n";
        std::cout << "5) Lock note\n";
        std::cout << "6) Remove note\n";
        std::cout << "7) Toggle important\n";
        std::cout << "8) Show note text\n";
        std::cout << "0) Exit\n";
        std::cout << "Choice: ";

        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) continue;

        choice = std::stoi(input);

        if (choice == 1) {
            std::string title, text;
            std::cout << "Title: ";
            std::getline(std::cin, title);
            std::cout << "Text: ";
            std::getline(std::cin, text);
            app.addNote(title, text);
        } else if (choice == 2) {
            printNotebook(app.mainNotebook());
        } else if (choice == 3) {
            printNotebook(app.importantNotebook());
        } else if (choice == 4) {
            std::cout << "Index: ";
            std::getline(std::cin, input);
            size_t idx = static_cast<size_t>(std::stoi(input));

            std::string title, text;
            std::cout << "New title: ";
            std::getline(std::cin, title);
            std::cout << "New text: ";
            std::getline(std::cin, text);

            if (!app.editNote(idx, title, text)) {
                std::cout << "Edit failed (invalid index or locked).\n";
            }
        } else if (choice == 5) {
            std::cout << "Index: ";
            std::getline(std::cin, input);
            size_t idx = static_cast<size_t>(std::stoi(input));

            if (!app.lockNote(idx)) {
                std::cout << "Lock failed (invalid index).\n";
            }
        } else if (choice == 6) {
            std::cout << "Index: ";
            std::getline(std::cin, input);
            size_t idx = static_cast<size_t>(std::stoi(input));

            if (!app.removeNote(idx)) {
                std::cout << "Remove failed (invalid index or locked).\n";
            }
        } else if (choice == 7) {
            std::cout << "Index: ";
            std::getline(std::cin, input);
            size_t idx = static_cast<size_t>(std::stoi(input));

            if (!app.toggleImportant(idx)) {
                std::cout << "Toggle failed (invalid index or locked).\n";
            }
        } else if (choice == 8) {
            std::cout << "Index: ";
            std::getline(std::cin, input);
            size_t idx = static_cast<size_t>(std::stoi(input));

            auto note = app.mainNotebook().getNoteAt(idx);

            if (!note) {
                std::cout << "Invalid index.\n";
            } else {
                std::cout << "\n--- Note Content ---\n";
                std::cout << "Title: " << note->getTitle() << "\n";
                std::cout << "Text:\n" << note->getText() << "\n";
            }
        }


        else if (choice == 0) {
            std::cout << "Bye!\n";
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}