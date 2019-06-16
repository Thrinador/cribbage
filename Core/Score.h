#pragma once

class Score {
public:
    int getTotal() {
        return fifteens + runs + ofAKind + flush + nubs + pegging;
    }

    int getTotalNoPegging() {
        return fifteens + runs + ofAKind + flush + nubs;
    }

    int fifteens = 0;
    int runs = 0;
    int ofAKind = 0;
    int flush = 0;
    int nubs = 0;
    int pegging = 0;
};