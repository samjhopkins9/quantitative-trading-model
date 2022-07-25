//
//  indicators.h
//  Quantitative Trading Model
//
//  Created by Sam Hopkins on 6/15/22.
//

#include "quotes.h"

class indicator{
protected:
    vector<float> value;
    stack<float> total_sum;
    vector<float> average;
    vector<float> signal;
    vector<float> change;
    vector<float> signal_change;
    vector<float> second_change;
    vector<float> signal_second_change;
    vector<float> difference;
    vector<float> areabetween_inlast;
    vector<float> area_between_valsig;
public:
    string name;
    int input_days;
    int signal_days1;
    int range_days1;
    int change_increments1;
    int area_days1;
    indicator(string name1, int input_days1, vector<float> a, int signal_days, int area_days, int signal_weighting, int change_increments, int length){
        name = name1;
        input_days = input_days1;
        signal_days1 = signal_days;
        change_increments1 = change_increments;
        area_days1 = area_days;
        for (int i=0; i < length; i++){
            value.push_back(a[i]);
        }
        for (int i=0; i<length; i++){
            for(int u=0; u<signal_days; u++){
                if (u==0){
                    total_sum.push(0.00+value[i+u]);
                }
                else {
                    total_sum.push(total_sum.top()+value[i+u]);
                }
            }
            average.push_back(total_sum.top()/total_sum.size());
            while (!total_sum.empty()){
                total_sum.pop();
            }
        }
        for(int i=0; i<length; i++){
            signal.push_back(value[i]*(signal_weighting/100.0) + average[i]*(1.0 - (signal_weighting/100.0)));
            difference.push_back(value[i] - signal[i]);
            change.push_back(value[i] - value[i+change_increments]);
            second_change.push_back((value[i] - value[i+change_increments]) - (value[i+change_increments] - value[i+2*change_increments]));
        }
        for(int i=0; i<length; i++){
            signal_change.push_back(signal[i] - signal[i+change_increments]);
            signal_second_change.push_back((signal[i] - signal[i+change_increments]) - (signal[i+change_increments] - signal[i+2*change_increments]));
        }
        for(int i=0; i<length; i++){
            float area = 0;
            int c = 0;
            do {
                area += difference[c+i];
                c++;
            } while (!(difference[c+i-1]/difference[c+i] < 0));
            area_between_valsig.push_back(area);
        }
        for(int j=0; j<length; j++){
            float area = 0;
            for (int i=0; i<area_days; i++){
                area += (difference[i+j]);
            }
            areabetween_inlast.push_back(area);
        }
    }
    float get_value(int day){
        return value[day];
    }
    float get_average(int day){
        return average[day];
    }
    float get_signal(int day){
        return signal[day];
    }
    float get_difference(int day){
        return difference[day];
    }
    float get_change(int day){
        return change[day];
    }
    float get_2change(int day){
        return second_change[day];
    }
    float get_areavalsig(int day){
        return area_between_valsig[day];
    }
    float get_areainlast(int day){
        return areabetween_inlast[day];
    }
    
    void output(quotes current, int length){
        for (int i=0; i<length; i++){
            cout << fixed << setprecision(2);
            cout << current.get_date(i) << "  ";
            cout << current.get_time(i) << endl;
            cout << name << input_days << ": " << value[i] << endl;
            cout << "Change" << change_increments1 << ": " << change[i] << endl;
            cout << "Second Change" << change_increments1 << ": " << second_change[i] << endl;
            cout << "Signal" << signal_days1 << ": " << signal[i] << endl;
            cout << "Difference: " << difference[i] << endl;
            cout << "Current Area between Value and Signal: " << area_between_valsig[i] << endl;
            cout << "Area between Value and Signal in L" << area_days1 << ": " << areabetween_inlast[i] << endl;
            cout << endl << endl;
        }
        cout << endl;
    }
    
