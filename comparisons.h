//
//  comparisons.h
//  Quantitative Trading Model
//
//  Created by Sam Hopkins on 6/15/22.
//

#include "indicators.h"

class comparison{
protected:
    string name1;
    string name2;
    int days1;
    int days2;
    string subset1;
    string subset2;
    vector<int> comparison_vector;
    float current_upper_restriction1;
    float current_upper_restriction2;
    float current_lower_restriction1;
    float current_lower_restriction2;
public:
    comparison(analysis a, analysis b, int length){
        name1 = a.get_name();
        name2 = b.get_name();
        days1 = a.get_days();
        days2 = b.get_days();
        subset1 = a.get_subset();
        subset2 = b.get_subset();
        current_lower_restriction1 = a.get_fifthp(0);
        current_lower_restriction2 = b.get_fifthp(0);
        current_upper_restriction1 = a.get_ninetyfifthp(0);
        current_upper_restriction2 = b.get_ninetyfifthp(0);
        for (int i=0; i<length; i++){
            bool upper_condition1 = a.upper_percentile_range(i);
            bool upper_condition2 = b.upper_percentile_range(i);
            bool lower_condition1 = a.lower_percentile_range(i);
            bool lower_condition2 = b.lower_percentile_range(i);
            if ((upper_condition1 == true) && (upper_condition2 == true)){
                comparison_vector.push_back(1);
            }
            else if ((upper_condition1 == true) && (upper_condition2 == false)){
                comparison_vector.push_back(2);
            }
            else if ((upper_condition1 == false) && (upper_condition2 == true)){
                comparison_vector.push_back(3);
            }
            else if ((lower_condition1 == true) && (lower_condition2 == true)){
                comparison_vector.push_back(4);
            }
            else if ((lower_condition1 == true) && (lower_condition2 == false)){
                comparison_vector.push_back(5);
            }
            else if ((lower_condition1 == false) && (lower_condition2 == true)){
                comparison_vector.push_back(6);
            }
            else if ((upper_condition1 == true) && (lower_condition2 == true)){
                comparison_vector.push_back(7);
            }
            else if ((lower_condition1 == true) && (lower_condition2 == true)){
                comparison_vector.push_back(8);
            }
            else{
                comparison_vector.push_back(0);
            }
        }
    }
    
    void comparison_output(quotes one, int length){
        for (int i=0; i<length; i++){
            cout << fixed << setprecision(2);
            cout << one.get_date(i) << " " << one.get_time(i) << "  " << comparison_vector[i] << "   " << one.get_change(i) << endl;
            }
        cout << endl;
    }

};

class pattern:comparison{
private:
    vector<map<string, int> > tradingtime_maps;
    vector<map<string, int> > premarket_maps;
    vector<map<string, int> > afterhours_maps;
    vector<map<string, int> > lateday_maps;
    int days;
    vector<string> dates;
    int input_days1;
    vector<int> pattern_reading;
public:
    pattern(analysis a, analysis b, int length)
    : comparison(a, b, length) {};
    
    void output_comparison(quotes one, int length){
        comparison_output(one, length);
    }
    
    void map_init(map<string, int> a){
        a.insert(pair<string, int>("N1", 0));
        a.insert(pair<string, int>("N2", 0));
        a.insert(pair<string, int>("H1", 0));
        a.insert(pair<string, int>("H2", 0));
        a.insert(pair<string, int>("L1", 0));
        a.insert(pair<string, int>("L2", 0));
        a.insert(pair<string, int>("NN", 0));
        a.insert(pair<string, int>("HH", 0));
        a.insert(pair<string, int>("HN", 0));
        a.insert(pair<string, int>("NH", 0));
        a.insert(pair<string, int>("LL", 0));
        a.insert(pair<string, int>("LN", 0));
        a.insert(pair<string, int>("NL", 0));
        a.insert(pair<string, int>("LH", 0));
        a.insert(pair<string, int>("LH", 0));
        a.insert(pair<string, int>("H", 0));
        a.insert(pair<string, int>("L", 0));
        a.insert(pair<string, int>("T", 0));
        a.insert(pair<string, int>("Volume", 0));
    }
    
    map<string, int> map_append(int i, map <string, int> comparison_map){
        comparison_map = comparison_map;
        comparison_map["T"]++;
        switch(comparison_vector[i]){
            case 0:
                comparison_map["NN"]++;
                comparison_map["N1"]++;
                comparison_map["N2"]++;
                break;
            case 1:
                comparison_map["HH"]++;
                comparison_map["H1"]++;
                comparison_map["H2"]++;
                comparison_map["H"]++;
                break;
            case 2:
                comparison_map["HN"]++;
                comparison_map["H1"]++;
                comparison_map["N2"]++;
                comparison_map["H"]++;
                break;
            case 3:
                comparison_map["NH"]++;
                comparison_map["N1"]++;
                comparison_map["H2"]++;
                comparison_map["H"]++;
                break;
            case 4:
                comparison_map["LL"]++;
                comparison_map["L1"]++;
                comparison_map["L2"]++;
                comparison_map["L"]++;
                break;
            case 5:
                comparison_map["LN"]++;
                comparison_map["L1"]++;
                comparison_map["N2"]++;
                comparison_map["L"]++;
                break;
            case 6:
                comparison_map["NL"]++;
                comparison_map["N1"]++;
                comparison_map["L2"]++;
                comparison_map["L"]++;
                break;
            case 7:
                comparison_map["HL"]++;
                comparison_map["H1"]++;
                comparison_map["L2"]++;
                comparison_map["L"]++;
                comparison_map["H"]++;
                break;
            case 8:
                comparison_map["LH"]++;
                comparison_map["L1"]++;
                comparison_map["H2"]++;
                comparison_map["L"]++;
                comparison_map["H"]++;
                break;
        }
        return comparison_map;
    }
    
