#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;

void navigateDirectories() {
    std::string directoryPath;

    while (true) {
        std::cout << "Enter a directory path (or 'q' to quit): ";
        std::getline(std::cin, directoryPath);

        if (directoryPath == "q") {
            break;
        }

        if (fs::is_directory(directoryPath)) {
            std::cout << "Current directory: " << directoryPath << std::endl;
            fs::directory_iterator it(directoryPath);
            for (const auto& entry : it) {
                if (fs::is_directory(entry)) {
                    std::cout << "  " << entry.path().filename() << " (directory)" << std::endl;
                } else {
                    std::cout << "  " << entry.path().filename() << std::endl;
                }
            }
        } else {
            std::cerr << "Error: " << directoryPath << " is not a directory." << std::endl;
        }
    }
}

void viewFiles(const std::string& directoryPath) {
    fs::directory_iterator it(directoryPath);
    for (const auto& entry : it) {
        if (fs::is_regular_file(entry)) {
            std::cout << "  " << entry.path().filename() << std::endl;
        }
    }
}

void createDirectory(const std::string& directoryPath) {
    try {
        fs::create_directory(directoryPath);
        std::cout << "Directory created successfully: " << directoryPath << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
}

void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
    try {
        fs::copy_file(sourcePath, destinationPath);
        std::cout << "File copied successfully: " << sourcePath << " to " << destinationPath << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }
}

void moveFile(const std::string& sourcePath, const std::string& destinationPath) {
    try {
        fs::rename(sourcePath, destinationPath);
        std::cout << "File moved successfully: " << sourcePath << " to " << destinationPath << std::endl;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "\nChoose an action:\n";
        std::cout << "1. Navigate directories\n";
        std::cout << "2. View files\n";
        std::cout << "3. Create directory\n";
        std::cout << "4. Copy file\n";
        std::cout << "5. Move file\n";
        std::cout << "0. Quit\n";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                navigateDirectories();
                break;
            case 2: {
                std::string directoryPath;
                std::cout << "Enter the directory path: ";
                std::cin >> directoryPath;
                viewFiles(directoryPath);
                break;
            }
            case 3: {
                std::string directoryPath;
                std::cout << "Enter the new directory path: ";
                std::cin >> directoryPath;
                createDirectory(directoryPath);
                break;
            }
            case 4: {
                std::string sourcePath, destinationPath;
                std::cout << "Enter the source file path: ";
                std::cin >> sourcePath;
                std::cout << "Enter the destination file path: ";
                std::cin >> destinationPath;
                copyFile(sourcePath, destinationPath);
                break;
            }
            case 5: {
                std::string sourcePath, destinationPath;
                std::cout << "Enter the source file path: ";
                std::cin >> sourcePath;
                std::cout << "Enter the destination file path: ";
                std::cin >> destinationPath;
                moveFile(sourcePath, destinationPath);
                break;
            }
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}


