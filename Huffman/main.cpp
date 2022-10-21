#include"compress.h"
#include<fstream>

int main() {
	/*潘霏霏 ff;
	万宇扬 yy;
	ff.小傻瓜("美女图片.jpg", "美女图片.huff");
	yy.大笨蛋("美女图片.huff", "美女图片.jpg");*/
	char buffer[256];
	std::fstream in("words.txt");
    if (!in.is_open())
        { std::cout << "Error opening file"; exit(1); }
     while (!in.eof())
      {
         in.getline(buffer, 100);
         in << "wor*";
         std::cout << "aline"<<buffer<<std::endl;
       }
     in.close();
}