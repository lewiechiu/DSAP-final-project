#define SELBAWARD_NO_NAMESPACE_SHORTCUT before including any Selba Ward
#include "SelbaWard/PieChart.hpp"
#include "SelbaWard/PieChart.cpp"

using namespace std;
#include <SFML/Graphics.hpp>
#include "SelbaWard/Line.hpp"
#include "SelbaWard/Line.cpp"
#include <iostream>

//Position
float thickness = 50, Gap=60;
//Week
float Bar_Week_Pos_X_Start = 240,Bar_Week_Pos_X_End =0, Bar_Week_Pos_X_Gap = 560, Bar_Week_Pos_Y = 530;
//Month
float Bar_Month_Pos_X_Start = 240,Bar_Month_Pos_X_End =0, Bar_Month_Pos_X_Gap = 560, Bar_Month_Pos_Y = Bar_Week_Pos_Y +2*Gap;
//Year
float Bar_Year_Pos_X_Start = 240,Bar_Year_Pos_X_End =0, Bar_Year_Pos_X_Gap = 560, Bar_Year_Pos_Y = Bar_Week_Pos_Y +4*Gap;


//Color
//Week
float Bar_Week_Red_Start = 125, Bar_Week_Green_Start = 197, Bar_Week_Blue_Start = 154;
double
Bar_Week_Red_Gap = 255-Bar_Week_Red_Start,
Bar_Week_Green_Gap = 255-Bar_Week_Green_Start,
Bar_Week_Blue_Gap = 255-Bar_Week_Blue_Start;
//Month
float Bar_Month_Red_Start = 90, Bar_Month_Green_Start = 175, Bar_Month_Blue_Start = 190;
double
Bar_Month_Red_Gap = 255-Bar_Month_Red_Start,
Bar_Month_Green_Gap = 255-Bar_Month_Green_Start,
Bar_Month_Blue_Gap = 255-Bar_Month_Blue_Start;
//Year
float Bar_Year_Red_Start = 27, Bar_Year_Green_Start = 102, Bar_Year_Blue_Start = 192;
double
Bar_Year_Red_Gap = 255-Bar_Year_Red_Start,
Bar_Year_Green_Gap = 255-Bar_Year_Green_Start,
Bar_Year_Blue_Gap = 255-Bar_Year_Blue_Start;

//Draw Bars Function
void DrawBar(sf::RenderWindow& wn, int Ratio[], int Amount, string& Scale);
//Ratio: Descending sorted list
//Scale: "W": week; "M": month; "Y": Year

void DrawBarTitle(sf::RenderWindow& wn);


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Line simple example");
    
    selbaward::PieChart pieChart;
    pieChart.slices.resize(3);
    pieChart.slices[0].color = sf::Color::Red;
    pieChart.slices[1].color = sf::Color::Green;
    pieChart.slices[2].color = sf::Color::Blue;
    
    pieChart.slices[0].size = 0.50f;
    pieChart.slices[1].size = 0.25f;
    pieChart.slices[2].size = 0.25f;
    pieChart.slices[1].explode = 0.3f;
    pieChart.setSize({ 300.f, 300.f });
    pieChart.update();
    pieChart.setOrigin(pieChart.getSize() / 2.f);
    pieChart.setPosition({ 500.f, 500.f });
    window.getView().getCenter();
    
    
    
    
    
    
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        int a[] = {25, 10,5};
        int n = 3;
        string w = "W", m="M", y ="Y";
        DrawBar(window, a, n, w);
        DrawBar(window, a, n, m);
        DrawBar(window, a, n, y);
        DrawBarTitle(window);
        //        window.draw(pieChart);
        window.display();
    }
    return EXIT_SUCCESS;
}


