#include <gtest/gtest.h>
#include <memory>
#include "Notebook.h"

TEST(NotebookTest, StartsEmpty) {
    Notebook nb("Test");
    EXPECT_EQ(nb.size(), 0u);
}

TEST(NotebookTest, AddNoteIncreasesSize) {
    Notebook nb("Test");
    auto note = std::make_shared<Note>("Title", "Text");

    EXPECT_TRUE(nb.addNote(note));
    EXPECT_EQ(nb.size(), 1u);
}

TEST(NotebookTest, CannotAddSameNoteTwice) {
    Notebook nb("Test");
    auto note = std::make_shared<Note>("Title", "Text");

    EXPECT_TRUE(nb.addNote(note));
    EXPECT_FALSE(nb.addNote(note));
    EXPECT_EQ(nb.size(), 1u);
}

TEST(NotebookTest, RemoveUnlockedNoteWorks) {
    Notebook nb("Test");
    auto note = std::make_shared<Note>("Title", "Text");

    nb.addNote(note);
    EXPECT_TRUE(nb.removeNote(note));
    EXPECT_EQ(nb.size(), 0u);
}

TEST(NotebookTest, CannotRemoveLockedNote) {
    Notebook nb("Test");
    auto note = std::make_shared<Note>("Title", "Text");

    note->lock();
    nb.addNote(note);

    EXPECT_FALSE(nb.removeNote(note));
    EXPECT_EQ(nb.size(), 1u);
}