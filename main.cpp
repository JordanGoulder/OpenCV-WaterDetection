#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Usage %s <Image Path>\n", argv[0]);
        return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_COLOR);

    resize(image, image, Size(640, 480));

    medianBlur(image, image, 13);
    
    if (!image.data) {
        printf("No image data\n");
        return -2;
    }

    Mat imageHsv;

    cvtColor(image, imageHsv, COLOR_BGR2HSV);

    std::vector<Mat> channels(3);

    split(imageHsv, channels);

    Mat satDivVal;

    divide(channels[1], channels[2], satDivVal, 40.0);

    Mat water;
    threshold(satDivVal, water, 64, 255, THRESH_BINARY_INV);

    imshow("Original", image);
    imshow("Water", water);

    waitKey(0);

    return 0;
}
