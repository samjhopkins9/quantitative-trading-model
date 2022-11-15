//
//  quotes.h
//  Quantitative Trading Model
//
//  Created by Sam Hopkins on 5/26/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

string input_line[1000000];
string input_date[1000000];
string input_open[1000000];
string input_high[1000000];
string input_low[1000000];
string input_close[1000000];
string input_volume[1000000];
int input_year_int[1000000];
int input_month_int[1000000];
int input_day_int[1000000];
int input_hour_int[1000000];
int input_minute_int[1000000];
int input_second_int[1000000];
float input_open_float[1000000];
float input_high_float[1000000];
float input_low_float[1000000];
float input_close_float[1000000];
int input_volume_int[1000000];

class quotes{
private:
    vector<string> date;
    vector<float> year;
    vector<float> month;
    vector<float> day;
    vector<int> hour;
    vector<int> minute;
    vector<float> second;
    vector<float> open;
    vector<float> high;
    vector<float> low;
    vector<float> close;
    vector<int> volume;
    void input(string name, string interval){
        ifstream fin;
        fin.open("~/Documents/Programming/Quantitative Trading Model/1.0/Data Files/" + name + "/" + name + "_" + interval + ".txt"); // opens file
        if (fin.is_open()){
                int n = 0;
                while(!fin.eof()) {
                    getline(fin, input_line[n]);
                    n++;
                }
                n -= 2;
                while(n>0){
                    // cout << input_line[n];
                    string& line = input_line[n];
                    string year2;
                    string month2;
                    string day2;
                    string hour2;
                    string minute2;
                    string second2;
                    string open2;
                    string high2;
                    string low2;
                    string close2;
                    string volume2;
                    for (int i=0; i<4; i++){
                        year2 += line[i];
                    }
                    for (int i=5; i<7; i++){
                        month2 += line[i];
                    }
                    for (int i=8; i<10; i++){
                        day2 += line[i];
                    }
                    for (int i=11; i<13; i++){
                        hour2 += line[i];
                    }
                    for (int i=14; i<16; i++){
                        minute2 += line[i];
                    }
                    for (int i=17; i<19; i++){
                        second2 += line[i];
                    }
                    int k = 20;
                    char p = '\0';
                    while(p != ',') {
                        p = line[k];
                        open2 += p;
                        k++;
                    }
                    p = '0';
                    while(p != ',') {
                        p = line[k];
                        high2 += p;
                        k++;
                    }
                    p = '0';
                    while(p != ',') {
                        p = line[k];
                        low2 += p;
                        k++;
                    }
                    p = '0';
                    while(p != ',') {
                        p = line[k];
                        close2 += p;
                        k++;
                    }
                    p = '0';
                    do {
                        p = line[k];
                        volume2 += p;
                        k++;
                    } while(p != line.back());
                    cout << "";
                    int Year;
                    stringstream year0;
                    year0 << year2;
                    year0 >> Year;
                    int Month;
                    stringstream month0;
                    month0 << month2;
                    month0 >> Month;
                    int Day;
                    stringstream day0;
                    day0 << day2;
                    day0 >> Day;
                    int Hour;
                    stringstream hour0;
                    hour0 << hour2;
                    hour0 >> Hour;
                    int Minute;
                    stringstream minute0;
                    minute0 << minute2;
                    minute0 >> Minute;
                    int Second;
                    stringstream second0;
                    second0 << second2;
                    second0 >> Second;
                    float Open;
                    stringstream open0;
                    open0 << open2;
                    open0 >> Open;
                    float High;
                    stringstream high0;
                    high0 << high2;
                    high0 >> High;
                    float Low;
                    stringstream low0;
                    low0 << low2;
                    low0 >> Low;
                    float Close;
                    stringstream close0;
                    close0 << close2;
                    close0 >> Close;
                    int Volume;
                    stringstream volume0;
                    volume0 << volume2;
                    volume0 >> Volume;
                    input_year_int[n] = Year;
                    input_month_int[n] = Month;
                    input_day_int[n] = Day;
                    input_hour_int[n] = Hour;
                    input_minute_int[n] = Minute;
                    input_second_int[n] = Second;
                    input_open_float[n] = Open;
                    input_high_float[n] = High;
                    input_low_float[n] = Low;
                    input_close_float[n] = Close;
                    input_volume_int[n] = Volume;
                    year.push_back(input_year_int[n]);
                    month.push_back(input_month_int[n]);
                    day.push_back(input_day_int[n]);
                    hour.push_back(input_hour_int[n]);
                    minute.push_back(input_minute_int[n]);
                    second.push_back(input_second_int[n]);
                    volume.push_back(input_volume_int[n]);
                    open.push_back(input_open_float[n]);
                    high.push_back(input_high_float[n]);
                    low.push_back(input_low_float[n]);
                    close.push_back(input_close_float[n]);
                    volume.push_back(input_volume_int[n]);
                    n--;
                }
            fin.close();
        }
        else {
            cout << "Build Failed";
            cout << endl;
        }
    }
    