    ~indicator() {
        name.clear();
        input_days = 0;
        signal_days1 = 0;
        area_days1 = 0;
        range_days1 = 0;
        change_increments1 = 0;
        value.clear();
        while(!total_sum.empty()){
            total_sum.pop();
        }
        average.clear();
        signal.clear();
        difference.clear();
        change.clear();
        second_change.clear();
        area_between_valsig.clear();
    }
};



vector<float> EmA(quotes current, int days, int weighting){
    vector<float> eMA;
    stack<float> total_sum;
    int length = current.lengthr;
    for (int j=0; j < length; j++){
        for(int i=0; i<days; i++){
            if (i==0){
                total_sum.push(current.get_close(j));
            }
            else {
                total_sum.push(total_sum.top() + current.get_close(i+j));
            }
        }
        eMA.push_back(current.get_close(j)*(weighting/100.0) + (total_sum.top()/total_sum.size())*(1.0 - (weighting/100.0)));
        while(!total_sum.empty()){
            total_sum.pop();
        }
    }
    return eMA;
}

vector<float> MACD(quotes current, int days1, int days2, int weighting){
    vector<float> macd;
    int length = current.lengthr;
    vector<float> macdema1 = EmA(current, days1, weighting);
    vector<float> macdema2 = EmA(current, days2, weighting);
    for (int i=0; i<length; i++){
        macd.push_back(macdema1[i] - macdema2[i]);
    }
    return macd;
}


vector<float> ROC(quotes current, int days){
    vector<float> RoC;
    int length = current.lengthr;
    for (int i = 0; i<length; i++){
        RoC.push_back(100*(current.get_close(i) - current.get_close(i+days))/current.get_close(i+days));
    }
    return RoC;
}

class rsi_components{
private:
    stack<float> total_gain_sum;
    stack<float> total_loss_sum;
    vector<float> average_gains;
    vector<float> average_losses;
public:
    rsi_components(quotes current, int days){
        int length = current.lengthr;
        for (int j=0; j<length; j++){
            for (int i=0; i<days; i++){
                if (i==0){
                    if (current.get_change(i+j) > 0){
                        total_gain_sum.push(current.get_change(i+j));
                        total_loss_sum.push(0.00);
                        // cout << CHANGE(i+day, 1) << " " << RsI_components.total_gain_sum[i] << " " << RsI_components.total_loss_sum[i] << endl;
                    }
                    else {
                        total_loss_sum.push(current.get_change(i+j));
                        total_gain_sum.push(0.00);
                        // cout << CHANGE(i+day, 1) << " " << RsI_components.total_gain_sum[i] << " " << RsI_components.total_loss_sum[i] << endl;
                    }
                        
                }
                else {
                    if (current.get_change(i+j) > 0){
                        total_gain_sum.push(total_gain_sum.top() + current.get_change(i+j));
                        total_loss_sum.push(total_loss_sum.top());
                        // cout << CHANGE(i+day, 1) << " " << RsI_components.total_gain_sum[i] << " " << RsI_components.total_loss_sum[i] << endl;
                    }
                    else {
                        total_loss_sum.push(total_loss_sum.top() + current.get_change(i+j));
                        total_gain_sum.push(total_gain_sum.top());
                        // cout << CHANGE(i+day, 1) << " " << RsI_components.total_gain_sum[i] << " " << RsI_components.total_loss_sum[i] << endl;
                    }
                }
            }
            average_gains.push_back(total_gain_sum.top()/total_gain_sum.size());
            average_losses.push_back(total_loss_sum.top()/total_loss_sum.size());
            while(!total_gain_sum.empty()){
                total_gain_sum.pop();
            }
            while(!total_loss_sum.empty()){
                total_loss_sum.pop();
            }
        }
    }
    float get_average_gains(int day){
        return average_gains[day];
    }
    float get_average_losses(int day){
        return average_losses[day];
    }
};


