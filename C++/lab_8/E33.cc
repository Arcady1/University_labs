// Escape-sequence manipulator
// to display color & alpha random mozaic

#include <iostream> // cin, cout
// #include <string>   // c_str, copy, length
#include <sstream>     // i(o)stringsteam, str
#include <iomanip>     // flush, endl
#include <sys/ioctl.h> // winsize, (tty_)ioctl
#include <termios.h>   // termios, tc(s)getattr
#include <fcntl.h>     // fcntl, O_NONBLOCK, F_S(G)ETFL
#include <stdio.h>     // EOF
#include <stdlib.h>    // (s)rand
#include <signal.h>    // signal, SIGINT
// #include <string.h> // strcpy, bzero
#include <unistd.h> // getpid, read, getopt

// Infinity loop control code

static int done = 0;

using namespace std; // Standard inout

namespace con
{ // Escape Console io block

  // Cursor max col location

  int comax()
  {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return (w.ws_col);
  } // comax

  // Cursor max row location

  int romax()
  {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return (w.ws_row);
  } // romax

  // ED, SCP, RCP with no parameter escape-manipulators

  // Eliminate Display
  // Spacing Screen by FormFeed (Scrooling Down)

  ostream &ED(ostream &s)
  {
    return s << string("\033[2J");
  } // ED

  // Eliminate Line
  // (Clear Line by spaces from cursor position)

  ostream &EL(ostream &s)
  {
    return s << string("\033[K");
  } // EL

  // Console class for escape-manipulators
  //  stream with parameter(s)

  class estream
  {
  private:
    string escape; // Escape string
  public:
    estream(string e) : escape(e){};
    friend ostream &operator<<(ostream &, estream);
  }; // estream

  // friend overload << for escape output

  ostream &operator<<(ostream &s, estream e)
  {
    s << e.escape << flush;
    return s;
  } // <<()

  // escape manipulator with 2 int parameters
  // to remove CUrsor in y row & x col Position
  // (equal $ echo -ne "\033[y;xH")

  estream CUP(int y, int x)
  {                                          // CUrsor Position
    ostringstream sout;                      // output string stream
    sout << "\033[" << y << ";" << x << "H"; // gotoxy ESC
    return estream(sout.str());              // return ESC object
  }                                          // CUP

  // Set pseudo-Graphic Regime escape manipulator
  // (equal $echo -ne "\033[Rm")
  // with Regime int parameter:

  // 0 default (black on white)
  // 1 Bold On
  // 4 Underscore
  // 5 Blink On
  // 7 Reverse video
  // 8 Cancelled On (invisible)
  // 3[0-7] foreground
  // 4[0-7] background
  // 2[1,4,5,7] cancel parameter in braces

  estream SGR(int r)
  {                              // Set Graphic Regime
    ostringstream sout;          // output string stream
    sout << "\033[" << r << "m"; // specify GraphMode
    return estream(sout.str());  // Return ESC object
  }                              // SGR

} // namespace con

// offen using Console Escape namespace

using con::CUP; // goto xy pos
using con::SGR; // Pseudo-graphic color mode

// Interrupt ^C catch function

void interruptor(int signo)
{
  done = signo;
  return;
} // interrupt

// Check KB enter has been

int kbin()
{
  char buf[512];                                // read buffer
  int n = 0;                                    // read bytes number
  int flags = fcntl(0, F_GETFL);                // stdin control flags
  usleep(1);                                    // delay 1 ms for fcntl
  fcntl(0, F_SETFL, flags | O_NONBLOCK);        // unblock input
  n = read(0, buf, 512);                        // nonblock read input line
  fcntl(0, F_SETFL, flags /* & ~O_NONBLOCK */); // block input
  return (n);                                   // return input bytes number
} // kbin

// Termios control any key pressed

