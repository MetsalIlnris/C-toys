#include<iostream>
#include<fstream>
#include<map>
#include"compress.h"

//**************************************//
//            HUFF ENCODE               //
//**************************************//

bool huffEncode::encode(const char* srcFilename, const char* destFilename) {
    if (!_getAlphaFreq(srcFilename)) return false;
    huffTree<uchar> htree(_afMap);
    htree.huffmanCode(_codeMap);
    return _encode(srcFilename, destFilename);
}

int huffEncode::_getLastValidBit() {
    int sum = 0;
    for (auto it : _codeMap) {
        sum += it.second.size() * _afMap.at(it.first);
        sum &= 0xFF;
    }
    sum &= 0x7;
    return sum == 0 ? 8 : sum;
}

bool huffEncode::_getAlphaFreq(const char* filename) {
    std::cout << "正在构筑字符集频数图表" << std::endl;
    uchar ch;
    std::ifstream is(filename, std::ios::binary);
    if (!is.is_open()) {
        printf("read file failed! filename: %s", filename);
        return false;
    }
    is.read((char*)&ch, sizeof(uchar));
    while (!is.eof()) {
        _afMap[ch]++;
        is.read((char*)&ch, sizeof(uchar));
    }
    is.close();
    return true;
}

bool huffEncode::_encode(const char* srcFilename, const char* destFilename) {
    uchar ch;
    uchar value;
    int bitIndex = 0;
    fileHead filehead = { 'h', 'u', 'f', 'f' };
    //由于大小端问题，不宜使用强制转换filehead.alphaVariety = (uchar)_afMap.size()
    filehead.alphaVariety = _afMap.size();
    filehead.lastValidBit = _getLastValidBit();

    std::cout << "正在尝试打开文件" << std::endl;

    std::ifstream is(srcFilename, std::ios::binary);
    if (!is.is_open()) {
        printf("read file failed! filename: %s", srcFilename);
        return false;
    }
    std::ofstream io(destFilename, std::ios::binary);
    if (!io.is_open()) {
        printf("read file failed! filename: %s", destFilename);
        return false;
    }

    std::cout << "正在文件" << destFilename << "中写入haffman编码" << std::endl;

    io.write((char*)&filehead, sizeof(fileHead));
    for (auto i : _afMap) {
        alphaFreq af(i);
        io.write((char*)&af, sizeof(alphaFreq));
    }

    is.read((char*)&ch, sizeof(uchar));
    while (!is.eof()) {
        auto iter = _codeMap.find(ch);
        if (iter == _codeMap.end())std::cout << "在哈夫曼中寻找字符" << ch << "失败" << std::endl;
        else {
            std::string code = iter->second;
            for (auto c : code) {
                if ('0' == c) {
                    CLR_BYTE(value, bitIndex);
                }
                else {
                    SET_BYTE(value, bitIndex);
                }
                ++bitIndex;
                if (bitIndex >= 8) {
                    bitIndex = 0;
                    io.write((char*)&value, sizeof(uchar));
                }
            }
        }
        is.read((char*)&ch, sizeof(uchar));
    }

    if (bitIndex) {
        io.write((char*)&value, sizeof(uchar));
    }
    is.close();
    io.close();
    std::cout << "压缩成功！"  << std::endl;
    return true;
}

//**************************************//
//            HUFF DECODE               //
//**************************************//

long huffDecode::_getFileSize(const char* strFileName) {
    std::ifstream in(strFileName);
    if (!in.is_open()) return 0;

    in.seekg(0, std::ios_base::end);
    std::streampos sp = in.tellg();
    in.close();
    return sp;
}
  
bool huffDecode::_getAlphaFreq(const char* filename) {
    std::cout << "正在构筑字符集频数图表" << std::endl;

    std::ifstream is(filename, std::ios::binary);
    if (!is) {
        printf("read file failed! filename: %s", filename);
        return false;
    }

    is.read((char*)_fileHead, sizeof(fileHead));
    if (!(_fileHead->flag[0] == 'h' &&
        _fileHead->flag[1] == 'u' &&
        _fileHead->flag[2] == 'f' &&
        _fileHead->flag[3] == 'f')) {
        printf("not support this file format! filename: %s\n", filename);
        return false;
    }
    for (int i = 0; i < static_cast<int>(_fileHead->alphaVariety); ++i) {
        alphaFreq af;
        is.read((char*)&af, sizeof(af));
        _afMap.insert(std::pair<char, int>(af.alpha, af.freq));
    }
    is.close();
    return true;
}
    
bool huffDecode::_decode(const char* srcFilename,
    const char* destFilename) {
    long fileSize = _getFileSize(srcFilename);


    std::ifstream is(srcFilename, std::ios::binary);
    if (!is) {
        printf("read file failed! filename: %s", srcFilename);
        return false;
    }
    is.seekg(sizeof(fileHead) + sizeof(alphaFreq) * _fileHead->alphaVariety);

    huffNode<uchar> node = _htree->getHuffTree();
    huffNode<uchar>* pNode = &node;

    std::cout << "正在尝试打开文件" << std::endl;

    std::ofstream io(destFilename, std::ios::binary);
    if (!io) {
        printf("create file failed! filename: %s", destFilename);
        return false;
    }

    std::cout << "正在文件" << destFilename << "中写入haffman解析编码" << std::endl;

    uchar value;
    std::string code;
    int index = 0;
    long curLocation = is.tellg();
    is.read((char*)&value, sizeof(uchar));
    while (1) {
        if (curLocation == -1) //curLocation >= fileSize && index >= _fileHead->lastValidBit
        {
            break;
        }
        if (_isLeaf(pNode)) {
            uchar alpha = _decodeMap[code];
            io.write((char*)&alpha, sizeof(uchar));
            code.clear();
            pNode = &node;
        }

        if (GET_BYTE(value, index)) {
            code += '1';
            pNode = pNode->right;
        }
        else {
            pNode = pNode->left;
            code += '0';
        }
        if (++index >= 8) {
            index = 0;
            is.read((char*)&value, sizeof(uchar));
            curLocation = is.tellg();
        }
    }

    is.close();
    io.close();
    std::cout << "解压缩成功！" << std::endl;
    return true;
}

bool huffDecode::decode(const char* srcFilename, const char* destFilename) {
    if (!_getAlphaFreq(srcFilename)) return false;
    long fileSize = _getFileSize(srcFilename);
    _htree = new huffTree<uchar>(_afMap);
    //_htree->watch();
    _htree->huffmanCode(_codeMap);

    for (auto it : _codeMap) {
        _decodeMap.insert(std::pair<std::string, uchar>(it.second, it.first));
    }

    return _decode(srcFilename, destFilename);
}