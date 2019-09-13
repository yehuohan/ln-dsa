//==============================================================================
/*!
 * @file bitmap.h
 * @brief bitmap算法
 *
 * @date
 * @version
 * @author
 * @copyright
 */
//==============================================================================


#ifndef DSAS_BITMAP_H
#define DSAS_BITMAP_H

#include <cstdio>
#include <cstring>

namespace dsa
{

/*!
 * @addtogroup LBitmap
 *
 * @{
 */

/*!
 * @brief Bitmap结构
 *
 * <pre>
 * (1) 原理：用一个bit来标记一个数是否存在。
 * 一个int-32bit，可以标记十进制0~31，即表示了32个整型数据。
 * 相当于存储32个数据只需要4个字节。
 * 若用char来存储32个数据(0~31)，则至少需要32个字节。
 *
 * (2) 存储序列图：
 * char  char[0]         char[n]
 * bit  [7      0]......[7      0]
 *      低字节          高字节
 *
 * k=0 : char[0]-bit[7]
 * k=7 : char[0]-bit[0]
 * k=8 : char[1]-bit[7]
 * k=9 : char[1]-bit[6]
 * k=15: char[1]-bit[0]
 * char[n]  : n = k/8 = k>>3
 * bit[n-1] : n = 0x80 >> (k%8) = 0x80 >> (k&0x07)
 *
 * </pre>
 */
class Bitmap
{
private:
    char*   m_cap;      /**< Bitmap内存空间m_cap[] */
    int     m_len;      /**< m_cap[]的长度，数据范围[0, m_len*8) */

public:
    Bitmap(int n = 8) {this->init(n);}
    /** 用char数组生成Bitmap */
    Bitmap(int len, const char bm[])
    {
        this->m_len = len;
        this->m_cap = new char[this->m_len];
        std::memcpy(this->m_cap, bm, len);
    }
    /** 从文件中读取数据 */
    Bitmap(const char* file, int n)
    {
        this->init(n);
        std::FILE* fp = std::fopen(file, "rb");
        std::fread(this->m_cap, sizeof(char), this->m_len, fp);
        std::fclose(fp);
    }
    /** 拷贝构造函数 */
    Bitmap(const Bitmap& bm)
    {
        this->m_len = bm.m_len;
        this->m_cap = new char[this->m_len];
        std::memcpy(this->m_cap, bm.m_cap, this->m_len);
    }
    ~Bitmap() {delete[] this->m_cap; this->m_cap = nullptr;}

    /** 标记对应k的bit为1，即插入数据 */
    void set(int k)   {this->expand(k); m_cap[k>>3] |=   (0x80 >> (k & 0x07));}
    /** 标记对应k的bit为0，即删除数据 */
    void clear(int k) {this->expand(k); m_cap[k>>3] &= (~(0x80 >> (k & 0x07)));}
    /** 返回对应k的bit，即数据存在与否 */
    bool test(int k)
    {
        if (k >= this->m_len*8) return false;
        return (m_cap[k>>3] & (0x80 >> (k & 0x07)));
    }

    /** 将Bitmap导出到二进制文件 */
    void dump(const char* file)
    {
        std::FILE* fp = std::fopen(file, "wb");
        std::fwrite(this->m_cap, sizeof(char), this->m_len, fp);
        std::fclose(fp);
    }

protected:
    /** 初始化Bitmap，按语义，数据范围为[0, n) */
    void init(int n)
    {
        this->m_len = (n + 7) / 8;  // 对n/8上取整
        this->m_cap = new char[this->m_len];
        std::memset(this->m_cap, 0, this->m_len);
    }

    /** 越界时，扩展容量 */
    void expand(int k)
    {
        if (k < this->m_len * 8) return;
        int old_len = this->m_len;
        char* old_cap = this->m_cap;
        this->init(2*k);
        std::memcpy(this->m_cap, old_cap, old_len);
        delete[] old_cap;
    }
};

/*! @} */

} /* dsa */ 

#endif /* ifndef DSAS_BITMAP_H */
