#ifndef NOTEAPP_CPP_NOTEBOOKOBSERVER_H
#define NOTEAPP_CPP_NOTEBOOKOBSERVER_H

#pragma once

#include <cstddef>// Necessario per usare size_t
//questa classe è un'interfaccia ed è astratta, definisce un comportamento. Ha metodo virtuale puro perchè non ha implementazione qui ma le classi derivate devono implementarla
class NotebookObserver {
public:
    virtual ~NotebookObserver() = default;//distruttore virtuale perchè potremmo distruggere oggetti derivati tramite ptr a notebookobserver

    virtual void onNotebookSizeChanged(size_t newSize) = 0;//metodo virtuale puro. =0 perchè è una funzione astratta.
    //chi eredita da notebookobserver deve implementarla
};

#endif //NOTEAPP_CPP_NOTEBOOKOBSERVER_H