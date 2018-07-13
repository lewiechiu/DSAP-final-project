#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<string>
#include "Bags&List.hpp"
using namespace std;

float inCM(float length)
{
    return 1600 * length / 33.867;
}
float inPT(float length)
{
    return inCM(length * 0.03527);
}
float font_resize(int oriSize)
{
    return 1.7 * static_cast<float>(oriSize);
}

/*------------------------------CHAO------------------------------*/
float toPx(float cm);

int TotalBoxes;
int BoxIndex;
bool DisplayBox= false;
sf::Font font;
OurTime NOW;
int BoxMes_Button_index;
const float Remove_Button_XLen = toPx(1.88);
const float Remove_Button_YLen = toPx(0.5);
float Remove_Button_X;
float Remove_Button_Y;
const float Check_Button_XLen = toPx(1.88);
const float Check_Button_YLen = toPx(0.5);
float Check_Button_X;
float Check_Button_Y;
float X_Metrix[7];
float X_Start;
float Y_Start;
float Y_Length;
const float X_Length = inCM(3.24);
const float Y_Origin = inCM(3.77);
const float Y_Width_perMin = inCM(3.15)/360;
int OutTimeHM2Int(OurTime& T);

OurTime CountDate(OurTime& TIME, int Gap);
int round(int MinuGap);
void DrawCalenderBox(sf::RenderWindow& wn, sf::RectangleShape* ALL_RECTAN, const MissionBag& MBag, const FixedEventBag& FEBag, int move=0);
//move: -1 ->past week
//move: +1 ->next week
int MouseOnBoxes(sf::RenderWindow& wn, sf::RectangleShape* RS, int total);
int MouseOnTurnPage(sf::RenderWindow& wn, sf::CircleShape& leftButton, sf::CircleShape& rightButton);
void DrawBoxMes(sf::RenderWindow& wn, sf::RectangleShape* RS,sf::RectangleShape* BoxMes_Button, const MissionBag& MBag, const FixedEventBag& FEBag, int index);
/*------------------------------CHAO------------------------------*/

