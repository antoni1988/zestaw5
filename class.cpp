#include "class.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
Canvas::Canvas(int width, int height) : width(width), height(height) {}

int Canvas::getWidth() const {
    return width;
}

int Canvas::getHeight() const {
    return height;
}

ASCIICanvas::ASCIICanvas(int width, int height) : Canvas(width, height) {
    canvas.resize(height, std::vector<char>(width, ' '));
}

void ASCIICanvas::draw()//wypisujemy plansze
{
    for (int j = 0; j < width + 2; ++j) {
        std::cout << '=';
    }
    std::cout << std::endl;

    for (int i = 0; i < height; ++i) {
        std::cout << '|';
        for (int j = 0; j < width; ++j) {
            std::cout << canvas[i][j];
        }
        std::cout << '|' << std::endl;
    }

    for (int j = 0; j < width + 2; ++j) {
        std::cout << '=';
    }
    std::cout << std::endl;
}

void ASCIICanvas::setCharacter(int x, int y, char ch) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        canvas[y][x] = ch;
    } else {
        std::cout<<"setCharacter Error, x:"<<x<<"y:"<<y<<"char:"<<ch<<std::endl;
        throw std::out_of_range("Invalid position");
    }
}

void ASCIICanvas::setBackground(char ch) {
    // ustawiamy dane tlo
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            canvas[i][j] = ch;
        }
    }
}
Figure::Figure(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}

Triangle::Triangle(int x, int y,char symbol, int base, int height) : Figure(x, y,symbol), base(base), height(height) {}

void Triangle::draw(ASCIICanvas& c) const  {
        for (int i = 0; i < height; ++i) {
            int width = base - 2 * i;
            int startX = x + i;

            for (int j = 0; j < width; ++j) {
                c.setCharacter(startX + j, y + i, symbol);
            }
        }
    }

Circle::Circle(int x, int y,char symbol, int radius) : Figure(x, y,symbol), radius(radius) {}

void Circle::draw(ASCIICanvas& c) const {
    int centerX = y;
    int centerY = x;
    //std::cout<<"Circle x:"<<x<<"y:"<<y<<"char:"<<symbol<<"radius:"<<radius<<std::endl;

for (int i = 0; i <= radius * 0.7071f; ++i)
        {
            int j = std::round(std::sqrt(radius * radius - i * i));
 
            c.setCharacter(j + centerY,i + centerX,symbol);
            c.setCharacter(j + centerY,-i + centerX,symbol);
            c.setCharacter(-j + centerY,-i + centerX,symbol);
            c.setCharacter(-j + centerY,i + centerX,symbol);
            
            c.setCharacter(i + centerY,j + centerX,symbol);
            c.setCharacter(-i + centerY,j + centerX,symbol);
            c.setCharacter(-i + centerY,-j + centerX,symbol);
            c.setCharacter(i + centerY,-j + centerX,symbol);
        }
}

Rectangle::Rectangle(int x, int y,char symbol, int width, int height): Figure(x, y,symbol), width(width), height(height) {}

    void Rectangle::draw(ASCIICanvas& c) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            c.setCharacter(x + j, y + i, symbol);
        }
    }
}
//do rysowania pustego prostokata
void Rectangle::drawOutline(ASCIICanvas& c) const {
    for (int i = 0; i < height; ++i) {
        c.setCharacter(x, y + i, symbol);
        c.setCharacter(x + width - 1, y + i, symbol);
    }
    for (int i = 0; i < width; ++i) {
        c.setCharacter(x + i, y, symbol);
        c.setCharacter(x + i, y + height - 1, symbol);
    }
}

Square::Square(int x, int y,char symbol, int side): Rectangle(x, y,symbol, side, side) {}

void Square::draw(ASCIICanvas& c) const {
    Rectangle::draw(c);
}
//do rysowania pustego kwadratu
void Square::drawOutline(ASCIICanvas& c) const {
    Rectangle::drawOutline(c);
}

void ASCIICanvas::prepareFromFile(const std::string& filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Read width, height, and symbol from the first line
    if (!(inputFile >> width >> height)) {
        std::cerr << "Invalid file format. Failed to read canvas dimensions." << std::endl << "Proper format: [width] [height] [symbol]" << std::endl;
        inputFile.close();
        return;
    }
    inputFile.ignore(); // Ignore the newline character
    if (inputFile.peek() != '\n') {
        inputFile >> backgroundChar;
    } else {
        backgroundChar = ' ';
    }

    canvas.assign(height, std::vector<char>(width, backgroundChar));

    // wykonujemy petle az do konca pliku
    //sprawdzamy co zawiera dana linijka
    std::string figureType;
    while (inputFile >> figureType) {
        if (figureType == "triangle") {
            int x, y, base, height;
            char symbol;
            if (!(inputFile >> x >> y >> symbol >> base >> height)) {
                std::cerr << "Invalid file format. Failed to read triangle parameters." << std::endl;
                inputFile.close();
                return;
            }
            Triangle triangle(x, y, symbol,base, height);
            std::cout << "Detected triangle with base " << base << ", height " << height << ", using symbol " << symbol << " at (" << x << ", " << y << ")" << std::endl;
            triangle.draw(*this);
        } else if (figureType == "circle") {
            int x, y, radius;
            char symbol;
            if (!(inputFile >> x >> y >> symbol >> radius)) {
                std::cerr << "Invalid file format. Failed to read circle parameters." << std::endl;
                inputFile.close();
                return;
            }
            Circle circle(x, y, symbol, radius );
            std::cout << "Detected circle with radius " << radius << ", using symbol " << symbol << " at (" << x << ", " << y << ")" << std::endl;
            circle.draw(*this);
        } else if (figureType == "rectangle") {
            int x, y, figureWidth, figureHeight;
            char symbol;
            if (!(inputFile >> x >> y >> symbol >> figureWidth >> figureHeight)) {
                std::cerr << "Invalid file format. Failed to read rectangle parameters." << std::endl;
                inputFile.close();
                return;
            }
            Rectangle rectangle(x, y,symbol, figureWidth, figureHeight);
            std::cout << "Detected rectangle with width " << figureWidth << ", height " << figureHeight << ", using symbol " << symbol << " at (" << x << ", " << y << ")" << std::endl;
            rectangle.draw(*this);
        } else if (figureType == "square") {
            int x, y, side;
            char symbol;
            if (!(inputFile >> x >> y >> symbol >> side)) {
                std::cerr << "Invalid file format. Failed to read square parameters." << std::endl;
                inputFile.close();
                return;
            }
            Square square(x, y,symbol, side);
            std::cout << "Detected square with side " << side << ", using symbol " << symbol << " at (" << x << ", " << y << ")" << std::endl;
            square.draw(*this);
        } else if (figureType == "squareOutline") {
            int x, y, side;
            char symbol;
            if (!(inputFile >> x >> y >> symbol >> side)) {
                std::cerr << "Invalid file format. Failed to read square parameters." << std::endl;
                inputFile.close();
                return;
            }
            Square square(x, y,symbol, side);
            std::cout << "Detected square with side " << side << ", using symbol " << symbol << " at (" << x << ", " << y << ")" << std::endl;
            square.drawOutline(*this);
        }    else {
            std::cerr << "Unknown figure type: " << figureType << std::endl;
        }
    }

    inputFile.close();
}
void ASCIICanvas::exportToFile(const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to create file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            outputFile << canvas[i][j];
        }
        outputFile << std::endl;
    }

    outputFile.close();
}


