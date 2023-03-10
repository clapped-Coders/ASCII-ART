#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int getLuminence(uchar b, uchar g, uchar r) {
    return int(0.2126 * r + 0.7152 * g + 0.0722 * b);
}

int imageAsciiArt()
{
    Mat canvas;
    canvas = Mat::zeros(800, 1000, CV_8UC3);
    imshow("canvas", canvas);
    waitKey(0);
    return 0;
}

int textAsciiArt() {
    string gscale = "@%#*+=-:. ";
    //string gscale = "$@B%8&amp;WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~i!lI;:,^`. ";

    Mat image;

    image = imread("C:\\Users\\Dell\\Desktop\\pfp.png");
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    // Display the original and binned images
    //imshow("Original Image", image);

    const int col = image.cols;
    const int row = image.rows;

    int** pxArry;
    //Allocating the row space in heap dynamically
    pxArry = new int* [row];
    //Allocating the column space in heap dynamically
    for (int i = 0; i < row; i++) {
        pxArry[i] = new int[col];
    }

    ofstream file("asciii.txt");
    if (!file) {
        printf("Error creating the file \n");
        return -1;
    }

    for (int i = 0; i < row; i++) 
    {
        for (int j = 0; j < col; j++) 
        {
            Vec3b px = image.at<Vec3b>(i, j);
            uchar b = px[0];
            uchar g = px[1];
            uchar r = px[2];
            int luminence = getLuminence(b, g, r);
            char ascii_char = gscale[9 - int((luminence * 9) / 255)];
            file << ascii_char;
        }
        file << endl;
    }

    for (int i = 0; i < row; i++)
    {
        delete[] pxArry[i];
    }

    delete[] pxArry;
    file.close();

    return 0;
}