    vector<bool> gain_loss;
    vector<bool> GAIN_loss(){
        int i = 0;
        for (float d : close){
            if (d > close[i+1]){
                gain_loss.push_back(true);
                i++;
            }
            else {
                gain_loss.push_back(false);
                i++;
            }
        }
        return gain_loss;
    }
    
    vector<float> change;
    vector<float> CHANGE(int days){
        int i = 0;
        for (float d : close){
            change.push_back(d-close[i+days]);
            i++;
        }
        return change;
    }

    vector<float> percent_change;
    vector<float> PERCENT_change(int days){
        int i = 0;
        for (float d : close){
            percent_change.push_back(100*(d-close[i+days])/d);
            i++;
        }
        return percent_change;
    }

    vector<int> gains_in_last;
    vector<int> GAINS_in_last(int days){
        stack<int> gains_in_last_counter;
        int j = 0;
        for (float d : close){
            d = d;
            for (int i=0; i<days; i++){
                if (i==0){
                    if (change[i+j]>0){
                        gains_in_last_counter.push(1);
                    }
                    else {
                        gains_in_last_counter.push(0);
                    }
                }
                else
                    if (change[i+j] > 0){
                        gains_in_last_counter.push(1+gains_in_last_counter.top());
                        // cout << gains_in_last_counter[i] << endl;
                    }
                    else {
                        gains_in_last_counter.push(gains_in_last_counter.top());
                       //  cout << gains_in_last_counter[i] << endl;
                    }
            }
            gains_in_last.push_back(gains_in_last_counter.top());
            while (!gains_in_last_counter.empty()){
                gains_in_last_counter.pop();
            }
            j++;
        }
        return gains_in_last;
    }
    
    vector<int> days_since_gain;
    vector<int> DAYS_since_gain(){
        vector<bool> gain_loss = GAIN_loss();
        int j = 0;
        stack<int> days_since_gain_counter;
        for (bool d : gain_loss){
            int i = 0;
            if (d == true){
                days_since_gain.push_back(0);
            }
            else if (gain_loss[i+j] == false){
                while(gain_loss[i+j] == false){
                    if (i==0){
                        days_since_gain_counter.push(1);
                        i++;
                    }
                    else {
                        days_since_gain_counter.push(1+days_since_gain_counter.top());
                        i++;
                    }
                }
            days_since_gain.push_back(days_since_gain_counter.top());
            while (!days_since_gain_counter.empty()){
                    days_since_gain_counter.pop();
                    }
                }
            j++;
            }
        return days_since_gain;
    }
    
    vector<int> days_since_loss;
    vector<int> DAYS_since_loss(){
        stack<int> days_since_loss_counter;
        int j = 0;
        for (bool d : gain_loss){
            int i = 0;
            if (d == false){
                days_since_loss.push_back(0);
            }
            else if (gain_loss[i+j] == true){
                while(gain_loss[i+j] == true){
                    if (i==0){
                        days_since_loss_counter.push(1);
                        i++;
                    }
                    else {
                        days_since_loss_counter.push(1+days_since_loss_counter.top());
                        i++;
                    }
                }
            days_since_loss.push_back(days_since_loss_counter.top());
            while (!days_since_loss_counter.empty()){
                    days_since_loss_counter.pop();
                    }
                }
            j++;
            }
        return days_since_loss;
    }

    
    
    void operations_input(int ints_days, int change_days){
        CHANGE(change_days);
        PERCENT_change(change_days);
        GAINS_in_last(ints_days);
        DAYS_since_gain();
        DAYS_since_loss();
    }
    
public:
    string interval3;
    int int_days;
    int lengthr;
    int LENGTH(){
        int length = 0;
        for (float d : close){
            d = d;
            length++;
        }
        return length;
    }
    
    quotes(string name, string interval, int ints_days, int change_days){
        input(name, interval);
        operations_input(ints_days, change_days);
        lengthr = LENGTH();
        int_days = ints_days;
        interval3 = interval;
    }
    
