#include <iostream>
#include <string>
#include <time.h>
#include "OurTime.hpp"
#include "mission.h"
#include "fixedevent.h"

#include <SFML/Graphics.hpp>
#include "LinkedBag.h"
#include "Knapscak.h"
#include <fstream>
#include <math.h>
#include "Read_Load_Struct.cpp"
#include "Day.hpp"


#define weeks 78
#define aweek 7
using namespace std;


float toPx(float cm)
{
    return cm*(1600/28.6);
}
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



int main()
{


    int oper;
	FixedEventBag FEBag;
	MissionBag MBag;
	MissionBag Done;
	OurTime today;
    OurTime start("201807080000");
	today.Current();
    today.setHour(0);
	today.setMinute(0);
    Day *year2018[weeks][aweek];
    Day *week[7];


    string MissionLocation = "Mission.txt";
    string FixedLocation = "Fixed.txt";
    MBag.LoadFile(MissionLocation);
    FEBag.LoadFile(FixedLocation);


    //draw window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "My Schedule Assistant", sf::Style::Titlebar | sf::Style::Close);
    string userpassword = "DSAP-final";

    //draw clock
    sf::CircleShape shapeOut(toPx(4.25), 100);
    shapeOut.setFillColor(sf::Color(86, 175, 191));
    shapeOut.setPosition(toPx(-4.25), toPx(3.69 - 1.5));
    sf::CircleShape shape(toPx(3), 100);
    shape.setFillColor(sf::Color(0,0,0));
    shape.setPosition(toPx(-3), toPx(4.95 - 1.5));
    shape.setOutlineThickness(toPx(0.25));
    shape.setOutlineColor(sf::Color(162, 219, 214));
    sf::RectangleShape line_hour(sf::Vector2f(toPx(2), toPx(0.1)));
    line_hour.setPosition(toPx(0.05),toPx(5.9 - 1.5));
    line_hour.setFillColor(sf::Color(86, 175, 191));
    line_hour.rotate(90);
    sf::RectangleShape line_minute(sf::Vector2f(toPx(2.5), toPx(0.05)));
    line_minute.setPosition(toPx(0.05), toPx(7.9 - 1.5));
    line_minute.setFillColor(sf::Color(86, 175, 191));
    line_minute.rotate(40);
    sf::CircleShape center(toPx(0.15), 100);
    center.setFillColor(sf::Color(86, 175, 191));
    center.setPosition(toPx(-0.15), toPx(7.79 - 1.5));

    //draw login bar
    sf::RectangleShape downRectangle(sf::Vector2f(toPx(33.87), toPx(1.79)));
    sf::Texture texture1;
    if(!texture1.loadFromFile("transparent.png"))
    {
        cout << "texture1 wrong";
    }
    texture1.loadFromFile("transparent.png");
    downRectangle.setTexture(&texture1);

    //draw text
    sf::Font font;
    if(!font.loadFromFile("calibri.ttf"))
    {
        cout << "font wrong";
    }
    sf::Text text;
    text.setFont(font);
    text.setString("My");
    text.setFillColor(sf::Color(255, 255, 255));
    text.setCharacterSize(font_resize(60));
    text.setPosition(toPx(5.81), toPx(4 - 1.5));
    text.setStyle(sf::Text::Bold);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Schedule");
    text2.setFillColor(sf::Color(255, 255, 255));
    text2.setCharacterSize(font_resize(60));
    text2.setPosition(toPx(5.81), toPx(6.5 - 1.5));
    text2.setStyle(sf::Text::Bold);

    sf::Text text3;
    text3.setFont(font);
    text3.setString("Assistant");
    text3.setFillColor(sf::Color(255, 255, 255));
    text3.setCharacterSize(font_resize(60));
    text3.setPosition(toPx(5.81), toPx(9 - 1.5));
    text3.setStyle(sf::Text::Bold);

    sf::Text loginIntroduction;
    loginIntroduction.setFont(font);
    loginIntroduction.setString("[ please enter your password ] ");
    loginIntroduction.setCharacterSize(font_resize(20));
    loginIntroduction.setFillColor(sf::Color(255, 255, 255, 100));


    sf::String password;
    string passwordStr;
    sf::Text userText;
    userText.setFont(font);
    userText.setCharacterSize(font_resize(20));
    userText.setFillColor(sf::Color::White);
    bool passwordCorrect = false;

//----------------------------------------------------------page 2
    bool page2 = false;


    //font
    sf::Font calibri_normal;
    calibri_normal.loadFromFile("calibri.ttf");
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

    //Title(2018 January)
    sf::Text title;
    title.setFont(calibri_bold);
    title.setString("2    0    1    8        J    A    N    U    A    R    Y");
    title.setCharacterSize(font_resize(20));
    title.setFillColor(sf::Color(86, 175, 191));
    title.setPosition(800 + inCM(1.5) - title.getLocalBounds().width / 2, inCM(1.14));

    //Vertical lines
    sf::RectangleShape v_linePtr[8];
    for(int i = 0; i < 8; i++)
    {
        v_linePtr[i].setSize(sf::Vector2f(inPT(0.5), inCM(15)));
        v_linePtr[i].setFillColor(sf::Color(65, 154, 169));
        v_linePtr[i].setPosition(inCM(7.36 + 3.24 * i), inCM(2.76));
    }
    //horizontal lines
    sf::RectangleShape h_linePtr[5];
    for(int i = 0; i < 5; i++)
    {
        h_linePtr[i].setSize(sf::Vector2f(inCM(23), inPT(0.6)));
        h_linePtr[i].setFillColor(sf::Color(166, 166, 166));
        h_linePtr[i].setPosition(inCM(7.05), inCM(3.77 + 3.51 * i));
    }
    //date
    sf::Text date[7];
    for(int i = 0; i < 7; i++)
    {
        date[i].setFont(calibri_normal);
        date[i].setCharacterSize(font_resize(18));
        date[i].setFillColor(sf::Color(255, 255, 255));
        date[i].setPosition(inCM(8.05 + 3.24 * i), inCM(2.76));
        switch(i)
        {
            case 0:
                date[i].setString(std::string("01 ") + std::string("Sun."));
                break;
            case 1:
                date[i].setString(std::string("02 ") + std::string("Mon."));
                break;
            case 2:
                date[i].setString(std::string("03 ") + std::string("Tues."));
                break;
            case 3:
                date[i].setString(std::string("04 ") + std::string("Wed."));
                break;
            case 4:
                date[i].setString(std::string("05 ") + std::string("Thu."));
                break;
            case 5:
                date[i].setString(std::string("06 ") + std::string("Fri."));
                break;
            case 6:
                date[i].setString(std::string("07 ") + std::string("Sat."));
                break;
        }

    }
    //Time
    sf::Text time[5];
    for(int i = 0; i < 5; i++)
    {
        time[i].setFont(calibri_normal);
        time[i].setCharacterSize(font_resize(14));
        time[i].setFillColor(sf::Color(166, 166, 166));
        time[i].setPosition(inCM(5.42), inCM(3.45 + 3.5 * i));
        if(i < 2)
            time[i].setString(std::string("0" + std::to_string(0 + 6 * i) + ":00"));
        else
            time[i].setString(std::string(std::to_string(0 + 6 * i) + ":00"));
    }

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

    //black filter
    bool filterOn = false;
    sf::RectangleShape filter(sf::Vector2f(1600 - inCM(1.5), 900));
    filter.setFillColor(sf::Color(0, 0, 0, 180));
    filter.setPosition(inCM(1.5), 0);

    //Select Event Menu//////////////////////////////////////////////////////////////////////////////////
    bool selectEventMenuOn = false;
    sf::RectangleShape selectEventMenu(sf::Vector2f(inCM(9), inCM(10)));
    selectEventMenu.setFillColor(sf::Color(255, 255, 255));
    selectEventMenu.setPosition(800 - inCM(9) / 2 + inCM(1.5), 450 - inCM(10) / 2);
    //Select Event Menu Title
    sf::Text selectEventMenuTitle;
    selectEventMenuTitle.setString("Select Event Type");
    selectEventMenuTitle.setCharacterSize(font_resize(20));
    selectEventMenuTitle.setFont(calibri_bold);
    selectEventMenuTitle.setFillColor(sf::Color(62, 149, 164));
    selectEventMenuTitle.setPosition(selectEventMenu.getPosition().x + selectEventMenu.getSize().x / 2 - selectEventMenuTitle.getLocalBounds().width / 2, selectEventMenu.getPosition().y + inCM(1.45));
    //flexible time mission button
    sf::RectangleShape FMbutton(sf::Vector2f(inCM(7), inCM(1)));
    FMbutton.setFillColor(sf::Color(162, 219, 214));
    FMbutton.setPosition(selectEventMenu.getPosition().x + selectEventMenu.getSize().x / 2 - FMbutton.getSize().x / 2, selectEventMenu.getPosition().y + inCM(3));
    sf::Text FMbuttonText;
    FMbuttonText.setString("Flexible Time Mission");
    FMbuttonText.setCharacterSize(font_resize(18));
    FMbuttonText.setFont(calibri_normal);
    FMbuttonText.setFillColor(sf::Color(62, 149, 164));
    FMbuttonText.setPosition(FMbutton.getPosition().x + FMbutton.getSize().x / 2 - FMbuttonText.getLocalBounds().width / 2, FMbutton.getPosition().y + inCM(0.1));
    //fixed time event button
    sf::RectangleShape FEbutton(sf::Vector2f(inCM(7), inCM(1)));
    FEbutton.setFillColor(sf::Color(162, 219, 214));
    FEbutton.setPosition(selectEventMenu.getPosition().x + selectEventMenu.getSize().x / 2 - FEbutton.getSize().x / 2, FMbutton.getPosition().y + inCM(2.25));
    sf::Text FEbuttonText;
    FEbuttonText.setString("Fixed Time Event");
    FEbuttonText.setCharacterSize(font_resize(18));
    FEbuttonText.setFont(calibri_normal);
    FEbuttonText.setFillColor(sf::Color(62, 149, 164));
    FEbuttonText.setPosition(FEbutton.getPosition().x + FEbutton.getSize().x / 2 - FEbuttonText.getLocalBounds().width / 2, FEbutton.getPosition().y + inCM(0.1));
    //cancel button
    sf::RectangleShape cancelButton(sf::Vector2f(inCM(3), inCM(1)));
    cancelButton.setFillColor(sf::Color(162, 219, 214));
    cancelButton.setPosition(selectEventMenu.getPosition().x + selectEventMenu.getSize().x / 2 - cancelButton.getSize().x / 2, FEbutton.getPosition().y + inCM(2.25));
    sf::Text cancelButtonText;
    cancelButtonText.setString("cancel");
    cancelButtonText.setCharacterSize(font_resize(18));
    cancelButtonText.setFont(calibri_normal);
    cancelButtonText.setFillColor(sf::Color(62, 149, 164));
    cancelButtonText.setPosition(cancelButton.getPosition().x + cancelButton.getSize().x / 2 - cancelButtonText.getLocalBounds().width / 2, cancelButton.getPosition().y + inCM(0.1));

    //add flexible time mission menu////////////////////////////////////////////////////////////////////////
    bool FMmenuOn = false;
    sf::RectangleShape FMmenu(sf::Vector2f(inCM(12), inCM(18)));
    FMmenu.setFillColor(sf::Color(255, 255, 255, 243));
    FMmenu.setPosition(800 - inCM(12) / 2 + inCM(1.5), 450 - inCM(18) / 2);
    //add flexible time mission title
    sf::Text FMmenuTitle;
    FMmenuTitle.setString("Add Flexible Time Mission");
    FMmenuTitle.setFont(calibri_bold);
    FMmenuTitle.setCharacterSize(font_resize(20));
    FMmenuTitle.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - FMmenuTitle.getLocalBounds().width / 2, FMmenu.getPosition().y + inCM(1.2));
    FMmenuTitle.setFillColor(sf::Color(62, 149, 164));
    //mission name text
    sf::Text missionNameText;
    missionNameText.setString("Mission Name");
    missionNameText.setFont(calibri_italic);
    missionNameText.setCharacterSize(font_resize(18));
    missionNameText.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - missionNameText.getLocalBounds().width / 2, FMmenu.getPosition().y + inCM(2.6));
    missionNameText.setFillColor(sf::Color(62, 149, 164));
    //mission name block
    bool missionNameBlockOn = false;
    sf::RectangleShape missionNameBlock(sf::Vector2f(inCM(6), inCM(1)));
    missionNameBlock.setFillColor(sf::Color(217, 217, 217));
    missionNameBlock.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - missionNameBlock.getSize().x / 2, FMmenu.getPosition().y + inCM(3.6));
    //mission name typed
    std::string missionName = "";
    sf::Text missionNameTyped;
    missionNameTyped.setString(missionName);
    missionNameTyped.setFont(calibri_normal);
    missionNameTyped.setCharacterSize(font_resize(15));
    missionNameTyped.setFillColor(sf::Color(100, 100, 100));
    missionNameTyped.setPosition(missionNameBlock.getPosition() + sf::Vector2f(inCM(0.5), inCM(0.1)));
    //category text
    sf::Text categoryText;
    categoryText.setString("Category");
    categoryText.setFont(calibri_italic);
    categoryText.setCharacterSize(font_resize(18));
    categoryText.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - categoryText.getLocalBounds().width / 2, missionNameText.getPosition().y + inCM(2.22));
    categoryText.setFillColor(sf::Color(62, 149, 164));
    //category block
    bool categoryBlockOn = false;
    sf::RectangleShape categoryBlock(sf::Vector2f(inCM(6), inCM(1)));
    categoryBlock.setFillColor(sf::Color(217, 217, 217));
    categoryBlock.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - categoryBlock.getSize().x / 2, missionNameBlock.getPosition().y + inCM(2.22));
    //category typed
    std::string FMcategory = "";
    sf::Text FMcategoryTyped;
    FMcategoryTyped.setString(FMcategory);
    FMcategoryTyped.setFont(calibri_normal);
    FMcategoryTyped.setCharacterSize(font_resize(15));
    FMcategoryTyped.setFillColor(sf::Color(100, 100, 100));
    FMcategoryTyped.setPosition(categoryBlock.getPosition() + sf::Vector2f(inCM(0.5), inCM(0.1)));
    //deadline text
    sf::Text deadlineText;
    deadlineText.setString("Deadline");
    deadlineText.setFont(calibri_italic);
    deadlineText.setCharacterSize(font_resize(18));
    deadlineText.setFillColor(sf::Color(62, 149, 164));
    deadlineText.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - deadlineText.getLocalBounds().width / 2, categoryText.getPosition().y + inCM(2.22));
    //deadline block
    bool deadlineBlockOn[5];
    for(int i = 0; i < 5; i++)
        deadlineBlockOn[i] = false;
    sf::RectangleShape deadlineBlock[5];
    for(int i = 0; i < 5; i++)
    {
        deadlineBlock[i].setSize(sf::Vector2f(inCM(1.15), inCM(1)));
        deadlineBlock[i].setFillColor(sf::Color(217, 217, 217));
        deadlineBlock[i].setPosition(categoryBlock.getPosition().x + inCM(1.2125) * i, categoryBlock.getPosition().y + inCM(2.22));
    }
    //deadline typed
    std::string FMdeadline[5];
    for(int i = 0; i < 5; i++)
        FMdeadline[i] = "";
    sf::Text FMdeadlineTyped[5];
    for(int i = 0; i < 5; i++)
    {
        FMdeadlineTyped[i].setString(FMdeadline[i]);
        FMdeadlineTyped[i].setFont(calibri_normal);
        FMdeadlineTyped[i].setCharacterSize(font_resize(12));
        FMdeadlineTyped[i].setFillColor(sf::Color(100, 100, 100));
        FMdeadlineTyped[i].setPosition(deadlineBlock[i].getPosition() + sf::Vector2f(inCM(0.2), inCM(0.2)));
    }
    //deadline block text
    sf::Text deadlineBlockText[5];
    deadlineBlockText[0].setString("[y]");
    deadlineBlockText[1].setString("[m]");
    deadlineBlockText[2].setString("[d]");
    deadlineBlockText[3].setString("[h]");
    deadlineBlockText[4].setString("[m]");
    for(int i = 0; i < 5; i++)
    {
        deadlineBlockText[i].setFont(calibri_normal);
        deadlineBlockText[i].setCharacterSize(font_resize(14));
        deadlineBlockText[i].setFillColor(sf::Color(255, 255, 255));
        deadlineBlockText[i].setPosition(deadlineBlock[i].getPosition() + sf::Vector2f(deadlineBlock[i].getSize().x / 2 - deadlineBlockText[i].getLocalBounds().width / 2, inCM(0.15)));
    }
    //duration text
    sf::Text durationText;
    durationText.setString("Duration");
    durationText.setFont(calibri_italic);
    durationText.setFillColor(sf::Color(62, 149, 164));
    durationText.setCharacterSize(font_resize(18));
    durationText.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - durationText.getLocalBounds().width / 2, deadlineText.getPosition().y + inCM(2.22));
    //duration block
    bool FMdurationBlockOn[2] = {false, false};
    sf::RectangleShape durationBlock[2];
    for(int i = 0; i < 2; i++)
    {
        durationBlock[i].setSize(sf::Vector2f(inCM(2.98), inCM(1)));
        durationBlock[i].setFillColor(sf::Color(217, 217, 217));
        durationBlock[i].setPosition(categoryBlock.getPosition().x + inCM(3.04) * i, deadlineBlock[0].getPosition().y + inCM(2.22));
    }
    //duration block typed
    std::string duration[2] = {""};
    sf::Text durationTyped[2];
    for(int i = 0; i < 2; i++)
    {
        durationTyped[i].setString(duration[2]);
        durationTyped[i].setFont(calibri_normal);
        durationTyped[i].setCharacterSize(font_resize(15));
        durationTyped[i].setFillColor(sf::Color(100, 100, 100));
        durationTyped[i].setPosition(durationBlock[i].getPosition() + sf::Vector2f(inCM(0.49), inCM(0.1)));
    }
    //duration block text
    sf::Text durationBlockText[2];
    durationBlockText[0].setString("[h]");
    durationBlockText[1].setString("[m]");
    for(int i = 0; i < 2; i++)
    {
        durationBlockText[i].setFont(calibri_normal);
        durationBlockText[i].setCharacterSize(font_resize(14));
        durationBlockText[i].setFillColor(sf::Color(255, 255, 255));
        durationBlockText[i].setPosition(durationBlock[i].getPosition() + sf::Vector2f(durationBlock[i].getSize().x / 2 - durationBlockText[i].getLocalBounds().width / 2, inCM(0.15)));
    }
    //max continuous duration text
    sf::Text maxContiDurationText;
    maxContiDurationText.setString("Max Continuous Duration");
    maxContiDurationText.setFont(calibri_italic);
    maxContiDurationText.setFillColor(sf::Color(62, 149, 164));
    maxContiDurationText.setCharacterSize(font_resize(18));
    maxContiDurationText.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - maxContiDurationText.getLocalBounds().width / 2, durationText.getPosition().y + inCM(2.22));
    //max continuous duration block
    bool maxContiDurationBlockOn[2] = {false, false};
    sf::RectangleShape maxContiDurationBlock[2];
    for(int i = 0; i < 2; i++)
    {
        maxContiDurationBlock[i].setSize(sf::Vector2f(inCM(2.98), inCM(1)));
        maxContiDurationBlock[i].setFillColor(sf::Color(217, 217, 217));
        maxContiDurationBlock[i].setPosition(durationBlock[i].getPosition() + sf::Vector2f(0, inCM(2.22)));
    }
    //max continuous duration typed
    std::string maxContiDuration[2] = {"", ""};
    sf::Text maxContiDurationTyped[2];
    for(int i = 0; i < 2; i++)
    {
        maxContiDurationTyped[i].setString(maxContiDuration[2]);
        maxContiDurationTyped[i].setFont(calibri_normal);
        maxContiDurationTyped[i].setCharacterSize(font_resize(15));
        maxContiDurationTyped[i].setFillColor(sf::Color(100, 100, 100));
        maxContiDurationTyped[i].setPosition(maxContiDurationBlock[i].getPosition() + sf::Vector2f(inCM(0.49), inCM(0.1)));
    }
    //max continuous duration block text
    sf::Text maxContiDurationBlockText[2];
    maxContiDurationBlockText[0].setString("[h]");
    maxContiDurationBlockText[1].setString("[m]");
    for(int i = 0; i < 2; i++)
    {
        maxContiDurationBlockText[i].setFont(calibri_normal);
        maxContiDurationBlockText[i].setCharacterSize(font_resize(14));
        maxContiDurationBlockText[i].setFillColor(sf::Color(255, 255, 255));
        maxContiDurationBlockText[i].setPosition(durationBlockText[i].getPosition() + sf::Vector2f(0, inCM(2.22)));
    }
    //priority text
    sf::Text priorityText;
    priorityText.setString("Priority");
    priorityText.setFont(calibri_italic);
    priorityText.setCharacterSize(font_resize(18));
    priorityText.setFillColor(sf::Color(62, 149, 164));
    priorityText.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x / 2 - priorityText.getLocalBounds().width / 2, maxContiDurationText.getPosition().y + inCM(2.22));
    //priority block
    bool priorityBlockOn = false;
    sf::RectangleShape priorityBlock(sf::Vector2f(inCM(6), inCM(1)));
    priorityBlock.setFillColor(sf::Color(217, 217, 217));
    priorityBlock.setPosition(maxContiDurationBlock[0].getPosition() + sf::Vector2f(0, inCM(2.22)));
    //priority typed
    std::string priority = "";
    sf::Text priorityTyped;
    priorityTyped.setString(priority);
    priorityTyped.setFont(calibri_normal);
    priorityTyped.setCharacterSize(font_resize(15));
    priorityTyped.setFillColor(sf::Color(100, 100, 100));
    priorityTyped.setPosition(priorityBlock.getPosition().x + priorityBlock.getSize().x / 2 - priorityTyped.getLocalBounds().width / 2, priorityBlock.getPosition().y + inCM(0.15));
    //priority block text
    sf::Text priorityBlockText;
    priorityBlockText.setString("1, 2, ..., 10");
    priorityBlockText.setFillColor(sf::Color(255, 255, 255));
    priorityBlockText.setCharacterSize(font_resize(14));
    priorityBlockText.setFont(calibri_normal);
    priorityBlockText.setPosition(priorityBlock.getPosition().x + priorityBlock.getSize().x / 2 - priorityBlockText.getLocalBounds().width / 2, maxContiDurationBlockText[0].getPosition().y + inCM(2.22));
    //add button
    sf::RectangleShape FMaddButton(sf::Vector2f(inCM(3), inCM(0.8)));
    FMaddButton.setFillColor(sf::Color(162, 219, 214));
    FMaddButton.setPosition(FMmenu.getPosition().x + inCM(1.5), FMmenu.getPosition().y + FMmenu.getSize().y - inCM(1.6));
    //add button text
    sf::Text FMaddButtonText;
    FMaddButtonText.setString("add");
    FMaddButtonText.setFont(calibri_normal);
    FMaddButtonText.setCharacterSize(font_resize(18));
    FMaddButtonText.setFillColor(sf::Color(62, 149, 164));
    FMaddButtonText.setPosition(FMaddButton.getPosition().x + FMaddButton.getSize().x / 2 - FMaddButtonText.getLocalBounds().width / 2, FMaddButton.getPosition().y);
    //cancel button
    sf::RectangleShape FMcancelButton(sf::Vector2f(inCM(3), inCM(0.8)));
    FMcancelButton.setFillColor(sf::Color(162, 219, 214));
    FMcancelButton.setPosition(FMmenu.getPosition().x + FMmenu.getSize().x - inCM(1.5) - FMcancelButton.getSize().x, FMaddButton.getPosition().y);
    //cancel button text
    sf::Text FMcancelButtonText;
    FMcancelButtonText.setString("cancel");
    FMcancelButtonText.setFont(calibri_normal);
    FMcancelButtonText.setCharacterSize(font_resize(18));
    FMcancelButtonText.setFillColor(sf::Color(62, 149, 164));
    FMcancelButtonText.setPosition(FMcancelButton.getPosition().x + FMcancelButton.getSize().x / 2 - FMcancelButtonText.getLocalBounds().width / 2, FMcancelButton.getPosition().y);

    //add fixed time event/////////////////////////////////////////////////////////////////////////////////
    bool FEmenuOn = false;
    sf::RectangleShape FEmenu(sf::Vector2f(inCM(12), inCM(15)));
    FEmenu.setFillColor(sf::Color(255, 255, 255, 243));
    FEmenu.setPosition(800 + inCM(1.5) - FEmenu.getSize().x / 2, 450 - FEmenu.getSize().y / 2);
    //add fixed time event title
    sf::Text FEmenuTitle;
    FEmenuTitle.setString("Add Fixed Time Event");
    FEmenuTitle.setFont(calibri_bold);
    FEmenuTitle.setCharacterSize(font_resize(20));
    FEmenuTitle.setFillColor(sf::Color(62, 149, 164));
    FEmenuTitle.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - FEmenuTitle.getLocalBounds().width / 2, FEmenu.getPosition().y + inCM(1.5));
    //event name text
    sf::Text eventNameText;
    eventNameText.setString("Event Name");
    eventNameText.setFont(calibri_italic);
    eventNameText.setCharacterSize(font_resize(18));
    eventNameText.setFillColor(sf::Color(62, 149, 164));
    eventNameText.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - eventNameText.getLocalBounds().width / 2, FEmenu.getPosition().y + inCM(3.2));
    //event name block
    bool eventNameBlockOn = false;
    sf::RectangleShape eventNameBlock(sf::Vector2f(inCM(6), inCM(1)));
    eventNameBlock.setFillColor(sf::Color(217, 217, 217));
    eventNameBlock.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - eventNameBlock.getSize().x / 2, FEmenu.getPosition().y + inCM(4.2));
    //event name typed
    std::string eventName = "";
    sf::Text eventNameTyped;
    eventNameTyped.setString(eventName);
    eventNameTyped.setFont(calibri_normal);
    eventNameTyped.setCharacterSize(font_resize(15));
    eventNameTyped.setFillColor(sf::Color(100, 100, 100));
    eventNameTyped.setPosition(eventNameBlock.getPosition() + sf::Vector2f(inCM(0.5), inCM(0.1)));
    //FE category text
    sf::Text FEcategoryText;
    FEcategoryText.setString("Category");
    FEcategoryText.setFillColor(sf::Color(62, 149, 164));
    FEcategoryText.setFont(calibri_italic);
    FEcategoryText.setCharacterSize(font_resize(18));
    FEcategoryText.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - FEcategoryText.getLocalBounds().width / 2, eventNameText.getPosition().y + inCM(2.22));
    //FE category block
    bool FEcategoryBlockOn = false;
    sf::RectangleShape FEcategoryBlock(sf::Vector2f(inCM(6), inCM(1)));
    FEcategoryBlock.setFillColor(sf::Color(217, 217, 217));
    FEcategoryBlock.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - FEcategoryBlock.getSize().x / 2, eventNameBlock.getPosition().y + inCM(2.22));
    //FE category typed
    std::string FEcategory = "";
    sf::Text FEcategoryTyped;
    FEcategoryTyped.setString(FEcategory);
    FEcategoryTyped.setFont(calibri_normal);
    FEcategoryTyped.setCharacterSize(font_resize(15));
    FEcategoryTyped.setFillColor(sf::Color(100, 100, 100));
    FEcategoryTyped.setPosition(FEcategoryBlock.getPosition() + sf::Vector2f(inCM(0.5), inCM(0.1)));
    //FE start time text
    sf::Text FEstartTimeText;
    FEstartTimeText.setString("Start Time");
    FEstartTimeText.setFont(calibri_italic);
    FEstartTimeText.setCharacterSize(font_resize(18));
    FEstartTimeText.setFillColor(sf::Color(62, 149, 164));
    FEstartTimeText.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - FEstartTimeText.getLocalBounds().width / 2, FEcategoryText.getPosition().y + inCM(2.22));
    //FE start time block
    bool FEstartTimeBlockOn[5];
    for(int i = 0; i < 5; i++)
        FEstartTimeBlockOn[i] = false;
    sf::RectangleShape FEstartTimeBlock[5];
    for(int i = 0; i < 5; i++)
    {
        FEstartTimeBlock[i].setSize(sf::Vector2f(inCM(1.15), inCM(1)));
        FEstartTimeBlock[i].setFillColor(sf::Color(217, 217, 217));
        FEstartTimeBlock[i].setPosition(FEcategoryBlock.getPosition().x + inCM(1.15 + 0.0625) * i, FEcategoryBlock.getPosition().y + inCM(2.22));
    }
    //FE start time block typed
    std::string FEstartTime[5];
    for(int i = 0; i < 5; i++)
        FEstartTime[i] = "";
    sf::Text FEstartTimeTyped[5];
    for(int i = 0; i < 5; i++)
    {
        FEstartTimeTyped[i].setString(FEstartTime[i]);
        FEstartTimeTyped[i].setFont(calibri_normal);
        FEstartTimeTyped[i].setCharacterSize(font_resize(12));
        FEstartTimeTyped[i].setFillColor(sf::Color(100, 100, 100));
        FEstartTimeTyped[i].setPosition(FEstartTimeBlock[i].getPosition().x + FEstartTimeBlock[i].getSize().x / 2 - FEstartTimeTyped[i].getLocalBounds().width / 2, FEstartTimeBlock[i].getPosition().y + inCM(0.15));
    }
    //FE start time block text
    sf::Text FEstartTimeBlockText[5];
    FEstartTimeBlockText[0].setString("[y]");
    FEstartTimeBlockText[1].setString("[m]");
    FEstartTimeBlockText[2].setString("[d]");
    FEstartTimeBlockText[3].setString("[h]");
    FEstartTimeBlockText[4].setString("[m]");
    for(int i = 0; i < 5; i++)
    {
        FEstartTimeBlockText[i].setFont(calibri_normal);
        FEstartTimeBlockText[i].setCharacterSize(font_resize(14));
        FEstartTimeBlockText[i].setFillColor(sf::Color(255, 255, 255));
        FEstartTimeBlockText[i].setPosition(FEstartTimeBlock[i].getPosition() + sf::Vector2f(FEstartTimeBlock[i].getSize().x / 2 - FEstartTimeBlockText[i].getLocalBounds().width / 2, inCM(0.15)));
    }
    //FE end time text
    sf::Text FEendTimeText;
    FEendTimeText.setString("End Time");
    FEendTimeText.setFont(calibri_italic);
    FEendTimeText.setCharacterSize(font_resize(18));
    FEendTimeText.setFillColor(sf::Color(62, 149, 164));
    FEendTimeText.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x / 2 - FEendTimeText.getLocalBounds().width / 2, FEstartTimeText.getPosition().y + inCM(2.22));
    //FE end time block
    bool FEendTimeBlockOn[5];
    for(int i = 0; i < 5; i++)
        FEendTimeBlockOn[i] = false;
    sf::RectangleShape FEendTimeBlock[5];
    for(int i = 0; i < 5; i++)
    {
        FEendTimeBlock[i].setSize(sf::Vector2f(inCM(1.15), inCM(1)));
        FEendTimeBlock[i].setFillColor(sf::Color(217, 217, 217));
        FEendTimeBlock[i].setPosition(FEcategoryBlock.getPosition().x + inCM(1.15 + 0.0625) * i, FEstartTimeBlock[0].getPosition().y + inCM(2.22));
    }
    //FE end time typed
    std::string FEendTime[5];
    for(int i = 0; i < 5; i++)
        FEendTime[i] = "";
    sf::Text FEendTimeTyped[5];
    for(int i = 0; i < 5; i++)
    {
        FEendTimeTyped[i].setString(FEendTime[i]);
        FEendTimeTyped[i].setFont(calibri_normal);
        FEendTimeTyped[i].setCharacterSize(font_resize(12));
        FEendTimeTyped[i].setFillColor(sf::Color(100, 100, 100));
        FEendTimeTyped[i].setPosition(FEendTimeBlock[i].getPosition().x + FEendTimeBlock[i].getSize().x / 2 - FEendTimeTyped[i].getLocalBounds().width / 2, FEendTimeBlock[i].getPosition().y + inCM(0.15));
    }
    //FE end time block text
    sf::Text FEendTimeBlockText[5];
    FEendTimeBlockText[0].setString("[y]");
    FEendTimeBlockText[1].setString("[m]");
    FEendTimeBlockText[2].setString("[d]");
    FEendTimeBlockText[3].setString("[h]");
    FEendTimeBlockText[4].setString("[m]");
    for(int i = 0; i < 5; i++)
    {
        FEendTimeBlockText[i].setFont(calibri_normal);
        FEendTimeBlockText[i].setCharacterSize(font_resize(14));
        FEendTimeBlockText[i].setFillColor(sf::Color(255, 255, 255));
        FEendTimeBlockText[i].setPosition(FEendTimeBlock[i].getPosition() + sf::Vector2f(FEendTimeBlock[i].getSize().x / 2 - FEendTimeBlockText[i].getLocalBounds().width / 2, inCM(0.15)));
    }
    //add button
    sf::RectangleShape FEaddButton(sf::Vector2f(inCM(3), inCM(0.8)));
    FEaddButton.setFillColor(sf::Color(162, 219, 214));
    FEaddButton.setPosition(FEmenu.getPosition().x + inCM(1.5), FEmenu.getPosition().y + FEmenu.getSize().y - inCM(2));
    //add button text
    sf::Text FEaddButtonText;
    FEaddButtonText.setString("add");
    FEaddButtonText.setFont(calibri_normal);
    FEaddButtonText.setCharacterSize(font_resize(18));
    FEaddButtonText.setFillColor(sf::Color(62, 149, 164));
    FEaddButtonText.setPosition(FEaddButton.getPosition().x + FEaddButton.getSize().x / 2 - FEaddButtonText.getLocalBounds().width / 2, FEaddButton.getPosition().y);
    //cancel button
    sf::RectangleShape FEcancelButton(sf::Vector2f(inCM(3), inCM(0.8)));
    FEcancelButton.setFillColor(sf::Color(162, 219, 214));
    FEcancelButton.setPosition(FEmenu.getPosition().x + FEmenu.getSize().x - inCM(1.5) - FEcancelButton.getSize().x, FEaddButton.getPosition().y);
    //cancel button text
    sf::Text FEcancelButtonText;
    FEcancelButtonText.setString("cancel");
    FEcancelButtonText.setFont(calibri_normal);
    FEcancelButtonText.setCharacterSize(font_resize(18));
    FEcancelButtonText.setFillColor(sf::Color(62, 149, 164));
    FEcancelButtonText.setPosition(FEcancelButton.getPosition().x + FEcancelButton.getSize().x / 2 - FEcancelButtonText.getLocalBounds().width / 2, FEcancelButton.getPosition().y);

    //invalid menu
    bool invalidMenuOn = false;
    bool invalidMenu_m = false;
    sf::RectangleShape invalidFilter(sf::Vector2f(1600 - inCM(1.5), 900));
    invalidFilter.setFillColor(sf::Color(0, 0, 0, 50));
    invalidFilter.setPosition(inCM(1.5), 0);
    sf::RectangleShape invalidMenu(sf::Vector2f(inCM(10), inCM(6)));
    invalidMenu.setFillColor(sf::Color(255, 255, 255));
    invalidMenu.setOutlineThickness(inCM(0.2));
    invalidMenu.setOutlineColor(sf::Color(157, 215, 208));
    invalidMenu.setPosition(800 + inCM(1.5) - invalidMenu.getSize().x / 2, 450 - invalidMenu.getSize().y / 2);
    //invalid text
    sf::Text invalidText;
    invalidText.setString("!!! INVALID INPUT !!!");
    invalidText.setFillColor(sf::Color(62, 149, 164));
    invalidText.setCharacterSize(font_resize(20));
    invalidText.setFont(calibri_bold);
    invalidText.setPosition(invalidMenu.getPosition().x + invalidMenu.getSize().x / 2 - invalidText.getLocalBounds().width / 2, invalidMenu.getPosition().y + inCM(2));
    //close button
    sf::RectangleShape closeButton(sf::Vector2f(inCM(3), inCM(1)));
    closeButton.setFillColor(sf::Color(162, 219, 214));
    closeButton.setPosition(invalidMenu.getPosition().x + invalidMenu.getSize().x / 2 - closeButton.getSize().x / 2, invalidMenu.getPosition().y + invalidMenu.getSize().y - inCM(2));
    //close button text
    sf::Text closeButtonText;
    closeButtonText.setString("close");
    closeButtonText.setFont(calibri_normal);
    closeButtonText.setCharacterSize(font_resize(18));
    closeButtonText.setFillColor(sf::Color(62, 149, 164));
    closeButtonText.setPosition(closeButton.getPosition().x + closeButton.getSize().x / 2 - closeButtonText.getLocalBounds().width / 2, closeButton.getPosition().y + inCM(0.1));




    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            year2018[i][j] = new Day(start);
            start = start + 1440;
        }
    }
    for(int i=0;i<aweek;i++)
    {
        week[i] = new Day(today);
        today = today +1440;
    }
    cout << "done initializing year2018" << endl;
    cout << "going into adding FE into year2018" << endl;
    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            for(int k=0;k<FEBag.Bag.get_itemCount();k++)
            {
                string FEtime = FEBag.Bag[k]->GetstartTime().substr(0,8);
                string cur = year2018[i][j]->getToday().substr(0,8);
                if(FEtime==cur)
                    year2018[i][j]->addFixedEvent(FEBag.Bag[k]);
                else
                    continue;
            }
