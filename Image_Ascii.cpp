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

    int gscale_len = gscale.length() - 1;

    Mat image;
    Mat resized_image;

    image = imread("C:\\Users\\Dell\\Desktop\\pfp.png");
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    // Display the original and binned images
    //imshow("Original Image", image);

    int col = image.cols;
    int row = image.rows;    

    if ( col > 100 && col < 600) {
        resize(image, resized_image, Size(), 0.2, 0.2, INTER_LINEAR);
        col = resized_image.cols;
        row = resized_image.rows;
    }
    else if (col >= 500 && col <= 2000) {
        resize(image, resized_image, Size(), 0.1, 0.1, INTER_LINEAR);
        col = resized_image.cols;
        row = resized_image.rows;
    } 
    else if (col > 2000) {
        cout << "File too large to convert to ASCII Art!" << endl;
        return -1;
    }   

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
            Vec3b px = resized_image.at<Vec3b>(i, j);
            uchar b = px[0];
            uchar g = px[1];
            uchar r = px[2];
            int luminence = getLuminence(b, g, r);
            char ascii_char = gscale[gscale_len - int((luminence * gscale_len) / 255)];
            file << ascii_char;
            file << " ";
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