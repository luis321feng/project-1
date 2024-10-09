#include "File.h"

#include<cctype>


std::string File::getName() const {
    return filename_;
}

std::string File::getContents() const {
    return contents_;
}

void File::setContents(const std::string& new_contents) {
    contents_ = new_contents;
}

int* File::getIcon() const {
    return icon_;
}

void File::setIcon(int* new_icon) {
    if (icon_) {
        delete[] icon_;
    }
    icon_ = new_icon;
}

std::ostream& operator<<(std::ostream& os, const File& target) {
    os << "Name: " << target.getName() << std::endl;
    os << "Size: " << target.getSize() << " bytes" << std::endl;
    os << "Contents: " << target.getContents();
    return os;
}

bool File::operator<(const File& rhs) const {
    return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE.
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a;
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================

File::File(const std::string& filename, const std::string& contents, int* icon)
    : filename_("NewFile.txt"), contents_(contents), icon_(icon) {

    if (filename.empty()) {
        filename_ = "NewFile.txt";
        return;
    }

    int dotCount = 0;  

    for (char c : filename) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '.') {
            throw InvalidFormatException("Invalid character in filename");
        }

        if (c == '.') {
            dotCount++;
        }

        if (dotCount > 1) {
            throw InvalidFormatException("Too many dots in filename");
        }
    }

    if (dotCount == 0) {
        filename_ = filename + ".txt";
    }
    else {
        filename_ = filename; 
    }
}

size_t File::getSize() const {
    return contents_.size();
}

File::File(const File& rhs) : filename_(rhs.filename_), contents_(rhs.contents_) {
    if (rhs.icon_) {
        icon_ = new int[ICON_DIM];
        std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
    }
    else {
        icon_ = nullptr;
    }
}

File& File::operator=(File&& rhs) noexcept {
    if (this != &rhs) {
        delete[] icon_;
        filename_ = std::move(rhs.filename_);
        contents_ = std::move(rhs.contents_);
        icon_ = rhs.icon_;
        rhs.icon_ = nullptr;
    }
    return *this;
}

File::File(File&& rhs) noexcept
    : filename_(std::move(rhs.filename_)), contents_(std::move(rhs.contents_)), icon_(rhs.icon_) {
    rhs.icon_ = nullptr;
}

File& File::operator=(const File& rhs) {
    if (this != &rhs) {
        filename_ = rhs.filename_;
        contents_ = rhs.contents_;
        if (icon_) { delete[] icon_; }
        if (rhs.icon_) {
            icon_ = new int[ICON_DIM];
            std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
        }
        else {
            icon_ = nullptr;
        }
    }
    return *this;
}

File::~File() {
    delete[] icon_;
}