vector<float> RSI(quotes current, int days, rsi_components a){
    vector<float> rsi;
    float avggains13;
    float avglosses13;
    int days_since_gain;
    int days_since_loss;
    float gain;
    float loss;
    int length = current.lengthr;
    for (int i=0; i<length; i++){
        avggains13 = 13*abs(a.get_average_gains(i));
        avglosses13 = 13*abs(a.get_average_losses(i));
        days_since_gain = current.get_days_since_gain(i);
        days_since_loss = current.get_days_since_loss(i);
        gain = current.get_change(i+days_since_gain);
        loss = current.get_change(i+days_since_loss);
        rsi.push_back(100.0 - (100.0/(1.0+((gain+avggains13)/(loss+avglosses13)))));
    }
    return rsi;
}

vector<float> area_since_conversion(quotes current, vector<float> a, vector<float> b){
    vector<float> areabetween2;
    int length = current.lengthr;
    vector<float> difference;
    for(int i=0; i<length; i++){
        difference.push_back(a[i]-b[i]);
    }
    for(int i=0; i<length; i++){
        float area = 0;
        int c = 0;
        do {
            area += difference[c+i];
            c++;
        } while (!(difference[c+i-1]/difference[c+i] < 0));
        areabetween2.push_back(area);
    }
    return areabetween2;
}

vector<float> area_in_last(quotes current, vector<float> a, vector<float> b, int input_length){
    vector<float> areabetween2;
    int total_length = current.lengthr;
    float area;
    for (int j=0; j<total_length; j++){
        area = 0;
        for (int i=0; i<input_length; i++){
            area += (a[j+i] - b[j+i]);
        }
        areabetween2.push_back(area);
    }
    return areabetween2;
}

class bollinger_bands{
private:
    stack<float> total_sum;
    vector<float> average;
    vector<float> middle_band;
    vector<float> variance;
    vector<float> standard_deviation;
    vector<float> upper_band;
    vector<float> lower_band;
public:
    bollinger_bands(quotes current, int days){
        int length = current.lengthr;
        for (int i=0; i<length; i++){
            for(int u=0; u<days; u++){
                if (u==0){
                    total_sum.push(current.get_close(i));
                }
                else {
                    total_sum.push(total_sum.top()+current.get_close(i+u));
                }
            }
            middle_band.push_back(total_sum.top()/total_sum.size());
            while (!total_sum.empty()){
                total_sum.pop();
            }
        }
        for (int i=0; i<length; i++){
            for (int u = 0; u < days; u++){
                if (u==0){
                    total_sum.push(pow((current.get_close(i) - middle_band[i]), 2));
                }
                else{
                    total_sum.push(total_sum.top()+pow((current.get_close(i+u) - middle_band[i]), 2));
                }
            }
            variance.push_back(total_sum.top()/(days - 1));
            standard_deviation.push_back(sqrt(variance[i]));
            while(!total_sum.empty()){
                total_sum.pop();
            }
        }
        for(int i=0; i<length; i++){
            upper_band.push_back(middle_band[i] + 2*standard_deviation[i]);
            lower_band.push_back(middle_band[i] - 2*standard_deviation[i]);
        }
    }
    vector<float> get_upper_prox(quotes current){
        vector<float> upper_prox;
        int length = current.lengthr;
        for (int i=0; i<length; i++){
            upper_prox.push_back((current.get_close(i) - upper_band[i]));
        }
        return upper_prox;
    }
    vector<float> get_lower_prox(quotes current){
        vector<float> lower_prox;
        int length = current.lengthr;
        for (int i=0; i<length; i++){
            lower_prox.push_back((current.get_close(i) - lower_band[i]));
        }
        return lower_prox;
    }
    vector<float>& upperband = upper_band;
    vector<float>& lowerband = lower_band;
    ~bollinger_bands(){
        while(!total_sum.empty()){
            total_sum.pop();
        }
        average.clear();
        middle_band.clear();
        variance.clear();
        standard_deviation.clear();
        upper_band.clear();
        lower_band.clear();
    }
};