    void create_maps(quotes one, int length){
        days = 0;
        map<string, int> loading_map;
        for (int i=0; i<length; i++){
            if(one.pre_markets(i) == true){
                if( /*one.pre_markets(i+1) == false || */ one.after_hours(i+1) == true ){
                    string date = one.get_date(i);
                    dates.push_back(date);
                    days++;
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                    map<string, int>& a1 = loading_map;
                    // cout << a1["HH"] << "  " << a1["LL"] << "  " << a1["NN"] << "  " << a1["Total" ] << endl;
                    premarket_maps.push_back(a1);
                    loading_map.clear();
                    map_init(loading_map);
                }
                else {
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                }
            }
            else if(one.trading_hours(i) == true){
                if(/* one.trading_hours(i+1) == false || */ one.pre_markets(i+1) == true){
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                    map<string, int>& a2 = loading_map;
                    // cout << a2["HH"] << "  " << a2["LL"] << "  " << a2["NN"] << "  " << a2["Total"]<< endl;
                    tradingtime_maps.push_back(a2);
                    loading_map.clear();
                    map_init(loading_map);
                }
                else {
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                }
            }
            else if(one.late_day(i) == true){
                if(/* one.late_day(i+1) == false || */ one.trading_hours(i+1) == true ){
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                    map<string, int>& a3 = loading_map;
                    // cout << a3["HH"] << "  " << a3["LL"] << "  " << a3["NN"] << "  " << a3["Total"]<< endl;
                    lateday_maps.push_back(a3);
                    loading_map.clear();
                    map_init(loading_map);
                }
                else {
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                }
            }
            else if(one.after_hours(i) == true){
                if(/* one.after_hours(i+1) == false || */ one.late_day(i+1) == true){
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                    map<string, int>& a4 = loading_map;
                    // cout << a4["HH"] << "  " << a4["LL"] << "  " << a4["NN"] << "  " << a4["Total"]<< endl;
                    afterhours_maps.push_back(a4);
                    loading_map.clear();
                    map_init(loading_map);
                }
                else {
                    loading_map = map_append(i, loading_map);
                    loading_map["Volume"] += one.get_volume(i);
                }
            }
        }
    }
    
    void map_output(string time_des, map<string, int> input, int i, float percent_threshold, float percentile){
        cout << endl << dates[i] << endl;
        cout << time_des << endl;
        cout << name1 << days1 << " " << subset1 << endl;
        cout << name2 << days2 << " " << subset2 << endl;
        cout << "H/L " << percentile*100 << "%" << endl;
        cout << endl;
        cout << "  H  N  L" << endl;
        cout << "H " << input["HH"] << " " << input["HN"] << " " << input ["HL"] << endl;
        cout << "N " << input["NH"] << " " << input["NN"] << " " << input["NL"] << endl;
        cout << "L " << input["LH"] << " " << input["LN"] << " " << input["LL"] << endl;
        float threshold = input["T"]*(percent_threshold/100);
        int t1 = int(threshold);
        // input.insert({"Thresh", t1});
        cout << "        Thresh: " << t1 << endl;
        // cout << "             H: " << input["H"] << endl;
        // cout << "             L: " << input["L"] << endl;
        cout << "             T: " << input["T"] << endl;
        cout << "        Volume: " << input["Volume"] << endl;
        cout << endl;
    }
    
    void maps_output(int percent_threshold, float percentile){
        for (int i=0; i<(days-1); i++){
            map<string, int>& afterhours_map = afterhours_maps[i];
            map_output("After Hours", afterhours_map, i, percent_threshold, percentile);
            map<string, int>& lateday_map = lateday_maps[i];
            map_output("Late Day", lateday_map, i, percent_threshold, percentile);
            map<string, int>& tradingtime_map = tradingtime_maps[i];
            map_output("Trading Hour", tradingtime_map, i, percent_threshold, percentile);
            map<string, int>& premarket_map = premarket_maps[i];
            map_output("Pre Market", premarket_map, i, percent_threshold, percentile);
        }
    }
    
    int read_mapvalues(map<string, int> a, string type, int i, int n, float percent_threshold){
        int& total = a["T"];
        int h;
        int l;
        switch(n){
            case 1:
                h = a["H1"];
                l = a["L1"];
                break;
            case 2:
                h = a["H2"];
                l = a["L2"];
                break;
        }
        int& highs = h;
        int& lows = l;
        float threshold = total*(percent_threshold/100);
        int t1 = int(threshold);
        if(type == "Direction"){
            if ((highs > lows) && highs > t1){
                return 1;
            }
            else if ((lows > highs) && lows > t1){
                return 2;
            }
            else{
                return 3;
            }
        }
        else if (type == "Magnitude"){
            if ((highs > t1) || (lows > t1)){
                return 1;
            }
            else{
                return 2;
            }
        }
        else{
            return 0;
        }
    }
    
