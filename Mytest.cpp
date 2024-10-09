#include <iostream>
#include <memory>  // For smart pointers
#include "File.h"
#include "Folder.h"

int main()
{
    File blankFile;
    std::cout << "Blank File:\n\tName: " << blankFile.getName()
        << "\n\tContents: " << blankFile.getContents()
        << "\n\tIcon Address: " << blankFile.getIcon() << std::endl;

    auto iconA = std::make_unique<int[]>(256);  
    auto iconB = std::make_unique<int[]>(256);  
    auto iconC = std::make_unique<int[]>(256);  

    File fileA("FileA.txt", "File A contents", iconA.get());
    File fileB("FileA.txt", "File A contents", iconB.get());
    File fileC("FileC.txt", "File C contents", iconC.get());

  
    Folder folder1("Folder1");
    Folder folder2("Folder2");

    bool fileAAdded = folder1.addFile(fileA);
    bool fileCAdded = folder1.addFile(fileC);

    std::cout << "Adding FileA.txt to Folder1: " << (fileAAdded ? "Success" : "Failure") << std::endl;
    std::cout << "Adding FileC.txt to Folder1: " << (fileCAdded ? "Success" : "Failure") << std::endl;

    bool fileCRemoved = folder1.removeFile("FileC.txt");
    std::cout << "Removing FileC.txt from Folder1: " << (fileCRemoved ? "Success" : "Failure") << std::endl;

    std::cout << "Trying to remove a non-existent file from Folder2: "
        << (folder2.removeFile("NonExistentFile.txt") ? "Success" : "Failure") << std::endl;

    return 0;
}