vector<float> closest_bollband(quotes current, bollinger_bands a){
    vector<float> upbands = a.upperband;
    vector<float> lowbands = a.lowerband;
    vector<float> upbandsp = a.get_upper_prox(current);
    vector<float> lowbandsp = a.get_lower_prox(current);
    vector<float> closest_band;
    int length = current.lengthr;
    for (int c=0; c<length; c++){
        if (upbandsp[c] < lowbandsp[c]){
            closest_band.push_back(upbands[c]);
        }
        else{
            closest_band.push_back(lowbands[c]);
        }
    }
    return closest_band;
}

vector<float> proximityto_closest_bollband(quotes current, bollinger_bands a){
    vector<float> upbandsp = a.get_upper_prox(current);
    vector<float> lowbandsp = a.get_lower_prox(current);
    vector<float> proxtolvl;
    int length = current.lengthr;
    for (int i=0; i<length; i++){
        if (abs(upbandsp[i]) < abs(lowbandsp[i])){
            proxtolvl.push_back(abs(upbandsp[i]));
        }
        else{
            proxtolvl.push_back(abs(lowbandsp[i]));
        }
    }
    return proxtolvl;
}

class fibonacci_levels{
private:
    vector<float> zero_percent;
    vector<float> twenty3point6_percent;
    vector<float> thirty8point2_percent;
    vector<float> fifty_percent;
    vector<float> sixty1point8_percent;
    vector<float> seventy8point6_percent;
    vector<float> onehundred_percent;
public:
    fibonacci_levels(quotes one, int interval){
        int multiplier = 0;
        int length = one.lengthr;
        if (one.interval3 == "1min"){
            multiplier = 960;
        }
        else if (one.interval3 == "5min"){
            multiplier = 192;
        }
        else if (one.interval3 == "30min"){
            multiplier = 32;
        }
        else if (one.interval3 == "1hour"){
            multiplier = 16;
        }
        for (int i = 0; i<length; i++){
            onehundred_percent.push_back(one.get_high_of_last(i, interval, multiplier));
            zero_percent.push_back(one.get_low_of_last(i, interval, multiplier));
            float range = onehundred_percent[i] - zero_percent[i];
            twenty3point6_percent.push_back(zero_percent[i] + range*0.236);
            thirty8point2_percent.push_back(zero_percent[i] + range*0.382);
            fifty_percent.push_back(zero_percent[i] + range*0.500);
            sixty1point8_percent.push_back(zero_percent[i] + range*0.618);
            seventy8point6_percent.push_back(zero_percent[i] + range*0.786);
        }
    }
    float lvl1(int c){
        return zero_percent[c];
    }
    float lvl2(int c){
        return twenty3point6_percent[c];
    }
    float lvl3(int c){
        return thirty8point2_percent[c];
    }
    float lvl4(int c){
        return fifty_percent[c];
    }
    float lvl5(int c){
        return sixty1point8_percent[c];
    }
    float lvl6(int c){
        return seventy8point6_percent[c];
    }
    float lvl7(int c){
        return onehundred_percent[c];
    }
    vector<float> fiblvl1(){
        vector<float> zero;
        for (float i : zero_percent){
            zero.push_back(i);
        }
        return zero;
    }
    vector<float> fiblvl2(){
        vector<float> zero;
        for (float i : twenty3point6_percent){
            zero.push_back(i);
        }
        return zero;
    }
    vector<float> fiblvl3(){
        vector<float> zero;
        for (float i : thirty8point2_percent){
            zero.push_back(i);
        }
        return zero;
    }
    vector<float> fiblvl4(){
        vector<float> zero;
        for (float i : fifty_percent){
            zero.push_back(i);
        }
        return zero;
    }
    vector<float> fiblvl5(){
        vector<float> zero;
        for (float i : sixty1point8_percent){
            zero.push_back(i);
        }
        return zero;
    }
    vector<float> fiblvl6(){
        vector<float> zero;
        for (float i : seventy8point6_percent){
            zero.push_back(i);
        }
        return zero;
    }
    vector<float> fiblvl7(){
        vector<float> zero;
        for (float i : onehundred_percent){
            zero.push_back(i);
        }
        return zero;
    }
    void output(quotes one, int length){
        cout << "Date" << "      " << "Time" << "   " << "0%" << "      " << "23.6%" << "   " << "38.2%" << "   " << "50%";
        cout << "     " << "61.8%" << "   " << "78.6%" << "   " << "100%" << endl;
        for (int i=0; i<length; i++){
            cout << one.get_date(i) << " " << one.get_time(i) << "  " << zero_percent[i] << "  " << twenty3point6_percent[i] << "  ";
            cout << thirty8point2_percent[i] << "  " << fifty_percent[i] << "  " << sixty1point8_percent[i] << "  ";
            cout << seventy8point6_percent[i] << "  " << onehundred_percent[i] << endl;
        }
        cout << endl;
    }
    ~fibonacci_levels(){
        zero_percent.clear();
        twenty3point6_percent.clear();
        thirty8point2_percent.clear();
        fifty_percent.clear();
        sixty1point8_percent.clear();
        seventy8point6_percent.clear();
        onehundred_percent.clear();
    }
};

