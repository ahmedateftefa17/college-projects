#include <iostream>
#include <iomanip>

using namespace std;

class CColor
{

private:

  int red, green, blue;

  string getHexString(){
    return "0x00" + to_HexString(this->red) + to_HexString(this->green) + to_HexString(this->blue);
  }

  string getDecString(){
    return "(" + to_string(this->red) + ", " + to_string(this->green) + ", " + to_string(this->blue) + ")";
  }

  string to_HexString(int handledInteger){
    stringstream ss;
    ss << hex << handledInteger;
    string res(ss.str());
    return handledInteger < 16 ? "0" + res : res;
  }

public:

  CColor(){
    this->red = 0;
    this->green = 0;
    this->blue = 0;
  }

  CColor(int red, int green, int blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
  }

  CColor(int hex){
    string strHex = "";
    while(hex != 0){
      strHex = to_string(hex % 16) + strHex;
      hex /= 16;
    }
    for(int i = strHex.length(); i < 6; i++)  strHex = "0" + strHex;
    this->red = stol("0x" + strHex.substr(0, 2), nullptr, 16);
    this->green = stol("0x" + strHex.substr(2, 2), nullptr, 16);
    this->blue = stol("0x" + strHex.substr(4, 2), nullptr, 16);
  }

  string operator () (string type){
    if(type == "hex")
      return this->getHexString();
    return this->getDecString();
  }

  friend ostream& operator << (ostream &os, CColor &C){
    os<<C.getDecString();
    return os;
  }

  CColor operator = (CColor &C){
    this->red = C.red;
    this->green = C.green;
    this->blue = C.blue;
    return *this;
  }

  friend CColor average(CColor &a, CColor &b, CColor &c);

};

CColor average(CColor &a, CColor &b, CColor &c){
  CColor temp;
  temp.red = (a.red + b.red + c.red) / 3;
  temp.green = (a.green + b.green + c.green) / 3;
  temp.blue = (a.blue + b.blue + c.blue) / 3;
  return temp;
}

int main(int argc, char const *argv[])
{
  CColor a(255/*red*/, 128/*green*/, 00/*blue*/);
  CColor b(0x00667700); //red: 0x66, green: 0x77, blue: 0x55
  CColor c(0x00552200);
  cout << "a color = " << a << endl; //should prints (255, 128, 192)
  cout << "b color = " << b("hex") << endl; //should prints 0x00667755
  //Make y = average of a and b and c
  CColor y = average(a, b, c);
  cout << "y color = " << y << endl;
  return 0;
}
