#include <iostream>

#include <vector>

#include <stdexcept>

#include <string>

#include "class.h"

using namespace std;
int main(int argc, char * argv[]) {

  std::string inputString(argv[1]);

  //testowanie pliku
  // /*
  ASCIICanvas canvas(1, 1);
  canvas.prepareFromFile(inputString);
  canvas.draw();
  // */

  //testowanie ogolne
  // /*
  ASCIICanvas canvasTest(30, 30);

  canvasTest.setCharacter(19, 9, '@');
  canvasTest.setCharacter(5, 3, '#');
  canvasTest.setCharacter(7, 1, '*');

  cout << "Obraz:" << endl;
  canvasTest.draw();
  cout << "koniec obrazu" << endl;

  canvasTest.setBackground('-');

  cout << "Obraz:" << endl;
  canvasTest.draw();
  cout << "koniec obrazu" << endl;

  Triangle triangle(1, 1, 'a', 10, 7);
  Circle circle(7, 15, '#', 6);
  Rectangle rectangle(8, 1, 'b', 6, 3);
  Square square(14, 6, 'd', 4);

  cout << "Obraz:" << endl;
  triangle.draw(canvasTest);
  canvasTest.draw();
  cout << "koniec obrazu" << endl;

  cout << "Obraz:" << endl;
  rectangle.draw(canvasTest);
  canvasTest.draw();
  cout << "koniec obrazu" << endl;

  cout << "Obraz:" << endl;
  circle.draw(canvasTest);
  canvasTest.draw();
  cout << "koniec obrazu" << endl;
  //*/
  canvasTest.exportToFile("plik.txt");

  return 0;
}
