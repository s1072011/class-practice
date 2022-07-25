#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <cmath>
#include <string>
#include <cstring>
#include <conio.h>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

using Byte = unsigned char;

template<class T>
class DataNode {
public:
  DataNode() = default;
  explicit DataNode(T data) :data(data) {}

private:
  T data = 0;
  shared_ptr<DataNode> next = nullptr;

  template<class U> friend class Queue;
};

template<class T>
class Queue {
public:
  Queue() = default;

  void push_back(T data) {
    if (empty()) {
      front = make_shared<Node>(data);
      back = front;
      size++;
      return;
    }

    auto newNode = make_shared<Node>(data);
    back->next = newNode;
    back = newNode;
    size++;
  }

  void pop() {
    if (empty())
      return;
    front = front->next;
    size--;
  }

  const T& get_front() const {
    return front->data;
  }

  const T& get_back() const {
    return back->data;
  }

  bool empty() const {
    return !(front.get() && back.get());
  }

  size_t get_size() const {
    return size;
  }

  const T& operator[](size_t index) const {
    auto temp = front;
    while (index--) {
      temp = temp->next;
    }
    return temp->data;
  }

private:
  using Node = DataNode<T>;

  shared_ptr<Node> front = nullptr;
  shared_ptr<Node> back = nullptr;
  size_t size = 0;
};

class ASCIIText {
public:
  ASCIIText() = default;

  static const unsigned __int64 kASCII[95];

  static Byte get_shape(const unsigned __int64& src) {
    int count_diff[95]{};

    int min = 48;
    int index = 0;

    for (int n = 0; n < 95; n++) {
      count_diff[n] = get_diff(src, kASCII[n]);
      if (min > count_diff[n]) {
        min = count_diff[n];
        index = n;
      }
    }
    return Byte(32 + index);
  }

  static Byte get_diff(unsigned __int64 X1, unsigned __int64 X2) {
    unsigned __int64 diff = X1 ^ X2;
    Byte result = 0;
    for (Byte i = 0; i < 48; i++) {
      result += ((diff >> i) & 1);
    }
    return result;
  }
};

const unsigned __int64 ASCIIText::kASCII[95]{
    0xffffffffffff,
    0xef1c7beffeff,
    0x924b7fffffff,
    0xff5835d60d7f,
    0xdf1bf3f63eff,
    0x9a6f7bdecb3f,
    0xdebaf7aadcbf,
    0xcf3dffffffff,
    0xef7df7df7eff,
    0xdfbefbefbdff,
    0xff5c60c75fff,
    0xffbee0efbfff,
    0xffffffff3cff,
    0xffffe0ffffff,
    0xffffffff3cff,
    0xffef7bdeffff,
    0xc6eb2a9aec7f,
    0xef3efbefbc7f,
    0xc6efb9def83f,
    0xc6efb1faec7f,
    0xf79d6d83df7f,
    0x82fbe1faec7f,
    0xe77be1baec7f,
    0x83ef7bdf7dff,
    0xc6ebb1baec7f,
    0xc6ebb0fbdcff,
    0xfffcf3ff3cff,
    0xfffcf3ff3cff,
    0xf7bdefdfbf7f,
    0xfff83ffe0fff,
    0xdfbf7ef7bdff,
    0xc6efb9effeff,
    0xc6ea2aa2fc7f,
    0xc6ebae82ebbf,
    0x86eba1bae87f,
    0xc6ebefbeec7f,
    0x86ebaebae87f,
    0x82fbe1bef83f,
    0x82fbe1befbff,
    0xc6ebe8baec3f,
    0xbaeba0baebbf,
    0xc7befbefbc7f,
    0xfbefbebaec7f,
    0xbadae7aedbbf,
    0xbefbefbef83f,
    0xba4aaebaebbf,
    0xba6aacbaebbf,
    0xc6ebaebaec7f,
    0x86eba1befbff,
    0xc6ebaeaadcbf,
    0x86eba1b6ebbf,
    0xc6ebf1faec7f,
    0x83befbefbeff,
    0xbaebaebaec7f,
    0xbaebaebb5eff,
    0xbaeaaaaaad7f,
    0xbaed7bd6ebbf,
    0xbaebb5efbeff,
    0x87def7bef87f,
    0xc77df7df7c7f,
    0xfefdfbf7efff,
    0xc7df7df7dc7f,
    0xef5bbfffffff,
    0xffffffffffe0,
    0xcf3effffffff,
    0xfffc7ec2ec3f,
    0xbef86ebae87f,
    0xfffc6ebeec7f,
    0xfbec2ebaec3f,
    0xfffc6e86fc7f,
    0xe77de1df7dff,
    0xfffc2ebb0fbf,
    0xbef8edb6db7f,
    0xeffefbefbe7f,
    0xf7fe7df7db7f,
    0xbefb6b9ebb7f,
    0xefbefbefbe7f,
    0xfff96aaaebbf,
    0xfff8edb6db7f,
    0xfffc6ebaec7f,
    0xfff86ebae87f,
    0xfffc2ebaec3f,
    0xfffa76df78ff,
    0xfffc6fc7ec7f,
    0xff7877df5eff,
    0xfffb6db69d7f,
    0xfffbaebb5eff,
    0xfffbaeaa0d7f,
    0xfffb6dcedb7f,
    0xfffb6db71eff,
    0xfff87dcef87f,
    0xe77de7df7e7f,
    0xefbeffefbeff,
    0xcfdf7cf7dcff,
    0xd6bfffffffff
};


