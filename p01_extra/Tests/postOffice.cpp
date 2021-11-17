#include "postOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode)
    : firstZipCode(firstZCode), lastZipCode(lastZCode) {}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) { mailToSend.push_back(m); }

void PostOffice::addMailToDeliver(Mail *m) { mailToDeliver.push_back(m); }

void PostOffice::addPostman(const Postman &p) { postmen.push_back(p); }

vector<Mail *> PostOffice::getMailToSend() const { return mailToSend; }

vector<Mail *> PostOffice::getMailToDeliver() const { return mailToDeliver; }

vector<Postman> PostOffice::getPostman() const { return postmen; }

//--------

// b)
vector<Mail *> PostOffice::removePostman(string name) {
    for (auto postman = postmen.begin(); postman < postmen.end(); ++postman)
        if ((*postman).getName() == name) {
            auto ret = (*postman).getMail();
            postmen.erase(postman);
            return ret;
        }

    return {};
}

// c)
vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
    balance = 0;
    vector<Mail *> ret{};

    for (auto &mail : mailToSend) {
        balance += (*mail).getPrice();

        if ((*mail).getZipCode() >= firstZipCode &&
            (*mail).getZipCode() <= lastZipCode)
            addMailToDeliver(mail);
        else
            ret.push_back(mail);
    }

    mailToSend.clear();

    return ret;
}

// d)
Postman PostOffice::addMailToPostman(Mail *m, string name) {
    for (auto postman : postmen)
        if (postman.getName() == name) {
            postman.addMail(m);
            return postman;
        }

    throw NoPostmanException{name};
}

NoPostmanException::NoPostmanException(string name) : name(name){};

string NoPostmanException::getName() const { return name; }