    int direction_or_reading(int a, int b){
        if (a == 1 || b == 1){
            return 1;
        }
        else if (a == 2 || b == 2){
            return 2;
        }
        else if (a == 3 && b == 3){
            return 3;
        }
        else{
            return 0;
        }
    }

    int direction_and_reading(int a, int b){
        if (a == 1 && b == 1){
            return 1;
        }
        else if (a == 2 && b == 2){
            return 2;
        }
        else{
            return 3;
        }
    }
    
    int direction_magnitude_and_reading_1(int a, int b){
        if (a == 1 && b == 1){
            return 1;
        }
        else if (a == 2 && b == 1){
            return 2;
        }
        else{
            return 3;
        }
    }
    
    
    int direction_magnitude_and_reading_2(int a, int b){
        if (a == 1 && b == 1){
            return 1;
        }
        else if (a == 1 && b == 2){
            return 2;
        }
        else{
            return 3;
        }
    }
    
    int read_pattern(int pre, int lastd, int lastt){
        if (lastt == 1 && lastd == 1 && pre == 1){
            return 1;
        }
        else if (lastt == 1 && lastd == 1 && pre == 2){
            return 1;
        }
        else if (lastt == 1 && lastd == 1 && pre == 3){
            return 1;
        }
        else if (lastt == 1 && lastd == 2 && pre == 1){
            return 1;
        }
        else if (lastt == 1 && lastd == 2 && pre == 2){
            return 2;
        }
        else if (lastt == 1 && lastd == 2 && pre == 3){
            return 2;
        }
        else if (lastt == 1 && lastd == 3 && pre == 1){
            return 1;
        }
        else if (lastt == 1 && lastd == 3 && pre == 2){
            return 2;
        }
        else if (lastt == 1 && lastd == 3 && pre == 3){
            return 3;
        }
        else if (lastt == 2 && lastd == 1 && pre == 1){
            return 1;
        }
        else if (lastt == 2 && lastd == 1 && pre == 2){
            return 2;
        }
        else if (lastt == 2 && lastd == 1 && pre == 3){
            return 1;
        }
        else if (lastt == 2 && lastd == 2 && pre == 1){
            return 2;
        }
        else if (lastt == 2 && lastd == 2 && pre == 2){
            return 2;
        }
        else if (lastt == 2 && lastd == 2 && pre == 3){
            return 2;
        }
        else if (lastt == 2 && lastd == 3 && pre == 1){
            return 1;
        }
        else if (lastt == 2 && lastd == 3 && pre == 2){
            return 2;
        }
        else if (lastt == 2 && lastd == 3 && pre == 3){
            return 3;
        }
        else if (lastt == 3 && lastd == 1 && pre == 1){
            return 1;
        }
        else if (lastt == 3 && lastd == 1 && pre == 2){
            return 2;
        }
        else if (lastt == 3 && lastd == 1 && pre == 3){
            return 3;
        }
        else if (lastt == 3 && lastd == 2 && pre == 1){
            return 1;
        }
        else if (lastt == 3 && lastd == 2 && pre == 2){
            return 2;
        }
        else if (lastt == 3 && lastd == 2 && pre == 3){
            return 3;
        }
        else if (lastt == 3 && lastd == 3 && pre == 1){
            return 3;
        }
        else if (lastt == 3 && lastd == 3 && pre == 2){
            return 3;
        }
        else if (lastt == 3 && lastd == 3 && pre == 3){
            return 3;
        }
        else{
            return 0;
        }
    }
    