//            year2018[i][j]->showToday();
        }
    }
    cout << "finish adding FE into year2018" << endl;
    cout << "start adding mission into year2018" << endl;
    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            for(int k=0;k<MBag.Bag.get_itemCount();k++)
            {
                string Mtime = MBag.Bag[k]->GetstartTime().substr(0,8);
                string cur = year2018[i][j]->getToday().substr(0,8);
                if(Mtime==cur)
                    year2018[i][j]->RestoreMission(MBag.Bag[k]);
                else
                    continue;
            }
//            year2018[i][j]->showToday();

        }
    }
    cout << "finish adding Mission into year2018" << endl;
    for(int i=0;i<FEBag.Bag.get_itemCount();i++)
    {
        week[0]->addFixedEvent(FEBag.Bag[i]);
    }
    for(int i=0;i<MBag.Bag.get_itemCount();i++)
    {
        week[0]->RestoreMission(MBag.Bag[i]);
    }



    while (window.isOpen())
    {
        sf::Event event;


        while (passwordCorrect == false && window.pollEvent(event))
        {
            //"text input" event
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode >= 32 && event.text.unicode < 128)
                {
                    password += "*";
                    passwordStr += event.text.unicode;
                }
                else if (event.text.unicode == 8 && password.getSize() > 0)
                {
                    password.erase(password.getSize() - 1, password.getSize());
                    passwordStr.erase(passwordStr.length() - 1, passwordStr.length());
                }
            }
            userText.setString(password);

            //"enter press" event
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if(userpassword==passwordStr)
                {
                    cout << passwordStr << endl;
                    passwordCorrect = true;
                    page2 = true;
                    break;
                }

                else
                {
                    password = "";
                    passwordStr = "";
                }

            }

            //"window close" event
            if (event.type == sf::Event::Closed)
                window.close();
        }




        while (window.pollEvent(event))
        {
            //close window
            if(event.type == sf::Event::Closed)
                window.close();
            //type FM mission name
            if(missionNameBlockOn == true && event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == 8 && missionName.length() != 0)
                    missionName.pop_back();
                else if(event.text.unicode >= 32 && event.text.unicode < 128 && missionNameTyped.getLocalBounds().width < inCM(4.8))
                    missionName += static_cast<char>(event.text.unicode);
                missionNameTyped.setString(missionName);
                missionNameTyped.setPosition(missionNameBlock.getPosition().x + missionNameBlock.getSize().x / 2 - missionNameTyped.getLocalBounds().width / 2, missionNameBlock.getPosition().y + inCM(0.15));
            }
            //type FM category
            if(categoryBlockOn == true && event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == 8 && FMcategory.length() != 0)
                    FMcategory.pop_back();
                else if(event.text.unicode >= 32 && event.text.unicode < 128 && FMcategoryTyped.getLocalBounds().width < inCM(4.8))
                    FMcategory += static_cast<char>(event.text.unicode);
                FMcategoryTyped.setString(FMcategory);
                FMcategoryTyped.setPosition(categoryBlock.getPosition().x + categoryBlock.getSize().x / 2- FMcategoryTyped.getLocalBounds().width / 2, categoryBlock.getPosition().y + inCM(0.15));
            }
            //type FM deadline
            for(int i = 0; i < 5; i++)
            {
                if(deadlineBlockOn[i] == true && event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode == 8 && FMdeadline[i].length() != 0)
                        FMdeadline[i].pop_back();
                    else if(event.text.unicode >= 48 && event.text.unicode <= 57 && FMdeadlineTyped[i].getLocalBounds().width < inCM(0.9))
                        FMdeadline[i] += static_cast<char>(event.text.unicode);
                    FMdeadlineTyped[i].setString(FMdeadline[i]);
                    FMdeadlineTyped[i].setPosition(deadlineBlock[i].getPosition().x + deadlineBlock[i].getSize().x / 2 - FMdeadlineTyped[i].getLocalBounds().width / 2, deadlineBlock[i].getPosition().y + inCM(0.2));
                }
            }
            //type FM duration
            for(int i = 0; i < 2; i++)
            {
                if(FMdurationBlockOn[i] == true && event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode == 8 && duration[i].length() != 0)
                        duration[i].pop_back();
                    else if(event.text.unicode >= 48 && event.text.unicode <= 57 && durationTyped[i].getLocalBounds().width < inCM(2.3))
                        duration[i] += static_cast<char>(event.text.unicode);
                    durationTyped[i].setString(duration[i]);
                    durationTyped[i].setPosition(durationBlock[i].getPosition().x + durationBlock[i].getSize().x / 2 - durationTyped[i].getLocalBounds().width / 2, durationBlock[i].getPosition().y + inCM(0.15));
                }
            }
            //type FM max continuous duration
            for(int i = 0; i < 2; i++)
            {
                if(maxContiDurationBlockOn[i] == true && event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode == 8 && maxContiDuration[i].length() != 0)
                        maxContiDuration[i].pop_back();
                    else if(event.text.unicode >= 48 && event.text.unicode <= 57 && maxContiDurationTyped[i].getLocalBounds().width < inCM(2.3))
                        maxContiDuration[i] += static_cast<char>(event.text.unicode);
                    maxContiDurationTyped[i].setString(maxContiDuration[i]);
                    maxContiDurationTyped[i].setPosition(maxContiDurationBlock[i].getPosition().x + maxContiDurationBlock[i].getSize().x / 2 - maxContiDurationTyped[i].getLocalBounds().width / 2, maxContiDurationBlock[i].getPosition().y + inCM(0.15));
                }
            }
            //type priority
            if(priorityBlockOn == true && event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == 8 && priority.length() != 0)
                    priority.pop_back();
                else if(event.text.unicode >= 32 && event.text.unicode < 128 && priorityTyped.getLocalBounds().width < inCM(4.8))
                    priority += static_cast<char>(event.text.unicode);
                priorityTyped.setString(priority);
                priorityTyped.setPosition(priorityBlock.getPosition().x + priorityBlock.getSize().x / 2- priorityTyped.getLocalBounds().width / 2, priorityBlock.getPosition().y + inCM(0.15));

            }
            //type FE event name
            if(eventNameBlockOn == true && event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == 8 && eventName.length() != 0)
                    eventName.pop_back();
                else if(event.text.unicode >= 32 && event.text.unicode < 128 && eventNameTyped.getLocalBounds().width < inCM(4.8))
                    eventName += static_cast<char>(event.text.unicode);
                eventNameTyped.setString(eventName);
                eventNameTyped.setPosition(eventNameBlock.getPosition().x + eventNameBlock.getSize().x / 2 - eventNameTyped.getLocalBounds().width / 2, eventNameBlock.getPosition().y + inCM(0.15));
            }
            //type FE category
            if(FEcategoryBlockOn == true && event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == 8 && FEcategory.length() != 0)
                    FEcategory.pop_back();
                else if(event.text.unicode >= 32 && event.text.unicode < 128 && FEcategoryTyped.getLocalBounds().width < inCM(4.8))
                    FEcategory += static_cast<char>(event.text.unicode);
                FEcategoryTyped.setString(FEcategory);
                FEcategoryTyped.setPosition(FEcategoryBlock.getPosition().x + FEcategoryBlock.getSize().x / 2 - FEcategoryTyped.getLocalBounds().width / 2, FEcategoryBlock.getPosition().y + inCM(0.15));
            }
            //type FE start time
            for(int i = 0; i < 5; i++)
            {
                if(FEstartTimeBlockOn[i] == true && event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode == 8 && FEstartTime[i].length() != 0)
                        FEstartTime[i].pop_back();
                    else if(event.text.unicode >= 48 && event.text.unicode <= 57 && FEstartTimeTyped[i].getLocalBounds().width < inCM(0.9))
                        FEstartTime[i] += static_cast<char>(event.text.unicode);
                    FEstartTimeTyped[i].setString(FEstartTime[i]);
                    FEstartTimeTyped[i].setPosition(FEstartTimeBlock[i].getPosition().x + FEstartTimeBlock[i].getSize().x / 2 - FEstartTimeTyped[i].getLocalBounds().width / 2, FEstartTimeBlock[i].getPosition().y + inCM(0.2));
                }
            }
            //type FE end time
            for(int i = 0; i < 5; i++)
            {
                if(FEendTimeBlockOn[i] == true && event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode == 8 && FEendTime[i].length() != 0)
                        FEendTime[i].pop_back();
                    else if(event.text.unicode >= 48 && event.text.unicode <= 57 && FEendTimeTyped[i].getLocalBounds().width < inCM(0.9))
                        FEendTime[i] += static_cast<char>(event.text.unicode);
                    FEendTimeTyped[i].setString(FEendTime[i]);
                    FEendTimeTyped[i].setPosition(FEendTimeBlock[i].getPosition().x + FEendTimeBlock[i].getSize().x / 2 - FEendTimeTyped[i].getLocalBounds().width / 2, FEendTimeBlock[i].getPosition().y + inCM(0.15));
                }
            }

        }


        window.clear(sf::Color::Black);
        if(passwordCorrect == false)
        {
            window.draw(shapeOut);
            window.draw(shape);
            window.draw(line_hour);
            window.draw(line_minute);
            window.draw(center);
            window.draw(text);
            window.draw(text2);
            window.draw(text3);

            // draw loginbar
            window.draw(downRectangle);
            downRectangle.setPosition(0, toPx(14.6 - 1.5));

            // draw login introduction text
            if(passwordStr == "")
                window.draw(loginIntroduction);
            loginIntroduction.setPosition(toPx(3.04), toPx(15.10 - 1.5));

            // draw password
            window.draw(userText);
            userText.setPosition(loginIntroduction.getPosition() + sf::Vector2f(0, inCM(0.15)));
        }
        if(page2)
        {
            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

            //invalid menu on///////////////////////////////////////////////////////////////////////////////
            if(invalidMenuOn == true)
            {
                if(closeButton.getPosition().x <= mousePosition.x && mousePosition.x <= (closeButton.getPosition().x + closeButton.getSize().x) && closeButton.getPosition().y <= mousePosition.y && mousePosition.y <= (closeButton.getPosition().y + closeButton.getSize().y))
                {
                    closeButton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        invalidMenuOn = false;
                        if(invalidMenu_m == true)
                        {
                            FMmenuOn = true;
                            FEmenuOn = false;
                        }
                        else if(invalidMenu_m == false)
                        {
                            FEmenuOn = true;
                            FMmenuOn = false;
                        }
                    }
                }
                else
                    closeButton.setFillColor(sf::Color(162, 219, 214));

            }
            //flexible mission menu on///////////////////////////////////////////////////////////////////////
            if(FMmenuOn == true)
            {
               //mission name
                if(missionNameBlock.getPosition().x <= mousePosition.x && mousePosition.x <= (missionNameBlock.getPosition().x + missionNameBlock.getSize().x) && missionNameBlock.getPosition().y <= mousePosition.y && mousePosition.y <= (missionNameBlock.getPosition().y + missionNameBlock.getSize().y))
                {
                    missionNameBlock.setOutlineThickness(inCM(0.05));
                    missionNameBlock.setOutlineColor(sf::Color(0, 0, 0, 50));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        missionNameBlockOn = true;
                        categoryBlockOn = false;
                        for(int j = 0; j < 5; j++)
                            deadlineBlockOn[j] = false;
                        for(int j = 0; j < 2; j++)
                            FMdurationBlockOn[j] = false;
                        for(int j = 0; j < 2; j++)
                            maxContiDurationBlockOn[j] = false;
                        priorityBlockOn = false;
                    }
                }
                else
                    missionNameBlock.setOutlineThickness(0);

                //category
                if(categoryBlock.getPosition().x <= mousePosition.x && mousePosition.x <= (categoryBlock.getPosition().x + categoryBlock.getSize().x) && categoryBlock.getPosition().y <= mousePosition.y && mousePosition.y <= (categoryBlock.getPosition().y + categoryBlock.getSize().y))
                {
                    categoryBlock.setOutlineThickness(inCM(0.05));
                    categoryBlock.setOutlineColor(sf::Color(0, 0, 0, 50));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        categoryBlockOn = true;
                        missionNameBlockOn = false;
                        for(int j = 0; j < 5; j++)
                            deadlineBlockOn[j] = false;
                        for(int j = 0; j < 2; j++)
                            FMdurationBlockOn[j] = false;
                        for(int j = 0; j < 2; j++)
                            maxContiDurationBlockOn[j] = false;
                        priorityBlockOn = false;
                    }
                }
                else
                    categoryBlock.setOutlineThickness(0);

                //deadline
                for(int i = 0; i < 5; i++)
                {
                    if(deadlineBlock[i].getPosition().x <= mousePosition.x && mousePosition.x <= (deadlineBlock[i].getPosition().x + deadlineBlock[i].getSize().x) && deadlineBlock[i].getPosition().y <= mousePosition.y && mousePosition.y <= (deadlineBlock[i].getPosition().y + deadlineBlock[i].getSize().y))
                    {
                        deadlineBlock[i].setOutlineThickness(inCM(0.03));
                        deadlineBlock[i].setOutlineColor(sf::Color(0, 0, 0, 50));
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            for(int j = 0; j < 5; j++)
                                deadlineBlockOn[j] = false;
                            deadlineBlockOn[i] = true;
                            categoryBlockOn = false;
                            missionNameBlockOn = false;
                            for(int j = 0; j < 2; j++)
                                FMdurationBlockOn[j] = false;
                            for(int j = 0; j < 2; j++)
                                maxContiDurationBlockOn[j] = false;
                            priorityBlockOn = false;
                        }
                    }
                    else
                        deadlineBlock[i].setOutlineThickness(0);
                }

                //duration
                for(int i = 0; i < 2; i++)
                {
                    if(durationBlock[i].getPosition().x <= mousePosition.x && mousePosition.x <= (durationBlock[i].getPosition().x + durationBlock[i].getSize().x) && durationBlock[i].getPosition().y <= mousePosition.y && mousePosition.y <= (durationBlock[i].getPosition().y + durationBlock[i].getSize().y))
                    {
                        durationBlock[i].setOutlineThickness(inCM(0.03));
                        durationBlock[i].setOutlineColor(sf::Color(0, 0, 0, 50));
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            for(int j = 0; j < 2; j++)
                                FMdurationBlockOn[j] = false;
                            FMdurationBlockOn[i] = true;
                            missionNameBlockOn = false;
                            categoryBlockOn = false;
                            for(int j = 0; j < 5; j++)
                                deadlineBlockOn[j] = false;
                            for(int j = 0; j < 2; j++)
                                maxContiDurationBlockOn[j] = false;
                            priorityBlockOn = false;
                        }
                    }
                    else
                        durationBlock[i].setOutlineThickness(0);
                }

                //max continuous duration
                for(int i = 0; i < 2; i++)
                {
                    if(maxContiDurationBlock[i].getPosition().x <= mousePosition.x && mousePosition.x <= (maxContiDurationBlock[i].getPosition().x + maxContiDurationBlock[i].getSize().x) && maxContiDurationBlock[i].getPosition().y <= mousePosition.y && mousePosition.y <= (maxContiDurationBlock[i].getPosition().y + maxContiDurationBlock[i].getSize().y))
                    {
                        maxContiDurationBlock[i].setOutlineThickness(inCM(0.03));
                        maxContiDurationBlock[i].setOutlineColor(sf::Color(0, 0, 0, 50));
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            for(int j = 0; j < 2; j++)
                                maxContiDurationBlockOn[j] = false;
                            maxContiDurationBlockOn[i] = true;
                            missionNameBlockOn = false;
                            categoryBlockOn = false;
                            for(int j = 0; j < 5; j++)
                                deadlineBlockOn[j] = false;
                            for(int j = 0; j < 2; j++)
                                FMdurationBlockOn[j] = false;
                            priorityBlockOn = false;
                        }
                    }
                    else
                        maxContiDurationBlock[i].setOutlineThickness(0);
                }

                //priority
                if(priorityBlock.getPosition().x <= mousePosition.x && mousePosition.x <= (priorityBlock.getPosition().x + priorityBlock.getSize().x) && priorityBlock.getPosition().y <= mousePosition.y && mousePosition.y <= (priorityBlock.getPosition().y + priorityBlock.getSize().y))
                {
                    priorityBlock.setOutlineThickness(inCM(0.05));
                    priorityBlock.setOutlineColor(sf::Color(0, 0, 0, 50));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        priorityBlockOn = true;
                        missionNameBlockOn = false;
                        categoryBlockOn = false;
                        for(int j = 0; j < 5; j++)
                            deadlineBlockOn[j] = false;
                        for(int j = 0; j < 2; j++)
                            FMdurationBlockOn[j] = false;
                        for(int j = 0; j < 2; j++)
                            maxContiDurationBlockOn[j] = false;
                    }
                }
                else
                    priorityBlock.setOutlineThickness(0);

                //add
                if(FMaddButton.getPosition().x <= mousePosition.x && mousePosition.x <= (FMaddButton.getPosition().x + FMaddButton.getSize().x) && FMaddButton.getPosition().y <= mousePosition.y && mousePosition.y <= (FMaddButton.getPosition().y + FMaddButton.getSize().y))
                {
                    FMaddButton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        bool invalid = false;
                        //check if invalid
                        if(missionName == "" || FMcategory == "" || priority == "")
                            invalid = true;
                        for(int i = 0; i < 5; i++)
                            if(FMdeadline[i] == "")
                                invalid = true;
                        for(int i = 0; i < 2; i++)
                            if(duration[i] == "" || maxContiDuration[i] == "")
                                invalid = true;
                        if(invalid == false)
                        {
                            int year = stoi(FMdeadline[0]);
                            int month = stoi(FMdeadline[1]);
                            int day = stoi(FMdeadline[2]);
                            int hour[3];
                            hour[0] = stoi(FMdeadline[3]);
                            hour[1] = stoi(duration[0]);
                            hour[2] = stoi(maxContiDuration[0]);
                            int minute[3];
                            minute[0] = stoi(FMdeadline[4]);
                            minute[1] = stoi(duration[1]);
                            minute[2] = stoi(maxContiDuration[1]);
                            int pri = stoi(priority);

                            if(!(year == 2018 || year == 2019))
                                invalid = true;
                            if(!(1 <= month && month <= 12))
                                invalid = true;
                            switch(month)
                            {
                                case 1:
                                case 3:
                                case 5:
                                case 7:
                                case 8:
                                case 10:
                                case 12:
                                    if(!(1 <= day && day <= 31))
                                        invalid = true;
                                    break;
                                case 4:
                                case 6:
                                case 9:
                                case 11:
                                    if(!(1 <= day && day <= 30))
                                        invalid = true;
                                    break;
                                case 2:
                                    if(year % 4 != 0 && !(1 <= day && day <= 28))
                                        invalid = true;
                                    else if(year % 4 == 0 && !(1 <= day && day <= 29))
                                        invalid = true;
                            }
                            for(int i = 0; i < 3; i++)
                                if(!(0 <= hour[i] && hour[i] <= 23))
                                    invalid = true;
                            for(int i = 0; i < 3; i++)
                                if(!(0 <= minute[i] && minute[i] <= 59))
                                    invalid = true;
                            if(!(1 <= pri && pri <= 10))
                                invalid = true;
                        }

                        if(invalid == true)
                        {
                            invalidMenuOn = true;
                            invalidMenu_m = true;
                            FMmenuOn = false;
                        }

                        //add FM
                        if(invalid == false)
                        {
                            string MissionName = missionName;
                            string Deadline;
                            for(int i=0;i<5;i++)
                                Deadline += FMdeadline[i];

                            string category = missionName;
                            string graph = FMcategory;

                            cout << "DDL: " << Deadline << endl;

                            int Priority = stoi(priority);
                            double Duration = stoi(duration[0])*60 + stoi(duration[1]);
                            double thresh =  stoi(maxContiDuration[0])*60 + stoi(maxContiDuration[1]);
                            OurTime ddl(Deadline);

                            double parts = ceil(Duration/thresh);

                            for(int i=0;i<parts;i++)
                            {
                                Mission *a;
                                if(thresh < Duration)
                                    a = new Mission(MissionName,graph,category,i,parts,Priority,ddl,thresh);
                                else
                                    a = new Mission(MissionName,graph,category,i,parts,Priority,ddl,Duration);
                                MBag.Bag.add(a);
                                Duration -= thresh;
                            }
                            cout << "DDL: " << Deadline << endl;

                            OurTime doodle;
                            doodle.Current();
                            string cur = doodle.getTimeStr().substr(0,8);
                            int weekN,dayN;
                            for(int i=0;i<weeks;i++)
                            {
                                for(int j=0;j<aweek;j++)
                                {
                                    string hello = year2018[i][j]->getToday().substr(0,8);
                                    if(hello==cur)
                                    {
                                        weekN = i;
                                        dayN = j;
                                        break;
                                    }
                                    else
                                        continue;
                                }
                            }
                            cout << "during deleting non fixed event" << endl;
                            for(int i=weekN;i<weeks;i++)
                            {
                                for(int j=dayN;j<aweek;j++)
                                {
                                    year2018[i][j]->deleteNonFixedEvent();
                                }
                            }
                            cout << "ended deleting non fixed event" << endl;
                            for(int i=weekN;i<weeks;i++)
                            {
                                for(int j=dayN;j<aweek;j++)
                                {
                                    year2018[i][j]->showToday();
                                }
                            }
                            bool eventNotAbleToAdd = false;
                            for(int i=weekN;i<weeks;i++)
                            {
                                for(int j=dayN;j<aweek;j++)
                                {
        //                            cout << "i:" << i << " j: " << j << endl;
        //                            year2018[i][j]->unCheck();
                                    while(1)
                                    {
                                        int freeTime = year2018[i][j]->getDuration();
                                        OurTime timeP = year2018[i][j]->getFreeTime();
                                        if(freeTime==-1)
                                            break;

                                        MissionBag* chosen = KnapSack(MBag,freeTime);
                                        for(int i=0;i<chosen->Bag.get_itemCount();i++)
                                        {
                                            OurTime DDL(chosen->Bag[i]->GetMdeadline());
                                            if(timeP - DDL >0)
                                            {
                                                string name = chosen->Bag[i]->GetName();
                                                int ind = stoi(chosen->Bag[i]->GetMindex());
                                                int tCnt = stoi(chosen->Bag[i]->GetMtotalCnt());
                                                chosen->Bag.remove(name,ind,tCnt);
                                                MBag.Bag.remove(name,ind,tCnt);
                                                eventNotAbleToAdd = true;
                                            }
                                        }

        //                                cout <<"chosen item count: " <<  chosen->Bag.get_itemCount() << endl;
                                        Event** fillin = new Event*[chosen->Bag.get_itemCount()];
                                        for(int k=0;k<chosen->Bag.get_itemCount();k++)
                                        {
                                            fillin[k] = chosen->Bag[k];
                                        }
        //                                cout << "start filling Time" << endl;
                                        year2018[i][j]->fillTime(fillin,chosen->Bag.get_itemCount());
                                        year2018[i][j]->showToday();
        //                                cout << "done filling Time" << endl;
        //                                cout << "start updating Time" << endl;
                                        for(int k=0;k<chosen->Bag.get_itemCount();k++)
                                        {
                                            MBag.Bag.remove(fillin[k]->GetName(),stoi(fillin[k]->GetMindex()),stoi(fillin[k]->GetMtotalCnt()));
                                            MBag.Bag.add(fillin[k]);
                                        }
        //                                cout << "done updating MBag" << endl;

                                    }
                                    year2018[i][j]->unCheck();
                                }
                            }
                            if(eventNotAbleToAdd)
                                cout << "Not Enough Time To Schedule Your Missions\nTry To Spend Less Time on Sleeping or Eating" << endl;
                            MBag.Bag.printBag();

                            MBag.SaveFile(MissionLocation);

                            cout << "DDL: " << Deadline << endl;

                        }
                    }
                }
                else
                    FMaddButton.setFillColor(sf::Color(162, 219, 214));

                //cancel
                if(FMcancelButton.getPosition().x <= mousePosition.x && mousePosition.x <= (FMcancelButton.getPosition().x + FMcancelButton.getSize().x) && FMcancelButton.getPosition().y <= mousePosition.y && mousePosition.y <= (FMcancelButton.getPosition().y + FMcancelButton.getSize().y))
                {
                    FMcancelButton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        selectEventMenuOn = true;
                        FMmenuOn = false;
                        missionNameBlockOn = false;
                        categoryBlockOn = false;
                        missionName = "";
                        missionNameTyped.setString(missionName);
                        FMcategory = "";
                        FMcategoryTyped.setString(FMcategory);
                        for(int i = 0; i < 5; i++)
                        {
                            deadlineBlockOn[i] = false;
                            FMdeadline[i] = "";
                            FMdeadlineTyped[i].setString(FMdeadline[i]);
                        }
                        for(int i = 0; i < 2; i++)
                        {
                            FMdurationBlockOn[i] = false;
                            duration[i] = "";
                            durationTyped[i].setString(duration[i]);
                            maxContiDurationBlockOn[i] = false;
                            maxContiDuration[i] = "";
                            maxContiDurationTyped[i].setString(maxContiDuration[i]);
                        }
                        priorityBlockOn = false;
                        priority = "";
                        priorityTyped.setString(priority);
                    }
                }
                else
                    FMcancelButton.setFillColor(sf::Color(162, 219, 214));
            }

            //fixed time event menu on
            if(FEmenuOn == true)
            {
                //event name
                if(eventNameBlock.getPosition().x <= mousePosition.x && mousePosition.x <= (eventNameBlock.getPosition().x + eventNameBlock.getSize().x) && eventNameBlock.getPosition().y <= mousePosition.y && mousePosition.y <= (eventNameBlock.getPosition().y + eventNameBlock.getSize().y))
                {
                    eventNameBlock.setOutlineThickness(inCM(0.05));
                    eventNameBlock.setOutlineColor(sf::Color(0, 0, 0, 50));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        eventNameBlockOn = true;
                        FEcategoryBlockOn = false;
                        for(int i = 0; i < 5; i++)
                            FEstartTimeBlockOn[i] = false;
                        for(int i = 0; i < 5; i++)
                            FEendTimeBlockOn[i] = false;
                    }
                }
                else
                    eventNameBlock.setOutlineThickness(0);

                //category
                if(FEcategoryBlock.getPosition().x <= mousePosition.x && mousePosition.x <= (FEcategoryBlock.getPosition().x + FEcategoryBlock.getSize().x) && FEcategoryBlock.getPosition().y <= mousePosition.y && mousePosition.y <= (FEcategoryBlock.getPosition().y + FEcategoryBlock.getSize().y))
                {
                    FEcategoryBlock.setOutlineThickness(inCM(0.05));
                    FEcategoryBlock.setOutlineColor(sf::Color(0, 0, 0, 50));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        FEcategoryBlockOn = true;
                        eventNameBlockOn = false;
                        for(int i = 0; i < 5; i++)
                            FEstartTimeBlockOn[i] = false;
                        for(int i = 0; i < 5; i++)
                            FEendTimeBlockOn[i] = false;
                    }
                }
                else
                    FEcategoryBlock.setOutlineThickness(0);

                //start time
                for(int i = 0; i < 5; i++)
                {
                    if(FEstartTimeBlock[i].getPosition().x <= mousePosition.x && mousePosition.x <= (FEstartTimeBlock[i].getPosition().x + FEstartTimeBlock[i].getSize().x) && FEstartTimeBlock[i].getPosition().y <= mousePosition.y && mousePosition.y <= (FEstartTimeBlock[i].getPosition().y + FEstartTimeBlock[i].getSize().y))
                    {
                        FEstartTimeBlock[i].setOutlineThickness(inCM(0.03));
                        FEstartTimeBlock[i].setOutlineColor(sf::Color(0, 0, 0, 50));
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            for(int i = 0; i < 5; i++)
                                FEstartTimeBlockOn[i] = false;
                            FEstartTimeBlockOn[i] = true;
                            FEcategoryBlockOn = false;
                            eventNameBlockOn = false;
                            for(int i = 0; i < 5; i++)
                                FEendTimeBlockOn[i] = false;
                        }
                    }
                    else
                        FEstartTimeBlock[i].setOutlineThickness(0);
                }

                //end time
                for(int i = 0; i < 5; i++)
                {
                    if(FEendTimeBlock[i].getPosition().x <= mousePosition.x && mousePosition.x <= (FEendTimeBlock[i].getPosition().x + FEendTimeBlock[i].getSize().x) && FEendTimeBlock[i].getPosition().y <= mousePosition.y && mousePosition.y <= (FEendTimeBlock[i].getPosition().y + FEendTimeBlock[i].getSize().y))
                    {
                        FEendTimeBlock[i].setOutlineThickness(inCM(0.03));
                        FEendTimeBlock[i].setOutlineColor(sf::Color(0, 0, 0, 50));
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            for(int i = 0; i < 5; i++)
                                FEendTimeBlockOn[i] = false;
                            FEendTimeBlockOn[i] = true;
                            FEcategoryBlockOn = false;
                            eventNameBlockOn = false;
                            for(int i = 0; i < 5; i++)
                                FEstartTimeBlockOn[i] = false;
                        }
                    }
                    else
                        FEendTimeBlock[i].setOutlineThickness(0);
                }

                //add
                if(FEaddButton.getPosition().x <= mousePosition.x && mousePosition.x <= (FEaddButton.getPosition().x + FEaddButton.getSize().x) && FEaddButton.getPosition().y <= mousePosition.y && mousePosition.y <= (FEaddButton.getPosition().y + FEaddButton.getSize().y))
                {
                    FEaddButton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        //check if invalid
                        bool invalid = false;
                        if(eventName == "" || FEcategory == "")
                            invalid = true;
                        for(int i = 0; i < 5; i++)
                            if(FEstartTime[i] == "" || FEendTime[i] == "")
                                invalid = true;
                        if(invalid == false)
                        {
                            int year[2] = {0, 0}, month[2] = {0, 0}, day[2] = {0, 0}, hour[2] = {0, 0}, minute[2] = {0, 0};
                            year[0] = stoi(FEstartTime[0]);
                            year[1] = stoi(FEendTime[0]);
                            month[0] = stoi(FEstartTime[1]);
                            month[1] = stoi(FEendTime[1]);
                            day[0] = stoi(FEstartTime[2]);
                            day[1] = stoi(FEendTime[2]);
                            hour[0] = stoi(FEstartTime[3]);
                            hour[1] = stoi(FEendTime[3]);
                            minute[0] = stoi(FEstartTime[4]);
                            minute[1] = stoi(FEendTime[4]);

                            for(int i = 0; i < 2; i++)
                            {
                                if(!(year[i] == 2018 || year[i] == 2019))
                                    invalid = true;
                                else if(!(1 <= month[i] && month[i] <= 12))
                                    invalid = true;
                                switch(month[i])
                                {
                                    case 1:
                                    case 3:
                                    case 5:
                                    case 7:
                                    case 8:
                                    case 10:
                                    case 12:
                                        if(!(1 <= day[i] && day[i] <= 31))
                                            invalid = true;
                                        break;
                                    case 4:
                                    case 6:
                                    case 9:
                                    case 11:
                                        if(!(1 <= day[i] && day[i] <= 30))
                                            invalid = true;
                                        break;
                                    case 2:
                                        if(year[i] % 4 != 0 && !(1 <= day[i] && day[i] <= 28))
                                            invalid = true;
                                        else if(year[i] % 4 == 0 && !(1 <= day[i] && day[i] <= 29))
                                            invalid = true;
                                }
                                if(!(0 <= hour[i] && hour[i] <= 23))
                                    invalid = true;
                                else if(!(0 <= minute[i] && minute[i] <= 59))
                                    invalid = true;
                            }
                            //end time before start time
                            if(year[0] > year[1])
                                invalid = true;
                            else if(year[0] == year[1])
                            {
                                if(month[0] > month[1])
                                    invalid = true;
                                else if(month[0] == month[1])
                                {
                                    if(day[0] > day[1])
                                        invalid = true;
                                    else if(day[0] == day[1])
                                    {
                                        if(hour[0] > hour[1])
                                            invalid = true;
                                        else if(hour[0] == hour[1])
                                        {
                                            if(minute[0] >= minute[1])
                                                invalid = true;
                                        }
                                    }
                                }
                            }
                        }
                        //invalid input
                        if(invalid == true)
                        {
                            invalidMenuOn = true;
                            invalidMenu_m = false;
                            FEmenuOn = false;
                        }
                        //add event
                        if(invalid == false)
                        {

                            string fixedEventName = eventName;
                            string startTime;
                            for(int i=0;i<5;i++)
                                startTime += FEstartTime[i];
                            string endTime;
                            for(int i=0;i<5;i++)
                                endTime += FEendTime[i];
                            string category = FEcategory;
                            int duration;


                            OurTime startT(startTime);


                            OurTime endT(endTime);

                            duration = endT - startT;
                            FixedEvent *one = new FixedEvent(fixedEventName,category,startT,endT,duration);
                            string moveto = startTime.substr(0,8);
                            for(int i=0;i<weeks;i++)
                            {
                                for(int j=0;j<aweek;j++)
                                {
                                    string TD = year2018[i][j]->getToday().substr(0,8);
                                    if(TD==moveto)
                                    {
                                        year2018[i][j]->addFixedEvent(one);
                                        cout << TD << endl;
                                    }

                                }
                            }
                            FEBag.Bag.add(one);
                            FEBag.SaveFile(FixedLocation);
                            system("pause");

                        }
                    }
                }
                else
                    FEaddButton.setFillColor(sf::Color(162, 219, 214));

                //cancel
                if(FEcancelButton.getPosition().x <= mousePosition.x && mousePosition.x <= (FEcancelButton.getPosition().x + FEcancelButton.getSize().x) && FEcancelButton.getPosition().y <= mousePosition.y && mousePosition.y <= (FEcancelButton.getPosition().y + FEcancelButton.getSize().y))
                {
                    FEcancelButton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        selectEventMenuOn = true;
                        FEmenuOn = false;
                        eventNameBlockOn = false;
                        FEcategoryBlockOn = false;
                        eventName = "";
                        eventNameTyped.setString(eventName);
                        FEcategory = "";
                        FEcategoryTyped.setString(FEcategory);
                        for(int i = 0; i < 5; i++)
                        {
                            FEstartTimeBlockOn[i] = false;
                            FEendTimeBlockOn[i] = false;
                            FEstartTime[i] = "";
                            FEendTime[i] = "";
                            FEstartTimeTyped[i].setString(FEstartTime[i]);
                            FEendTimeTyped[i].setString(FEendTime[i]);
                        }
                    }
                }
                else
                    FEcancelButton.setFillColor(sf::Color(162, 219, 214));
            }


            //select event menu on//////////////////////////////////////////////////////////////////////////////
            if(selectEventMenuOn == true)
            {
                //flexible time mission
                if(FMbutton.getPosition().x <= mousePosition.x && mousePosition.x <= FMbutton.getPosition().x + FMbutton.getSize().x && FMbutton.getPosition().y <= mousePosition.y && mousePosition.y < FMbutton.getPosition().y + cancelButton.getSize().y)
                {
                    FMbutton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        FMmenuOn = true;
                        FEmenuOn = false;
                        selectEventMenuOn = false;
                    }
                }
                else
                    FMbutton.setFillColor(sf::Color(162, 219, 214));

                //fixed time event
                if(FEbutton.getPosition().x <= mousePosition.x && mousePosition.x <= FEbutton.getPosition().x + FEbutton.getSize().x && FEbutton.getPosition().y <= mousePosition.y && mousePosition.y < FEbutton.getPosition().y + cancelButton.getSize().y)
                {
                    FEbutton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        FEmenuOn = true;
                        FMmenuOn = false;
                        selectEventMenuOn = false;
                    }
                }
                else
                    FEbutton.setFillColor(sf::Color(162, 219, 214));

                //cancel
                if(cancelButton.getPosition().x <= mousePosition.x && mousePosition.x <= cancelButton.getPosition().x + cancelButton.getSize().x && cancelButton.getPosition().y <= mousePosition.y && mousePosition.y < cancelButton.getPosition().y + cancelButton.getSize().y)
                {
                    cancelButton.setFillColor(sf::Color(197, 233, 230));
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        filterOn = false;
                        selectEventMenuOn = false;
                    }
                }
                else
                    cancelButton.setFillColor(sf::Color(162, 219, 214));
            }

            //add button/////////////////////////////////////////////////////////////////////////////////////
            float distanceToAdd_o = sqrt(pow(mousePosition.x - inCM(0.75), 2) + pow(mousePosition.y - inCM(9.5), 2));
            if(distanceToAdd_o <= inCM(0.75))
            {
                addButton.setOutlineThickness(15);
                addButton.setOutlineColor(sf::Color(255, 255, 255, 80));
                //button clicked
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    filterOn = true;
                    selectEventMenuOn = true;
                }
            }
            else
                addButton.setOutlineThickness(0);

            //schedule button/////////////////////////////////////////////////////////////////////////////
            if(distanceToAdd_o > inCM(0.75) && mousePosition.x < inCM(1.5) && mousePosition.y < inCM(9.5))
                scheduleButton.setFillColor(sf::Color(116, 190, 202));
            else
                scheduleButton.setFillColor(sf::Color(86, 175, 191));

            //dashboard button//////////////////////////////////////////////////////////////////////////////
            if(distanceToAdd_o > inCM(0.75) && mousePosition.x < inCM(1.5) && mousePosition.y > inCM(9.5))
                dashboardButton.setFillColor(sf::Color(13, 100, 179));
            else
                dashboardButton.setFillColor(sf::Color(11, 83, 149));
            //left page button/////////////////////////////////////////////////////////////////////////////////
            float distanceToLeft_o = sqrt(pow(mousePosition.x - leftButton.getPosition().x - leftButton.getRadius(), 2) + pow(mousePosition.y - leftButton.getPosition().y - leftButton.getRadius(), 2));
            if(distanceToLeft_o < inCM(0.25))
                leftButton.setFillColor(sf::Color(185, 223, 229));
            else
                leftButton.setFillColor(sf::Color(86, 175, 191));
            //right page button////////////////////////////////////////////////////////////////////////////////
            float distanceToRight_o = sqrt(pow(mousePosition.x - rightButton.getPosition().x - rightButton.getRadius(), 2) + pow(mousePosition.y - rightButton.getPosition().y - rightButton.getRadius(), 2));
            if(distanceToRight_o < inCM(0.25))
                rightButton.setFillColor(sf::Color(185, 223, 229));
            else
                rightButton.setFillColor(sf::Color(86, 175, 191));

            //draw text and shapes///////////////////////////////////////////////////////////////////////////////
            window.draw(scheduleButton);
            window.draw(scheduleText);
            window.draw(dashboardButton);
            window.draw(dashboardText);
            window.draw(title);
            for(int i = 0; i < 8; i++) //vertical line
                window.draw(v_linePtr[i]);
            for(int i = 0; i < 5; i++) //horizontal line
                window.draw(h_linePtr[i]);
            for(int i = 0; i < 7; i++) //date text
                window.draw(date[i]);
            for(int i = 0; i < 5; i++) //time text
                window.draw(time[i]);
            window.draw(leftButton);
            window.draw(rightButton);
            if(filterOn == true)
                window.draw(filter);
            window.draw(addButton);
            window.draw(h_plus);
            window.draw(v_plus);
            if(selectEventMenuOn == true)
            {
                window.draw(selectEventMenu);
                window.draw(selectEventMenuTitle);
                window.draw(FMbutton);
                window.draw(FMbuttonText);
                window.draw(FEbutton);
                window.draw(FEbuttonText);
                window.draw(cancelButton);
                window.draw(cancelButtonText);
            }
            if(FMmenuOn == true)
            {
                window.draw(FMmenu);
                window.draw(FMmenuTitle);
                window.draw(missionNameText);
                if(missionNameBlockOn == true)
                    missionNameBlock.setFillColor(sf::Color(200, 200, 200));
                else
                    missionNameBlock.setFillColor(sf::Color(217, 217, 217));
                window.draw(missionNameBlock);
                window.draw(categoryText);
                if(categoryBlockOn == true)
                    categoryBlock.setFillColor(sf::Color(200, 200, 200));
                else
                    categoryBlock.setFillColor(sf::Color(217, 217, 217));
                window.draw(categoryBlock);
                window.draw(deadlineText);
                for(int i = 0; i < 5; i++)
                {
                    if(deadlineBlockOn[i] == true)
                        deadlineBlock[i].setFillColor(sf::Color(200, 200, 200));
                    else
                        deadlineBlock[i].setFillColor(sf::Color(217, 217, 217));
                    window.draw(deadlineBlock[i]);
                }
                for(int i = 0; i < 5; i++)
                    if(!(deadlineBlockOn[i] == true || (deadlineBlockOn[i] == false && FMdeadline[i] != "")))
                        window.draw(deadlineBlockText[i]);
                window.draw(durationText);
                for(int i = 0; i < 2; i++)
                {
                    if(FMdurationBlockOn[i] == true)
                        durationBlock[i].setFillColor(sf::Color(200, 200, 200));
                    else
                        durationBlock[i].setFillColor(sf::Color(217, 217, 217));
                    window.draw(durationBlock[i]);
                }
                for(int i = 0; i < 2; i++)
                    if(!(FMdurationBlockOn[i] == true || (FMdurationBlockOn[i] == false && duration[i] != "")))
                        window.draw(durationBlockText[i]);
                window.draw(maxContiDurationText);
                for(int i = 0; i < 2; i++)
                {
                    if(maxContiDurationBlockOn[i] == true)
                        maxContiDurationBlock[i].setFillColor(sf::Color(200, 200, 200));
                    else
                        maxContiDurationBlock[i].setFillColor(sf::Color(217, 217, 217));
                    window.draw(maxContiDurationBlock[i]);
                }
                for(int i = 0; i < 2; i++)
                    if(!(maxContiDurationBlockOn[i] == true || (maxContiDurationBlockOn[i] == false && maxContiDuration[i] != "")))
                        window.draw(maxContiDurationBlockText[i]);
                window.draw(priorityText);
                if(priorityBlockOn == true)
                    priorityBlock.setFillColor(sf::Color(200, 200, 200));
                else
                    priorityBlock.setFillColor(sf::Color(217, 217, 217));
                window.draw(priorityBlock);
                if(!(priorityBlockOn == true || (priorityBlockOn == false && priority != "")))
                    window.draw(priorityBlockText);
                window.draw(FMaddButton);
                window.draw(FMaddButtonText);
                window.draw(FMcancelButton);
                window.draw(FMcancelButtonText);
                window.draw(missionNameTyped);
                window.draw(FMcategoryTyped);
                for(int i = 0; i < 5; i++)
                    window.draw(FMdeadlineTyped[i]);
                for(int i = 0; i < 2; i++)
                    window.draw(durationTyped[i]);
                for(int i = 0; i < 2; i++)
                    window.draw(maxContiDurationTyped[i]);
                window.draw(priorityTyped);
            }
            if(FEmenuOn == true)
            {
                window.draw(FEmenu);
                window.draw(FEmenuTitle);
                window.draw(eventNameText);
                if(eventNameBlockOn == true)
                    eventNameBlock.setFillColor(sf::Color(200, 200, 200));
                else
                    eventNameBlock.setFillColor(sf::Color(217, 217, 217));
                window.draw(eventNameBlock);
                window.draw(FEcategoryText);
                if(FEcategoryBlockOn == true)
                    FEcategoryBlock.setFillColor(sf::Color(200, 200, 200));
                else
                    FEcategoryBlock.setFillColor(sf::Color(217, 217, 217));
                window.draw(FEcategoryBlock);
                window.draw(FEstartTimeText);
                for(int i = 0; i < 5; i++)
                {
                    if(FEstartTimeBlockOn[i] == true)
                        FEstartTimeBlock[i].setFillColor(sf::Color(200, 200, 200));
                    else
                        FEstartTimeBlock[i].setFillColor(sf::Color(217, 217, 217));
                    window.draw(FEstartTimeBlock[i]);
                }
                for(int i = 0; i < 5; i++)
                    if(!(FEstartTimeBlockOn[i] == true || (FEstartTimeBlockOn[i] == false && FEstartTime[i].length() != 0)))
                        window.draw(FEstartTimeBlockText[i]);
                window.draw(FEendTimeText);
                for(int i = 0; i < 5; i++)
                {
                    if(FEendTimeBlockOn[i] == true)
                        FEendTimeBlock[i].setFillColor(sf::Color(200, 200, 200));
                    else
                        FEendTimeBlock[i].setFillColor(sf::Color(217, 217, 217));
                    window.draw(FEendTimeBlock[i]);
                }
                for(int i = 0; i < 5; i++)
                    if(!(FEendTimeBlockOn[i] == true || (FEendTimeBlockOn[i] == false && FEendTime[i].length() != 0)))
                        window.draw(FEendTimeBlockText[i]);
                window.draw(FEaddButton);
                window.draw(FEaddButtonText);
                window.draw(FEcancelButton);
                window.draw(FEcancelButtonText);
                window.draw(eventNameTyped);
                window.draw(FEcategoryTyped);
                for(int i = 0; i < 5; i++)
                    window.draw(FEstartTimeTyped[i]);
                for(int i = 0; i < 5; i++)
                    window.draw(FEendTimeTyped[i]);
            }
            if(invalidMenuOn == true)
            {
                window.draw(invalidFilter);
                window.draw(invalidMenu);
                window.draw(invalidText);
                window.draw(closeButton);
                window.draw(closeButtonText);

            }
        }
        window.display();


    }
    window.clear();





    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            year2018[i][j] = new Day(start);
            start = start + 1440;
        }
    }
    for(int i=0;i<aweek;i++)
    {
        week[i] = new Day(today);
        today = today +1440;
    }
    cout << "done initializing year2018" << endl;
    cout << "going into adding FE into year2018" << endl;
    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            for(int k=0;k<FEBag.Bag.get_itemCount();k++)
            {
                string FEtime = FEBag.Bag[k]->GetstartTime().substr(0,8);
                string cur = year2018[i][j]->getToday().substr(0,8);
                if(FEtime==cur)
                    year2018[i][j]->addFixedEvent(FEBag.Bag[k]);
                else
                    continue;
            }
