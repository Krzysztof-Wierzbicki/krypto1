#ifndef KRYPTO1_DSAKEY_H
#define KRYPTO1_DSAKEY_H

#include <ttmathuint.h>
#include <CipherInterface.h>

struct DSAParameters{
    ttmath::UInt<16> p, q, g;
    static DSAParameters create(unsigned L, unsigned N);
};

class DSAKey : public KeyInterface{
public:
    DSAKey(ttmath::UInt<16> p, ttmath::UInt<16> q, ttmath::UInt<16> g);
private:
    ttmath::UInt<16> publicKey;
    ttmath::UInt<16> privateKey;
};


#endif //KRYPTO1_DSAKEY_H
