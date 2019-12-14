#pragma once

#include "../general.h"
#include "../collections/arr.h"

struct SuffixAutomaton {
    int length;
    SuffixAutomaton* link;
    arr<SuffixAutomaton*> edges;

    SuffixAutomaton(SuffixAutomaton* link, int length, int alphabetSize) : link(link), length(length) {
        edges = arr<SuffixAutomaton*>(alphabetSize, nullptr);
    }
    
    SuffixAutomaton* addLetter(SuffixAutomaton* head, int c, int alphabetSize) {
        auto current = new SuffixAutomaton(nullptr, length + 1, alphabetSize);
        for (SuffixAutomaton* previous = this; ; previous = previous->link) {
            if (previous == nullptr) {
                current->link = head;
                break;
            }
            SuffixAutomaton* curLink = previous->edges[c];
            if (curLink != nullptr) {
                if (previous->length + 1 == curLink->length) {
                    current->link = curLink;
                } else {
                    auto clone = new SuffixAutomaton(curLink->link, previous->length + 1, alphabetSize);
                    for (int j = 0; j < alphabetSize; j++) {
                        clone->edges[j] = curLink->edges[j];
                    }
                    for (; previous != nullptr; previous = previous->link) {
                        SuffixAutomaton* to = previous->edges[c];
                        if (to != curLink) {
                            break;
                        }
                        previous->edges[c] = clone;
                    }
                    current->link = curLink->link = clone;
                }
                break;
            }
            previous->edges[c] = current;
        }
        return current;
    }
};

SuffixAutomaton* buildAutomaton(const string& s, char first = 'a', char last = 'z') {
    int alphabetSize = last - first + 1;
    auto tail = new SuffixAutomaton(nullptr, 0, alphabetSize);
    SuffixAutomaton* head = tail;

    for (size_t i = 0; i < s.length(); i++) {
        int c = s[i] - first;
        tail = tail->addLetter(head, c, alphabetSize);
    }
    return head;
}
