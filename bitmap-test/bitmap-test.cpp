#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

typedef struct {
    byte b;
    byte g;
    byte r;
}RGB;

class CBitmap {
public:
    ~CBitmap() {
        Free(img, infoHeader.biHeight);
    }
    void load(const char* path) {
        bmpIn.open(path, ios::binary | ios::in);
        if (!bmpIn.good())
            exit(1);
        bmpIn.read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
        if (fileHeader.bfType != 0x4d42 || fileHeader.bfOffBits != 0x36)
            exit(1);
        bmpIn.read((char*)&infoHeader, sizeof(BITMAPINFOHEADER));
        if (infoHeader.biBitCount != 24)
            exit(1);
        img = new RGB * [infoHeader.biHeight];
        for (long i = 0; i < infoHeader.biHeight; i++) {
            img[i] = new RGB[infoHeader.biWidth];
            bmpIn.read((char*)img[i], (streamsize)infoHeader.biWidth * sizeof(RGB));
            for (long j = 0; j < checkOffset(); j++) bmpIn.get();
        }
        bmpIn.close();
    }
    void write(const char* path) {
        ofstream bmpOut;
        bmpOut.open(path, ios::out | ios::binary | ios::trunc);
        bmpOut.write((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
        bmpOut.write((char*)&infoHeader, sizeof(BITMAPINFOHEADER));
        for (long i = 0; i < infoHeader.biHeight; i++) {
            bmpOut.write((char*)img[i], (streamsize)infoHeader.biWidth * sizeof(RGB));
            for (long j = 0; j < checkOffset(); j++) bmpOut << 0;
        }
        bmpOut.close();
    }
    void toMirror() {
        RGB** newImg;
        newImg = new RGB * [infoHeader.biHeight];
        for (long i = 0; i < infoHeader.biHeight; i++) {
            newImg[i] = new RGB[infoHeader.biWidth];
            for (long j = 0; j < infoHeader.biWidth; j++)
                newImg[i][j] = img[i][infoHeader.biWidth - 1 - j];
        }
        for (long i = 0; i < infoHeader.biHeight; i++)
            for (long j = 0; j < infoHeader.biWidth; j++)
                img[i][j] = newImg[i][j];
        Free(newImg, infoHeader.biHeight);
    }
    void toRotate90() {
        long temp = infoHeader.biHeight;
        infoHeader.biHeight = infoHeader.biWidth;
        infoHeader.biWidth = temp;
        RGB** newImg;
        newImg = new RGB * [infoHeader.biHeight];
        for (long i = 0; i < infoHeader.biHeight; i++) {
            newImg[i] = new RGB[infoHeader.biWidth];
            for (long j = 0; j < infoHeader.biWidth; j++)
                newImg[i][j] = img[j][infoHeader.biHeight - 1 - i];
        }
        Free(img, infoHeader.biWidth);
        img = new RGB * [infoHeader.biHeight];
        for (long i = 0; i < infoHeader.biHeight; i++) {
            img[i] = new RGB[infoHeader.biWidth];
            for (long j = 0; j < infoHeader.biWidth; j++)
                img[i][j] = newImg[i][j];
        }
        Free(newImg, infoHeader.biHeight);
    }
    string fileHeaderToString() {
        string s("[Bitmap file header] type:");
        s += char(fileHeader.bfType & 0xff);
        s += char(fileHeader.bfType >> 8);
        s += " file size:" + to_string(fileHeader.bfSize);
        s += " offset:" + to_string(fileHeader.bfOffBits);
        return s;
    }
    string inforHeaderToString() {
        string s("[Bitmap info header]");
        s += " width:" + to_string(infoHeader.biWidth);
        s += " height:" + to_string(infoHeader.biHeight);
        s += " planes:" + to_string(infoHeader.biPlanes);
        s += " depth:" + to_string(infoHeader.biBitCount);
        s += " image size:" + to_string(infoHeader.biSizeImage);
        s += " header size:" + to_string(infoHeader.biSize);
        return s;
    }
private:
    RGB** img{};
    ifstream bmpIn{};
    BITMAPFILEHEADER fileHeader{};
    BITMAPINFOHEADER infoHeader{};
    void Free(RGB**& img, long row) {
        for (long i = 0; i < row; i++)
            delete[] img[i];
        delete[] img;
    }
    long checkOffset() {
        long offset = 4 - (infoHeader.biWidth * 3) % 4;
        return offset == 4 ? 0 : offset;
    }
};

int main()
{
    CBitmap bmp;
    bmp.load("d:\\a.bmp");
    cout << bmp.fileHeaderToString() << endl;
    cout << bmp.inforHeaderToString() << endl;
    bmp.toMirror();
    bmp.write("d:\\a1.bmp");
    bmp.toRotate90();
    bmp.write("d:\\a2.bmp");
    system("d:\\a.bmp");
    system("d:\\a1.bmp");
    system("d:\\a2.bmp");
}