    void read_patterns(string type1, string type2, string way, int percent_threshold){ // make way different for patterns and entry signals
        for (int i=0; i<(days-1); i++){
            map<string, int>& premarket = premarket_maps[i];
            map<string, int>& lastday = lateday_maps[i+1];
            map<string, int>& lasttrading = tradingtime_maps[i+1];
            int pm1 = read_mapvalues(premarket, type1, i, 1, percent_threshold);
            int pm2 = read_mapvalues(premarket, type2, i, 2, percent_threshold);
            int ld1 = read_mapvalues(lastday, type1, i, 1, percent_threshold);
            int ld2 = read_mapvalues(lastday, type2, i, 2, percent_threshold);
            int lt1 = read_mapvalues(lasttrading, type1, i, 1, percent_threshold);
            int lt2 = read_mapvalues(lasttrading, type2, i, 2, percent_threshold);
            // cout << lt1 << "  " << lt2 << "  " << ld1 << "  " << ld2 << "  " << pm1 << "  " << pm2 << endl;
            int premarket_reading;
            int lastday_reading;
            int lasttrading_reading;
            if (type1 == "Direction" && type2 == "Direction"){
                if (way == "OR"){
                    premarket_reading = direction_or_reading(pm1, pm2);
                    lastday_reading = direction_or_reading(ld1, ld2);
                    lasttrading_reading = direction_or_reading(lt1, lt2);
                    // cout << lasttrading_reading << "  " << lastday_reading << "  " << premarket_reading << endl;
                    int reading = read_pattern(premarket_reading, lastday_reading, lasttrading_reading);
                    // cout << reading << endl;
                    pattern_reading.push_back(reading);
                }
                else if (way == "AND"){
                    premarket_reading = direction_and_reading(pm1, pm2);
                    lastday_reading = direction_and_reading(ld1, ld2);
                    lasttrading_reading = direction_and_reading(lt1, lt2);
                    // cout << lasttrading_reading << "  " << lastday_reading << "  " << premarket_reading << endl;
                    int reading = read_pattern(premarket_reading, lastday_reading, lasttrading_reading);
                    // cout << reading << endl;
                    pattern_reading.push_back(reading);
                }
            }
            else if (type1 == "Direction" && (type2 == "Magnitude")){
                premarket_reading = direction_magnitude_and_reading_1(pm1, pm2);
                lastday_reading = direction_magnitude_and_reading_1(ld1, ld2);
                lasttrading_reading = direction_magnitude_and_reading_1(lt1, lt2);
                // cout << lasttrading_reading << "  " << lastday_reading << "  " << premarket_reading << endl;
                int reading = read_pattern(premarket_reading, lastday_reading, lasttrading_reading);
                // cout << reading << endl;
                pattern_reading.push_back(reading);
            }
            else if ((type1 == "Magnitude") && type2 == "Direction"){
                premarket_reading = direction_magnitude_and_reading_2(pm1, pm2);
                lastday_reading = direction_magnitude_and_reading_2(ld1, ld2);
                lasttrading_reading = direction_magnitude_and_reading_2(lt1, lt2);
                // cout << lasttrading_reading << "  " << lastday_reading << "  " << premarket_reading << endl;
                int reading = read_pattern(premarket_reading, lastday_reading, lasttrading_reading);
                // cout << reading << endl;
                pattern_reading.push_back(reading);
            }
        }
    }
    
