#include <iostream>
#include <string>
#include "NotesManager.h"
#include "NotebookObserver.h"

class ConsoleObserver : public NotebookObserver { // eredito notebookObserver dicendo effettivamente in che modo notifico gli observer
public:
    explicit ConsoleObserver(const std::string& label) : label(label) {}

    void onNotebookSizeChanged(size_t newSize) override {    //Ogni volta che il notebook cambia dimensione stampa su console il nome del notebook e la nuova dimensione
        std::cout << ">> [" << label << "] size = " << newSize << "\n";
    }

private:
    std::string label;
};

static void printNotebook(const Notebook& nb) { //passo in ingresso un notebook
    const auto& notes = nb.getNotes();
    std::cout << "\n--- " << nb.getName() << " ---\n";
    if (notes.empty()) {
        std::cout << "(empty)\n"; // se il vettore notes è vuoto rende empty senno eseguo for
        return;
    }

    for (size_t i = 0; i < notes.size(); ++i) { //stampa le note
        const auto& n = notes[i]; //n è la nota in posizione i
        std::cout << "[" << i << "] "
                  << "\"" << n->getTitle() << "\""
                  << " | locked=" << (n->isLocked() ? "YES" : "NO")
                  << " | important=" << (n->isImportant() ? "YES" : "NO")
                  << "\n";
    }
}

int main() {
    NotesManager app;
    ConsoleObserver obsMain("MAIN");  //il main e important sono già da osservare e hanno label main e important
    ConsoleObserver obsImp("IMPORTANT");
    std::vector<std::unique_ptr<Notebook>> customNotebooks;// vettore del notebook custom

    int choice = -1; //-1 poichè non esiste nel menù quindi fa partire il while
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
        std::cout << "9) Create new Notebook\n";
        std::cout << "10) Show Notebook's list\n";
        std::cout << "0) Exit\n";
        std::cout << "Choice: ";

        std::string input;
        std::getline(std::cin, input); //Legge una riga intera di testo dalla tastiera e la salva nella variabile input
        if (input.empty()) continue;

        choice = std::stoi(input); //da stringa a intero

        if (choice == 1) {

    std::string title, text;

    std::cout << "Title: ";
    std::getline(std::cin, title);

    std::cout << "Text: ";
    std::getline(std::cin, text);

    // Aggiunge la nota nel MAIN
    app.addNote(title, text);

    auto note = app.mainNotebook().getNoteAt(app.mainNotebook().size() - 1); //da alla nota il proprio indice

    // Mostra tutti i notebook disponibili (MAIN + custom)
    std::cout << "\nAvailable notebooks:\n";
    std::cout << "- MAIN\n";

    for (const auto& nb : customNotebooks) {
        std::cout << "- " << nb->getName() << "\n"; //stampa il nome dei notebooks
    }

    std::cout << "Insert note into which notebook? (write name or MAIN): ";
    std::string chosenName;
    std::getline(std::cin, chosenName);

    if (chosenName != "MAIN") {
        bool found = false;

        for (auto& nb : customNotebooks) { //scorro tutti i custom e inserisco la nota se trovo
            if (nb->getName() == chosenName) {
                nb->addNote(note);
                found = true;
                std::cout << "Note added to notebook " << chosenName << ".\n";
                break;
            }
        }
        if (!found) { //se non la trovo scrivo questo
            std::cout << "Notebook not found. Note remains only in MAIN.\n";
        }
    }

} else if (choice == 2) { //stampa lista main

    printNotebook(app.mainNotebook());

} else if (choice == 3) {//stampa lista importate

    printNotebook(app.importantNotebook());

} else if (choice == 4) {

    std::cout << "Index: ";
    std::getline(std::cin, input);
    size_t idx = static_cast<size_t>(std::stoi(input));//input->int->size_t

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

} else if (choice == 9) {

    std::cout << "Notebook name: ";
    std::string name;
    std::getline(std::cin, name);

    auto newNotebook = std::make_unique<Notebook>(name);
    customNotebooks.push_back(std::move(newNotebook)); //metto nella lista custom il nuovo notebook

    std::cout << "Notebook created successfully.\n";

} else if (choice == 10) {

    if (customNotebooks.empty()) {
        std::cout << "No custom notebooks available.\n";
    } else {

        for (auto& nb : customNotebooks) {

            std::cout << "\nNotebook: " << nb->getName() << "\n";

            const auto& notes = nb->getNotes();

            if (notes.empty()) {
                std::cout << "  (empty)\n";
            } else {
                for (size_t i = 0; i < notes.size(); ++i) {
                    std::cout << "  [" << i << "] "
                              << notes[i]->getTitle()
                              << " | locked="
                              << (notes[i]->isLocked() ? "YES" : "NO")
                              << " | important="
                              << (notes[i]->isImportant() ? "YES" : "NO")
                              << "\n";
                }
            }
        }
    }

} else if (choice == 0) {

    std::cout << "Bye!\n";

} else {

    std::cout << "Invalid choice.\n";
}

    }
    return 0;
}

