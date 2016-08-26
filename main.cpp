#include <iostream>
#include <opencv2/opencv.hpp>
#include "crowdsight.h"

using namespace std;
using namespace cv;

int main() {
    
    CrowdSight* crowdsight;

    //string license = "7a8785a125b248439d5a1a02f8dba034";
    string datadir = "/usr/local/crowdsight/data/";

    cout << "Init crowdsight..." << endl;

    crowdsight = new CrowdSight(datadir, REDISTRIBUTION);

    cout << "Authenticate..." << endl;
    if (!crowdsight->authenticate(license)) {
        delete crowdsight;
        crowdsight = NULL;
    }

    namedWindow("Test", CV_WINDOW_AUTOSIZE);

    VideoCapture videoCapture;

    cout << "OPen camera..." << endl;
    videoCapture.open(0);

    Mat frame;

    for(;;) {
        videoCapture >> frame;

        if (frame.empty()) {
            videoCapture.release();
            break;
        }

        crowdsight->process(frame);

        std::vector<Person> people;
        crowdsight->getCurrentPeople(people);

        for(int i = 0; i < people.size(); i++) {
            Rect face = people[i].getFaceRect();
            cout << "ID#: " << people[i].getID() << endl;;
            cout << "Gender: " << ((people[i].getGender()) < 0 ? "male":"female") << endl;
            cout << "Age: " << people[i].getAge() << endl;
        }

        cout << "PeopleCount: " << crowdsight->getPeopleCount() << endl;

    }
}