int kbhit()
{
  int n = 0;
  char buf[512];
  struct termios t[2];
  tcgetattr(0, &t[0]);
  tcgetattr(0, &t[1]);
  t[0].c_lflag &= ~(ICANON | ECHO);
  t[0].c_cc[VMIN] = 0;
  t[0].c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &t[0]);
  n = read(0, buf, 512);
  tcsetattr(0, TCSAFLUSH, &t[1]);
  return (n);
} // kbhit

// command line options parse

int parser(int n, char **v)
{
  int p = 0; // mosaico control bit
  int opt;   // mosaico option code
  while ((opt = getopt(n, v, "afb")) != EOF)
  {
    switch (opt)
    { // set mosaico bit by option
    case 'a':
      p |= 1; // alpha mosaico
      break;
    case 'f':
      p |= 2; // foreground
      break;
    case 'b':
      p |= 4; // background
      break;
    case '?':
      break;
    } // switch
  }   // while
  return (p);
} // parser

// Command line format

int usage()
{
  cout << "Usage: E33 -afb" << endl;
  cout << "-a RANDOM ALPHA" << endl;
  cout << "-f RANDOM FOREGROUND" << endl;
  cout << "-b RANDOM BACKGROUND" << endl;
  return (0);
} // usage

// Main function test

int main(int argc, char **argv)
{
  int m; // mosaico type

  // Parse command line

  if ((argc = parser(argc, argv)) == 0)
    return (usage());

  // init graph mode to clear screen

  cout << SGR(30 + 7); // white=7, foreground=30
  cout << SGR(40 + 4); // blue=4, background=40
  cout << SGR(1);      // bold=1
  // cout << SGR(4) << flush; // underscore 4

  // Move curser to end row=24 and begin col=1

  cout << con::CUP(24, 1); // SouthWest gravity

  // Clear screen by FormFeed
  // by current (blue) background

  cout << con::ED; // Scrooling Down

  // Blinking Print exit prompt
  // by current (bold white) foreground

  cout << con::SGR(5); // Blink On
  cout << "^C or Enter to exit" << flush;
  cout << con::SGR(20 + 5); // Blink Off

  // ioctl get & type console window size

  cout << con::CUP(23, 1);
  cout << con::romax() << "x" << con::comax() << flush;

  // CONSOLE RANDOM DYNAMIC BLOCK

  int x, y;                    // cursor location
  char a;                      // alpha ascii code
  int f, b;                    // fore- & back-ground
  srand(getpid());             // random seed by process id
  signal(SIGINT, interruptor); // set ^C signal catch
  a = 32;
  b = (40 + 4);
  f = (30 + 7); // static init
  while (done < 1)
  {                          // while no ^C
    x = rand() % (80 + 1);   // random 1-80 cursor col
    y = rand() % (24 - 1);   // random 1-22 cursor row
    if (argc & 1)            //  -a
      a = 'A' + rand() % 26; // random A-Z
    if (argc == (2 + 1))     // -af
      f = 30 + rand() % 8;   // random 0-7 foreground 30
    if (argc & 4)            // -b
      b = 40 + rand() % 8;   // random 0-7 background 40
    cout << SGR(b) << CUP(y, x);
    cout << SGR(f) << a << flush;
    if (kbhit() > 0) // break any key hit
      break;
    // if(kbin() > 0)  // break any enter
    //   break;
  } // while-done

  // Clear bottom=24 line for sh prompt
  // (from begin=1 to ending pos)
  // with reset default 0 color & text mode

  cout << CUP(24, 1) << SGR(0) << con::EL;

  { /* termios & escape to get console size */
    // info block
    int x, y;
    char a;
    struct termios t[2];
    tcgetattr(0, &t[0]);
    tcgetattr(0, &t[1]);
    t[0].c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSAFLUSH, &t[0]);
    cout << "\033[512;512H" << flush;
    cout << "\033[6n" << flush;
    // read as typed from KB "\033[y;xR"
    cin >> a >> a >> y >> a >> x >> a;
    cout << " info:" << y << ';' << x << endl;
    tcsetattr(0, TCSAFLUSH, &t[1]);
  } // termios block

  return (m);

} // main
