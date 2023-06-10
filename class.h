#ifndef CLASS_H
#define CLASS_H

#include <vector>

#include <string>

class Canvas {
  protected: int width;
  int height;

  public: Canvas(int width, int height);

  virtual void draw() = 0;

  int getWidth() const;
  int getHeight() const;
  void setBackground(char ch);
};

class ASCIICanvas: public Canvas {
  private: std::vector < std::vector < char >> canvas;
  char backgroundChar; //tlo planszy

  public: ASCIICanvas(int width, int height); // wielkosc planszy x to szerokosc y to wysokosc

  void draw() override; // wypisuje plansze

  void setCharacter(int x, int y, char ch); //ustawia na wspolrzednych (x,y) znak ch

  void setBackground(char ch); // ustawia wszystkie znaki w tablicy na dany znak ale celowo nie zmienia znaku tla ( moze sie przydac do porownywan)

  void prepareFromFile(const std::string & filename); // zajmuje sie wszyskim przy wczytywaniu pliku

  void exportToFile(const std::string & filename); //zapisuje kanwe do pliku
};

class Figure {
  protected: int x;
  int y;
  char symbol; //czym rysujemy
  // int dimension;//lepiej by bylo zdefiniowac w poszczegolnych figurach

  public: Figure(int x, int y, char symbol);

  virtual void draw(ASCIICanvas & c) const = 0;
};

class Triangle: public Figure { //trojkat rownoramienny 
  private: int base;
  int height;

  public: Triangle(int x, int y, char symbol, int base, int height);

  void draw(ASCIICanvas & c) const override;
};

class Circle: public Figure {
  private: int radius;

  public: Circle(int x, int y, char symbol, int radius);

  void draw(ASCIICanvas & c) const override;
};

class Rectangle: public Figure {
  private: int width;
  int height;

  public: Rectangle(int x, int y, char symbol, int width, int height);
  void drawOutline(ASCIICanvas & c) const;
  void draw(ASCIICanvas & c) const override; //default
};

class Square: public Rectangle {
  public: Square(int x, int y, char symbol, int side);

  void drawOutline(ASCIICanvas & c) const;
  void draw(ASCIICanvas & c) const;
};

#endif // CLASS_H