    string get_date(int c){
        stringstream ss;
        string mm;
        ss << month[c];
        ss >> mm;
        stringstream aa;
        string dd;
        aa << day[c];
        aa >> dd;
        stringstream bb;
        string yy;
        bb << year[c];
        bb >> yy;
        string date_public = mm + '/' + dd + '/' + yy;
        return date_public;
    }
    
    vector<string> dates_public(){
        vector<string> publicdates;
        for (int c=0; c<lengthr; c++){
            publicdates.push_back(get_date(c));
        }
        return publicdates;
    }
    
    string get_time(int c){
        stringstream ss;
        string hh;
        ss << hour[c];
        ss >> hh;
        stringstream aa;
        string mm;
        aa << minute[c];
        aa >> mm;
        stringstream bb;
        string time_public = hh + ":" + mm;
        return time_public;
    }
    
    bool pre_markets(int i){
        if (hour[i]<=8 || (hour[i] == 9 && minute[i] <=29)){
            return true;
        }
        else {
            return false;
        }
    }
    
    bool trading_hours(int c){
        if((hour[c] == 9 && minute[c] >= 30) || (hour[c] == 10 && minute[c] <= 29)){
            return true;
        }
        else {
            return false;
        }
    }
    
    bool late_day(int c){
        if ((hour[c] <=16 && hour[c] >= 11) || (hour[c] == 10 && minute[c] >= 30)){
            return true;
        }
        else {
            return false;
        }
    }
    
    bool after_hours(int c){
        if (hour[c] >=16){
            return true;
        }
        else {
            return false;
        }
    }
    
    float get_day(int c){
        return day[c];
    }
    
    int get_minute(int c){
        return minute[c];
    }
    
    int get_hour(int c){
        return hour[c];
    }
    
    float get_close(int c){
        return close[c];
    }
    
    float get_high(int c){
        return high[c];
    }
    
    float get_low(int c){
        return low[c];
    }
    
    int get_volume(int c){
        return volume[c];
    }
    
    float get_change(int c){
        return change[c];
    }
    
    int get_gains_in_last(int c){
        return gains_in_last[c];
    }

    int get_days_since_gain(int c){
        return days_since_gain[c];
    }
    
    int get_days_since_loss(int c){
        return days_since_loss[c];
    }
    
    vector<float> closes_public(){
        return close;
    }
    
    vector<float> gainsinlast(){
        vector<float> gs;
        for (int i : gains_in_last){
            gs.push_back(i);
        }
        return gs;
    }
    
    vector<float> dayssincegain(){
        vector<float> gs;
        for (int i : days_since_gain){
            gs.push_back(i);
        }
        return gs;
    }
    
    vector<float> dayssinceloss(){
        vector<float> gs;
        for (int i : days_since_loss){
            gs.push_back(i);
        }
        return gs;
    }
    
    float get_high_of_last(int i, int days, int multiplier){
        float high2 = close[i];
        int day1 = day[i];
        // cout << day1 << endl;
        int exit = day[i+days*multiplier];
        // cout << exit << endl;
        int c = 0;
        while(day1 != exit){
            day1 = day[i+c];
            if (close[i+c] > high2){
                high2 = close[i+c];
            }
            c++;
        }
        return high2;
    }
    
    float get_low_of_last(int i, int days, int multiplier){
        float low2 = close[i];
        int day1 = day[i];
        int exit = day[i+days*multiplier];
        int c = 0;
        while(day1 != exit){
            day1 = day[i+c];
            if (close[i+c] < low2){
                low2 = close[i+c];
            }
            c++;
        }
        return low2;
    }
    
    void output(int length){
        cout << "Date" << "       " << "Time" << "   " << "Open" << "    " << "High" << "    " << "Low" << "    " << "Close" << "   " << "Volume" << "  ";
        cout << "Change" << " " << "%Change" << "  " << "Gains in L" << int_days << " " << "Since G" << "  " << "Since L" << endl;
        for (int i=0; i<length; i++){
            cout << fixed << setprecision(0);
            cout << month[i] << "/" << day[i] << "/" << year[i] << "  ";
            cout << hour[i] << ":" << minute[i] << "  ";
            cout << fixed << setprecision(2) << open[i] << "  " << high[i] << "  " << low[i] << "  " << close[i] << "  " << volume[i] << "  ";
            cout << change[i] << "  " << percent_change[i] << "%       " << gains_in_last[i] << "           " << days_since_gain[i] << "           " << days_since_loss[i] << endl;
        }
        cout << endl;
    }
    
    ~quotes() {
    }
};