template<class T>
class MATRIX {
public:
  MATRIX() = default;

  explicit MATRIX(size_t row, size_t column) :row(row), column(column) {
    init();
  }

  MATRIX(const MATRIX& other) {
    if (this == &other) {
      return;
    }
    *this = other;
  }

  ~MATRIX() = default;

  void init() {
    if (matrix) {
      for (int i = 0; i < row; i++) {
        matrix[i].reset();
      }
      matrix.reset();
    }

    matrix = make_unique<Row>(row);
    for (int i = 0; i < row; i++) {
      matrix[i] = make_unique<Col>(column);
    }
  }

  unique_ptr<T[]>& operator[](size_t index) const {
    return matrix[index];
  }

  MATRIX& operator=(const MATRIX& other) {
    if (this == &other) {
      return *this;
    }
    row = other.row;
    column = other.column;
    init();
    for (size_t i = 0; i < row; i++)
      for (size_t j = 0; j < column; j++)
        matrix[i][j] = other[i][j];
    return *this;
  }

  friend ostream& operator<<(ostream& os, const MATRIX& _matrix) {
    string temp("");
    size_t i = 0;
    for (i = 0; i < _matrix.row; i++) {
      temp.append(_matrix[i].get(), _matrix.column);
      temp += '\n';
    }
    cout << temp;
    temp = "";
    return os;
  }

private:
  using Mat = unique_ptr<unique_ptr<T[]>[]>;
  using Row = unique_ptr<T[]>[];
  using Col = T[];
  size_t     row = 0;
  size_t     column = 0;
  Mat matrix = nullptr;
};

class CBitmap {
public:
  using RGB = struct RGB {
    Byte B;
    Byte G;
    Byte R;
  };

  CBitmap() = default;

  explicit CBitmap(const char* path)
  {
    Load(path);
  }

  void Load(const char* path) {
    ifstream bmp_in;
    bmp_in.open(path, ios::binary | ios::in);

    bmp_in.read((char*)&file_header, sizeof(BITMAPFILEHEADER));
    bmp_in.read((char*)&info_header, sizeof(BITMAPINFOHEADER));

    if (!bmp_in || file_header.bfType != 0x4d42) {
      bmp_in.close();
      return;
    }

    img = CreateImg(info_header.biHeight, info_header.biWidth);
    padding = get_offset();

    for (long i = 0; i < info_header.biHeight; i++) {
      bmp_in.read((char*)img[i].get(), (streamsize)info_header.biWidth * 3);
      bmp_in.ignore(padding);
    }
    bmp_in.close();
  }

