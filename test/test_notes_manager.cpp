#include <gtest/gtest.h>
#include "NotesManager.h"

TEST(NotesManagerTest, AddNoteAddsToMainNotebook) {
    NotesManager mgr;

    size_t before = mgr.mainNotebook().size();
    mgr.addNote("A", "B");
    EXPECT_EQ(mgr.mainNotebook().size(), before + 1);
}

TEST(NotesManagerTest, ToggleImportantMovesNoteToImportantNotebook) {
    NotesManager mgr;

    mgr.addNote("A", "B");
    EXPECT_EQ(mgr.mainNotebook().size(), 1u);
    EXPECT_EQ(mgr.importantNotebook().size(), 0u);

    EXPECT_TRUE(mgr.toggleImportant(0));
    EXPECT_EQ(mgr.importantNotebook().size(), 1u);

    EXPECT_TRUE(mgr.toggleImportant(0));
    EXPECT_EQ(mgr.importantNotebook().size(), 0u);
}

TEST(NotesManagerTest, LockPreventsEditAndToggleImportant) {
    NotesManager mgr;

    mgr.addNote("A", "B");
    EXPECT_TRUE(mgr.lockNote(0));

    EXPECT_FALSE(mgr.editNote(0, "X", "Y"));
    EXPECT_FALSE(mgr.toggleImportant(0)); // setImportant non cambia se locked
}

TEST(NotesManagerTest, RemoveAlsoRemovesFromImportantIfPresent) {
    NotesManager mgr;

    mgr.addNote("A", "B");
    EXPECT_TRUE(mgr.toggleImportant(0));
    EXPECT_EQ(mgr.importantNotebook().size(), 1u);

    EXPECT_TRUE(mgr.removeNote(0));
    EXPECT_EQ(mgr.mainNotebook().size(), 0u);
    EXPECT_EQ(mgr.importantNotebook().size(), 0u);
}