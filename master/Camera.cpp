#include<opencv2/opencv.hpp>
#include <rasoicam_cv.h>
#include<iostream.h>
#include<chrono>
#include<ctime>

    

using namespace std;
using namespace cv;
using namespace raspicam;
RaspiCam_Cv Camera;



Mat frame,Matrix,framePerspective;
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
}

void Capture(){
    Camera.grab();
    Camera.retrieve(frame);
    cvtColor(frame,frame,COLOR_BGR2RGB);
    
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
        namedWindow("RGB",WINDOW_KEEPRATIO);
        moveWindow("RGB",50,100);
        resizeWindow("RGB",680,480);
        imshow("RGB",frame);
        
        namedWindow("framePerspective",WINDOW_KEEPRATIO);
        moveWindow("framePerspective",700,100);
        resizeWindow("framePerspective",680,400);
        imshow("franePerspective",framePerspective);
       
        auto end=std::chrono::system_clock::now();
        std::chrono::duration::<double> elapsed_seconds=end-start;
        float t=elapsed_seconds.count();
        int FPS=1/t;
        cout<<"FPS"<<FPS<<endl;
        waitKey();
    }
        return 0;


}