#include <gtest/gtest.h>
#include "Note.h"

TEST(NoteTest, CreationWorks) {
    Note n("Titolo", "Testo");
    EXPECT_EQ(n.getTitle(), "Titolo");
    EXPECT_EQ(n.getText(), "Testo");
}

TEST(NoteTest, NoteIsNotLockedByDefault) {
    Note n("T", "T");
    EXPECT_FALSE(n.isLocked());
}

TEST(NoteTest, LockedNoteCannotBeModified) {
    Note n("Titolo", "Testo");
    n.lock();

    EXPECT_FALSE(n.setTitle("Nuovo titolo"));
    EXPECT_FALSE(n.setText("Nuovo testo"));

    EXPECT_EQ(n.getTitle(), "Titolo");
    EXPECT_EQ(n.getText(), "Testo");
}

TEST(NoteTest, ImportantFlagWorks) {
    Note n("T", "T");

    EXPECT_FALSE(n.isImportant());
    n.setImportant(true);
    EXPECT_TRUE(n.isImportant());
}
