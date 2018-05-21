#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage %s < Image(s) >\n", argv[0]);
        return -1;
    }

    int index = 1;

    while (index < argc) {
        Mat image;
        image = imread(argv[index++], IMREAD_COLOR);

        if (!image.data) {
            printf("No image data\n");
            continue;
        }

        resize(image, image, Size(640, 480));

        Mat imageBlur;
        medianBlur(image, imageBlur, 13);

        Mat imageHsv;

        cvtColor(imageBlur, imageHsv, COLOR_BGR2HSV);

        std::vector<Mat> channels(3);

        split(imageHsv, channels);

        Mat satDivVal;

        divide(channels[1], channels[2], satDivVal, 40.0);

        Mat water;
        threshold(satDivVal, water, 64, 255, THRESH_BINARY_INV);

        Mat displayImage(image.size().height, image.size().width+image.size().width, CV_8UC3);

        cvtColor(water, water, COLOR_GRAY2BGR);

        hconcat(image, water, displayImage);

        imshow("Result", displayImage);

        if ( (char) 27 == (char) waitKey(0)) {
            return 0;
        }
    }

    return 0;
}
