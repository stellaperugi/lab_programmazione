Questo progetto implementa un'applicazione per la gestione di note. 
Classe "Note": rappresenta una singola nota. Ogni nota ha un titolo, testo, può essere bloccata e/o marcata come importante.
               Inoltre se una nota è bloccata non può essere modificata e rimossa dal noptebook.
Classe "Notebook": rappresenta una collezione di note. Permette di aggiungere note, rimuoverle, controllarne il numero e verificare se una nota è contenuta.
                   Usa il pattern Observer per notificare quando cambia il numero di note. 
Classe "NotebookObserver": quando il numero di note varia viene chiamato onNotebookSizeChanged(size_t newSize). Nel main è presente un ConsoleObserver che stampa il numero aggiornato.
Classe "NotesManager": Gestisce un notebook principale e una collezione separata di note importanti
Unit testing: il progetto usa GoogleTest. Sono presenti test per Note, Notebook, NotebookObserver e NotesManager