vector<float> closest_fiblvl(quotes a, fibonacci_levels b){
    vector<float> v;
    int length = a.lengthr;
    for (int i=0; i<length; i++){
        map<float, float> levels_diffs;
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl1(i)), b.lvl1(i)));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl2(i)), b.lvl2(i)));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl3(i)), b.lvl3(i)));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl4(i)), b.lvl4(i)));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl5(i)), b.lvl5(i)));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl6(i)), b.lvl6(i)));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl7(i)), b.lvl7(i)));
        v.push_back(levels_diffs.begin()->second);
    }
    return v;
}

vector<float> proximityto_closest_fiblvl(quotes a, fibonacci_levels b){
    vector<float> v;
    int length = a.lengthr;
    for (int i=0; i<length; i++){
        map<float, float> levels_diffs;
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl1(i)), (a.get_close(i) - b.lvl1(i))));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl2(i)), (a.get_close(i) - b.lvl2(i))));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl3(i)), (a.get_close(i) - b.lvl3(i))));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl4(i)), (a.get_close(i) - b.lvl4(i))));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl5(i)), (a.get_close(i) - b.lvl5(i))));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl6(i)), (a.get_close(i) - b.lvl6(i))));
        levels_diffs.insert(pair<float, float>(abs(a.get_close(i) - b.lvl7(i)), (a.get_close(i) - b.lvl7(i))));
        v.push_back(abs(levels_diffs.begin()->second));
    }
    return v;
}

class analysis:indicator{
private:
    string name;
    int input_days;
    string subset;
    vector<float> base;
    vector<float> lows;
    vector<float> fifthp;
    vector<float> Q1s;
    vector<float> medians;
    vector<float> Q3s;
    vector<float> ninetyfifthp;
    vector<float> highs;
    vector<float> IQR;
    vector<float> RANGE;
    void load_base(string user_choice, int total_days){
        subset = user_choice;
            if (user_choice == "Value"){
                for(int c=0; c<total_days; c++){
                    base.push_back(value[c]);
                }
            }
            else if (user_choice == "Average"){
                for(int c=0; c<total_days; c++){
                    base.push_back(average[c]);
                }
            }
            else if (user_choice == "Signal"){
                for(int c=0; c<total_days; c++){
                    base.push_back(signal[c]);
                }
            }
            else if (user_choice == "Difference"){
                for(int c=0; c<total_days; c++){
                    base.push_back(difference[c]);
                }
            }
            else if (user_choice == "Change"){
                for(int c=0; c<total_days; c++){
                    base.push_back(change[c]);
                }
            }
            else if (user_choice == "2Change"){
                for(int c=0; c<total_days; c++){
                    base.push_back(second_change[c]);
                }
            }
            else if (user_choice == "Signal Change"){
                for(int c=0; c<total_days; c++){
                    base.push_back(signal_change[c]);
                }
            }
            else if (user_choice == "Signal 2Change"){
                for(int c=0; c<total_days; c++){
                    base.push_back(signal_second_change[c]);
                }
            }
            else if (user_choice == "TArea"){
                for(int c=0; c<total_days; c++){
                    base.push_back(area_between_valsig[c]);
                }
            }
            else if (user_choice == "LArea"){
                for(int c=0; c<total_days; c++){
                    base.push_back(areabetween_inlast[c]);
                }
            }
    }

public:
    analysis(string name1, int input_days1, vector<float> a, int signal_days, int signal_weighting, int area_days, int change_increments, int length1)
    : indicator(name1, input_days1, a, signal_days, area_days, signal_weighting, change_increments, length1), name(name1), input_days(input_days1) {};
    
