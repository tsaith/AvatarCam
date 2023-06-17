#include "CvPlotLibrary.h"

TArray<TArray<int>> CvPlotLibrary::GetPoseConnect() {

    TArray<TArray<int>> connect{
        {0, 1}, {1, 2}, {2, 3}, {0, 4}, {4, 5},
        {5, 6}, {0, 7}, {7, 8}, {8, 9}, {9, 10},
        {8, 11}, {11, 12}, {12, 13}, {8, 14}, {14, 15}, {15, 16}
    };

    return connect;

}

TArray<TArray<int>> CvPlotLibrary::GetMpPoseConnect() {

    TArray<TArray<int>> connect{
        {0, 1}, {1, 2}, {2, 3}, {3, 7},
        {0, 4}, {4, 5}, {5, 6}, {6, 8},
        {9, 10},
        {11, 23}, {23, 24}, {24, 12}, {12, 11},
        {11, 13}, {13, 15}, {15, 21}, {15, 19}, {15, 17},
        {12, 14}, {14, 16}, {16, 22}, {16, 20}, {16, 18},
        {23, 25}, {25, 27}, {27, 29}, {27, 31},
        {24, 26}, {26, 28}, {28, 30}, {28, 32}
    };

    return connect;

}

void CvPlotLibrary::PlotPose2d(cv::Mat& Image, TArray<FVector> &Pose) {

    // Plot connection lines
    int indexStart, indexEnd;
    float x1, y1, x2, y2;
    cv::Point p1, p2;
    cv::Scalar lineColor = cv::Scalar(255, 0, 0);
    int lineThickness = 3;
    for (auto& connect : GetPoseConnect()) {

        indexStart = connect[0];
        indexEnd = connect[1];

        x1 = Pose[indexStart][0];
        y1 = Pose[indexStart][1];

        x2 = Pose[indexEnd][0];
        y2 = Pose[indexEnd][1];

        p1 = cv::Point(x1, y1);
        p2 = cv::Point(x2, y2);

        line(Image, p1, p2, lineColor, lineThickness, cv::LINE_8);
    }

    // Plot keypoints
    cv::Point point;
    for (auto& bone : Pose) {

        point.x = bone[0];
        point.y = bone[1];

        cv::circle(Image, point, 3, cv::Scalar(0, 255, 255), -1);

    }

}


void CvPlotLibrary::PlotMpPose2d(cv::Mat& Image, TArray<FVector> &Pose) {

    // Plot connection lines
    int indexStart, indexEnd;
    float x1, y1, x2, y2;
    cv::Point p1, p2;
    cv::Scalar lineColor = cv::Scalar(255, 0, 0);
    int lineThickness = 3;
    for (auto& connect : GetMpPoseConnect()) {

        indexStart = connect[0];
        indexEnd = connect[1];

        x1 = Pose[indexStart][0];
        y1 = Pose[indexStart][1];

        x2 = Pose[indexEnd][0];
        y2 = Pose[indexEnd][1];

        p1 = cv::Point(x1, y1);
        p2 = cv::Point(x2, y2);

        line(Image, p1, p2, lineColor, lineThickness, cv::LINE_8);
    }

    // Plot keypoints
    cv::Point point;
    for (auto& bone : Pose) {

        point.x = bone[0];
        point.y = bone[1];

        cv::circle(Image, point, 3, cv::Scalar(0, 255, 255), -1);

    }

}

