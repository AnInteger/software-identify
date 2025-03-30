#include "../src/identify.h"

#include <iostream>

using namespace software::identify;

using Soft = std::shared_ptr<SoftwareInfo>;

int main(int argc, char** argv) {

    std::string soft_name = "code";
    if (argc == 2) soft_name = argv[1];

    SoftwareIdentify identify;

    Soft soft = identify.IdentifyOneByName(soft_name);

    std::cout << "Package: " << soft->Package << std::endl;
    std::cout << "Installed_Size: " << soft->Installed_Size << std::endl;
    std::cout << "Version: " << soft->Version << std::endl;
    std::cout << "Maintainer: " << soft->Maintainer << std::endl;
    std::cout << "Section: " << soft->Section << std::endl;
    std::cout << "Description: " << soft->Description << std::endl;
    std::cout << "Homepage: " << soft->Homepage << std::endl;

    return 0;
}