int main()
{
    for(int i=0; i<7; i++)
        X_Metrix[i] = inCM(7.36 + 3.24 * i);
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "My Schedule Assistant", sf::Style::Titlebar | sf::Style::Close);

    //font
    font.loadFromFile("Calibri.ttf");
    sf::Font calibri_normal;
    calibri_normal.loadFromFile("Calibri.ttf");
    sf::Font calibri_italic;
    calibri_italic.loadFromFile("calibrii.ttf");
    sf::Font calibri_bold;
    calibri_bold.loadFromFile("calibrib.ttf");

    //Schedule button
    sf::RectangleShape scheduleButton(sf::Vector2f(inCM(1.5), inCM(9.5)));
    scheduleButton.setFillColor(sf::Color(86, 175, 191));
    scheduleButton.setPosition(0, 0);
    sf::Text scheduleText;
    scheduleText.setFont(calibri_normal);
    scheduleText.setPosition(inCM(0.6), inCM(1.5));
    scheduleText.setString("S\nC\nH\nE\nD\nU\nL\nE");
    scheduleText.setCharacterSize(font_resize(18));
    scheduleText.setFillColor(sf::Color(255, 255, 255));
    //Dashboard button
    sf::RectangleShape dashboardButton(sf::Vector2f(inCM(1.5), inCM(9.5)));
    dashboardButton.setFillColor(sf::Color(11, 83, 149));
    dashboardButton.setPosition(inCM(0), inCM(9.53));
    sf::Text dashboardText;
    dashboardText.setFont(calibri_normal);
    dashboardText.setPosition(inCM(0.6), inCM(1.5 + 9.5));
    dashboardText.setString("D\nA\nS\nH\nB\nO\nA\nR\nD");
    dashboardText.setCharacterSize(font_resize(18));
    scheduleText.setFillColor(sf::Color(255, 255, 255));
    //Add button
    sf::CircleShape addButton(inCM(0.75), 100);
    addButton.setPosition(0, inCM(9.5 - 0.75));
    addButton.setFillColor(sf::Color(255, 255, 255));
    sf::RectangleShape h_plus(sf::Vector2f(inCM(0.6), inCM(0.1)));
    h_plus.setFillColor(sf::Color(62, 149, 164));
    h_plus.setPosition(inCM(1.5 / 2 - 0.6 / 2), inCM(9.5 - 0.1 / 2));
    sf::RectangleShape v_plus(sf::Vector2f(inCM(0.1), inCM(0.6)));
    v_plus.setFillColor(sf::Color(62, 149, 164));
    v_plus.setPosition(inCM(1.5 / 2 - 0.1 / 2), inCM(9.5 - 0.6 / 2));

    
    //Left page button
    sf::CircleShape leftButton(inCM(0.5 / 2), 3);
    leftButton.setFillColor(sf::Color(86, 175, 191));
    leftButton.setPosition(inCM(2.72), inCM(9.28));
    leftButton.rotate(30);
    //Right page button
    sf::CircleShape rightButton(inCM(0.5 / 2), 3);
    rightButton.setFillColor(sf::Color(86, 175, 191));
    rightButton.setPosition(inCM(32.13), inCM(9.28));
    rightButton.rotate(-30);


    //horizontal lines
    sf::RectangleShape h_linePtr[5];
    for(int i = 0; i < 5; i++)
    {
        h_linePtr[i].setSize(sf::Vector2f(inCM(23), inPT(0.6)));
        h_linePtr[i].setFillColor(sf::Color(166, 166, 166));
        h_linePtr[i].setPosition(inCM(7.05), inCM(3.77 + 3.51 * i));
    }
    
    //Time
    sf::Text time[5];
    for(int i = 0; i < 5; i++)
    {
        time[i].setFont(font);
        time[i].setCharacterSize(font_resize(14));
        time[i].setFillColor(sf::Color(166, 166, 166));
        time[i].setPosition(inCM(5.42), inCM(3.45 + 3.5 * i));
        if(i < 2)
            time[i].setString(std::string("0" + std::to_string(0 + 6 * i) + ":00"));
        else
            time[i].setString(std::string(std::to_string(0 + 6 * i) + ":00"));
    }
    
    /*------------------------------CHAO------------------------------*/
    MissionBag M_Bag;
    FixedEventBag FE_Bag;
    M_Bag.LoadFile("Mission.txt");
    FE_Bag.LoadFile("FE.txt");
    
    //Remove, Check, Close of Mes Box
    sf::RectangleShape BoxMes_Button[3];
    //Check if there is aother box opened
    bool NoOtherMesBox=true;
    int move_page = 0;

    while (window.isOpen())
    {
        //Drawing Order
        //Buttons -> horizontal line -> time text -> Boxes&Week&DateTitle -> Boxes Detailed Information

//        window.clear();
//
//        //Turn Page
//        window.draw(leftButton);
//        window.draw(rightButton);
//
//        //Box Position information and amount
//        TotalBoxes = M_Bag.Bag.getSize()+FE_Bag.Bag.getSize();
//        sf::RectangleShape RS[M_Bag.Bag.getSize()+FE_Bag.Bag.getSize()];
//        BoxMes_Button_index=-1;

//
//        for(int i = 0; i < 5; i++) //horizontal line
//            window.draw(h_linePtr[i]);
//        for(int i = 0; i < 5; i++) //time text 06:00...
//            window.draw(time[i]);
//
//        //Draw all events boxes
//        DrawCalenderBox(window,RS, M_Bag, FE_Bag, move_page);

        sf::Event event;
        while (window.pollEvent(event))
        {
//            //close window
//            if(event.type == sf::Event::Closed)
//                window.close();
//            //check if the user click the box for detail
//            if(MouseOnBoxes(window, RS, TotalBoxes)!=-1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&NoOtherMesBox)
//            {
//                BoxIndex = MouseOnBoxes(window, RS, TotalBoxes);
//                while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//                    ;
//                DisplayBox = true;
//                cout<<"you click it!\n";
//            }
//
//            //check if the user click the buttons in the box
//            if(MouseOnBoxes(window, BoxMes_Button, 3)!=-1 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
//            {
//                BoxMes_Button_index = MouseOnBoxes(window, BoxMes_Button, 3);
//                while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//                    ;
//                cout<<BoxMes_Button_index<<"\n";
//            }
//
//            //check if the user turn the page
//            if(MouseOnTurnPage(window, leftButton, rightButton)!=0 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
//            {
//                move_page += MouseOnTurnPage(window, leftButton, rightButton);
//                while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//                    ;
//            }
//
        }
        
//        if(BoxMes_Button_index==0)//Remove event
//        {
//            if(BoxIndex>=M_Bag.Bag.getSize())//FE
//            {
//                FE_Bag.Bag.remove(FE_Bag.Bag[BoxIndex-M_Bag.Bag.getSize()]);
//            }
//            else//Mission
//            {
//                M_Bag.Bag.remove(M_Bag.Bag[BoxIndex]);
//            }
//            DisplayBox = false;
//            NoOtherMesBox =true;
//            
//        }
//        if(BoxMes_Button_index==1)//Done Mission
//        {
//            if(BoxIndex<M_Bag.Bag.getSize())//Mission
//            {
//                M_Bag.Bag[BoxIndex]->setIsDone(true);
//            }
//            NoOtherMesBox =true;
//            DisplayBox = false;
//        }
//        else if (BoxMes_Button_index==2)//Close Box information
//        {
//            NoOtherMesBox =true;
//            DisplayBox =false;
//        }
//        
//        if(DisplayBox)//Display Box information
//        {
//            NoOtherMesBox =false;
//            DrawBoxMes(window, RS, BoxMes_Button, M_Bag, FE_Bag, BoxIndex);
//        }
        /*------------------------------CHAO------------------------------*/

        window.draw(scheduleButton);
        window.draw(scheduleText);
        window.draw(dashboardButton);
        window.draw(dashboardText);
        window.display();
    }
    return 0;
}