    string get_name(){
        return name;
    }
    
    string get_subset(){
        return subset;
    }
    
    int get_days(){
        return input_days;
    }
    
    void indicator_output(quotes current, int length){
        output(current, length);
    }
    
    void load_percentiles(string user_choice, float percentile, int trailing_days, int total_days){
        load_base(user_choice, total_days);
        // deque<float> values_now;
        /* for (int c=0; c<trailing_days; c++){
            values_now.push_back(base[c]);
        } */
        for(int i=0; i<total_days; i++){
            vector<float> values_now;
            for (int c=0; c<trailing_days; c++){
                values_now.push_back(base[i+c]);
            }
            sort(values_now.begin(), values_now.end(), greater<float>());
            // is there a faster way to do this?
            int i0 = trailing_days-1;
            int i1 = ((3*trailing_days)/4);
            int i2 = (trailing_days/2);
            int i3 = (trailing_days/4);
            int i4 = (trailing_days*percentile);
            int i5 = (trailing_days*(1.0-percentile));
            float low = values_now[i0];
            float fivep = values_now[i5];
            float q1 = values_now[i1];
            float median = values_now[i2];
            float q3 = values_now[i3];
            float ninetyfivep = values_now[i4];
            float high = values_now[0];
            float iqr = q3-q1;
            float range = high-low;
            highs.push_back(high);
            lows.push_back(low);
            fifthp.push_back(fivep);
            Q1s.push_back(q1);
            Q3s.push_back(q3);
            medians.push_back(median);
            ninetyfifthp.push_back(ninetyfivep);
            IQR.push_back(iqr);
            RANGE.push_back(range);
            // values_now.pop_front();
            // values_now.push_back(base[i+trailing_days]);
            do{
                values_now.pop_back();
            } while (!values_now.empty());
        }
    }
    
    bool upper_percentile_range(int i){
        float value = base[i];
        float upperrestriction = ninetyfifthp[i];
        if(value >= upperrestriction){
            return true;
        }
        else{
            return false;
        }
    }
    
    float get_ninetyfifthp(int i){
        return ninetyfifthp[i];
    }
    
    bool lower_percentile_range(int i){
        float value = base[i];
        float lowerrestriction = fifthp[i];
        if(value <= lowerrestriction){
            return true;
        }
        else{
            return false;
        }
    }
    
    float get_fifthp(int i){
        return fifthp[i];
    }
    
    vector<float> base_public(){
        return base;
    }
    
    int get_input_days(){
        return input_days;
    }
    
    void clear(){
        base.clear();
        lows.clear();
        fifthp.clear();
        Q1s.clear();
        medians.clear();
        Q3s.clear();
        ninetyfifthp.clear();
        highs.clear();
        RANGE.clear();
        IQR.clear();
    }
    
    ~analysis(){
        base.clear();
        lows.clear();
        fifthp.clear();
        Q1s.clear();
        medians.clear();
        Q3s.clear();
        ninetyfifthp.clear();
        highs.clear();
        RANGE.clear();
        IQR.clear();
    }
};