void DrawBar(sf::RenderWindow& wn, int Ratio[], int Amount, string& Scale)
{
    int Sum = 0;
    for (int i=0; i<Amount; i++)
        Sum+=Ratio[i];
    float Bar_Pos_X_Start = 0,Bar_Pos_X_End =0, Bar_Pos_X_Gap = 0, Bar_Pos_Y = 0;
    float Bar_Red_Start = 0, Bar_Green_Start = 0, Bar_Blue_Start = 0;
    
    if(Scale=="W")
    {
        Bar_Pos_X_Start = ::Bar_Week_Pos_X_Start;
        Bar_Pos_X_End = ::Bar_Week_Pos_X_End;
        Bar_Pos_X_Gap = ::Bar_Week_Pos_X_Gap;
        Bar_Pos_Y = ::Bar_Week_Pos_Y;
        Bar_Red_Start = ::Bar_Week_Red_Start;
        Bar_Green_Start = ::Bar_Week_Green_Start;
        Bar_Blue_Start = ::Bar_Week_Blue_Start;
    }
    else if(Scale=="M")
    {
        Bar_Pos_X_Start = ::Bar_Month_Pos_X_Start;
        Bar_Pos_X_End = ::Bar_Month_Pos_X_End;
        Bar_Pos_X_Gap = ::Bar_Month_Pos_X_Gap;
        Bar_Pos_Y = ::Bar_Month_Pos_Y;
        Bar_Red_Start = ::Bar_Month_Red_Start;
        Bar_Green_Start = ::Bar_Month_Green_Start;
        Bar_Blue_Start = ::Bar_Month_Blue_Start;
    }
    else if(Scale=="Y")
    {
        Bar_Pos_X_Start = ::Bar_Year_Pos_X_Start;
        Bar_Pos_X_End = ::Bar_Year_Pos_X_End;
        Bar_Pos_X_Gap = ::Bar_Year_Pos_X_Gap;
        Bar_Pos_Y = ::Bar_Year_Pos_Y;
        Bar_Red_Start = ::Bar_Year_Red_Start;
        Bar_Green_Start = ::Bar_Year_Green_Start;
        Bar_Blue_Start = ::Bar_Year_Blue_Start;
    }
    float Bar_Red_Gap = 255-Bar_Red_Start, Bar_Green_Gap = 255-Bar_Green_Start, Bar_Blue_Gap = 255-Bar_Blue_Start;
    
    
    int Count=0;
    selbaward::Line* LineSet = new selbaward::Line[Amount];
    while(Count<Amount)
    {
        Bar_Pos_X_End = Bar_Pos_X_Start+Bar_Pos_X_Gap*Ratio[Count]/Sum;
        LineSet[Count] = *new selbaward::Line({ Bar_Pos_X_Start, Bar_Pos_Y }, { Bar_Pos_X_End, Bar_Pos_Y }, ::thickness, sf::Color(Bar_Red_Start,Bar_Green_Start,Bar_Blue_Start));
        Bar_Pos_X_Start = Bar_Pos_X_End;
        
        Bar_Red_Start+=Bar_Red_Gap*Ratio[Count]/Sum;
        Bar_Green_Start+=Bar_Green_Gap*Ratio[Count]/Sum;
        Bar_Blue_Start+=Bar_Blue_Gap*Ratio[Count]/Sum;
        Count++;
    }
    for(int i=0; i<Amount; i++)
        wn.draw(LineSet[i]);
}

void DrawBarTitle(sf::RenderWindow& wn)
{
    int Title_number=4;
    sf::Text* Time_Spent_Title = new sf::Text[Title_number];
    //0: Time Spent
    //1: "Week (2018.01.21 – 2018. 01.27)"
    //2: "Month (2018.01)"
    //3: "Year (2018)"
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        system("pause");
    }
    for(int i=0; i<Title_number; i++)
    {
        Time_Spent_Title[i].setFont(font);
        Time_Spent_Title[i].setCharacterSize(30);
        Time_Spent_Title[i].setFillColor(sf::Color::White);
        Time_Spent_Title[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
        if (i==0)
        {
            Time_Spent_Title[i].setString("Time Spent");
            Time_Spent_Title[i].setPosition({240,370});
        }
        else if(i==1)
        {
            Time_Spent_Title[i].setString("Week (2018.01.21 - 2018. 01.27)");
            Time_Spent_Title[i].setPosition({240,430});
        }
        else if (i==2)
        {
            Time_Spent_Title[i].setString("Month (2018.01)");
            Time_Spent_Title[i].setPosition({240,560});
        }
        else if (i==3)
        {
            Time_Spent_Title[i].setString("Year (2018)");
            Time_Spent_Title[i].setPosition({240,690});
        }
    }
    for(int i=0; i<Title_number; i++)
        wn.draw(Time_Spent_Title[i]);
}
