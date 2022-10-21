#pragma once
#include<string>
#include<map>
#include"HuffmanTree.h"
#define 潘霏霏 huffEncode
#define 万宇扬 huffDecode
#define 小傻瓜 encode
#define 大笨蛋 decode

//得到index位的值，若index位为0，则GET_BYTE值为假，否则为真
#define GET_BYTE(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)
//index位置1
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
//index位置0
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

using uchar = unsigned char;

struct fileHead {
    char flag[4];                //压缩二进制文件头部标志huff
    int alphaVariety;            //字符种类数
    uchar lastValidBit;            //最后一个字节的有效位数
    char unused[10];            //待用空间
};                                //这个结构体总共占用16个字节的空间

struct alphaFreq {
    uchar alpha;                //字符,考虑到文件中有汉字，所以定义成uchar
    int freq;                    //字符出现的频度
    alphaFreq() {}
    alphaFreq(const std::pair<char, int>& x)
        : alpha(x.first), freq(x.second) {}
};

class huffEncode {
public:
    bool encode(const char* srcFilename, const char* destFilename);
private:
    int _getLastValidBit();
    bool _getAlphaFreq(const char* filename);
    bool _encode(const char* srcFilename, const char* destFilename);
private:
    std::map<uchar, int> _afMap;
    std::map<uchar, std::string> _codeMap;
};

class huffDecode {
public:
    huffDecode() : _fileHead(nullptr), _htree(nullptr) {
        _fileHead = new fileHead();
    }
    ~huffDecode() {
        if (!_fileHead) delete _fileHead;
        if (!_htree) delete _htree;
    }
private:
    static bool _isLeaf(huffNode<uchar>* n) {
        return n->left == nullptr && n->right == nullptr;
    }//判断是否为叶子节点
    long _getFileSize(const char* strFileName);
    bool _getAlphaFreq(const char* filename);
    bool _decode(const char* srcFilename,
        const char* destFilename);
public:
    bool decode(const char* srcFilename, const char* destFilename);
private:
    fileHead* _fileHead;
    huffTree<uchar> * _htree;
    std::map<uchar, int> _afMap;
    std::map<uchar, std::string> _codeMap;
    std::map<std::string, uchar> _decodeMap;
};