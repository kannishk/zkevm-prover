#ifndef COMMIT_POLS_BASIC_C12_HPP
#define COMMIT_POLS_BASIC_C12_HPP

#include <cstdint>
#include "goldilocks_base_field.hpp"
#include "zkassert.hpp"

class CommitPolBasic12
{
private:
    Goldilocks::Element * _pAddress;
    uint64_t _degree;
    uint64_t _index;
public:
    CommitPolBasic12(Goldilocks::Element * pAddress, uint64_t degree, uint64_t index) : _pAddress(pAddress), _degree(degree), _index(index) {};
    Goldilocks::Element & operator[](int i) { return _pAddress[i*12]; };
    Goldilocks::Element * operator=(Goldilocks::Element * pAddress) { _pAddress = pAddress; return _pAddress; };

    Goldilocks::Element * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t index (void) { return _index; }
};

class CompressorCommitPolsBasic12
{
public:
    CommitPolBasic12 a[12];
private:
    void * _pAddress;
    uint64_t _degree;
public:

    CompressorCommitPolsBasic12 (void * pAddress, uint64_t degree) :
        a{
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 0), degree, 0),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 8), degree, 1),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 16), degree, 2),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 24), degree, 3),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 32), degree, 4),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 40), degree, 5),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 48), degree, 6),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 56), degree, 7),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 64), degree, 8),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 72), degree, 9),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 80), degree, 10),
            CommitPolBasic12((Goldilocks::Element *)((uint8_t *)pAddress + 88), degree, 11)
        },
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 131072; }
    static uint64_t pilSize (void) { return 96; }
    static uint64_t numPols (void) { return 12; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*12*sizeof(Goldilocks::Element); }
};

class CommitPolsBasicC12
{
public:
    CompressorCommitPolsBasic12 Compressor;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    CommitPolsBasicC12 (void * pAddress, uint64_t degree) :
        Compressor(pAddress, degree),
        _pAddress(pAddress),
        _degree(degree) {}

    static uint64_t pilSize (void) { return 12582912; }
    static uint64_t pilDegree (void) { return 131072; }
    static uint64_t numPols (void) { return 12; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*12*sizeof(Goldilocks::Element); }

    Goldilocks::Element &getElement (uint64_t pol, uint64_t evaluation)
    {
        zkassert((pol < numPols()) && (evaluation < degree()));
        return ((Goldilocks::Element *)_pAddress)[pol + evaluation * numPols()];
    }
};

#endif // COMMIT_POLS_HPP