/*------------------------------CHAO------------------------------*/

float toPx(float cm)
{
    //return cm*(1600/28.6);
    return cm*(991/20.81);
}

int round(int MinuGap)
{
    int week  =MinuGap/1440;
    if(MinuGap%1440 !=0)
        week++;
    return week-1;
}

int OutTimeHM2Int(OurTime& T)
{
    int SUM=0;
    SUM+=T.getMinute()+T.getHour()*60;
    return SUM;
}

void DrawCalenderBox(sf::RenderWindow& wn, sf::RectangleShape*ALL_RECTAN, const MissionBag& MBag, const FixedEventBag& FEBag, int move)
{
    OurTime Default("201807080000");
    NOW.Current();

    int Now_MinuGap = NOW - Default;
    int Now_DayGap = round(Now_MinuGap);
    
    int Now_Week_Day = (Now_DayGap)%7;
    OurTime Start = CountDate(NOW, Now_Week_Day);//start date of this week
    OurTime End =  CountDate(NOW, Now_Week_Day-6);//end date of this week
    End.setHour(23);
    End.setMinute(59);
    if(move<0)
    {
        int count = abs(move);
        while(count>0)
        {
            Start = CountDate(Start, 7);
            End = CountDate(End, 7);
            count--;
        }
    }
    else if(move>0)
    {
        int count = abs(move);
        while(count>0)
        {
            Start = CountDate(Start, -7);
            End = CountDate(End, -7);
            count--;
        }
    }


    for(int i=0; i<MBag.Bag.getSize(); i++)
    {
        OurTime MStartTime;
        OurTime MEndTime;

        string MName;

        MStartTime  =  MBag.Bag[i]->getStartTime();
        MEndTime =  MBag.Bag[i]->GetendTime();
        MName = MBag.Bag[i]->GetName();

        //Draw Missions
        if(Start<=MStartTime && End>=MStartTime && !MBag.Bag[i]->GetMisDone())
        {
            int M_MinuGap = MStartTime - Default;
            int M_DayGap = round(M_MinuGap);
            int M_Week_Day = (M_DayGap)%7;
            
            X_Start = X_Metrix[M_Week_Day];
            Y_Start = Y_Origin+OutTimeHM2Int(MStartTime)*Y_Width_perMin;
            Y_Length =Y_Width_perMin*(MEndTime-MStartTime);
            
            //Draw Boxes
            
            ALL_RECTAN[i].setFillColor(sf::Color(90, 175, 190, 250.0));
            ALL_RECTAN[i].setOutlineColor(sf::Color(0, 0, 0, 250.0));
            ALL_RECTAN[i].setOutlineThickness(3.f);
        
            
            ALL_RECTAN[i].setPosition(X_Start, Y_Start);
            ALL_RECTAN[i].setSize(sf::Vector2f(X_Length, Y_Length));
            wn.draw(ALL_RECTAN[i]);
            
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(font_resize(14));
            text.setFillColor(sf::Color(255, 255, 255));
            text.setString(MName);
            float offset_x = text.getLocalBounds().width;
            float offset_y = text.getLocalBounds().height;
            
            
            text.setPosition(X_Start+(X_Length-offset_x)/2, Y_Start+(Y_Length-offset_y-10)/2);
            if((MEndTime-MStartTime)>=60)
                wn.draw(text);
        }

    }
    for(int i=0; i<FEBag.Bag.getSize(); i++)
    {

        OurTime FEStartTime;
        OurTime FEEndTime;
        string FEName;
        
        FEStartTime  =  FEBag.Bag[i]->getStartTime();
        FEEndTime =  FEBag.Bag[i]->GetendTime();
        FEName = FEBag.Bag[i]->GetName();

        //Draw FixedEvent
        if(Start<=FEStartTime && End>=FEStartTime)
        {
            
            int FE_MinuGap = FEStartTime - Default;
            int FE_DayGap = round(FE_MinuGap);
            int FE_Week_Day = (FE_DayGap)%7;
            
            X_Start = X_Metrix[FE_Week_Day];
            Y_Start = Y_Origin+OutTimeHM2Int(FEStartTime)*Y_Width_perMin;
            Y_Length =Y_Width_perMin*(FEEndTime-FEStartTime);
            
            //Draw Boxes
            ALL_RECTAN[i+MBag.Bag.getSize()].setFillColor(sf::Color(162, 219, 214));
            ALL_RECTAN[i+MBag.Bag.getSize()].setOutlineColor(sf::Color(0, 0, 0, 250.0));
            ALL_RECTAN[i+MBag.Bag.getSize()].setOutlineThickness(3.f);
            
            ALL_RECTAN[i+MBag.Bag.getSize()].setPosition(X_Start, Y_Start);
            ALL_RECTAN[i+MBag.Bag.getSize()].setSize(sf::Vector2f(X_Length, Y_Length));
            wn.draw(ALL_RECTAN[i+MBag.Bag.getSize()]);
            
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(font_resize(14));
            text.setFillColor(sf::Color(66, 149, 163, 250.0));
            text.setString(FEName);
            float offset_x = text.getLocalBounds().width;
            float offset_y = text.getLocalBounds().height;
            
            
            text.setPosition(X_Start+(X_Length-offset_x)/2, Y_Start+(Y_Length-offset_y-10)/2);
            if((FEEndTime-FEStartTime) >=60)
                wn.draw(text);
        }
    }
        //Date
        sf::Text date[7];
        OurTime Itorator = Start;
        for(int i = 0; i < 7; i++)
        {
            string Day = to_string(Itorator.getDay());
            if(Day.length()==1)
                Day.insert(0,"0");
            Day+=" ";
            date[i].setFont(font);
            date[i].setCharacterSize(font_resize(18));
            date[i].setFillColor(sf::Color(255, 255, 255));
            date[i].setPosition(inCM(8.05 + 3.24 * i), inCM(2.76));
            switch(i)
            {
                case 0:
                    date[i].setString(Day +std::string("Sun."));
                    break;
                case 1:
                    date[i].setString(Day + std::string("Mon."));
                    break;
                case 2:
                    date[i].setString(Day + std::string("Tues."));
                    break;
                case 3:
                    date[i].setString(Day + std::string("Wed."));
                    break;
                case 4:
                    date[i].setString(Day + std::string("Thu."));
                    break;
                case 5:
                    date[i].setString(Day + std::string("Fri."));
                    break;
                case 6:
                    date[i].setString(Day + std::string("Sat."));
                    break;
            }
            Itorator = CountDate(Itorator, -1);
        }

        for(int i = 0; i < 7; i++) //date text
            wn.draw(date[i]);
        
        //Title(2018 January)
        string Year = to_string(Start.getYear());
        int Month =  Start.getMonth();
        sf::Text title;
        title.setFont(font);
    string Title_S = Year.substr(0,1)+"    "+Year.substr(1,1)+"    "+Year.substr(2,1)+"    "+Year.substr(3,1)+"        ";
        if(Month==1)
            Title_S+="J    A    N    U    A    R    Y";
        else if(Month==2)
            Title_S+="F    A    B    U    A    R    Y";
        else if(Month==3)
            Title_S+="M    A    R    C    H";
        else if(Month==4)
            Title_S+="A    P    R    I    L";
        else if(Month==5)
            Title_S+="M    A    Y";
        else if(Month==6)
            Title_S+="J    U    N    E";
        else if(Month==7)
            Title_S+="J    U    L    Y";
        else if(Month==8)
            Title_S+="A    U    G    U    S    T";
        else if(Month==9)
            Title_S+="S    E    P    T    E    M    B    E    R";
        else if(Month==10)
            Title_S+="O    C    T    O    B    E    R";
        else if(Month==11)
            Title_S+="N    O    V    E    N    B    E    R";
        else if(Month==12)
            Title_S+="D    E    C    E    M    B    E    R";
        
        title.setString(Title_S);
        title.setCharacterSize(font_resize(20));
        title.setStyle(sf::Text::Bold);
        title.setFillColor(sf::Color(86, 175, 191));
        title.setPosition(800 + inCM(1.5) - title.getLocalBounds().width / 2, inCM(1.14));
        wn.draw(title);
    
    //Vertical lines
    sf::RectangleShape v_linePtr[8];
    for(int i = 0; i < 8; i++)
    {
        v_linePtr[i].setSize(sf::Vector2f(inPT(0.5), inCM(15)));
        v_linePtr[i].setFillColor(sf::Color(65, 154, 169));
        v_linePtr[i].setPosition(inCM(7.36 + 3.24 * i), inCM(2.76));
    }

    for(int i = 0; i < 8; i++) //vertical line
        wn.draw(v_linePtr[i]);
    
}

