
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

/*!
 * @brief 三通道卷积
 *
 * 指RGB通道分别与卷积核进行卷积。
 *
 * @param img: RGB图像，尺寸与卷积核一样
 * @param kernel: 卷积核
 * @param flip: 是否进行卷积翻转
 * @param nore: 是否对卷积核进行归一化
 * @return 卷积结果
 * @retval None
 */
cv::Vec3b _conv2drgb(cv::InputArray img, cv::InputArray kernel, bool flip, bool norm)
{
    cv::Mat _img = img.getMat();
    cv::Mat _kernel = kernel.getMat();
    int ir = _kernel.rows - 1;
    int ic = _kernel.rows - 1;
    cv::Vec3d val(0.0, 0.0, 0.0);
    double sum = 0.0, kv;
    for (int r = 0; r < _img.rows; r ++)
    {
        for (int c = 0; c < _img.cols; c ++)
        {
            kv = (flip) ? _kernel.at<double>(ir - r, ic - c) : kv = _kernel.at<double>(r, c);
            val[0] += _img.at<cv::Vec3b>(r,c)[0] * kv;
            val[1] += _img.at<cv::Vec3b>(r,c)[1] * kv;
            val[2] += _img.at<cv::Vec3b>(r,c)[2] * kv;
            sum += kv;
        }
    }
    if (norm)
        return cv::Vec3b(cv::saturate_cast<uchar>(val[0] / sum),
                         cv::saturate_cast<uchar>(val[1] / sum),
                         cv::saturate_cast<uchar>(val[2] / sum));
    else
        return cv::Vec3b(cv::saturate_cast<uchar>(val[0]),
                         cv::saturate_cast<uchar>(val[1]),
                         cv::saturate_cast<uchar>(val[2]));
}

/*!
 * @brief 灰度图卷积
 *
 * 卷积核进行翻转。

 * @param img: RGB图像，尺寸与卷积核一样
 * @param kernel: 卷积核
 * @param flip: 是否进行卷积翻转
 * @param nore: 是否对卷积核进行归一化
 * @return 卷积结果
 * @retval None
 */
uchar _conv2dgray(cv::InputArray img, cv::InputArray kernel, bool flip, bool norm)
{
    cv::Mat _img = img.getMat();
    cv::Mat _kernel = kernel.getMat();
    int ir = _kernel.rows - 1;
    int ic = _kernel.rows - 1;
    double val = 0.0, sum = 0.0,  kv;
    for (int r = 0; r < _img.rows; r ++)
    {
        for (int c = 0; c < _img.cols; c ++)
        {
            kv = (flip) ? _kernel.at<double>(ir - r, ic - c) : kv = _kernel.at<double>(r, c);
            val += _img.at<uchar>(r, c) * kv;
            sum += kv;
        }
    }
    return cv::saturate_cast<uchar>((norm) ? (val / sum) : val);
}

/*!
 * @brief 卷积
 *
 */
void conv2d(cv::InputArray img, cv::OutputArray dsr, cv::InputArray kernel, bool flip = false, bool norm = false)
{
    cv::Mat _kernel = kernel.getMat();
    int s = _kernel.rows;
    int m = _kernel.rows/2;

    cv::Mat _img;
    cv::copyMakeBorder(img.getMat(), _img, m, m, m, m, cv::BORDER_REPLICATE);
    int w = _img.cols - _kernel.cols + 1;
    int h = _img.rows - _kernel.rows + 1;

    dsr.create(h, w, _img.type());
    cv::Mat _dsr = dsr.getMatRef();

    for (int r = 0; r < h; r++)
    {
        for (int c = 0; c < w; c++)
        {
            _dsr.at<cv::Vec3b>(r, c) = _conv2drgb(cv::Mat(_img, cv::Rect(c+1-m, r+1-m, s, s)),
                                                  _kernel, flip, norm);
        }
    }
}


int main(void)
{
    cv::Mat img = cv::imread("pic.jpg");
    cv::Mat img_out;
    cv::Mat img_conv;
    cv::Matx<double, 3, 3> ck;
    //ck <<  1,  2,  1,
    //       2,  4,  2,
    //       1,  2,  1;
    ck << -1, -1, -1,
          -1,  9, -1,
          -1, -1, -1;
    //ck << -1,  0,  1,
    //      -2,  0,  2,
    //      -1,  0,  1;
    //ck << -1,  0, -1,
    //       0,  4,  0,
    //      -1,  0, -1;

    cv::filter2D(img, img_out, img.depth(), ck);
    conv2d(img, img_conv, ck); //, false, true);

    cv::imshow("img", img);
    cv::imshow("filter2D", img_out);
    cv::imshow("conv2d", img_conv);

    while (1)
    {
        char key = cv::waitKey(10);
        if (key == 'q' || key == 27)
            break;
    }
    cv::destroyAllWindows();
    return 0;
}