    void read_current_pattern(string type1, string type2, string interval, string way, int percent_threshold){
        map<string, int>& lateday = lateday_maps[0];
        map<string, int>& trading = tradingtime_maps[0];
        int ld1 = read_mapvalues(lateday, type1, 0, 1, percent_threshold);
        int ld2 = read_mapvalues(lateday, type2, 0, 2, percent_threshold);
        int lt1 = read_mapvalues(trading, type1, 0, 1, percent_threshold);
        int lt2 = read_mapvalues(trading, type2, 0, 2, percent_threshold);
        float threshold = 0;
        if (interval == "1min"){
            threshold = 330*(float(percent_threshold)/100);
        }
        else if (interval == "5min"){
            threshold = 66*(float(percent_threshold)/100);
        }
        else if (interval == "30min"){
            threshold = 11*(float(percent_threshold)/100);
        }
        else if (interval == "1hour"){
            threshold = 5*(float(percent_threshold)/100);
        }
        int t1 = int(threshold);
        int lateday_reading;
        int trading_reading;
        if (type1 == "Direction" && type2 == "Direction"){
            if (way == "OR"){
                lateday_reading = direction_or_reading(ld1, ld2);
                trading_reading = direction_or_reading(lt1, lt2);
                int reading_if_1 = read_pattern(trading_reading, lateday_reading, 1);
                int reading_if_2 = read_pattern(trading_reading, lateday_reading, 2);
                int reading_if_3 = read_pattern(trading_reading, lateday_reading, 3);
                cout << endl << "Pattern Signals: " << endl;
                cout << "If " << t1 << " or more " << interval << " " << name1 << days1 << " " << subset1 << "s are above " << current_upper_restriction1 << " ";
                cout << way << endl;
                cout << t1 << " or more " << interval << " " << name2 << days2 << " " << subset2 << "s are above " << current_upper_restriction2;
                cout <<  " in the premarket, the reading of the current day is " << reading_if_1 << endl;
                cout << "If " << t1 << " or more " << interval << " " << name1 << days1 << " " << subset1 << "s are below " << current_lower_restriction1 << " ";
                cout << way << endl;
                cout << t1 << " or more " << interval << " " << name2 << days2 << " " << subset2 << "s are below " << current_lower_restriction2;
                cout <<  " in the premarket, the reading of the current day is " << reading_if_2 << endl;
                cout <<  "Otherwise, the reading of the current day is " << reading_if_3 << endl;
            }
            else if(way == "AND"){
                lateday_reading = direction_and_reading(ld1, ld2);
                trading_reading = direction_and_reading(lt1, lt2);
                int reading_if_1 = read_pattern(trading_reading, lateday_reading, 1);
                int reading_if_2 = read_pattern(trading_reading, lateday_reading, 2);
                int reading_if_3 = read_pattern(trading_reading, lateday_reading, 3);
                cout << endl << "Pattern Signals: " << endl;
                cout << "If " << t1 << " or more " << interval << " " << name1 << days1;
                cout << " " << subset1 << "s are above " << current_upper_restriction1 << " ";
                cout << way << endl;
                cout << t1 << " or more " << interval << " " << name2 << days2;
                cout << " " << subset2 << "s are above " << current_upper_restriction2;
                cout <<  " in the premarket, the reading of the current day is " << reading_if_1 << endl;
                cout << "If " << t1 << " or more " << name1 << days1 << " " << subset1 << "s are below " << current_lower_restriction1 << " ";
                cout << way << endl;
                cout << t1 << " or more " << name2 << days2 << " " << subset2 << "s are below " << current_lower_restriction2;
                cout <<  " in the premarket, the reading of the current day is " << reading_if_2 << endl;
                cout <<  "Otherwise, the reading of the current day is " << reading_if_3 << endl;
            }
        }
        else if (type1 == "Direction" && type2 == "Magnitude"){
            lateday_reading = direction_magnitude_and_reading_1(ld1, ld2);
            trading_reading = direction_magnitude_and_reading_1(lt1, lt2);
            int reading_if_1 = read_pattern(trading_reading, lateday_reading, 1);
            int reading_if_2 = read_pattern(trading_reading, lateday_reading, 2);
            int reading_if_3 = read_pattern(trading_reading, lateday_reading, 3);
            cout << endl << "Pattern Signals: " << endl;
            cout << "If " << t1 << " or more " << interval << " " << name1 << days1 << " " << subset1 << "s are above " << current_upper_restriction1 << " ";
            cout << way << endl;
            cout << t1 << " or more " << interval << " " << name2 << days2 << " " << subset2 << "s are above " << current_upper_restriction2 << " or below " << current_lower_restriction2;
            cout <<  " in the premarket, the reading of the current day is " << reading_if_1 << endl;
            cout << "If " << t1 << " or more " << interval << " " << name1 << days1 << " " << subset1 << "s are below " << current_lower_restriction1 << " ";
            cout << "AND" << endl;
            cout << t1 << " or more " << interval << " " << name2 << days2 << " " << subset2 << "s are above " << current_upper_restriction2 << " or below " << current_lower_restriction2 << " ";
            cout <<  " in the premarket, the reading of the current day is " << reading_if_2 << endl;
            cout <<  "Otherwise, the reading of the current day is " << reading_if_3 << endl;
        }
        else if (type1 == "Magnitude" && type2 == "Direction"){
            lateday_reading = direction_magnitude_and_reading_2(ld1, ld2);
            trading_reading = direction_magnitude_and_reading_2(lt1, lt2);
            int reading_if_1 = read_pattern(trading_reading, lateday_reading, 1);
            int reading_if_2 = read_pattern(trading_reading, lateday_reading, 2);
            int reading_if_3 = read_pattern(trading_reading, lateday_reading, 3);
            cout << endl << "Pattern Signals: " << endl;
            cout << "If " << threshold << " or more " << interval << " " << name1 << days1 << " " << subset1 << "s are above " << current_upper_restriction1 << " " << " or below " << current_lower_restriction1 << " ";
            cout << "AND" << endl;
            cout << threshold << " or more " << interval << " " << name2 << days2 << " " << subset2 << "s are above " << current_upper_restriction2;
            cout <<  " in the premarket, the reading of the current day is " << reading_if_1 << endl;
            cout << "If " << threshold << " or more " << interval << " " << name1 << days1 << " " << subset1 << "s are above " << current_upper_restriction1 << " " << " or below " << current_lower_restriction1 << " ";
            cout << way << endl;
            cout << threshold << " or more " << interval << " " << name2 << days2 << " " << subset2 << "s are below " << current_lower_restriction2;
            cout <<  " in the premarket, the reading of the current day is " << reading_if_2 << endl;
            cout <<  "Otherwise, the reading of the current day is " << reading_if_3 << endl;
        }
    }
    
    int get_pattern_reading(int c){
        return pattern_reading[c];
    }
    
    map<string, int> get_premarket_map(int c){
        return premarket_maps[c];
    }
    
    map<string, int> get_tradingtime_map(int c){
        return tradingtime_maps[c];
    }
    
    map<string, int> get_lateday_map(int c){
        return lateday_maps[c];
    }
    
    map<string, int> get_afterhours_map(int c){
        return afterhours_maps[c];
    }
    
};

class backtest{
private:
    string name1;
    int days1;
    string subset1;
    string name2;
    int days3;
    string subset2;
    vector<float> base1;
    vector<float> base2;
    vector<float> entry_low1s;
    vector<float> entry_up1s;
    vector<float> entry_base1s;
    vector<float> entry_low2s;
    vector<float> entry_up2s;
    vector<float> entry_base2s;
    vector<string> entry_times;
    vector<float> entry_points;
    vector<string> exit_times;
    vector<float> exit_points;
    vector<float> changes_from_entry;
public:
    backtest(analysis a, analysis b){
        base1 = a.base_public();
        base2 = b.base_public();
        name1 = a.get_name();
        days1 = a.get_days();
        subset1 = a.get_subset();
        name2 = b.get_name();
        days3 = b.get_days();
        subset2 = b.get_subset();
    }
    
