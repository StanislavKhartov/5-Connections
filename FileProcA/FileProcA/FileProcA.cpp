#include <iostream>
#include <fstream>

#define ID 2;

void callMenu() {
    std::cout << "1 - Send message\n";
    std::cout << "2 - Recieve message\n";
    std::cout << "0 - Exit\n";
}

void cleanBuffer() {
    std::ofstream out;
    out.open("..\\..\\Buffer");
    out.close();
}

int main()
{
    int state = 1;
    while (state) {
        callMenu();
        std::cin >> state;
        if (state > 2 || state < 0) {
            std::cout << "Wrong state";
            return 1;
        }
        if (state == 1) {
            int num;
            std::cin >> num;
            std::ofstream out("..\\..\\..\\Buffer");
            out << "1" << "\n";
            out << num;
            out.close();
        }
        if (state == 2) {
            std::ifstream in("..\\..\\..\\Buffer");
            int buf = 0;
            in >> buf;
            if (buf == 2) {
                in >> buf;
                std::cout << buf << "\n";
            }
            else {
                std::cout << "Nothing to recieve\n";
            }
            in.close();
        }
    }
}
