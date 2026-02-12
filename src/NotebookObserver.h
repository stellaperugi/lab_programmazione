#ifndef NOTEAPP_CPP_NOTEBOOKOBSERVER_H
#define NOTEAPP_CPP_NOTEBOOKOBSERVER_H

#pragma once

#include <cstddef>// Necessario per usare size_t

class NotebookObserver {
public:
    virtual ~NotebookObserver() = default;

    virtual void onNotebookSizeChanged(size_t newSize) = 0;
};

#endif //NOTEAPP_CPP_NOTEBOOKOBSERVER_H