    bool direction_high_outliers(float bs, float up){
        if (bs >= up){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool direction_low_outliers(float bs, float lw){
        if (bs <= lw){
            return true;
        }
        else{
            return false;
        }
    }

    bool magnitude_outliers(float bs, float up, float lw){
        if ((bs >= up) || (bs <= lw)){
            return true;
        }
        else{
            return false;
        }
    }
    
    void do_backtest(quotes one, analysis a, analysis b, pattern ss, string type1, string type2, string way, float take_profit, float stop_loss, int length, int days2){
        // input_days1 = a.get_input_days();
        int kthreshold = 0;
        if (one.interval3 == "1min"){
            kthreshold = 60;
        }
        else if (one.interval3 == "5min"){
            kthreshold = 12;
        }
        else if (one.interval3 == "30min"){
            kthreshold = 2;
        }
        int c = 0;
        int tries = 0;
        int successes = 0;
        int total = 0;
        float success_rate = 0;
        int calltries = 0;
        int callsuccesses = 0;
        float call_success_rate = 0;
        int puttries = 0;
        int putsuccesses = 0;
        float put_success_rate = 0;
        int opposing_tries = 0;
        int opposing_successes = 0;
        float opposing_successrate = 0;
        int matching_tries = 0;
        int matching_successes = 0;
        float matching_successrate = 0;
        float recent_successrate = 0;
        float highvolume_successrate = 0;
        int successes_inarow = 0;
        int failures_inarow = 0;
        float clump_index = 0;
        float profits_taken = 0;
        float losses_stopped = 0;
        int allminutes_toexit = 0;
        float averageminutes_toexit = 0;
        for(int i=0; i<length; i++){
            if(one.get_hour(i) == 9 && one.get_minute(i) == 30){
                total++;
                int k = 0;
                int o = 0;
                float base1now;
                float base2now;
                float upper;
                float lower;
                float upper2;
                float lower2;
                int reading1 = ss.get_pattern_reading(c);
                int& reading = reading1;
                bool success_failure = false;
                bool trye = false;
                int minutes_to_exit = 0;
                string entrymethod = "";
                while(k<kthreshold){
                    base1now = base1[i-k+1];
                    float& bs1 = base1now;
                    base2now = base2[i-k+1];
                    float& bs2 = base2now;
                    upper = a.get_ninetyfifthp(i-k+1);
                    float& up = upper;
                    lower = a.get_fifthp(i-k+1);
                    float& lw = lower;
                    upper2 = b.get_ninetyfifthp(i-k+1);
                    float& up2 = upper2;
                    lower2 = b.get_fifthp(i-k+1);
                    float& lw2 = lower2;
                    bool lowrange1 = false;
                    bool uprange1 = false;
                    bool lowrange2 = false;
                    bool uprange2 = false;
                    if (type1 == "Direction"){
                        lowrange1 = direction_low_outliers(bs1, lw);
                        uprange1 = direction_high_outliers(bs1, up);
                    }
                    else if (type1 == "Magnitude"){
                        lowrange1 = magnitude_outliers(bs1, up, lw);
                        uprange1 = magnitude_outliers(bs1, up, lw);
                    }
                    if (type2 == "Direction"){
                        lowrange2 = direction_low_outliers(bs2, lw2);
                        uprange2 = direction_high_outliers(bs2, up2);
                    }
                    else if (type2 == "Magnitude"){
                        lowrange2 = magnitude_outliers(bs2, up2, lw2);
                        uprange2 = magnitude_outliers(bs2, up2, lw2);
                    }
                    if (way == "OR"){
                        if (reading == 1){
                            if (lowrange1 || lowrange2){
                                tries++;
                                opposing_tries++;
                                calltries++;
                                trye = true;
                                entrymethod = "Opposing";
                                break;
                            }
                            else if (uprange1 || uprange2){
                                o++;
                            }
                            else if (o != 0){
                                matching_tries++;
                                calltries++;
                                tries++;
                                trye = true;
                                entrymethod = "Matching";
                                break;
                            }
                        }
                        else if (reading == 2){
                            if (uprange1 || uprange2){
                                opposing_tries++;
                                puttries++;
                                tries++;
                                trye = true;
                                entrymethod = "Opposing";
                                break;
                            }
                            else if (lowrange1 || lowrange2){
                                o++;
                            }
                            else if (o != 0){
                                matching_tries++;
                                puttries++;
                                tries++;
                                trye = true;
                                entrymethod = "Matching";
                                break;
                            }
                        }
                        else if (reading == 3){
                            break;
                        }
                    }
                    else if (way == "AND"){
                        if (reading == 1){
                            if (lowrange1 && lowrange2){
                                opposing_tries++;
                                calltries++;
                                tries++;
                                trye = true;
                                entrymethod = "Opposing";
                                break;
                            }
                            else if (uprange1 && uprange2){
                                o++;
                            }
                            else if (o != 0){
                                matching_tries++;
                                calltries++;
                                tries++;
                                trye = true;
                                entrymethod = "Matching";
                                break;
                            }
                        }
                        else if (reading == 2){
                            if (lowrange1 && lowrange2){
                                o++;
                            }
                            else if (o != 0){
                                matching_tries++;
                                puttries++;
                                tries++;
                                trye = true;
                                entrymethod = "Matching";
                                break;
                            }
                            else if (uprange1 && uprange2){
                                opposing_tries++;
                                puttries++;
                                tries++;
                                entrymethod = "Opposing";
                                trye = true;
                                break;
                            }
                        }
                        else if (reading == 3){
                            break;
                        }
                    }
                    k++;
                }
                float& up1_atentry = upper;
                float& low1_atentry = lower;
                float& base1_atentry = base1now;
                float& up2_atentry = upper2;
                float& low2_atentry = lower2;
                float& base2_atentry = base2now;
                entry_up1s.push_back(up1_atentry);
                entry_up2s.push_back(up2_atentry);
                entry_base1s.push_back(base1_atentry);
                entry_base2s.push_back(base2_atentry);
                entry_low1s.push_back(low1_atentry);
                entry_low2s.push_back(low2_atentry);
                float entry = one.get_close(i-k+1);
                float& current_entrypoint = entry;
                entry_points.push_back(current_entrypoint);
                string time1 = one.get_time(i-k);
                string& current_entrytime = time1;
                entry_times.push_back(current_entrytime);
                float exit = 0;
                while(k<kthreshold+(kthreshold/2)){
                    /* float highnow = one.get_high(i-k+1);
                    float& hn = highnow;
                    float lownow = one.get_low(i-k+1);
                    float& ln = lownow; */
                    minutes_to_exit++;
                    allminutes_toexit++;
                    float closenow = one.get_close(i-k+1);
                    float& cn = closenow;
                    if (reading == 1){
                        if(((cn - current_entrypoint) / current_entrypoint) >= take_profit/100){
                            if (entrymethod == "Matching"){
                                matching_successes++;
                            }
                            else if (entrymethod == "Opposing"){
                                opposing_successes++;
                            }
                            callsuccesses++;
                            successes++;
                            success_failure = true;
                            profits_taken += ((cn - current_entrypoint) / current_entrypoint)*100;
                            exit = cn;
                            break;
                        }
                        else if(-((cn - current_entrypoint) / current_entrypoint) >= stop_loss/100){
                            losses_stopped += (-(cn - current_entrypoint) / current_entrypoint)*100;
                            exit = cn;
                            break;
                        }
                    }
                    else if (reading == 2){
                        if(((cn - current_entrypoint) / current_entrypoint) <= -take_profit/100){
                            if (entrymethod == "Matching"){
                                matching_successes++;
                            }
                            else if (entrymethod == "Opposing"){
                                opposing_successes++;
                            }
                            putsuccesses++;
                            successes++;
                            success_failure = true;
                            profits_taken += (-(cn - current_entrypoint) / current_entrypoint)*100;
                            exit = cn;
                            break;
                        }
                        else if (((cn - current_entrypoint) / current_entrypoint) >= stop_loss/100){
                            losses_stopped += ((cn - current_entrypoint) / current_entrypoint)*100;
                            exit = cn;
                            break;
                        }
                    }
                    else if (reading == 3){
                        break;
                    }
                    k++;
                }
                if (exit == 0){
                    exit = one.get_close(i-k+1);
                }
                float& current_exitpoint = exit;
                exit_points.push_back(current_exitpoint);
                string time = one.get_time(i-k);
                string& current_exittime = time;
                exit_times.push_back(current_exittime);
                string date = one.get_date(i-k);
                string& d1 = date;
                float ratio = (current_exitpoint - current_entrypoint) / current_entrypoint;
                float& r1 = ratio;
                changes_from_entry.push_back(r1);
                if (k == kthreshold+(kthreshold/2) && trye == true){
                    if (reading == 1){
                        if (r1 > 0){
                            profits_taken += abs(r1*100);
                            if (entrymethod == "Matching"){
                                matching_successes++;
                            }
                            else if (entrymethod == "Opposing"){
                                opposing_successes++;
                            }
                            successes++;
                            callsuccesses++;
                            success_failure = true;
                        }
                        else{
                            losses_stopped += abs(r1*100);
                        }
                    }
                    else if (reading == 2){
                        if (r1 < 0){
                            profits_taken += abs(r1*100);
                            if (entrymethod == "Matching"){
                                matching_successes++;
                            }
                            else if (entrymethod == "Opposing"){
                                opposing_successes++;
                            }
                            successes++;
                            putsuccesses++;
                            success_failure = true;
                        }
                        else{
                            losses_stopped += abs(r1*100);
                        }
                    }
                }
                if (trye == true){
                    cout << fixed << setprecision(2);
                    string day_status;
                    if (reading == 1){
                        day_status = "Calls";
                    }
                    else if (reading == 2){
                        day_status = "Puts";
                    }
                    cout << d1 << "  " << current_entrytime << "  " << current_entrypoint << "  " << day_status << "  " << take_profit << "%";
                    cout << "  " << stop_loss << "%" << endl;
                    cout << "           " << entrymethod << endl;
                    cout << "           " << name1 << days1 << " " << subset1 << "  " << base1_atentry << "  " << low1_atentry << "  " << up1_atentry;
                    cout << endl;
                    cout << "           " << name2 << days3 << " " << subset2 << "  " << base2_atentry << "  " << low2_atentry << "  " << up2_atentry << endl;
                    cout << "           " << current_exittime << "  " << current_exitpoint << "  " << r1*100 << "%  " << success_failure;
                    cout << "  " << trye << endl;
                    cout << "           " << minutes_to_exit << " minutes" << endl << endl;
                }
                c++;
                if (c==days2){
                    break;
                }
            }
        }
        float t = float(tries);
        float s = float(successes);
        success_rate = float(s/t)*100;
        float ct = float(calltries);
        float cs = float(callsuccesses);
        call_success_rate = float(cs/ct)*100;
        float pt = float(puttries);
        float ps = float(putsuccesses);
        put_success_rate = float(ps/pt)*100;
        float mt = float(matching_tries);
        float ms = float(matching_successes);
        matching_successrate = float(ms/mt)*100;
        float ot = float(opposing_tries);
        float os = float(opposing_successes);
        opposing_successrate = float(os/ot)*100;
        float mte = float(allminutes_toexit);
        averageminutes_toexit = (mte/t);
        cout << endl << fixed << setprecision(2);
        cout << "Success Rate: " << success_rate << "% " << successes << "/" << tries << "/" << total << endl;
        cout << "Calls: " << call_success_rate << "% " << callsuccesses << "/" << calltries << endl;
        cout << "Puts: " << put_success_rate << "% " << putsuccesses << "/" << puttries << endl;
        cout << "Matching Side Entry: " << matching_successrate << "% " << matching_successes << "/" << matching_tries << endl;
        cout << "Opposing Side Entry: " << opposing_successrate << "% " << opposing_successes << "/" << opposing_tries << endl;
        cout << "Average Minutes to Exit: " << averageminutes_toexit << endl;
        cout << "Profits Taken:Losses Stopped: " << profits_taken*100 << "%:" << losses_stopped*100 << "%" << endl;
        /*
        cout << "$250 Per Attempt: $" << (profits_taken*250) - (losses_stopped*250) << endl;
        cout << "$500 Per Attempt: $" << (profits_taken*500) - (losses_stopped*500) << endl;
        cout << "$1000 Per Attempt: $" << (profits_taken*1000) - (losses_stopped*1000) << endl;
        cout << "$2500 Per Attempt: $" << (profits_taken*2500) - (losses_stopped*2500) << endl;
        cout << "$5000 Per Attempt: $" << (profits_taken*5000) - (losses_stopped*5000) << endl;
        cout << "$10000 Per Attempt: $" << (profits_taken*10000) - (losses_stopped*10000) << endl;
        */
    }
    void get_entry_signals(quotes one, analysis a, analysis b, string way, string type1, string type2){
        cout << endl << "Entry Signals: " << endl;
        if (type1 == "Direction" && type2 == "Direction"){
            cout << one.interval3 << " " << a.get_name() << a.get_days() << " " << a.get_subset() << " below " << a.get_fifthp(0) << " " << way << " ";
            cout << one.interval3 << " " << b.get_name() << b.get_days() << " " << b.get_subset() << " below " << b.get_fifthp(0) << ", or" << endl;
            cout << one.interval3 << " " << a.get_name() << a.get_days() << " " << a.get_subset() << " above " << a.get_ninetyfifthp(0) << " " << way << " ";
            cout << one.interval3 << " " << b.get_name() << b.get_days() << " " << b.get_subset() << " above " << b.get_ninetyfifthp(0) << endl << endl;
        }
        else if(type1 == "Direction" && type2 == "Magnitude"){
            cout << one.interval3 << " " << a.get_name() << a.get_days() << " " << a.get_subset() << " below " << a.get_fifthp(0) << " AND ";
            cout << one.interval3 << " " << b.get_name() << b.get_days() << " " << b.get_subset() << " above " << b.get_ninetyfifthp(0) << " or below " << b.get_fifthp(0) << ", or" << endl;
            cout << one.interval3 << " " << a.get_name() << a.get_days() << " " << a.get_subset() << " above " << a.get_ninetyfifthp(0) << " AND ";
            cout << one.interval3 << " " << b.get_name() << b.get_days() << " " << b.get_subset() << " above " << b.get_ninetyfifthp(0) << " or below " << b.get_fifthp(0) << endl;
        }
        else if (type1 == "Magnitude" && type2 == "Direction"){
            cout << one.interval3 << " " << a.get_name() << a.get_days() << " " << a.get_subset() << " above " << a.get_ninetyfifthp(0) << " or below " << a.get_fifthp(0) << " AND ";
            cout << one.interval3 << " " << b.get_name() << b.get_days() << " " << b.get_subset() << " below " << b.get_fifthp(0) << ", or" << endl;
            cout << one.interval3 << " " << a.get_name() << a.get_days() << " " << a.get_subset() << " above " << a.get_ninetyfifthp(0) << " or below " << a.get_fifthp(0) << " AND ";
            cout << one.interval3 << " " << b.get_name() << b.get_days() << " " << b.get_subset() << " above " << b.get_ninetyfifthp(0) << endl;
        }
    }
    void get_exit_signals(float takep, float stopl){
        cout << "Exit when the underlying changes " << takep << "% in the correct direction for a profit, or ";
        cout << stopl << "% in the incorrect direction for a loss" << endl << endl;
    }
};