  void Save(const char* path) {
    ofstream bmp_out;

    bmp_out.open(path, ios::out | ios::binary | ios::trunc);
    bmp_out.write((char*)&file_header, sizeof(BITMAPFILEHEADER));
    bmp_out.write((char*)&info_header, sizeof(BITMAPINFOHEADER));

    if (color_table) {
      auto color_table_size = (int)pow(2, info_header.biBitCount);
      for (int i = 0; i < color_table_size; i++) {
        bmp_out.write((char*)&color_table[i], 4);
      }
    }

    padding = get_offset();

    switch (info_header.biBitCount) {
    case 24:
      for (long i = 0; i < info_header.biHeight; i++) {
        bmp_out.write((char*)img[i].get(), (streamsize)info_header.biWidth * (info_header.biBitCount / 8));
        for (long j = 0; j < padding; j++)
          bmp_out << 0;
      }
      break;
    case 8:
      for (long i = 0; i < info_header.biHeight; i++) {
        for (long j = 0; j < info_header.biWidth; j++) {
          bmp_out.write((char*)&img[i][j].B, 1);
        }
        for (long n = 0; n < padding; n++)
          bmp_out << 0;
      }
      break;
    default:
      auto real_col = size_t(ceil(info_header.biWidth / 32.0) * 4);
      auto output = make_unique<Byte[]>(real_col);

      for (long i = 0; i < info_header.biHeight; i++) {
        memset(output.get(), 0, real_col);
        for (long j = 0, shift = 7, n = 0; j < info_header.biWidth; j++) {
          if (j != 0 && !(j & 7)) {
            n++;
            shift = 7;
          }
          output[n] |= (img[i][j].B << shift);
          shift--;
        }

        bmp_out.write((char*)output.get(), real_col);
      }
      break;
    }

    bmp_out.close();
  }

  void Resize(long new_width, long new_height) {
    double delta_i = info_header.biHeight / (double)new_height;
    double delta_j = info_header.biWidth / (double)new_width;

    double new_i = 0;
    double new_j = 0;

    auto scaled_img = CreateImg(new_height, new_width);

    for (long i = 0; i < new_height; i++) {
      new_i = (i + 0.5) * delta_i - 0.5;

      for (long j = 0; j < new_width; j++) {
        new_j = (j + 0.5) * delta_j - 0.5;
        scaled_img[i][j] = NearestNeighbor(new_i, new_j);
      }
    }

    for (int i = 0; i < info_header.biHeight; i++) {
      img[i].reset();
    }
    img.reset(scaled_img.release());

    info_header.biHeight = new_height;
    info_header.biWidth = new_width;
    padding = get_offset();

    file_header.bfSize = get_file_size();
    info_header.biSizeImage = get_img_size();
  }

  void to_gray_scale() {
    if (info_header.biBitCount == 24) {
      for (long i = 0; i < info_header.biHeight; i++) {
        for (long j = 0; j < info_header.biWidth; j++) {
          //RGB轉YUV，只計算Y值(明亮度, 0 <= Y <=255)
          auto new_color = get_gray_value(img[i][j]);
          img[i][j].B = new_color;
          img[i][j].G = new_color;
          img[i][j].R = new_color;
        }
      }
      padding = get_offset();

      info_header.biBitCount = 8;
      set_color_table();

      file_header.bfOffBits = 0x436; //0x36 + 0x400
      info_header.biSizeImage = get_img_size();
      file_header.bfSize = get_file_size();
    }
  }

  //to black and white
  void to_binary(Byte threshold) {
    switch (info_header.biBitCount)
    {
    case 1:
      return;
    case 8:
      for (long i = 0; i < info_header.biHeight; i++) {
        for (long j = 0; j < info_header.biWidth; j++) {
          auto new_color = get_binary(img[i][j].B, threshold);
          img[i][j].B = new_color;
          img[i][j].G = new_color;
          img[i][j].R = new_color;
        }
      }
      break;
    case 24:
      for (long i = 0; i < info_header.biHeight; i++) {
        for (long j = 0; j < info_header.biWidth; j++) {
          auto new_color = get_binary(get_gray_value(img[i][j]), threshold);
          img[i][j].B = new_color;
          img[i][j].G = new_color;
          img[i][j].R = new_color;
        }
      }
      break;
    default:
      break;
    }
    info_header.biBitCount = 1;
    set_color_table();

    file_header.bfOffBits = 0x3E; //0x36 + 0x08
    file_header.bfSize = get_file_size();
    info_header.biSizeImage = get_img_size();
  }

  void to_matrix(const MATRIX<Byte>& matrix) const {
    if (info_header.biBitCount == 1) {
      for (long i = 0; i < info_header.biHeight; i++) {
        for (long j = 0; j < info_header.biWidth; j++) {
          matrix[i][j] = img[i][j].B;
        }
      }
    }
  }

