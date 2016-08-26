#include <iostream>
#include <opencv2/opencv.hpp>
#include "crowdsight.h"

using namespace std;
using namespace cv;

int main() {
    
    CrowdSight* crowdsight;

    string license = "f187f8d8b27f424fbab9064c18a7e0e4";
    string datadir = "/usr/local/crowdsight/data/";

    crowdsight = new CrowdSight(datadir, DEVELOPER);

    if (!crowdsight->authenticate(license)) {
        delete crowdsight;
        crowdsight = NULL;
    }

    namedWindow("Test", CV_WINDOW_AUTOSIZE);

    VideoCapture videoCapture;

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
