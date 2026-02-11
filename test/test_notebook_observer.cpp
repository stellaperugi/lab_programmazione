#include <gtest/gtest.h>
#include <memory>
#include "Notebook.h"

class TestObserver : public NotebookObserver {
public:
    void onNotebookSizeChanged(size_t newSize) override {
        lastSize = newSize;
        called = true;
    }

    size_t lastSize{0};
    bool called{false};
};

TEST(NotebookObserverTest, ObserverIsNotifiedOnAddAndRemove) {
    Notebook nb("Test");
    TestObserver obs;

    nb.addObserver(&obs);

    auto note = std::make_shared<Note>("T", "T");

    nb.addNote(note);
    EXPECT_TRUE(obs.called);
    EXPECT_EQ(obs.lastSize, 1u);

    obs.called = false;

    nb.removeNote(note);
    EXPECT_TRUE(obs.called);
    EXPECT_EQ(obs.lastSize, 0u);
}