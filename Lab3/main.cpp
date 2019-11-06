#include <iostream>
#include "NetworkServer.h"
#include "SharedEditor.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    NetworkServer network;

    SharedEditor ed1(network);
    SharedEditor ed2(network);

    try {
        ed1.localInsert(0, 'c');
        network.dispatchMessages();

        ed2.localInsert(1, 'd');

        network.dispatchMessages();
        std::cout << "ed1: " << ed1.to_string() << std::endl;
        std::cout << "ed2: " << ed2.to_string() << std::endl;

        std::cout << std::endl << "+++ EDITOR1 SYMBOLS +++" << std::endl;
        for (auto i : ed1.getSymbols()) {
            std::cout << i.getValue();
            std::cout << " [";
            for (auto j : i.getPos())
                std::cout << j << ", ";
            std::cout << "]" << std::endl;
        }

        std::cout << std::endl << "+++ EDITOR2 SYMBOLS +++" << std::endl;
        for (auto i : ed2.getSymbols()) {
            std::cout << i.getValue();
            std::cout << " [";
            for (auto j : i.getPos())
                std::cout << j << ", ";
            std::cout << "]" << std::endl;
        }

        ed1.localInsert(1, 'i');
        network.dispatchMessages();

        ed2.localInsert(1, 'a');
        network.dispatchMessages();

        std::cout << "ed1: " << ed1.to_string() << std::endl;
        std::cout << "ed2: " << ed2.to_string() << std::endl;

        std::cout << std::endl << "+++ EDITOR1 SYMBOLS +++" << std::endl;
        for (auto i : ed1.getSymbols()) {
            std::cout << i.getValue();
            std::cout << " [";
            for (auto j : i.getPos())
                std::cout << j << ", ";
            std::cout << "]" << std::endl;
        }

        std::cout << std::endl << "+++ EDITOR2 SYMBOLS +++" << std::endl;
        for (auto i : ed2.getSymbols()) {
            std::cout << i.getValue();
            std::cout << " [";
            for (auto j : i.getPos())
                std::cout << j << ", ";
            std::cout << "]" << std::endl;
        }

        ed1.localInsert(1,'h');
        ed2.localErase(1);
        network.dispatchMessages();

        ed1.localInsert(2,'Z');
        network.dispatchMessages();

        ed1.localInsert(2,'P');
        ed2.localErase(2);
        network.dispatchMessages();

        std::cout << "ed1: "<< ed1.to_string() << std::endl;
        std::cout << "ed2: "<< ed2.to_string() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Generic Out of Range error.";
        return -1;
    }
    catch (NotFoundException& f) {
        std::cout << std::endl << f.what() << ": Index not found." << std::endl;
        return -1;
    }
    catch (InsertedIndexNotValid& f) {
        std::cout << std::endl << f.what() << ": Inserted index is not valid." << std::endl;
        return -1;
    }

    std::cout << std::endl << "+++ EDITOR1 SYMBOLS +++" << std::endl;
    for (auto i : ed1.getSymbols()) {
        std::cout << i.getValue();
        std::cout << " [";
        for (auto j : i.getPos())
            std::cout << j << ", ";
        std::cout << "]" << std::endl;
    }

    std::cout << std::endl << "+++ EDITOR2 SYMBOLS +++" << std::endl;
    for (auto i : ed2.getSymbols()) {
        std::cout << i.getValue();
        std::cout << " [";
        for (auto j : i.getPos())
            std::cout << j << ", ";
        std::cout << "]" << std::endl;
    }
    return 0;
}