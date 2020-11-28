#include<opencv2/opencv.hpp>
#include <rasoicam_cv.h>
#include<iostream.h>
#include<chrono>
#include<ctime>
#include<vector>
    

using namespace std;
using namespace cv;
using namespace raspicam;
RaspiCam_Cv Camera;
vector<int> HistogramLane;
int LeftLanePos,RightLanePos ,laneCenter,frameCenter,result;
stringstream ss;



Mat frame,Matrix,framePerspective,frameGray,frameThresh,frameEdge,frameFinal;
Mat ROILane,frameFinalDuplicate;
Point2f Source[]={
    Point2f(50,200),Point2f(280,200),Point2f(0,240),Point2f(360,240)
};

Point2f Destination[]={
    Point2f(60,0),Point2f(300,0),Point2f(60,240),Point2f(300,240)
};


void Setup(int argc,int **argv,RaspCam_Cv &Camera)
{
    Camera.set(CAP_PROP_FRAME_WIDTH,('-w',argc,argv,360));
    Camera.set(CAP_PROP_FRAME_HEIGHT,('-h',argc,argv,240));
    Camera.set(CAP_PROP_FRAME_BRIGHTNESS,('-br',argc,argv,50));
    Camera.set(CAP_PROP_FRAME_CONTRAST,('-co',argc,argv,50));
    Camera.set(CAP_PROP_FRAME_SATURATION,('-sa',argc,argv,50));
    Camera.set(CAP_PROP_FRAME_SATURATION,('-sa',argc,argv,50));
    Camera.set(CAP_PROP_GAIN,('-g',argc,argv,50))
    Camera.set(CAP_PROP_FPS,('-fps',argc,argv,0))







}

void Perspective(){
    line(frame,Source[0],Source[1],Scaler(0,255,0),2);
    line(frame,Source[1],Source[3],Scaler(0,255,0),2);
    line(frame,Source[3],Source[2],Scaler(0,255,0),2);
    line(frame,Source[2],Source[0],Scaler(0,255,0),2);



    //line(frame,Destination[0],Destination[1],Scaler(0,0,255),2);
    //line(frame,Destination[1],Destination[3],Scaler(0,0,255),2);
    //line(frame,Destination[3],Destination[2],Scaler(0,0,255),2);
    //line(frame,Destination[2],Destination[0],Scaler(0,0,255),2);

    Matrix=getPerspectiveTransformation(Source,Destination);
    warpPerspective(frame,framePerspective,Matrix,Size(360,240));
}


void Threshold(){
    
    cvtColor(framePerspective,frameGray,COLOR_RGB2GRAY);
    inRange(frameGray,245,255,frameThresh);
    Canny(frameGray,frameEdge,100,500,3,true);
    add(frameThresh,frameGray,framefinal);
    cvtColor(frameFinal,frameFinal,COLOR_GRAY2RGB);
    cvtColor(frameFinal,frameFinalDuplicate,COLOR_RGB2BRG);

}

void Capture(){
    Camera.grab();
    Camera.retrieve(frame);
    cvtColor(frame,frame,COLOR_BGR2RGB);
    cvtColor(frameFinal,frameFinal,COLOR_GARY2RGB);
}

void Histogram(){
HistogramLane.resize(400);
HistogramLane.clear();
for(i=0;i<frame.size().width;i++){
    ROILane=frameFinalDuplicate(Rect(i,140,1,100));
    devide(255,ROILane,ROILane);
    HistogramLane.push_back((int)(sum(ROILane)[0]));

}


void LaneFinder(){
    vector<int>::iterator LeftPtr;
    LeftPtr=max_element(HistogramLane.begin(),HistogramLane.begin()+150);
    LeftLanePos=distance(HistogramLane.begin(),LeftPtr);


    vector<int>::iterator RightPtr;
    RightPtr=max_element(HistogramLane.begin()+250,HistogramLane.end());
    RightLanePos=distance(HistogramLane.begin(),RightPtr);
    line(frameFinal,Point2f(LeftLanePos,0),Point2f(LeftLanePos,240),Scaler(0,255,0),2);
    line(frameFinal,Point2f(RightLanePos,0),Point2f(RightLanePos,240),Scaler(0,255,0),2);

}

void LaneCenter(){
    laneCenter=(RightLanePos-LeftLanePos)/2+LeftLanePos;
    frameCenter=200;
    line(frameFinal,Point2f(laneCenter,0),Point2f(laneCenter,240),Scaler(0,255,0),2);
    line(frameFinal,Point2f(frameCenter,0),Point2f(frameCenter,240),Scaler(255,0,0),2);
    result=laneCenter-frameCenter;
}


int main()
{
    Setup(argc,argv,Camera);
    cout<<" connecting Camera"<<endl;
    if(!Camera.open()){
        cout<<"Failed to connect"<<endl;
        return -1;

    }
    cout<<"Camera id"<<Camera.getId()<<endl;
    while(1){

        auto start=std::chrono::system_clock::now();
        Capture();
        Perspective();
        Threshold();
        Histogram();
        LaneFinder();
        LaneCenter();

        ss.string(" ")
        ss.clear();
        ss<<"Result:"<<result<<endl;
        putText(frame,ss.str(),Point2f(1,50),0.1,Scaler(0,0,255));

        namedWindow("RGB",WINDOW_KEEPRATIO);
        moveWindow("RGB",50,100);
        resizeWindow("RGB",680,480);
        imshow("RGB",frame);
        
        namedWindow("framePerspective",WINDOW_KEEPRATIO);
        moveWindow("framePerspective",700,100);
        resizeWindow("framePerspective",680,480);
        imshow("franePerspective",framePerspective);

        namedWindow("GRAY",WINDOW_KEEPRATIO);
        moveWindow("GRAY",700,100);
        resizeWindow("GRAY",680,400);
        imshow("GRAY",frameGray);


        namedWindow("Edge",WINDOW_KEEPRATIO);
        moveWindow("Edge",700,100);
        resizeWindow("Edge",680,400);
        imshow("GRAY",frameEdge);
       

       namedWindow("Final",WINDOW_KEEPRATIO);
        moveWindow("Final",700,100);
        resizeWindow("Final",680,400);
        imshow("GRAY",frameFinal);
       
       
       
        auto end=std::chrono::system_clock::now();
        std::chrono::duration::<double> elapsed_seconds=end-start;
        float t=elapsed_seconds.count();
        int FPS=1/t;
        cout<<"FPS"<<FPS<<endl;
        waitKey();
    }
        return 0;


}