//            year2018[i][j]->showToday();
        }
    }
    cout << "finish adding FE into year2018" << endl;
    cout << "start adding mission into year2018" << endl;
    for(int i=0;i<weeks;i++)
    {
        for(int j=0;j<aweek;j++)
        {
            for(int k=0;k<MBag.Bag.get_itemCount();k++)
            {
                string Mtime = MBag.Bag[k]->GetstartTime().substr(0,8);
                string cur = year2018[i][j]->getToday().substr(0,8);
                if(Mtime==cur)
                    year2018[i][j]->RestoreMission(MBag.Bag[k]);
                else
                    continue;
            }
//            year2018[i][j]->showToday();

        }
    }
    cout << "finish adding Mission into year2018" << endl;
    for(int i=0;i<FEBag.Bag.get_itemCount();i++)
    {
        week[0]->addFixedEvent(FEBag.Bag[i]);
    }
    for(int i=0;i<MBag.Bag.get_itemCount();i++)
    {
        week[0]->RestoreMission(MBag.Bag[i]);
    }

    while(1)
    {

	cout << "press 1 for showing the view eventlist" << endl;
	cout << "press 4 for showing the dash board" << endl;

	cout << "press 0 for exit" << endl;

	oper = 0;
    cin >> oper;
    cin.ignore();


	//201804231934
/*

	Initialize an linklist of week pointer like 52 week
	With each of it being a pointer pointing to 7 days (an array)
	I have to initalize everyday and restart


	readin the event txt that includes info
	new mission or fixed event txt according to the infor
	ptr to the item i just create

	get start time and put it into the day


	Offline method would be right before closing

	mission name cannot be the same
*/









//					view past calendar
//						display the past calendar

	if(oper==1)
	{

		/*
		view list should be able to display past and current and future
		First display current week


		We should be able to display what is in a day with view point of a week
		on a certain time period
		e.g.
		2018/06/01
			Study Calculus xx hour yy minute from 9:00 to 11:00
			Play hoverboard xx hour yy minute from 20:00 to 23:05
		2018/06/02
			... and so on
		The schedule here should be able to display in chronological order
		*/
            cout << "press 1 for viewing what happened today" << endl;
            cout << "press 2 for adding a new Fixed event / Mission" << endl;
			cout << "press 3 for finishing a mission" << endl;
			cout << "press 4 for deleting a fixed event / Mission" << endl;
			cin >> oper;
			cin.ignore();
			if(oper == 2)
			{
				/*
				Rule of thumbs to keep in mind:
				1. We do not determine whether the mission needs more time or not
				2. Once the event within three days have been made, no further changes should be made.
				2-1 Unless it is significantly import and of great urgency
				2-2 If we encounter running out of time, let the user decide what he/she should do either
					1. sleep less
					2. Abandon unimportant missions


				First, we require the uncompleted mission sorted list to give us a bag of mission.
				From the bag of mission we can
				*/
				cout << "press 1 for adding a fixed event" << endl;
				cout << "press 2 for adding a flexible mission" << endl;
				cin >> oper;
				cin.ignore();
				if(oper==1)
				{
					string fixedEventName;
					string startTime;
					string endTime;
					string category;
					int duration;

					cout << "Please type fixedEventName" << endl;
					getline(cin,fixedEventName);

					cout << "Please type startTime in the form of: \n201806301125 " << endl;
					getline(cin,startTime);

					OurTime startT(startTime);

					cout << "end Time please keep this event in the same day" << endl;
					getline(cin,endTime);

					cout << "category" << endl;
					getline(cin,category);
					cout << category;

					OurTime endT(endTime);
					duration = endT - startT;
					FixedEvent *one = new FixedEvent(fixedEventName,category,startT,endT,duration);
                    string moveto = startTime.substr(0,8);
                    for(int i=0;i<weeks;i++)
                    {
                        for(int j=0;j<aweek;j++)
                        {
                            string TD = year2018[i][j]->getToday().substr(0,8);
                            if(TD==moveto)
                            {
                                year2018[i][j]->addFixedEvent(one);
                                cout << TD << endl;
                            }

                        }
                    }
                    FEBag.Bag.add(one);
                    FEBag.SaveFile(FixedLocation);

					/*
					Now we would have a fixed event
					We need just passing the event into the Day class
					The Day class might need some function to help making the time occupied by fixed event be unavailable to use

					*/
				}
				else if(oper==2)
				{
					string MissionName;
					string Deadline;
					string StartTime;
					string category;
					string graph;
					int priority;
					double duration;
					double thresh;
					cout << "Please type mission Name" << endl;
					getline(cin,MissionName);
					//	total time to complete the mission
					cout << "Enter how long will you need to finish it (in minute) " << endl;
					cin >> duration;


					cout << "Maximum continuous minutes" << endl;
					cin >> thresh;
					cin.ignore();

                    cout << "DeadLine?" << endl;
					getline(cin,Deadline);

					OurTime ddl(Deadline);

					double parts = ceil(duration/thresh);
					cout << "please type in priority\nwith least important:1 to utmost important:10" << endl;
					cin >> priority;
					cin.ignore();

                    cout << "which type do you want this to graph???" << endl;
                    getline(cin,graph);

					cout << "category" << endl;
					getline(cin,category);

					for(int i=0;i<parts;i++)
                    {
                        Mission *a;
                        if(thresh < duration)
                            a = new Mission(MissionName,graph,category,i,parts,priority,ddl,thresh);
                        else
                            a = new Mission(MissionName,graph,category,i,parts,priority,ddl,duration);
                        MBag.Bag.add(a);
                        duration -= thresh;
                    }

                    OurTime doodle;
                    doodle.Current();
                    string cur = doodle.getTimeStr().substr(0,8);
                    int weekN,dayN;
                    for(int i=0;i<weeks;i++)
                    {
                        for(int j=0;j<aweek;j++)
                        {
                            string hello = year2018[i][j]->getToday().substr(0,8);
                            if(hello==cur)
                            {
                                weekN = i;
                                dayN = j;
                                break;
                            }
                            else
                                continue;
                        }
                    }
                    cout << "during deleting non fixed event" << endl;
                    for(int i=weekN;i<weeks;i++)
                    {
                        for(int j=dayN;j<aweek;j++)
                        {
                            year2018[i][j]->deleteNonFixedEvent();
                        }
                    }
                    cout << "ended deleting non fixed event" << endl;
                    for(int i=weekN;i<weeks;i++)
                    {
                        for(int j=dayN;j<aweek;j++)
                        {
                            year2018[i][j]->showToday();
                        }
                    }
                    bool eventNotAbleToAdd = false;
                    for(int i=weekN;i<weeks;i++)
                    {
                        for(int j=dayN;j<aweek;j++)
                        {
//                            cout << "i:" << i << " j: " << j << endl;
//                            year2018[i][j]->unCheck();
                            while(1)
                            {
                                int freeTime = year2018[i][j]->getDuration();
                                OurTime timeP = year2018[i][j]->getFreeTime();
                                if(freeTime==-1)
                                    break;

                                MissionBag* chosen = KnapSack(MBag,freeTime);
                                for(int i=0;i<chosen->Bag.get_itemCount();i++)
                                {
                                    OurTime DDL(chosen->Bag[i]->GetMdeadline());
                                    if(timeP - DDL >0)
                                    {
                                        string name = chosen->Bag[i]->GetName();
                                        int ind = stoi(chosen->Bag[i]->GetMindex());
                                        int tCnt = stoi(chosen->Bag[i]->GetMtotalCnt());
                                        chosen->Bag.remove(name,ind,tCnt);
                                        MBag.Bag.remove(name,ind,tCnt);
                                        eventNotAbleToAdd = true;
                                    }
                                }

//                                cout <<"chosen item count: " <<  chosen->Bag.get_itemCount() << endl;
                                Event** fillin = new Event*[chosen->Bag.get_itemCount()];
                                for(int k=0;k<chosen->Bag.get_itemCount();k++)
                                {
                                    fillin[k] = chosen->Bag[k];
                                }
//                                cout << "start filling Time" << endl;
                                year2018[i][j]->fillTime(fillin,chosen->Bag.get_itemCount());
                                year2018[i][j]->showToday();
//                                cout << "done filling Time" << endl;
//                                cout << "start updating Time" << endl;
                                for(int k=0;k<chosen->Bag.get_itemCount();k++)
                                {
                                    MBag.Bag.remove(fillin[k]->GetName(),stoi(fillin[k]->GetMindex()),stoi(fillin[k]->GetMtotalCnt()));
                                    MBag.Bag.add(fillin[k]);
                                }
//                                cout << "done updating MBag" << endl;

                            }
                            year2018[i][j]->unCheck();
                        }
                    }
                    if(eventNotAbleToAdd)
                        cout << "Not Enough Time To Schedule Your Missions\nTry To Spend Less Time on Sleeping or Eating" << endl;
                    MBag.Bag.printBag();

                    MBag.SaveFile(MissionLocation);

                    /*
                        When I finish creating a or multiple series of mission
                        I need to put it into the mission bag
                        after that give it to knapsack and then it would return to me an array
                        after that

						Now that I can create a new flexible mission variable.
						We need to gain the access of the Uncompleted mission list
						We pass the list into
						Acquire how much time is available in a single day.
						Pass that amount, and the uncompleted mission list into the knapsack algorithm
						The algorithm should return an array containing
							1. Mission name
							2. Mission duration
						That array would be passed into the day class and be inserted.
					*/
				}
				else
					cout << "Enter something that is readable FOOL!!" << endl;
						/*
							add a mission event
								clear out all the mission
								add a new mission
								recalculate
								put it back into the day list
							add a fixed event
								if there is an overlapping
									not allowed

								clear out al the mission
								insert fixed event
								recalculate and then insert

							viewing style would be weekly
						*/
			}
			else if (oper == 1)
            {
                OurTime sony;
                sony.Current();
                string cur = sony.getTimeStr().substr(0,8);
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                    {
                        string hello = year2018[i][j]->getToday().substr(0,8);
                        if(hello==cur)
                        {
                            year2018[i][j]->showToday();
                            break;
                        }
                        else
                            continue;
                    }
                }
            }
            else if (oper == 3)
            {
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                        year2018[i][j]->showToday();
                }
                cout << "enter event date" << endl;
                cout << "e.g. 20180720" << endl;
                string date;
                cin >> date;
                cout << "enter mission name within that day" << endl;
                int weekN,dayN;
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                    {
                        string hello = year2018[i][j]->getToday().substr(0,8);
                        if(hello==date)
                        {
                            year2018[i][j]->showToday();
                            weekN = i;
                            dayN = j;
                            break;
                        }
                        else
                            continue;
                    }
                }
                string missionName;
                cin.ignore();
                getline(cin,missionName);
                cout << "enter which part of the mission" << endl;
                int parr = 0;
                cin >> parr;
                cin.ignore();
                year2018[weekN][dayN]->deleteSpecificEvent(missionName,parr,true);
                MBag.SaveFile(MissionLocation);
            }
            else if (oper == 4)
            {
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                        year2018[i][j]->showToday();
                }
                cout << "enter event date" << endl;
                cout << "e.g. 20180720" << endl;
                string date;
                cin >> date;
                cout << "enter mission / Fixed event name within that day" << endl;
                int weekN,dayN;
                for(int i=0;i<weeks;i++)
                {
                    for(int j=0;j<aweek;j++)
                    {
                        string hello = year2018[i][j]->getToday().substr(0,8);
                        if(hello==date)
                        {
                            year2018[i][j]->showToday();
                            weekN = i;
                            dayN = j;
                            break;
                        }
                        else
                            continue;
                    }
                }
                cout << "press 1 to delete mission" << endl;
                cout << "press 2 to delete Fixed Event" << endl;
                int FEorM=0;
                cin >> FEorM;
                if(FEorM==1)
                {
                    cout << "enter mission name within that day" << endl;
                    string missionName;
                    cin.ignore();
                    getline(cin,missionName);
                    cout << "enter which part of the mission" << endl;
                    int parr = 0;
                    cin >> parr;
                    year2018[weekN][dayN]->deleteSpecificEvent(missionName,parr,false);
                    MBag.SaveFile(MissionLocation);
                }
                else
                {
                    cout << "enter Fixed event name within that day" << endl;
                    string FixedName;
                    cin.ignore();
                    getline(cin,FixedName);
                    year2018[weekN][dayN]->deleteSpecificEvent(FixedName,-1,false);
                    FEBag.Bag.remove(FixedName);
                    FEBag.SaveFile(FixedLocation);
                }
            }
	}
	else if(oper==0)
	{
        return 0;
	}
	else if(oper==3)
	{
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<aweek;j++)
                year2018[i][j]->showToday();
        }
	}
	else if(oper==4)
	{
		/*
		We should be able to display a list showing the total amount of time contributed to each tag
		We may need some for loops to add up all of the time we used in the past week.
		Showing in the form of:
			Studying 5 hr 42 min ->20%
			Riding fixed gear 20 hr 30 min ->50%
			Facebook 3 hr 20 min ->30%
		*/
	}
	else
		cout << "Enter something that is readable FOOL!!" << endl;
    }

	return 0;
}
