#include "opencv2/opencv.hpp"
#include <fstream>
#include "raylib.h"


using namespace cv;
using namespace std;


// #include <iostream>
// // #include "Image_Ascii.hpp"

// using namespace std;





int getLuminence(uchar b, uchar g, uchar r) {
    return int(0.2126 * r + 0.7152 * g + 0.0722 * b);
}

int imageAsciiArt(void)
{
    ifstream infile("asciii.txt");


    vector<string> lines;
    string line;


    while (getline(infile, line)) {
        lines.push_back(line);
    }

    infile.close();

    const int screenWidth = 1500;
    const int screenHeight = 1500;
    float y = 10;
    Font font = LoadFont("/Users/macbook/my_Files/Code/ASCII-ART/ASCII-ART/AlmaMono-Regular.ttf");

    InitWindow(screenWidth, screenHeight, "ASCII-ART");

    SetTargetFPS(60);               

    while (!WindowShouldClose()) 
    {
        BeginDrawing();

            ClearBackground(BLACK);
            
            for (string line : lines) {

                char* text = line.c_str();
                DrawTextEx(font, *text, Vector2{0, y}, 20, 0, WHITE);
                y += 10;
            }

            

        EndDrawing();
    }

    CloseWindow();   

    // Mat canvas = Mat::zeros(600, 800, CV_8UC3);
    // int y = 10;

    // for (string line : lines) {
    //     putText(canvas, line, Point(10, y), FONT_HERSHEY_PLAIN, 0.5, Scalar(255, 255, 255), 1);
    //     y += 10;
    // }

    // imshow("canvas", canvas);
    return 0;
}

int textAsciiArt(Mat webcam_image) {
    const string gscale = "@%#*+=-:.   ";

    // string gscale = "$@B%8&amp;WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~i!lI;:,^`. ";

    unsigned long int gscale_len = gscale.length() - 1;

    Mat image = webcam_image;
    Mat resized_image;

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

int videoCapture() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Unable to open the webcam!" << endl;
        return -1;

    }
    Mat frame;
    while (true) {
        cap  >> frame;
        if (frame.empty()) {
            cerr << "Unable to capture frame!" << endl;
            break;
        }
        imshow("Webcam", frame);
        if (waitKey(1) == 27) {
            break;
        }
        textAsciiArt(frame);
        imageAsciiArt();

    }
    cap.release();
    destroyAllWindows();
    return 0;
}




// int main()
// {
//     videoCapture();
    
//     return 0;
// }