OurTime CountDate(OurTime& TIME, int Gap)
{
    //Draw date
    int start_year = TIME.getYear();
    int start_month  = TIME.getMonth();
    int start_date  = TIME.getDay();
    
    start_date-=Gap;
    if(start_date<0)
    {
        if(start_month==1)
        {
            start_year--;
            start_month =12;
        }
        else
            start_month--;
        
        if(start_month==1||start_month==3||start_month==5||start_month==7||start_month==8||start_month==10||start_month==12)
            start_date+=31;
        else if (start_month==2 && (start_year%4==0))
            start_date+=29;
        else if (start_month==2 && (start_year%4!=0))
            start_date+=28;
        else if(start_month==4||start_month==6||start_month==9||start_month==11)
            start_date+=30;
    }
    
    if(start_date>28)
    {
        if(start_month==2 && (start_year%4!=0))
        {
            if(start_date>28)
            {
                start_date-=28;
                start_month++;
            }
        }
        else if(start_month==2 && (start_year%4==0))
        {
            if(start_date>29)
            {
                start_date-=29;
                start_month++;
            }
        }
        else if(start_month==12)
        {
            if(start_date>31)
            {
                start_date-=31;
                start_month =1 ;
                start_year++;
            }
        }
        else if(start_month==1||start_month==3||start_month==5||start_month==7||start_month==8||start_month==10)
        {
            if(start_date>31)
            {
                start_date-=31;
                start_month++;
            }
        }
        else if(start_month==4||start_month==6||start_month==9||start_month==11)
        {
            if(start_date>30)
            {
                start_date-=30;
                start_month++;
            }
        }
    }
    string year = to_string(start_year);
    string month = to_string(start_month);
    if(month.length()==1)
        month.insert(0,"0");
    string day = to_string(start_date);
    if(day.length()==1)
        day.insert(0,"0");
    string hour =to_string(0);
    if(hour.length()==1)
        hour.insert(0,"0");
    string min = to_string(0);
    if(min.length()==1)
        min.insert(0,"0");
    string s = year+month+day+hour+min;
    OurTime RESULT(s);
    return RESULT;
}

