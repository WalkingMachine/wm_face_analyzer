#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <memory>
#include <chrono>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <PhotoDetector.h>

#include <opencv2/highgui/highgui.hpp>

#include "PlottingImageListener.h"

using namespace std;
using namespace affdex;
using namespace cv;

class AFaceListener : public FaceListener
{
    void onFaceFound(float timestamp, FaceId faceId)
    {
        //std::cout << "Face id " << faceId << " found at timestamp " << timestamp << std::endl;

    }
    void onFaceLost(float timestamp, FaceId faceId)
    {
        //std::cout << "Face id " << faceId << " lost at timestamp " << timestamp << std::endl;
    }
};

class AImageListener : public ImageListener
{
    void onImageCapture(Frame image)
    {
        if(image.getImage()->size().height>0)
            //imshow("camera", *image.getImage());
        waitKey(0);
    }
    void onImageResults(std::map<FaceId,Face> faces, Frame image)
    {
        //cout << faces[0].appearance.age;
        cout << "Age : ";
        switch ( int(faces[0].appearance.age) )
        {
            case 0:
                cout << "Unknown";
                break;
            case 1:
                cout << "Under 18";
                break;
            case 2:
                cout << "18-24";
                break;
            case 3:
                cout << "25-34";
                break;
            case 4:
                cout << "35-44";
                break;
            case 5:
                cout << "45-54";
                break;
            case 6:
                cout << "55-64";
                break;
            case 7:
                cout << "65+";
                break;
            default:
                // Code
                break;
        }
        cout << endl << "Gender : ";
        switch ( int(faces[0].appearance.gender) )
        {
            case 0:
                cout << "Unknown";
                break;
            case 1:
                cout << "Male";
                break;
            case 2:
                cout << "Female";
                break;
            default:
                // Code
                break;
        }
        cout << endl << "Ethnicité : ";

        switch ( int(faces[0].appearance.ethnicity) )
        {
            case 0:
                cout << "Unknown";
                break;
            case 1:
                cout << "Caucasian";
                break;
            case 2:
                cout << "Black african";
                break;
            case 3:
                cout << "South asian";
                break;
            case 4:
                cout << "East asian";
                break;
            case 5:
                cout << "Hispanic";
                break;
            default:
                // Code
                break;
        }
        cout << endl << "Glasses : ";
        switch ( int(faces[0].appearance.glasses) )
        {
            case 0:
                cout << "No";
                break;
            case 1:
                cout << "Yes";
                break;
            default:
                // Code
                break;
        }
        cout << endl << "Anger : " << faces[0].emotions.anger << "%";
        cout << endl << "Joy : " << faces[0].emotions.joy << "%" << endl;
    }
};

int main(int argc, char ** argsv)
{
    namedWindow( "camera", WINDOW_AUTOSIZE );

    PhotoDetector detector = PhotoDetector(2);
    std::string classifierPath="/home/jeffrey/affdex-sdk/data";
    detector.setClassifierPath(classifierPath);

    AImageListener * imagelistener_ptr = new AImageListener();
    detector.setImageListener(imagelistener_ptr);

    AFaceListener * facelistener_ptr  = new AFaceListener();
    detector.setFaceListener(facelistener_ptr);

    detector.setDetectAllExpressions(true);
    detector.setDetectAllEmotions(true);
    detector.setDetectAllEmojis(true);
    detector.setDetectAllAppearances(true);

    detector.start();
    VideoCapture camera(0);
    Mat cameraFrame;

    if (!camera.isOpened()) { //check if video device has been initialised
        cout << "cannot open camera";
        return 1;
    }

    //unconditional loop
    //while (true)
    while(!cameraFrame.data)
    {
        camera >> cameraFrame;
        if(cameraFrame.data)
        {
            //imshow("camera", cameraFrame);

        }
    }
    while (true)
    {
        camera >> cameraFrame;

        Frame photo(cameraFrame.size().width, cameraFrame.size().height, cameraFrame.data, Frame::COLOR_FORMAT::BGR);

        detector.process(photo);

        if (waitKey(30) >= 0)
            break;

        cout << endl << endl;
    }

    cerr << "Picture taken"<<endl;


}