  MATRIX<char> Quantization() const {
    MATRIX<Byte> matrix(info_header.biHeight, info_header.biWidth);
    to_matrix(matrix);

    auto new_height = (size_t)(info_header.biHeight / 8);
    auto new_width = (size_t)(info_header.biWidth / 6);
    MATRIX<char> new_mat(new_height, new_width);

    size_t index_h = new_height - 1;
    for (long i = 0; i < info_header.biHeight; i += 8) {
      for (long j = 0; j < info_header.biWidth; j += 6) {
        unsigned __int64 temp = 0;
        for (long n = i, shift = 42; n < i + 8; n++, shift -= 6) {
          unsigned __int64 w_bit = 0;
          for (long k = j, w_shift = 5; k < j + 6; k++, w_shift--) {
            w_bit |= ((unsigned __int64)matrix[n][k] << w_shift);
          }
          temp |= (w_bit << shift);
        }
        new_mat[index_h][j / 6] = ASCIIText::get_shape(temp);
      }
      index_h--;
    }
    return new_mat;
  }

  DWORD get_file_size() const {
    auto size = (DWORD)(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

    if (info_header.biBitCount == 1) {
      size += (get_img_size() + 8);
      return size;
    }
    else if (info_header.biBitCount == 8) {
      size += 1024;
    }

    size += ((size_t)get_img_size() * (info_header.biBitCount / 8) + (size_t)padding * info_header.biHeight);
    return size;
  }

  DWORD get_img_size() const {
    if (info_header.biBitCount == 1) {
      return DWORD(info_header.biHeight * ceil(info_header.biWidth / 32.0) * 4);
    }
    else {
      return DWORD(info_header.biHeight * info_header.biWidth);
    }
  }

  bool operator!() const {
    return (img.get() == nullptr);
  }

private:
  using Img = unique_ptr<unique_ptr<RGB[]>[]>;
  using Row = unique_ptr<RGB[]>[];
  using Col = RGB[];

  Img img = nullptr;
  BITMAPFILEHEADER file_header = {};
  BITMAPINFOHEADER info_header = {};
  unique_ptr<RGBQUAD[]> color_table;

  unsigned short padding{};

  RGB NearestNeighbor(double new_x, double new_y) const {
    auto x = (long)round(new_x);
    auto y = (long)round(new_y);
    if (x >= info_header.biHeight) x = info_header.biHeight - 1;
    else if (x < 0) x = 0;
    if (y >= info_header.biWidth) x = info_header.biWidth - 1;
    else if (y < 0) y = 0;
    return img[x][y];
  }

  Img CreateImg(long height, long width) const {
    auto temp = make_unique<Row>(height);
    for (long i = 0; i < height; i++)
      temp[i] = make_unique<Col>(width);
    return temp;
  }

  void set_color_table() {
    if (color_table)
      color_table.reset();

    auto size = size_t(pow(2, info_header.biBitCount));
    color_table = make_unique<RGBQUAD[]>(size);

    if (info_header.biBitCount == 1) {
      memset(&color_table[0], 0, 3);
      memset(&color_table[1], 255, 3);
      return;
    }
    else if (info_header.biBitCount == 8) {
      for (size_t i = 0; i < size; i++) {
        memset(&color_table[i], (int)i, 3);
      }
    }
  }

  Byte get_gray_value(RGB _RGB) const {
    return Byte(round((double)_RGB.B * 0.114 + (double)_RGB.G * 0.587 + (double)_RGB.R * 0.299));
  }

  Byte get_binary(Byte val, Byte threshold = 127) const {
    return (val > threshold) ? 0 : 1;
  }

  unsigned short get_offset() const {
    if (info_header.biBitCount < 8)
      return 0;

    unsigned short offset;
    offset = 4 - (info_header.biWidth * (info_header.biBitCount / 8)) % 4;
    return (offset == 4) ? 0 : offset;
  }
};

class Frame
{
private:
  MATRIX<char> matrix;
public:
  Frame() = default;
  explicit Frame(const MATRIX<char>& _matrix) : matrix(_matrix) {}

  void Show() const
  {
    cout << matrix;
  }
};

class Animator
{
public:
  explicit Animator(int size) : n_frames(size) {
    frames.resize(size);
  }

  ~Animator() {
    system("cls");
  }