int MouseOnBoxes(sf::RenderWindow& wn, sf::RectangleShape* RS, int total)
{
    float Mx = sf::Mouse::getPosition(wn).x;
    float My = sf::Mouse::getPosition(wn).y;
    int index=-1;
    for(int i=0; i<total; i++)
    {
        sf::Vector2f Pos = RS[i].getPosition();
        sf::Vector2f Leng = RS[i].getSize();
        if(Mx>=Pos.x && Mx<=Pos.x+Leng.x && My >=Pos.y && My<= Pos.y+Leng.y)
        {
            index = i;
            break;
        }
    }
    return index;
}

int MouseOnTurnPage(sf::RenderWindow& wn, sf::CircleShape& leftButton, sf::CircleShape& rightButton)
{
    float Mx = sf::Mouse::getPosition(wn).x;
    float My = sf::Mouse::getPosition(wn).y;
    sf::Vector2f LPos= {110.,440.};
    float Lsiz= 30;
    sf::Vector2f RPos= {1520.,430.};
    float Rsiz=  30;

    if(Mx>=LPos.x && Mx<=LPos.x+Lsiz && My >=LPos.y && My<= LPos.y+Lsiz)
        return -1;
    else if(Mx>=RPos.x && Mx<=RPos.x+Rsiz && My >=RPos.y && My<= RPos.y+Rsiz)
        return 1;
    return 0;
}


