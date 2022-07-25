//
//  user_input.h
//  Quantitative Trading Model
//
//  Created by Sam Hopkins on 6/19/22.
//

#include "comparisons.h"

void user_input(){
    string symbol;
    string symbol1;
    string interval;
    string interval1;
    cout << "Symbol for Pattern Reading: ";
    cin >> symbol;
    cout << "Interval for Pattern Reading: ";
    cin >> interval;
    cout << "Symbol for Backtest: ";
    cin >> symbol1;
    cout << "Interval for Backtest: ";
    cin >> interval1;
    cout << "Trading Days for Test: ";
    int days1;
    cin >> days1;
    cout << endl;
    string choice1;
    int c1;
    int input_days;
    int signal_days;
    int area_days;
    string choice2;
    int c2;
    int input_days2;
    int signal_days2;
    int area_days2;
    string choice3;
    int c3;
    int input_days3;
    int signal_days3;
    int area_days3;
    string choice4;
    int c4;
    int input_days4;
    int signal_days4;
    int area_days4;
    cout << "Pattern Indicators: " << endl;
    cout << "  Direction: " << endl;
    cout << "     1) Close" << endl;
    cout << "     2) EMA" << endl;
    cout << "     3) MACD" << endl;
    cout << "     4) MACA" << endl;
    cout << "     5) MADA" << endl;
    cout << "     6) ROC" << endl;
    cout << "     7) RSI" << endl;
    cout << "  Support/Resistance: " << endl;
    cout << "     8) BOLL Proximity" << endl;
    cout << "     9) FibLvl Proximity" << endl;
    cout << endl << "Pattern Indicator 1: ";
    cin >> c1;
    cout << "Units: ";
    cin >> input_days;
    cout << "Signal Units: ";
    cin >> signal_days;
    cout << "Area Units: ";
    cin >> area_days;
    cout << endl << "Pattern Indicator 2: ";
    cin >> c2;
    cout << "Units: ";
    cin >> input_days2;
    cout << "Signal Units: ";
    cin >> signal_days2;
    cout << "Area Units: ";
    cin >> area_days2;
    cout << "Indicator Sub-Values" << endl;
    cout << "     1) Value" << endl;
    cout << "     2) Signal" << endl;
    cout << "     3) Change" << endl;
    cout << "     4) Signal Change" << endl;
    cout << "     5) 2Change" << endl;
    cout << "     6) Signal 2Change" << endl;
    cout << "     7) Difference" << endl;
    cout << "     8) Area in Last X" << endl;
    cout << "     9) Area since Conversion" << endl;
    cout << endl;
    cout << "Sub-Value of Indicator 1: ";
    int c9;
    string user_choice1;
    cin >> c9;
    cout << "Sub-Value of Indicator 2: ";
    int c5;
    string user_choice2;
    cin >> c5;
    int days3;
    cout << endl << "Trading Days Measured for Determining Outliers of Pattern Indicators: ";
    cin >> days3;
    float per1;
    cout << "Required Upper/Lower Percentile for Pattern Indicator Outlier Status: ";
    cin >> per1;
    float percentile = per1/100;
    float takep1;
    float stopl1;
    int percentage;
    int c8;
    int c7;
    cout << "Required Percentage of Values at Outliers to Signal Pattern: ";
    cin >> percentage;
    cout << "Conditions for Reading Pattern Signals" << endl;
    cout << "     1) OR" << endl;
    cout << "     2) AND" << endl;
    cout << "Enter: ";
    cin >> c8;
    cout << endl;
    cout << "Entry Indicators: " << endl;
    cout << "  Direction: " << endl;
    cout << "     1) Close" << endl;
    cout << "     2) EMA" << endl;
    cout << "     3) MACD" << endl;
    cout << "     4) MACA" << endl;
    cout << "     5) MADA" << endl;
    cout << "     6) ROC" << endl;
    cout << "     7) RSI" << endl;
    cout << "  Support/Resistance: " << endl;
    cout << "     8) BOLL Proximity" << endl;
    cout << "     9) FibLvl Proximity" << endl;
    cout << endl << "Entry Indicator 1: ";
    cin >> c3;
    cout << "Units: ";
    cin >> input_days3;
    cout << "Signal Units: ";
    cin >> signal_days3;
    cout << "Area Units: ";
    cin >> area_days3;
    cout << endl << "Entry Indicator 2: ";
    cin >> c4;
    cout << "Units: ";
    cin >> input_days4;
    cout << "Signal Units: ";
    cin >> signal_days4;
    cout << "Area Units: ";
    cin >> area_days4;
    cout << "Indicator Sub-Values" << endl;
    cout << "     1) Value" << endl;
    cout << "     2) Signal" << endl;
    cout << "     3) Change" << endl;
    cout << "     4) Signal Change" << endl;
    cout << "     5) 2Change" << endl;
    cout << "     6) Signal 2Change" << endl;
    cout << "     7) Difference" << endl;
    cout << "     8) Area in Last X" << endl;
    cout << "     9) Area since Conversion" << endl;
    cout << endl;
    cout << "Sub-Value of Indicator 1: ";
    int c10;
    string user_choice3;
    cin >> c10;
    cout << "Sub-Value of Indicator 2: ";
    int c11;
    string user_choice4;
    cin >> c11;
    int days4;
    cout << endl << "Trading Days Measured for Determining Outliers of Entry Indicators: ";
    cin >> days4;
    cout << "Required Upper/Lower Percentile for Entry Indicator Outlier Status: ";
    float per2;
    cin >> per2;
    float percentile2 = per2/100;
    cout << "Conditions for Reading Entry Signals" << endl;
    cout << "     1) OR" << endl;
    cout << "     2) AND" << endl;
    cout << "Enter: ";
    cin >> c7;
    cout << "%Change in Correct Direction for Take Profit Trigger: ";
    cin >> takep1;
    cout << "%Change in Incorrect Direction for Stop Loss Trigger: ";
    cin >> stopl1;
    cout << endl;
    int multiplier;
    int multiplier1;
    int patterns_length;
    int backtest_length;
    if (interval == "1min"){
        multiplier = 960;
    }
    else if (interval == "5min"){
        multiplier = 192;
    }
    else if (interval == "30min"){
        multiplier = 32;
    }
    else if (interval == "1hour"){
        multiplier = 16;
    }
    else{
        multiplier = 0;
    }
    if (interval1 == "1min"){
        multiplier1 = 960;
    }
    else if (interval1 == "5min"){
        multiplier1 = 192;
    }
    else if (interval1 == "30min"){
        multiplier1 = 32;
    }
    else if (interval1 == "1hour"){
        multiplier1 = 16;
    }
    else{
        multiplier1 = 0;
    }
    patterns_length = days1*multiplier;
    backtest_length = days1*multiplier1;
    quotes patterns(symbol, interval, 10, 1);
    quotes backtests(symbol1, interval1, 10, 1);
    vector<float> base1;
    vector<float> base2;
    vector<float> base3;
    vector<float> base4;
    string type1;
    string type2;
    string type3;
    string type4;
    if(c1 == 1){
        base1 = patterns.closes_public();
        choice1 = "Close";
        type1 = "Direction";
    }
    else if (c1 == 2){
        base1 = EmA(patterns, input_days, 10);
        choice1 = "EMA";
        type1 = "Direction";
    }
    else if (c1 == 3){
        base1 = MACD(patterns, input_days, input_days*2, 10);
        choice1 = "MACD";
        type1 = "Direction";
    }
    else if (c1 == 6){
        base1 = ROC(patterns, input_days);
        choice1 = "ROC";
        type1 = "Direction";
    }
    else if (c1 == 7){
        base1 = RSI(patterns, input_days, rsi_components(patterns, input_days));
        choice1 = "RSI";
        type1 = "Direction";
    }
    else if (c1 == 4){
        base1 = area_since_conversion(patterns, EmA(patterns, input_days, 10), EmA(patterns, input_days*2, 10));
        choice1 = "AreainceC";
        type1 = "Direction";
    }
    else if (c1 == 5){
        base1 = area_in_last(patterns, EmA(patterns, input_days, 10), EmA(patterns, input_days*2, 10), input_days);
        choice1 = "AreainL";
        type1 = "Direction";
    }
    else if (c1 == 8){
        base1 = proximityto_closest_bollband(patterns, bollinger_bands(patterns, input_days));
        choice1 = "ProxtoBoll";
        type1 = "Magnitude";
    }
    else if (c1 == 9){
        base1 = proximityto_closest_fiblvl(patterns, fibonacci_levels(patterns, input_days));
        choice1 = "ProxtoFib";
        type1 = "Magnitude";
    }
    if(c2 == 1){
        base2 = patterns.closes_public();
        choice2 = "Close";
        type2 = "Direction";
    }
    else if (c2 == 2){
        base2 = EmA(patterns, input_days2, 10);
        choice2 = "EMA";
        type2 = "Direction";
    }
    else if (c2 == 3){
        base2 = MACD(patterns, input_days2, input_days2*2, 10);
        choice2 = "MACD";
        type2 = "Direction";
    }
    else if (c2 == 6){
        base2 = ROC(patterns, input_days2);
        choice2 = "ROC";
        type2 = "Direction";
    }
    else if (c2 == 7){
        base2 = RSI(patterns, input_days2, rsi_components(patterns, input_days2));
        choice2 = "RSI";
        type2 = "Direction";
    }
    else if (c2 == 4){
        base2 = area_since_conversion(patterns, EmA(patterns, input_days2, 10), EmA(patterns, input_days2*2, 10));
        choice2 = "AreainceC";
        type2 = "Direction";
    }
    else if (c2 == 5){
        base2 = area_in_last(patterns, EmA(patterns, input_days2, 10), EmA(patterns, input_days2*2, 10), input_days2);
        choice2 = "AreainL";
        type2 = "Direction";
    }
    else if (c2 == 8){
        base2 = proximityto_closest_bollband(patterns, bollinger_bands(patterns, input_days2));
        choice2 = "ProxtoBoll";
        type2 = "Magnitude";
    }
    else if (c2 == 9){
        base2 = proximityto_closest_fiblvl(patterns, fibonacci_levels(patterns, input_days2));
        choice2 = "ProxtoFib";
        type2 = "Magnitude";
    }
    if(c3 == 1){
        base3 = backtests.closes_public();
        choice3 = "Close";
        type3 = "Direction";
    }
    else if (c3 == 2){
        base3 = EmA(backtests, input_days3, 10);
        choice3 = "EMA";
        type3 = "Direction";
    }
    else if (c3 == 3){
        base3 = MACD(backtests, input_days3, input_days3*2, 10);
        choice3 = "MACD";
        type3 = "Direction";
    }
    else if (c3 == 6){
        base3 = ROC(backtests, input_days3);
        choice3 = "ROC";
        type3 = "Direction";
    }
    else if (c3 == 7){
        base3 = RSI(backtests, input_days3, rsi_components(backtests, input_days3));
        choice3 = "RSI";
        type3 = "Direction";
    }
    else if (c3 == 4){
        base3 = area_since_conversion(patterns, EmA(patterns, input_days3, 10), EmA(patterns, input_days3*2, 10));
        choice3 = "AreainceC";
        type3 = "Direction";
    }
    else if (c3 == 5){
        base3 = area_in_last(patterns, EmA(patterns, input_days3, 10), EmA(patterns, input_days3*2, 10), input_days3);
        choice3 = "AreainL";
        type3 = "Direction";
    }
    else if (c3 == 8){
        base3 = proximityto_closest_bollband(patterns, bollinger_bands(patterns, input_days3));
        choice3 = "ProxtoBoll";
        type3 = "Magnitude";
    }
    else if (c3 == 9){
        base3 = proximityto_closest_fiblvl(patterns, fibonacci_levels(patterns, input_days3));
        choice3 = "ProxtoFib";
        type3 = "Magnitude";
    }
    if(c4 == 1){
        base4 = backtests.closes_public();
        choice4 = "Close";
        type4 = "Direction";
    }
    else if (c4 == 2){
        base4 = EmA(backtests, input_days4, 10);
        choice4 = "EMA";
        type4 = "Direction";
    }
    else if (c4 == 3){
        base4 = MACD(backtests, input_days4, input_days4*2, 10);
        choice4 = "MACD";
        type4 = "Direction";
    }
    else if (c4 == 6){
        base4 = ROC(backtests, input_days4);
        choice4 = "ROC";
        type4 = "Direction";
    }
    else if (c4 == 7){
        base4 = RSI(backtests, input_days4, rsi_components(backtests, input_days4));
        choice4 = "RSI";
        type4 = "Direction";
    }
    else if (c4 == 4){
        base4 = area_since_conversion(patterns, EmA(patterns, input_days4, 10), EmA(patterns, input_days4*2, 10));
        choice4 = "AreainceC";
        type4 = "Direction";
    }
    else if (c4 == 5){
        base4 = area_in_last(patterns, EmA(patterns, input_days4, 10), EmA(patterns, input_days4*2, 10), input_days4);
        choice4 = "AreainL";
        type4 = "Direction";
    }
    else if (c4 == 8){
        base4 = proximityto_closest_bollband(patterns, bollinger_bands(patterns, input_days4));
        choice4 = "ProxtoBoll";
        type4 = "Magnitude";
    }
    else if (c4 == 9){
        base4 = proximityto_closest_fiblvl(patterns, fibonacci_levels(patterns, input_days4));
        choice4 = "ProxtoFib";
        type4 = "Magnitude";
    }
    analysis i1(choice1, input_days, base1, signal_days, 10, area_days, 1, patterns_length);
    analysis i2(choice2, input_days2, base2, signal_days2, 10, area_days2, 1, patterns_length);
    analysis j1(choice3, input_days3, base3, signal_days3, 10, area_days3, 1, backtest_length);
    analysis j2(choice4, input_days4, base4, signal_days4, 10, area_days4, 1, backtest_length);
    switch(c9){
        case 1:
            user_choice1 = "Value";
            break;
        case 2:
            user_choice1 = "Signal";
            break;
        case 3:
            user_choice1 = "Change";
            break;
        case 4:
            user_choice1 = "Signal Change";
            break;
        case 5:
            user_choice1 = "2Change";
            break;
        case 6:
            user_choice1 = "Signal 2Change";
            break;
        case 7:
            user_choice1 = "Difference";
            break;
        case 8:
            user_choice1 = "LArea";
            break;
        case 9:
            user_choice1 = "TArea";
            break;
    }
    switch(c5){
        case 1:
            user_choice2 = "Value";
            break;
        case 2:
            user_choice2 = "Signal";
            break;
        case 3:
            user_choice2 = "Change";
            break;
        case 4:
            user_choice2 = "Signal Change";
            break;
        case 5:
            user_choice2 = "2Change";
            break;
        case 6:
            user_choice2 = "Signal 2Change";
            break;
        case 7:
            user_choice2 = "Difference";
            break;
        case 8:
            user_choice2 = "LArea";
            break;
        case 9:
            user_choice2 = "TArea";
            break;
    }
    switch(c10){
        case 1:
            user_choice3 = "Value";
            break;
        case 2:
            user_choice3 = "Signal";
            break;
        case 3:
            user_choice3 = "Change";
            break;
        case 4:
            user_choice3 = "Signal Change";
            break;
        case 5:
            user_choice3 = "2Change";
            break;
        case 6:
            user_choice3 = "Signal 2Change";
            break;
        case 7:
            user_choice3 = "Difference";
            break;
        case 8:
            user_choice3 = "LArea";
            break;
        case 9:
            user_choice3 = "TArea";
            break;
    }
    switch(c11){
        case 1:
            user_choice4 = "Value";
            break;
        case 2:
            user_choice4 = "Signal";
            break;
        case 3:
            user_choice4 = "Change";
            break;
        case 4:
            user_choice4 = "Signal Change";
            break;
        case 5:
            user_choice4 = "2Change";
            break;
        case 6:
            user_choice4 = "Signal 2Change";
            break;
        case 7:
            user_choice4 = "Difference";
            break;
        case 8:
            user_choice4 = "LArea";
            break;
        case 9:
            user_choice4 = "TArea";
            break;
    }
    string way1;
    string way2;
    switch(c8){
        case 1:
            way1 = "OR";
            break;
        case 2:
            way1 = "AND";
            break;
    }
    switch(c7){
        case 1:
            way2 = "OR";
            break;
        case 2:
            way2 = "AND";
            break;
    }
    cout << interval << " " << choice1 << input_days << " " << user_choice1 << "s, " << choice2 << input_days2 << " " << user_choice2 << "s in the top or bottom " << per1 << "% of values recorded in the trailing ";
    cout << days3 << " days are marked as outliers." << endl;
    // cout << "If the indicator is a magnitude indicator, either subset of " << endl;
    cout << "If " << percentage << "% or more of all " << interval << " " << choice1 << input_days << " " << user_choice1 << "s " << way1 << " " << choice2 << input_days2 << " " << user_choice2 << "s in a subset of a day are outliers, that period is marked according to the skew in outliers; if not, it is marked null." << endl;
    cout << "The day leading up to each market open is split up into three subsets:" << endl;
    cout << "     - first hour of day" << endl;
    cout << "     - rest of day" << endl;
    cout << "     - pre-market" << endl;
    cout << "After-hours is not considered due to lack of volatility." << endl;
    cout << "Each subset of the trailing day is marked according to its skew in outliers as upward leaning, downward leaning, or neither." << endl;
    cout << "The pattern leading up to the trading day is marked according to the most common skew among the three. If no skew is most common, it is marked according to the most recent." << endl << endl;
    cout << interval1 << " " << choice3 << input_days3 << " " << user_choice3 << "s, " << choice4 << input_days4 << " " << user_choice4 << "s in the top or bottom " << per2 << "% of values recorded in the trailing ";
    cout << days4 << " days are marked as outliers." << endl;
    cout << "If " << interval1 << " " << choice3 << input_days3 << " " << user_choice3 << " " << way2 << " " << choice4 << input_days4 << " " << user_choice4 << " reaches an outlier value between 9:30 and 10:30:" << endl;
    cout << "     - if it implies the opposite of the recognized pattern, an entry is triggered;" << endl;
    cout << "     - if it implies the same as the recognized pattern, an entry is triggered when it leaves outlier territory." << endl;
    cout << "     - If neither input reaches an outlier value, the day is marked null." << endl << endl;
    cout << "The change in the underlying from the entry point is recorded." << endl;
    cout << "If the underlying changes " << takep1 << "% in the correct direction, an exit is recorded and the day is marked a success. " << endl;
    cout << "If the underlying changes " << stopl1 << "% in the incorrect direction, an exit is recorded and the day is marked a failure." << endl;
    cout << "If neither one of these things happens by 11:00, the day is marked according to whether or not the direction of the change since the entry matches that of the chosen position." << endl << endl;
    int units3 = days3*multiplier;
    int units4 = days4*multiplier1;
    i1.load_percentiles(user_choice1, percentile, units3, patterns_length);
    i2.load_percentiles(user_choice2, percentile, units3, patterns_length);
    pattern pat(i1, i2, patterns_length);
    // pat.output_comparison(patterns, patterns_length);
    pat.create_maps(patterns, patterns_length);
    pat.read_patterns(type1, type2, way1, percentage);
    j1.load_percentiles(user_choice3, percentile2, units4, backtest_length);
    j2.load_percentiles(user_choice4, percentile2, units4, backtest_length);
    backtest back(j1, j2);
    // pat.maps_output(percentage, percentile);
    back.do_backtest(backtests, j1, j2, pat, type3, type4, way2, takep1, stopl1, backtest_length, days1);
    pat.read_current_pattern(type1, type2, interval, way1, percentage);
    back.get_entry_signals(backtests, j1, j2, way2, type3, type4);
    back.get_exit_signals(takep1, stopl1);
}