  void Load(const string& folder) {
    auto finished = 0.0;

    mutex _lock;
    auto load = [&, folder](int n) {
      string input = folder + "\\" + to_string(n) + ".bmp";
      CBitmap bitmap(input.c_str());
      if (!bitmap) {
        cout << "Can't load" << input << endl;
        return;
      }
      bitmap.Resize(564, 1000);
      bitmap.to_binary(147);
      //string out = folder + "\\binary" + to_string(n) + ".bmp";
      //bitmap.Save(out.c_str());
      frames[n] = Frame(bitmap.Quantization());
      finished++;
      _lock.lock();
      Clear();
      cout << "Loading... ";
      cout << short((finished / (double)n_frames) * 100) << '%';
      this_thread::sleep_for(chrono::milliseconds(100));
      _lock.unlock();
    };

    vector<jthread> tasks;
    for (int i = 0; i < n_frames; i++) {
      tasks.emplace_back(load, i);
      this_thread::sleep_for(chrono::milliseconds::duration(400));
    }
    tasks.clear();
  }

  void Play() {
    CONSOLE_FONT_INFOEX cf = {};
    cf.cbSize = sizeof cf;
    cf.dwFontSize.X = 4;
    cf.dwFontSize.Y = 6;
    wcscpy_s(cf.FaceName, L"Terminal");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cf);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    state = State::kIsPlaying;

    auto last = chrono::steady_clock::now();
    auto now = chrono::steady_clock::now();
    auto difference = chrono::duration_cast<chrono::milliseconds>(now - last);

    double fps = 0.0;
    double avr = 0.0;
    Queue<double> fps_record;

    chrono::milliseconds delay(20);

    while (state == State::kIsPlaying || state == State::kIsPause)
    {
      for (int current_f = 0; current_f < n_frames;)
      {
        switch (state)
        {
        case State::kIsPlaying:
          Clear();
          frames[current_f].Show();
          fps++;
          cout << avr;
          this_thread::sleep_for(delay);
          now = chrono::steady_clock::now();
          difference = chrono::duration_cast<chrono::milliseconds>(now - last);
          if (difference.count() >= 1000) {
            fps_record.push_back(fps);
            fps = 0;

            if (auto size = fps_record.get_size(); size == 5) {
              double sum = 0.0;
              for (size_t n = 0; n < size; n++) {
                sum += fps_record[n];
              }
              avr = (sum / (double)size);
              fps_record.pop();
            }
            last = chrono::steady_clock::now();
          }
          current_f++;
          break;
        case State::kLArrowKeyDown:
          current_f--;
          if (current_f < 0)
            current_f = n_frames - 1;
          state = State::kIsPause;
          Clear();
          frames[current_f].Show();
          break;
        case State::kRArrowKeyDown:
          current_f++;
          if (current_f >= n_frames) {
            current_f = 0;
          }
          state = State::kIsPause;
          Clear();
          frames[current_f].Show();
          break;
        case State::kIsStop:
          return;
        default:
          break;
        }
      }
    }
  }

  void Stop() {
    state = State::kIsStop;
  }

  void Pause() {
    if (state == State::kIsPlaying)
      state = State::kIsPause;
    else
      state = State::kIsPlaying;
  }

  void NextFrame() {
    if (state == State::kIsPause)
      state = State::kRArrowKeyDown;
    else if (state == State::kIsPlaying)
      state = State::kIsPause;
  }

  void LastFrame() {
    if (state == State::kIsPause)
      state = State::kLArrowKeyDown;
    else if (state == State::kIsPlaying)
      state = State::kIsPause;
  }

  static void Clear() {
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    static COORD coord{ 0,0 };
    SetConsoleCursorPosition(handle, coord);
  }

private:
  enum class State {
    kIsStop,
    kIsPlaying,
    kIsPause,
    kRArrowKeyDown,
    kLArrowKeyDown
  };

  int n_frames;
  State state = State::kIsStop;
  vector<Frame> frames;
};

class App {
public:
  void run() const {
    Animator animator(89);
    animator.Load("C:\\Users\\LENOVO\\Desktop\\test1");

    jthread play([&] {
      animator.Play();
      });

    for (;;) {
      auto key = _getch();
      if (key == ' ') {
        animator.Pause();
      }
      else if (key == 'q' || key == 'Q') {
        break;
      }
      else if (key == 224) {
        key = _getch();
        if (key == 77) {
          animator.NextFrame();
        }
        else if (key == 75) {
          animator.LastFrame();
        }
      }
    }
    animator.Stop();
  }
};

int main() {
  App app;
  app.run();
  return 0;
}