void DrawBoxMes(sf::RenderWindow& wn, sf::RectangleShape* RS,sf::RectangleShape* BoxMes_Button, const MissionBag& MBag, const FixedEventBag& FEBag, int index)
{
    OurTime Default("201807080000");
    OurTime Event;
    sf::Vector2f Pos = RS[index].getPosition();
    string name;
    string StartTime;
    string EndTime;
    string TIME;
    string H_Duration;
    string M_Duration;
    bool isM=false;
    //FixedEvent
    if(index >= MBag.Bag.getSize())
    {
        name = FEBag.Bag[index-MBag.Bag.getSize()]->GetName();
        StartTime= FEBag.Bag[index-MBag.Bag.getSize()]->GetstartTime();
        EndTime = FEBag.Bag[index-MBag.Bag.getSize()]->GetendTime();
        
        TIME += StartTime.substr(8,2)+":"+StartTime.substr(10,2)+" - ";
        TIME += EndTime.substr(8,2)+":"+EndTime.substr(10,2);
        H_Duration = to_string(FEBag.Bag[index-MBag.Bag.getSize()]->getDuration()/60);
        M_Duration = to_string(FEBag.Bag[index-MBag.Bag.getSize()]->getDuration()%60);
        Event = FEBag.Bag[index-MBag.Bag.getSize()]->getStartTime();
    }
    else
    {
        isM =true;
        name = MBag.Bag[index]->GetName();
        StartTime= MBag.Bag[index]->GetstartTime();
        EndTime = MBag.Bag[index]->GetendTime();
        
        TIME += StartTime.substr(8,2)+":"+StartTime.substr(10,2)+" - ";
        TIME += EndTime.substr(8,2)+":"+EndTime.substr(10,2);
        H_Duration = to_string(MBag.Bag[index]->getDuration()/60);
        M_Duration = to_string(MBag.Bag[index]->getDuration()%60);
        Event = MBag.Bag[index]->getStartTime();
    }
    
    float Y_Mes = Pos.y;
    float X_Mes;
    if( ((Event - Default)/1440)%7 ==6 )
        X_Mes = Pos.x-10-toPx(4.8);
    else
        X_Mes =  Pos.x+X_Length+10;
    float Y_Mes_len = inCM(3.15);
    float X_Mes_len = toPx(4.8);
    sf::RectangleShape rectangle;
    rectangle.setFillColor(sf::Color(255, 255, 255));
    
    rectangle.setPosition(X_Mes, Y_Mes);
    rectangle.setSize(sf::Vector2f(X_Mes_len, Y_Mes_len));
    wn.draw(rectangle);

    
    //Name TIME Duraiton
    for(int i=0; i<3; i++)
    {
        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color(90, 175, 190));
        if(i==0)
        {
            text.setCharacterSize(font_resize(16));
            text.setStyle(sf::Text::Bold|sf::Text::Underlined);
            text.setString(name);
            text.setPosition(X_Mes+10, Y_Mes+10);
            Remove_Button_X = X_Mes+10;
        }
        else if(i==1)
        {
            text.setCharacterSize(font_resize(14));
            text.setString(TIME);
            text.setPosition(X_Mes+10, Y_Mes+toPx(1));
        }
        
        else if(i==2)
        {
            text.setCharacterSize(font_resize(14));
            text.setString(H_Duration+" Hour "+M_Duration+" Min");
            text.setPosition(X_Mes+10, Y_Mes+toPx(1.6));
            Remove_Button_Y = Y_Mes+toPx(1.6)+text.getLocalBounds().height+toPx(0.5);
        }
        wn.draw(text);
    }
    
    sf::Text text[2];

    //Remove

    BoxMes_Button[0].setFillColor(sf::Color(249, 109, 134));
    
    BoxMes_Button[0].setPosition(Remove_Button_X, Remove_Button_Y);
    BoxMes_Button[0].setSize(sf::Vector2f(Remove_Button_XLen, Remove_Button_YLen));
    text[0].setFont(font);
    text[0].setFillColor(sf::Color::White);
    text[0].setCharacterSize(font_resize(12));
    text[0].setString("Remove");
    text[0].setPosition(Remove_Button_X+10, Remove_Button_Y);
    
    
    if(isM)
    {
        //Check
        BoxMes_Button[1].setFillColor(sf::Color(167, 221, 216));
        
        BoxMes_Button[1].setPosition(Remove_Button_X+Remove_Button_XLen+10, Remove_Button_Y);
        BoxMes_Button[1].setSize(sf::Vector2f(Check_Button_XLen, Check_Button_YLen));
        text[1].setFont(font);
        text[1].setFillColor(sf::Color::White);
        text[1].setCharacterSize(font_resize(12));
        text[1].setString("Done");
        text[1].setPosition(Remove_Button_X+Remove_Button_XLen+30, Remove_Button_Y);
    }
    
    //Close Mes Box
    BoxMes_Button[2].setFillColor(sf::Color::Black);
    
    BoxMes_Button[2].setPosition(X_Mes_len+X_Mes-toPx(0.6), Y_Mes+5);
    BoxMes_Button[2].setSize(sf::Vector2f(toPx(0.5), toPx(0.5)));
    wn.draw(BoxMes_Button[2]);
    if(isM)
        wn.draw(BoxMes_Button[1]);
    wn.draw(BoxMes_Button[0]);
    wn.draw(text[0]);
    wn.draw(text[1]);
}
