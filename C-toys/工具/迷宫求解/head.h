#include<stdio.h>
#include <iostream> 
#define MAXLEN 50

using namespace std;

typedef struct
{
 char a[50];
 int length;
}sstring;


/********************/
void Initsstring(sstring& s)
{
 char b;
 s.length = 0;
 cin >> b;
 while (b != '#')
 {
  s.length++;
  s.a[s.length] = b;
  cin >> b;
 }
}//直接输入字符



/********************/
void printfsstring(sstring s)
{
 int i;
 for (i = 1; i <= s.length; i++)
 {
  cout << s.a[i];
 }
}//打印输入的字符串


