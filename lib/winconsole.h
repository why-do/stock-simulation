#pragma once
#ifndef STOCKAPP_LIB_WINCONSOLE
#define STOCKAPP_LIB_WINCONSOLE
#include "consolecolor.h"
#include "string.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>

const int SETW_WIDTH = 11;
const int SET_PRECISION = 2;
const int START_X = 0;
const int CONSOLE_WIDTH = 140;
const int CONSOLE_HEIGHT = 45;
const char TABLE_SPLITE_CHAR = '-';

enum colorType {RED, BLUE, WHITE, YELLOW, GREEN, BLACK};

using namespace std;

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void initConsole() {
    char cmder[64];
    system("cls");
    sprintf(cmder, "mode con cols=%d lines=%d", CONSOLE_WIDTH, CONSOLE_HEIGHT);
    system(cmder);//�ı�console���
    cout<<setiosflags(ios::left)<<setprecision(8)<<setiosflags(ios::fixed); 
}


void setPrintLine(int line){
    gotoxy(START_X, line);
}


int printFieldsFinal(int line) {
    cout << white << endl;
    return line+1;
}

template <typename T1, typename T2>
string concat(const T1 &v1, const T2 &v2)
{
    stringstream oss;
    oss << fixed << setprecision(2) << v1 << v2;
    return oss.str();
}

template <typename T>
T fixArgs(T t) 
{
    return t;
}
template<typename T, typename... Args>
string fixArgs(T t, Args... args) // recursive variadic function
{
    return concat(t, fixArgs(args...));
}


// template <typename T>
template <typename T, typename... Args>
void printField(enum colorType color, T t,  Args...args){
    
    cout << setw(SETW_WIDTH) << fixed << setprecision(SET_PRECISION);
    switch(color)
    {
        case WHITE:
            cout << white ;
            break;
        case YELLOW:
            cout << yellow ;
            break;
        case BLUE:
            cout << blue ;
            break;
        case GREEN:
            cout << green ;
            break;
        case RED:
            cout << red ;
            break;
    }
     cout << fixArgs(t, args...);
    
}


template <typename T, typename... Args>
int printLine(int line, T t, Args...args)
{
    setPrintLine(line);
    cout << fixArgs(t, args...);
    return line+1;

}

template <typename T, typename... Args>
int printLineEnd(int line, T t, Args...args)
{
    setPrintLine(line);
    cout << fixArgs(t, args...) << endl;
    return line+1;

}


int printSplitLine(int startLine)
{
    string splitLine;
    setPrintLine(startLine);
    for(int i=0; i<CONSOLE_WIDTH; i++){
        splitLine += TABLE_SPLITE_CHAR;
    }
    cout << splitLine;

    return startLine+1;
}

int printCenterLine(int startLine, string str)
{
    
    int x = CONSOLE_WIDTH/2 - str.size()/2;
    gotoxy(x, startLine);
    cout << str << endl;
    
    return startLine+1;
}


char getKey(void) {
  char key = getch();
  if (key == -32 || key == 0) {
    key = getch();
  }

  return key;
}


char catchKey(void) {
  if (!kbhit()) {
    return 0;
  }

  return getKey();
}

#endif