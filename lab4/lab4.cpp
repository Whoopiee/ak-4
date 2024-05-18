#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;


//C:\Users\valma\Desktop\ak4\from
// 
//C:\Users\valma\Desktop\ak4\to


// функція для перенесення файлів
void moveFiles(const std::string& sourceDir, const std::string& targetDir, const std::string& extension = "") {
    // перевірка на існування папки з якої будуть вирізані файли 
    if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir)) {
        std::cerr << "Source directory does not exist or is not a directory: " << sourceDir << std::endl;
        return;
    }

    // перевірка на існування папки в яку будуть перенесенні файли 

    if (!fs::exists(targetDir)) {
        char answer;
        std::cout << "There is no such target directory. Want to create one? Y/N" << std::endl; // якщо такої директорії немає - вона буде створена
        std::cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            fs::create_directory(targetDir);
            std::cout << "Target directory created: " << targetDir << std::endl;
        }
        else return;
    }

    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        const auto& path = entry.path();
        if (!extension.empty() && path.extension() != extension) {
            continue; // пропускає файли, які не підходять по розширенню 
        }

        fs::path targetPath = fs::path(targetDir) / path.filename();

        try {
            fs::rename(path, targetPath);
            std::cout << "Moved: " << path << " -> " << targetPath << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error moving file " << path << ": " << e.what() << std::endl;
        }
    }
}

int main() {
    std::string sourceDir;
    std::string targetDir;
    std::string extension;

    std::cout << "Enter the source directory: ";
    std::getline(std::cin, sourceDir);
    std::cout << "Enter the target directory: ";
    std::getline(std::cin, targetDir);
    std::cout << "Enter the file extension to move (leave empty to move all files): ";
    std::getline(std::cin, extension);

    // перевірка чи є перед розширенням точка
    if (!extension.empty() && extension.front() != '.') {
        extension = "." + extension;
    }

    moveFiles(sourceDir, targetDir, extension);

    return 0;
}