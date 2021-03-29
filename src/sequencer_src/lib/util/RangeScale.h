#ifndef RangeScale_h
#define RangeScale_h

class RangeScale {
    public:
        RangeScale(int fromMin, int fromMax, int toMin, int toMax) {
            this->fromMin = fromMin;
            this->fromMax = fromMax;
            this->toMin = toMin;
            this->toMax = toMax;
            fromRange = fromMax - fromMin;
            toRange = toMax - toMin;
            fromRangeRecip = 1 / fromRange;
        }

        int convert(int fromValue) {
            return (((fromValue - fromMin) * toRange) / fromRange) + toMin;
        }

    private:
        int fromMin, fromMax, toMin, toMax;
        int fromRange, toRange, fromRangeRecip;

};

#endif